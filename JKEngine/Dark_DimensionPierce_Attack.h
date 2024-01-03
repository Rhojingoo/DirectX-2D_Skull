#pragma once
#include "Effect.h"

namespace jk
{
	class Dark_DimensionPierce_Attack : public Effect
	{
	public:
		Dark_DimensionPierce_Attack();
		virtual ~Dark_DimensionPierce_Attack();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		static void SetDirection(int set) { mDir = set; }
		static int	mDir;
		bool _SwitchOn = false;
		bool _SwitchOff = false;

		void Compelete();

	private:
		class Animator* at = nullptr;
		class RigidBody* _rigidbody = nullptr;
		class Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
	};
}