#pragma once
#include "Effect.h"


namespace jk
{
	class Yggdraisl_Groggy_StartImpact : public Effect
	{
	public:
		Yggdraisl_Groggy_StartImpact();
		virtual ~Yggdraisl_Groggy_StartImpact();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void Compelete();

		bool _groggystartefeect_switch = true;


	private:
		class Animator* at = nullptr;
		class RigidBody* _rigidbody = nullptr;
		class Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		float _attackatime = 0.f;
	};
}