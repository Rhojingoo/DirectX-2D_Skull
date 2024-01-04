#pragma once
#include "jkScript.h"

namespace jk
{
	class CameraScript : public Script
	{
	public:
		virtual void Update() override;

		static void SetTarget(GameObject* target) { mTarget = target; }
		static void Clear();
		bool SetCamera = false;
	
	private:
		static Vector2 mResolution;
		static Vector2 mLookPosition;
		static Vector2 mDistance;
		static GameObject* mTarget;	
		static int camera;

		static Vector2 mMove;
		static Vector2 target_pos;
	};
}
