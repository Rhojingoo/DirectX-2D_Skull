#pragma once
#include "Effect.h"

namespace jk
{
	class TwinMeteor_Boss : public Effect
	{
	public:
		TwinMeteor_Boss();
		virtual ~TwinMeteor_Boss();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		static void SetDirection(int set) { _Dir = set; }
		static int	_Dir;
		static bool	_SwitchOn;
		static bool	_SwitchOff;

		void Compelete_Pierce();

	private:
		class Animator* at = nullptr;
		class RigidBody* _rigidbody = nullptr;
		class Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
	};
}