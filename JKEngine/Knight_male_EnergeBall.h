#pragma once
#include "Include_Common.h"
#include "MiniBoss_Bullet_Knight.h"
#include "Kngiht_EnergyBall_Impact.h"

namespace jk
{
	class Knight_male_EnergeBall : public MiniBoss_Bullet_Knight
	{
	public:
		Knight_male_EnergeBall();
		virtual ~Knight_male_EnergeBall();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void EnergeBall_Boomb();

	public:
		bool _EffectSwitch = true;
		bool _BoomSwitch = false;

	private:
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;

	private:
		Kngiht_EnergyBall_Impact* Bullet_Effect;

	private:
		float _attackatime = 0.f;

	};
}