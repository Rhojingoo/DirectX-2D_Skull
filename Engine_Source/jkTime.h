#pragma once
#include "JKEngine.h"

namespace jk
{
	class Time
	{
	public:
		static void Initiailize();
		static void Update();
		static void Render();

		__forceinline static double DeltaTime() { return mDeltaTime; }
		Vector3 ChangeWorldPos(Vector3 pos);

	private:
		static double mDeltaTime;
		static double mSecond;
		static LARGE_INTEGER mCpuFrequency;
		static LARGE_INTEGER mPrevFrequency;
		static LARGE_INTEGER mCurFrequency;
		GameObject* mCamera;
	};
}
