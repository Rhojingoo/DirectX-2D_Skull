#pragma once
#include "Effect.h"

namespace jk
{
	class Transform;
	class Collider2D;
	class RigidBody;
	class Animator;
	class Archer_Arrow_Upward_Sign : public Effect
	{
	public:
		Archer_Arrow_Upward_Sign();
		virtual ~Archer_Arrow_Upward_Sign();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void Compelete();

		bool _effect_On = false;


	private:
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		float _attackatime = 0.f;
	};
}