#include "jkGridScript.h"
#include "jkConstantBuffer.h"
#include "jkCamera.h"
#include "jkTransform.h"
#include "jkApplication.h"
#include "jkGameObject.h"
#include "jkRenderer.h"

extern jk::Application application;


namespace jk
{
	GridScript::GridScript()
		: mCamera(nullptr)
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
		if (mCamera == nullptr)
			return;

		GameObject* gameObj = mCamera->GetOwner();


		Transform* tr = gameObj->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		float scale = mCamera->GetSize();

		HWND hWnd = application.GetHwnd();
		RECT winRect = {};
		GetClientRect(hWnd, &winRect);

		float width = winRect.right - winRect.left;
		float height = winRect.bottom - winRect.top;
		Vector2 resolution(width, height);

		///cs buffer
		graphics::ConstantBuffer* cb
			= renderer::constantBuffer[(int)eCBType::Grid];

		renderer::GridCB data;
		data.CameraPosition = Vector4(pos.x, pos.y, pos.z, 1.0f);
		data.Resolution = resolution;
		data.CameraScale = Vector2(scale, scale);

		cb->SetData(&data);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);
	}

	void GridScript::LateUpdate()
	{
	}

	void GridScript::Render()
	{
	}
}