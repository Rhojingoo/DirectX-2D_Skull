#pragma once
#include "Include_Common.h"

namespace jk
{
	class CameraScript : public Script
	{
	public:
		virtual void Update() override;

		//virtual void OnCollisionEnter(Collider2D* other) override;
		//virtual void OnCollisionStay(Collider2D* other) override;
		//virtual void OnCollisionExit(Collider2D* other) override;
		static void SetTarget(GameObject* target) { mTarget = target; }
		static void Clear();
	
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
