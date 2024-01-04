#pragma once
#include "Effect.h"

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
		void SetDirection(int set) { _dir = set; }

		bool _effect_On = true;
		bool _effect_check = true;
		int _dir = 1;

	private:
		class Animator* at = nullptr;
		class RigidBody* _rigidbody = nullptr;
		class Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
	};
}