#pragma once
#include "Include_Common.h"

namespace jk
{
	class Knight_EnergyBall_StartEffect : public Effect
	{
	public:
		Knight_EnergyBall_StartEffect();
		virtual ~Knight_EnergyBall_StartEffect();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void Compelete();
		void SetDirection(int set) { _dir = set; }
		static bool _effect_switch;
		static bool _effect_animation;

	private:
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		float _attackatime = 0.f;
		int _dir = 1;
	};
}