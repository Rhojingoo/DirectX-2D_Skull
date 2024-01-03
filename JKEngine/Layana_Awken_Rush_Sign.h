#pragma once
#include "Effect.h"

namespace jk
{
	class Layana_Awken_Rush_Sign : public Effect
	{
	public:
		Layana_Awken_Rush_Sign();
		virtual ~Layana_Awken_Rush_Sign();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		static void SetDirection(int set) { _Dir = set; }
		static int	_Dir;
		bool _SwitchOn =false;

		void Compelete_Pierce();

	private:
		class Animator* at = nullptr;
		class RigidBody* _rigidbody = nullptr;
		class Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
	};
}