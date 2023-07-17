#include "jkApplication.h"
#include "jkInput.h"
#include "jkTime.h"
#include "jkRenderer.h"
#include "jkSceneManager.h"
#include "jkCollisionManager.h"

namespace jk
{
	Application::Application()
		: graphicDevice(nullptr)
		, mHwnd(NULL)
		, mToolHwnd(NULL)
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
		Destroy();
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
		CollisionManager::Update();
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

		//SceneManager::Render();
		renderer::Render();
		//graphicDevice->Draw();				
	}

	void Application::Destroy()
	{
		SceneManager::Destroy();
	}

	void Application::Present()
	{
		graphicDevice->Present();
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