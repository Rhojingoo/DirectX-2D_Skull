
#pragma once
#include "Include_Common.h"
#include "Effect.h"

namespace jk
{
	class Yggdrasil_EnergeBall_CreateEffect : public Effect
	{
	public:
		Yggdrasil_EnergeBall_CreateEffect();
		virtual ~Yggdrasil_EnergeBall_CreateEffect();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void Compelete();

	public:
		static bool Groggy_Strat;

	public:
		bool _EffectOn = true;

	private:
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
	};
}