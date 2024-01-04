#pragma once
#include "Effect.h"

namespace jk
{
	class Monster_Hammer_Effect : public Effect
	{
	public:
		Monster_Hammer_Effect();
		virtual ~Monster_Hammer_Effect();

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