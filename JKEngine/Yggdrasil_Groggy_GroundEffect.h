#pragma once
#include "Effect.h"

namespace jk
{
	class Yggdrasil_Groggy_GroundEffect : public Effect
	{
	public:
		Yggdrasil_Groggy_GroundEffect();
		virtual ~Yggdrasil_Groggy_GroundEffect();

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
		static void SetDirection(int set) { mDir = set; }
		static int	mDir;

	private:
		class Animator* at = nullptr;
		class RigidBody* _rigidbody = nullptr;
		class Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
	};
}