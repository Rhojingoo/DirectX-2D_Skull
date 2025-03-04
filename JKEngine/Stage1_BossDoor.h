#pragma once
#include "Door.h"

namespace jk
{
	class Stage1_BossDoor : public Door
	{
	public:
		Stage1_BossDoor();
		virtual ~Stage1_BossDoor();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

	private:
		class Animator* at = nullptr;
		class Collider2D* _collider = nullptr;
		class Alpha_Blend* _Alpha = nullptr;
		Transform* tr = nullptr;
		float _time = 0.f;
		bool _Fadecheck = false;	
	};
}