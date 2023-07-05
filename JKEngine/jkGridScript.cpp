#include "jkGridScript.h"
#include "jkRenderer.h"
#include "jkGameObject.h"
#include "jkTransform.h"
#include "jkApplication.h"
#include "jkConstantBuffer.h"
#include "jkInput.h"
#include "jkTime.h"
#include "jkSceneManager.h"
#include "jkScene.h"

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
	
		
		//Scene* scene = SceneManager::GetActiveScene();
		//eSceneType type = SceneManager::GetActiveScene()->GetSceneType();
		//mCamera = renderer::cameras[(UINT)type][0];
	}

	void GridScript::Update()
	{
		//if (mCamera == nullptr)
		//	return;

		//float scale = mCamera->GetScale();

		//if (Input::GetKeyState(eKeyCode::T) == eKeyState::Pressed)
		//{
		//	float adjustVal = 1.f * Time::DeltaTime();
		//	float newCameraScale = 0.f;

		//	if (mMeshScale + adjustVal > 2.9f)
		//	{
		//		mMeshScale = 2.9f;
		//		newCameraScale = 0.1f;
		//	}
		//	else
		//	{
		//		mMeshScale += adjustVal;
		//		newCameraScale = scale - adjustVal;
		//	}

		//	mCamera->SetScale(newCameraScale);
		//}
		//if (Input::GetKeyState(eKeyCode::G) == eKeyState::Pressed)
		//{
		//	float adjustVal = 1.f * Time::DeltaTime();
		//	float newCameraScale = 0.f;

		//	if (mMeshScale - adjustVal < 0.1f)
		//	{
		//		mMeshScale = 0.1f;
		//		newCameraScale = 2.9f;
		//	}
		//	else
		//	{
		//		mMeshScale -= adjustVal;
		//		newCameraScale = scale + adjustVal;
		//	}

		//	mCamera->SetScale(newCameraScale);
		//}
	}

	void GridScript::FixedUpdate()
	{


		GameObject* gameObj = mCamera->GetOwner();
		Transform* tr = gameObj->GetComponent<Transform>();

		Vector3 cameraPos = tr->GetPosition();
		Vector4 position = Vector4(cameraPos.x, cameraPos.y, cameraPos.z, 1.f);

		float scale = mCamera->GetScale();

		RECT winRect;
		GetClientRect(application.GetHwnd(), &winRect);
		float width = static_cast<float>(winRect.right - winRect.left);
		float height = static_cast<float>(winRect.bottom - winRect.top);
		Vector2 resolution(width, height);


		// Constant Buffer
		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Grid];
		renderer::GridCB data;
		data.cameraPosition = position;
		data.cameraScale = Vector2(scale, scale);
		data.resolution = resolution;
		data.meshScale = mMeshScale;

		cb->SetData(&data);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);


		//if (mCamera == nullptr)
		//	return;

		//GameObject* gameObj = mCamera->GetOwner();
		//Transform* tr = gameObj->GetComponent<Transform>();

		//Vector3 cameraPos = tr->GetPosition();
		//Vector4 position = Vector4(cameraPos.x, cameraPos.y, cameraPos.z, 1.f);

		//float scale = mCamera->GetScale();

		//RECT winRect;
		//GetClientRect(application.GetHwnd(), &winRect);
		//float width = static_cast<float>(winRect.right - winRect.left);
		//float height = static_cast<float>(winRect.bottom - winRect.top);
		//Vector2 resolution(width, height);

		//// Constant Buffer
		//ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Grid];
		//renderer::GridCB data;
		//data.cameraPosition = position;
		//data.cameraScale = Vector2(scale, scale);
		//data.resolution = resolution;
		//data.meshScale = mMeshScale;

		//cb->SetData(&data);
		//cb->Bind(eShaderStage::VS);
		//cb->Bind(eShaderStage::PS);
	}

	void GridScript::Render()
	{
	}
}