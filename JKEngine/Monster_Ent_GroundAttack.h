#pragma once
#include "Monster_Bullet.h"

namespace jk
{
	class Monster_Ent_GroundAttack : public Monster_Bullet
	{
	public:
		Monster_Ent_GroundAttack();
		virtual ~Monster_Ent_GroundAttack();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void complete();
		bool _bullet_Life = false;

	private:
		class Animator* at = nullptr;
		class RigidBody* _rigidbody = nullptr;
		class Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		float _attackatime = 0.f;
		int _dir = 1;

	};
}