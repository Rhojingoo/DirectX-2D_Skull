#pragma once
#include "Include_Common.h"
#include "Effect.h"

namespace jk
{
	class Layana_Dark_HomingPierce_Effect : public Effect
	{
	public:
		Layana_Dark_HomingPierce_Effect();
		virtual ~Layana_Dark_HomingPierce_Effect();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;


		void SetDirection(int set) { mDir = set; }
		int	mDir = 1;
		bool _effect_switch = false;
		bool _bulletoff = false;


	private:
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;

	private:
		float _attackatime = 0.f;
	};
}