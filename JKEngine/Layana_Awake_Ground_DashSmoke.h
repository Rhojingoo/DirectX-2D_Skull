#pragma once
#include "Effect.h"

namespace jk
{
	class Layana_Awake_Ground_DashSmoke : public Effect
	{
	public:
		Layana_Awake_Ground_DashSmoke();
		virtual ~Layana_Awake_Ground_DashSmoke();

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