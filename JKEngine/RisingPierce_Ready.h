#pragma once
#include "Include_Common.h"
#include "Effect.h"

namespace jk
{
	class RisingPierce_Ready : public Effect
	{
	public:
		RisingPierce_Ready();
		virtual ~RisingPierce_Ready();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void SetDirection(int set) { mDir = set; }
		void SetSwitch(bool set) { _SwitchOn = set; }

		void Compelete_Pierce();

	private:
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;

		int	mDir = 1;
		bool	_SwitchOn = false;
	};
}