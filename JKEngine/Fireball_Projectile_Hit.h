#pragma once
#include "Include_Common.h"

namespace jk
{
	class Fireball_Projectile_Hit : public Effect
	{
	public:
		Fireball_Projectile_Hit();
		virtual ~Fireball_Projectile_Hit();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void Compelete();

		bool _effect_On = true;
		bool _effect_check = true;

	private:
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
	};
}