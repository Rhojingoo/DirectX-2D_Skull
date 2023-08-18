#pragma once
#include "Include_Common.h"

namespace jk
{
	class Kngiht_EnergyBall_Impact : public Effect
	{
	public:
		Kngiht_EnergyBall_Impact();
		virtual ~Kngiht_EnergyBall_Impact();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void Compelete();

		static bool _effect_switch;


	private:
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		float _attackatime = 0.f;
	};
}