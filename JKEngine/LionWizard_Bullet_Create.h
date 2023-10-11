#pragma once
#include "Include_Common.h"

namespace jk
{
	class LionWizard_Bullet_Create : public Effect
	{
	public:
		LionWizard_Bullet_Create();
		virtual ~LionWizard_Bullet_Create();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;


		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void SetDirection(int set) { _dir = set; }
		void Compelete();

		bool _effect_On = false;
		bool _endanimation = false;

	private:
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		float _attackatime = 0.f;
		int _dir = 1;
	};
}