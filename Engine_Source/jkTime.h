#pragma once
#include "JKEngine.h"

#include "jkGameObject.h"

namespace jk
{
	class Time
	{
	public:
		static void Initiailize();
		static void Update();
		static void Render();

		__forceinline static double DeltaTime() { return mDeltaTime; }	



		//std::wstring stringToWstring(const std::string& s)
		//{
		//	int len;
		//	int slength = (int)s.length() + 1;
		//	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
		//	wchar_t* buf = new wchar_t[len];
		//	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
		//	std::wstring r(buf);
		//	delete[] buf;
		//	return r;
		//}
		//std::string Path;

	private:
		static double mDeltaTime;
		static double mSecond;
		static LARGE_INTEGER mCpuFrequency;
		static LARGE_INTEGER mPrevFrequency;
		static LARGE_INTEGER mCurFrequency;
		GameObject* mCamera;


	};
}
