#pragma once
#include "Include_Common.h"
#include "MiniBoss_Bullet_Archer.h"

namespace jk
{
	class Archer_Upward_Impact_Bullet : public MiniBoss_Bullet_Archer
	{
	public:
		Archer_Upward_Impact_Bullet();
		virtual ~Archer_Upward_Impact_Bullet();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void complete();

		bool _bullet_On = false;

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