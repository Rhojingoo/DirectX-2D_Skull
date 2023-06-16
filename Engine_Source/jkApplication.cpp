#include "jkApplication.h"
#include "jkInput.h"
#include "jkTime.h"
#include "jkRenderer.h"
#include "jkSceneManager.h"

namespace jk
{
	Application::Application()
		: graphicDevice(nullptr)
		, mHwnd(NULL)
		, mWidth(-1)
		, mHeight(-1)
		, mScene(nullptr)
	{

	}

	Application::~Application()
	{
	}



	void Application::Run()
	{
		Update();
		LateUpdate();
		Render();
	}

	void Application::Initialize()
	{
		Time::Initiailize();
		Input::Initialize();

		renderer::Initialize();
		SceneManager::Initialize();
	}

	void Application::Update()
	{
		Time::Update();
		Input::Update();
		SceneManager::Update();
	}

	void Application::LateUpdate()
	{
		SceneManager::LateUpdate();
	}

	void Application::Render()
	{
		Time::Render();

		graphicDevice->ClearTarget();
		graphicDevice->UpdateViewPort();
		SceneManager::Render();
		//graphicDevice->Draw();

		graphicDevice->Present();


		//static Vector4 pos{};
		//if (Input::GetKey(eKeyCode::RIGHT))
		//{
		//	pos.x += 0.001;
		//}
		//if (Input::GetKey(eKeyCode::LEFT))
		//{
		//	pos.x -= 0.001;
		//}
		//if (Input::GetKey(eKeyCode::UP))
		//{
		//	pos.y += 0.001;
		//}
		//if (Input::GetKey(eKeyCode::DOWN))
		//{
		//	pos.y -= 0.001;
		//}
		//jk::graphics::GetDevice()->SetConstantBuffer(jk::renderer::triangleConstantBuffer, &pos, sizeof(Vector4));
		//jk::graphics::GetDevice()->BindConstantBuffer(eShaderStage::VS, eCBType::Transform, jk::renderer::triangleConstantBuffer);
		//graphicDevice->Draw();		
	}

	void Application::SetWindow(HWND hwnd, UINT width, UINT height)
	{
		if (graphicDevice == nullptr)
		{
			mHwnd = hwnd;
			mWidth = width;
			mHeight = height;

			graphicDevice = std::make_unique<jk::graphics::GraphicDevice_Dx11>();
			jk::graphics::GetDevice() = graphicDevice.get();
		}

		RECT rt = { 0, 0, (LONG)width , (LONG)height };
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(mHwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
		ShowWindow(mHwnd, true);
		UpdateWindow(mHwnd);
	}
}