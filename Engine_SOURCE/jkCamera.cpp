#include "jkCamera.h"
#include "jkTransform.h"
#include "jkGameObject.h"
#include "jkApplication.h"
#include "jkRenderer.h"
#include "jkScene.h"
#include "jkSceneManager.h"
#include "jkMeshRenderer.h"
#include "jkBaseRenderer.h"
#include "jkInput.h"
#include "jkTime.h"

extern jk::Application application;

namespace jk
{
	GameObject* Camera::mTarget = nullptr;
	GameObject* Camera::mTarget_BG = nullptr;


	bool CompareZSort(GameObject* a, GameObject* b)
	{
		if (a->GetComponent<Transform>()->GetPosition().z
			<= b->GetComponent<Transform>()->GetPosition().z)
			return false;

		return true;
	}

	Matrix Camera::View = Matrix::Identity;
	Matrix Camera::Projection = Matrix::Identity;

	Camera::Camera()
		: Component(eComponentType::Camera)
		, mType(eProjectionType::OrthoGraphic)
		, mAspectRatio(1.0f)
		, mNear(1.0f)
		, mFar(1000.0f)
		, mSize(1.0f)
		, mLayerMask{}
		, mOpaqueGameObjects{}
		, mCutOutGameObjects{}
		, mTransparentGameObjects{}
		, mView(Matrix::Identity)
		, mProjection(Matrix::Identity)
	{
		EnableLayerMasks();
	}

	Camera::~Camera()
	{
	}

	void Camera::Initialize()
	{
	}

	void Camera::Update()
	{

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
	

		if (SetCamera == true)
		{
			Transform* PlayerTR = mTarget->GetComponent<Transform>();
			Vector3 _pos = PlayerTR->GetPosition();			

			if(StayCamera == false)
			{
				if (SetCameraXY == true)
					pos = Vector3(_pos.x, _pos.y + 65, -10);
				if (SetCameraX == true)
					pos.x = _pos.x;
				if (SetCameraY == true)
					pos.y = _pos.y + 65;

				if (_MaxPlayerX < pos.x)
					StayCamera = true;
				if (_MinPlayerX > pos.x)
					StayCamera = true;
				if (_MaxPlayerY < pos.y)
					StayCamera = true;
				if (_MinPlayerY > pos.y)
					StayCamera = true;


				if ((_MaxBgX >= pos.x)&& (_MinBgX <= pos.x))
					BgCamera = true;
				
				tr->SetPosition(pos);
			}
			else
			{
				if (SetCameraX == true)
				{
					if ((_MaxPlayerX >= _pos.x) && (_MinPlayerX <= _pos.x))
						StayCamera = false;
				}
				if (SetCameraY == true)
				{
					if ((_MaxPlayerY >= _pos.x) && (_MinPlayerY <= _pos.x))
						StayCamera = false;
				}
			}
			if (BgCamera == true)
			{
				if (_MaxBgX < pos.x)
					BgCamera = false;
				if (_MinBgX > pos.x)
					BgCamera = false;


				Transform* BGTR = mTarget_BG->GetComponent<Transform>();
				Vector3 posBG = BGTR->GetPosition();
				Vector3 CurrentposBG = Vector3(0.f,0.f, posBG.z);

				if (Input::GetKey(eKeyCode::RIGHT))
					posBG.x += 65 * Time::DeltaTime();
				if(Input::GetKey(eKeyCode::LEFT))
					posBG.x -= 65 * Time::DeltaTime();
				
				BGTR->SetPosition(posBG);
			}
		}		
		else
		{
			if (Input::GetKey(eKeyCode::E))
			{
				pos.x += 100.0f * (float)Time::DeltaTime();
				tr->SetPosition(pos);
			}
			else if (Input::GetKey(eKeyCode::Q))
			{
				pos.x -= 100.0f * (float)Time::DeltaTime();
				tr->SetPosition(pos);
			}
		}		
	}

	void Camera::LateUpdate()
	{
		CreateViewMatrix();
		CreateProjectionMatrix(mType);
		RegisterCameraInRenderer();
	}

	void Camera::Render()
	{	
		View = mView;
		Projection = mProjection;

		AlphaSortGameObjects();
		ZSortTransparencyGameObjects();
		RenderOpaque();

		DisableDepthStencilState();
		RenderCutOut();
		RenderTransparent();
		EnableDepthStencilState();
	}

	bool Camera::CreateViewMatrix()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		// View Translate Matrix
		mView = Matrix::Identity;
		mView *= Matrix::CreateTranslation(-pos);

		// View Rotation Matrix
		Vector3 up = tr->Up();
		Vector3 right = tr->Right();
		Vector3 foward = tr->Foward();

		Matrix viewRotate;
		viewRotate._11 = right.x;	viewRotate._12 = up.x;	viewRotate._13 = foward.x;
		viewRotate._21 = right.y;	viewRotate._22 = up.y;	viewRotate._23 = foward.y;
		viewRotate._31 = right.z;	viewRotate._32 = up.z;	viewRotate._33 = foward.z;
		mView *= viewRotate;

		return true;
	}

	bool Camera::CreateProjectionMatrix(eProjectionType type)
	{
		RECT rect = {};
		GetClientRect(application.GetHwnd(), &rect);
		float width = (float)rect.right - (float)rect.left;
		float height = (float)rect.bottom - (float)rect.top;
		mAspectRatio = width / height;;

		if (mType == eProjectionType::OrthoGraphic)
		{
			float OrthorGraphicRatio = mSize;
			if (SetCamera == true)
				OrthorGraphicRatio = mSize / 2.5;			
			else
			 OrthorGraphicRatio = mSize;
			
			width *= OrthorGraphicRatio;
			height *= OrthorGraphicRatio;

			mProjection = Matrix::CreateOrthographicLH(width, height, mNear, mFar);
		}

		else
		{
			mProjection = Matrix::CreatePerspectiveFieldOfViewLH(XM_2PI / 6.0f, mAspectRatio, mNear, mFar);
		}

		return true;
	}

	void Camera::RegisterCameraInRenderer()
	{
		renderer::cameras.push_back(this);
	}

	void Camera::TurnLayerMask(eLayerType type, bool enable)
	{
		mLayerMask.set((UINT)type, enable);
	}

	void Camera::AlphaSortGameObjects()
	{
		mOpaqueGameObjects.clear();
		mCutOutGameObjects.clear();
		mTransparentGameObjects.clear();

		//alpha sorting
		Scene* scene = SceneManager::GetActiveScene();
		for (size_t i = 0; i < (UINT)eLayerType::End; i++)
		{
			if (mLayerMask[i] == true)
			{
				Layer& layer = scene->GetLayer((eLayerType)i);
				const std::vector<GameObject*> gameObjs
					= layer.GetGameObjects();
				// layer에 있는 게임오브젝트를 들고온다.

				DivideAlphaBlendGameObjects(gameObjs);
			}
		}
	}

	void Camera::ZSortTransparencyGameObjects()
	{
		std::sort(mCutOutGameObjects.begin()
			, mCutOutGameObjects.end()
			, CompareZSort);
		std::sort(mTransparentGameObjects.begin()
			, mTransparentGameObjects.end()
			, CompareZSort);
	}

	void Camera::DivideAlphaBlendGameObjects(const std::vector<GameObject*> gameObjs)
	{
		for (GameObject* obj : gameObjs)
		{
			//렌더러 컴포넌트가 없다면?
			BaseRenderer* mr
				= obj->GetComponent<BaseRenderer>();
			if (mr == nullptr)
				continue;
			
			////선생님코드
			//MeshRenderer* mr
			//	= obj->GetComponent<MeshRenderer>();
			//if (mr == nullptr)
			//	continue;
			
			std::shared_ptr<Material> mt = mr->GetMaterial();
			eRenderingMode mode = mt->GetRenderingMode();
			switch (mode)
			{
			case jk::graphics::eRenderingMode::Opaque:
				mOpaqueGameObjects.push_back(obj);
				break;
			case jk::graphics::eRenderingMode::CutOut:
				mCutOutGameObjects.push_back(obj);
				break;
			case jk::graphics::eRenderingMode::Transparent:
				mTransparentGameObjects.push_back(obj);
				break;
			default:
				break;
			}
		}
	}

	void Camera::RenderOpaque()
	{
		for (GameObject* gameObj : mOpaqueGameObjects)
		{
			if (gameObj == nullptr)
				continue;

			if (gameObj->GetState()
				!= GameObject::eState::Active)
				continue;

			gameObj->Render();
		}
	}

	void Camera::RenderCutOut()
	{
		for (GameObject* gameObj : mCutOutGameObjects)
		{
			if (gameObj == nullptr)
				continue;

			if (gameObj->GetState()
				!= GameObject::eState::Active)
				continue;

			gameObj->Render();
		}
	}

	void Camera::RenderTransparent()
	{
		for (GameObject* gameObj : mTransparentGameObjects)
		{
			if (gameObj == nullptr)
				continue;

			if (gameObj->GetState()
				!= GameObject::eState::Active)
				continue;

			gameObj->Render();
		}
	}

	void Camera::EnableDepthStencilState()
	{
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> dsState
			= renderer::depthStencilStates[(UINT)eDSType::Less];
		GetDevice()->BindDepthStencilState(dsState.Get());
	}

	void Camera::DisableDepthStencilState()
	{
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> dsState
			= renderer::depthStencilStates[(UINT)eDSType::None];
		GetDevice()->BindDepthStencilState(dsState.Get());
	}

	Vector3 Camera::GetWorldTransform(Vector3 pos)
	{
		Vector3 mpos = Vector3(pos.x, pos.y, pos.z);
		Matrix world = Matrix::Identity;
		RECT rt = {};
		GetClientRect(application.GetHwnd(), &rt);

		Viewport viewport(rt);
		Vector3 translatePos = viewport.Unproject(mpos, mProjection, mView, world);

		return Vector3(translatePos.x, translatePos.y, translatePos.z);
	}

	Vector3 Camera::GetWorldpos_Camera(Vector3 pos)
	{
		RECT rt = {};
		GetClientRect(application.GetHwnd(), &rt);

		Viewport viewport(rt);
		Vector3 translatePos = viewport.Unproject(pos, Projection, View, Matrix::Identity);

		return Vector3(translatePos);	
	}
}
