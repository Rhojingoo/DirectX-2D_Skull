#pragma once
#include "Bullet.h"


namespace jk
{
	class Knight_UltimateSkill_Projectile : public Bullet
	{
	public:
		Knight_UltimateSkill_Projectile();
		virtual ~Knight_UltimateSkill_Projectile();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void Compelete();

		void SetDirection(int set) { _dir = set; }
		bool _effect_switch = false;
		bool _effect_animation = false;

	private:
		class Animator* at = nullptr;
		class RigidBody* _rigidbody = nullptr;
		class Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		float _attackatime = 0.f;
		int _dir = 1;
	};
}