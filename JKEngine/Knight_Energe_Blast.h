#pragma once
#include "Include_Common.h"
#include "Bullet.h"


namespace jk
{
	class Knight_Energe_Blast : public Bullet
	{
	public:
		Knight_Energe_Blast();
		virtual ~Knight_Energe_Blast();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void Compelete();

	public:
		bool _EffectEnd = false;

	private:
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;

	private:
		float _attackatime = 0.f;

	};
}