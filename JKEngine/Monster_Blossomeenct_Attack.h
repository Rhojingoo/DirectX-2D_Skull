#pragma once
#include "Include_Common.h"
#include "Bullet.h"

namespace jk
{
	class Monster_Blossomeenct_Attack : public Bullet
	{
	public:
		Monster_Blossomeenct_Attack();
		virtual ~Monster_Blossomeenct_Attack();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void complete();
		void SetDirection(int set) { _dir = set; }
		bool _bullet_Life = false;
		bool _bullet_animation = false;

	private:
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		float _attackatime = 0.f;
		int _dir = 1;

	};
}