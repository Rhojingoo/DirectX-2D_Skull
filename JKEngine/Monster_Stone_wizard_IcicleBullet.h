#pragma once
#include "Monster_Bullet.h"

namespace jk
{
	class Monster_Stone_wizard_IcicleBullet : public Monster_Bullet
	{
	public:
		Monster_Stone_wizard_IcicleBullet();
		virtual ~Monster_Stone_wizard_IcicleBullet();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void complete();

		void SetDirection(int set) { _dir = set; }
		bool _bullet_animation = false;
		bool _Life = false;

	private:
		class Animator* at = nullptr;
		class RigidBody* _rigidbody = nullptr;
		class Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		float _attackatime = 0.f;
		int _dir = 1;


	};
}