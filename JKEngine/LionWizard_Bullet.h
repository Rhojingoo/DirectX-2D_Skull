#pragma once
#include "Include_Common.h"

namespace jk
{
	class LionWizard_Bullet : public Monster_Bullet
	{
	public:
		LionWizard_Bullet();
		virtual ~LionWizard_Bullet();

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
		bool _animationswitch = false;

	private:
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		float _attackatime = 0.f;
		int _dir = 1;
	};
}