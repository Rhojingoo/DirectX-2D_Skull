#include "jkTime.h"
#include "jkInput.h"
#include "jkApplication.h"
#include "jkCamera.h"
#include "jkUI_Mouse.h"

extern jk::Application application;

namespace jk
{
	double Time::mDeltaTime = 0.0l;
	double Time::mSecond = 0.0f;
	LARGE_INTEGER Time::mCpuFrequency = {};
	LARGE_INTEGER Time::mPrevFrequency = {};
	LARGE_INTEGER Time::mCurFrequency = {};

	void Time::Initiailize()
	{
		// CPU 고유 진동수 가져오기
		QueryPerformanceFrequency(&mCpuFrequency);

		// 프로그램이 처음 시작할때 진동수
		QueryPerformanceCounter(&mPrevFrequency);
	}

	void Time::Update()
	{
		QueryPerformanceCounter(&mCurFrequency);

		double differnceFrequency = (double)mCurFrequency.QuadPart - (double)mPrevFrequency.QuadPart;

		mDeltaTime = differnceFrequency / mCpuFrequency.QuadPart;

		mPrevFrequency.QuadPart = mCurFrequency.QuadPart;
	}

	void Time::Render()
	{
		mSecond += mDeltaTime;

		if (mSecond > 1.0f)
		{
			HWND hWnd = application.GetHwnd();
			Vector2 _MousePos = jk::Input::GetMousePos();
			Vector3 tPos = Camera::GetWorldpos_Camera(Vector3(_MousePos.x, _MousePos.y, 0.0f));
			wchar_t szFloat[50] = {};
			float FPS = 1.0f / (float)mDeltaTime;
			swprintf_s(szFloat, 50, L"FPS : %d Mouse : %d, %d", (UINT)FPS, (UINT)tPos.x, (UINT)tPos.y);
			//int iLen = wcsnlen_s(szFloat, 50);
			SetWindowText(hWnd, szFloat);
			//TextOut(hdc, 0, 0, szFloat, 20);
			mSecond = 0.0f;
		}



		mSecond += mDeltaTime;

		HWND hWnd = application.GetHwnd();
		wchar_t szFloat[100] = {};

		//if (mSecond > 1.0f)
		//{
		//	//wchar_t szFloat[100] = {};
		//	FPS = 1.0f / (float)mDeltaTime;
		//	//swprintf_s(szFloat, 50, L"FPS : %d, Stage : %d, Chapter : %d, Num : %d", (UINT)FPS, index[0], index[1], index[2]);
		//	////int iLen = wcsnlen_s(szFloat, 50);
		//	//SetWindowText(hWnd, szFloat);

		//	//TextOut(hdc, 0, 0, szFloat, 20);
		//	mSecond = 0.0f;
		//}



		//Vector2 MousePos = Input::GetMousePos();
		//Vector3 worldPos = Time::ChangeWorldPos(Vector3(MousePos.x, MousePos.y, 0.0f));

		//swprintf_s(szFloat, 50, L"FPS : %d Mouse : %d, %d", (UINT)FPS, (UINT)MousePos.x, (UINT)MousePos.y);
		////swprintf_s(szFloat, 100, L"FPS : %d,  x : %d, y : %d", (UINT)FPS, index[0], index[1], index[2], (int)worldPos.x, (int)worldPos.y);
		//SetWindowText(hWnd, szFloat);

	}

	//Vector3 Time::ChangeWorldPos(Vector3 pos)
	//{
	//	Camera* camera = mCamera->GetComponent<Camera>();
	//	Vector3 mpos = Vector3(pos.x, pos.y, pos.z);
	//	Matrix projection = camera->GetProjectionMatrix();
	//	Matrix view = camera->GetViewMatrix();
	//	Matrix world = Matrix::Identity;
	//	RECT rt = {};
	//	GetClientRect(application.GetHwnd(), &rt);
	//	Viewport viewport(rt);
	//	Vector3 Current_Pos = viewport.Unproject(mpos, projection, view, world);
	//	return Vector3(Current_Pos.x, Current_Pos.y, Current_Pos.z);
	//}
}
