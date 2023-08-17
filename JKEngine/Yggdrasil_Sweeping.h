#pragma once
#include "Include_Common.h"
#include "Effect.h"

namespace jk
{
	class Yggdrasil_Sweeping : public Effect
	{
	public:
		Yggdrasil_Sweeping();
		virtual ~Yggdrasil_Sweeping();

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
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
	};
}