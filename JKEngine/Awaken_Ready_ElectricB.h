#pragma once
#include "Effect.h"

namespace jk
{
	class Awaken_Ready_ElectricB : public Effect
	{
	public:
		Awaken_Ready_ElectricB();
		virtual ~Awaken_Ready_ElectricB();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void SetDirection(int set) { _Dir = set; }
		void SetSwitch(bool set) { _SwitchOn = set; }

		void Compelete_Pierce();

	private:
		class Animator* at = nullptr;
		class RigidBody* _rigidbody = nullptr;
		class Collider2D* _collider = nullptr;
		Transform* tr = nullptr;

		int	_Dir = 1;
		bool	_SwitchOn = false;
	};
}