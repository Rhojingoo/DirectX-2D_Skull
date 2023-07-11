#include "jkGridScript.h"
#include "jkConstantBuffer.h"
#include "jkCamera.h"
#include "jkTransform.h"
#include "jkApplication.h"
#include "jkGameObject.h"
#include "jkRenderer.h"
#include "jkTime.h"
#include "jkInput.h"
#include "jkObject.h"

extern jk::Application application;


namespace jk
{
	GridScript::GridScript()
		: Script()
		, mCamera(nullptr)
		, mMeshScale(2.f)
	{
	}
	GridScript::~GridScript()
	{
	}
	void GridScript::Initialize()
	{
	}
	void GridScript::Update()
	{

		//그리드가 없어지게 하능 방법
		//static float chTime = 0.0f;
		//chTime += Time::DeltaTime();
	
		//if (chTime > 3.0f)
		//{
		//	object::Destroy(GetOwner());
		//}	

		if (mCamera == nullptr)
			return;

		float scale = mCamera->GetSize();

		if (Input::GetKeyState(eKeyCode::T) == eKeyState::Pressed)
		{
			float adjustVal = 1.f * Time::DeltaTime();
			float newCameraScale = 0.f;

			if (mMeshScale + adjustVal > 2.9f)
			{
				mMeshScale = 2.9f;
				newCameraScale = 0.1f;
			}
			else
			{
				mMeshScale += adjustVal;
				newCameraScale = scale - adjustVal;
			}

			mCamera->SetSize(newCameraScale);
		}
		if (Input::GetKeyState(eKeyCode::G) == eKeyState::Pressed)
		{
			float adjustVal = 1.f * Time::DeltaTime();
			float newCameraScale = 0.f;

			if (mMeshScale - adjustVal < 0.1f)
			{
				mMeshScale = 0.1f;
				newCameraScale = 2.9f;
			}
			else
			{
				mMeshScale -= adjustVal;
				newCameraScale = scale + adjustVal;
			}

			mCamera->SetSize(newCameraScale);
		}

		//GameObject* gameObj = mCamera->GetOwner();

		//Transform* tr = gameObj->GetComponent<Transform>();
		//Vector3 pos = tr->GetPosition();

		//float scale = mCamera->GetSize();

		//HWND hWnd = application.GetHwnd();
		//RECT winRect = {};
		//GetClientRect(hWnd, &winRect);

		//float width = winRect.right - winRect.left;
		//float height = winRect.bottom - winRect.top;
		//Vector2 resolution(width, height);

		/////cs buffer
		//graphics::ConstantBuffer* cb
		//	= renderer::constantBuffer[(int)eCBType::Grid];

		//renderer::GridCB data;
		//data.CameraPosition = Vector4(pos.x, pos.y, pos.z, 1.0f);
		//data.Resolution = resolution;
		//data.CameraScale = Vector2(scale, scale);

		//cb->SetData(&data);
		//cb->Bind(eShaderStage::VS);
		//cb->Bind(eShaderStage::PS);
	}

	void GridScript::LateUpdate()
	{
		if (mCamera == nullptr)
			return;

		GameObject* gameObj = mCamera->GetOwner();
		Transform* tr = gameObj->GetComponent<Transform>();

		Vector3 cameraPos = tr->GetPosition();
		Vector4 position = Vector4(cameraPos.x, cameraPos.y, cameraPos.z, 1.f);

		float scale = mCamera->GetSize();

		RECT winRect;
		GetClientRect(application.GetHwnd(), &winRect);
		float width = static_cast<float>(winRect.right - winRect.left);
		float height = static_cast<float>(winRect.bottom - winRect.top);
		Vector2 resolution(width, height);

		// Constant Buffer
			graphics::ConstantBuffer* cb
			= renderer::constantBuffer[(int)eCBType::Grid];
		//ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Grid];
		renderer::GridCB data;
		data.cameraPosition = position;
		data.cameraScale = Vector2(scale, scale);
		data.resolution = resolution;
		data.meshScale = mMeshScale;

		cb->SetData(&data);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);
	}

	void GridScript::Render()
	{
	}
}