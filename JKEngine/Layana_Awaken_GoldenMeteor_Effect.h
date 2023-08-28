#pragma once
#include "Include_Common.h"
#include "Effect.h"

namespace jk
{
	class Layana_Awaken_GoldenMeteor_Effect : public Effect
	{
	public:
		Layana_Awaken_GoldenMeteor_Effect();
		virtual ~Layana_Awaken_GoldenMeteor_Effect();

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

		void Compelete();

	private:
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
	};
}