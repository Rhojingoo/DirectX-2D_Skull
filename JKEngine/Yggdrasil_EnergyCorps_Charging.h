#pragma once
#include "Effect.h"

namespace jk
{
	class Yggdrasil_EnergyCorps_Charging : public Effect
	{
	public:
		Yggdrasil_EnergyCorps_Charging();
		virtual ~Yggdrasil_EnergyCorps_Charging();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void Compelete();

	public:
		bool _EffectOn = true;

	private:
		class Animator* at = nullptr;
		class RigidBody* _rigidbody = nullptr;
		class Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
	};
}