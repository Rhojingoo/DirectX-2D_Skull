#pragma once
#include "Include_Common.h"
#include "Bullet.h"

namespace jk
{
	class Archer_Upward_Impact_Bullet : public Bullet
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