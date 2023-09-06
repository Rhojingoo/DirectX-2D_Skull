#pragma once
#include "Include_Common.h"
#include "MiniBoss_Bullet.h"

namespace jk
{
	class Archer_Arrow : public MiniBoss_Bullet
	{
	public:
		Archer_Arrow();
		virtual ~Archer_Arrow();

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

	private:
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		float _attackatime = 0.f;
		int _dir = 1;

	private:
		//Kngiht_EnergyBall_Impact* Bullet_Effect;

	};
}