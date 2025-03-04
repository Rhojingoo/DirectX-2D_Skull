#pragma once
#include "Effect.h"

namespace jk
{
	class Death_IntroEffect : public Effect
	{
	public:
		Death_IntroEffect();
		virtual ~Death_IntroEffect();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void SetDirection(int set) { _Dir = set; }
		void SetSwitch(bool set) { _SwitchOn = set; }
		bool GetFinish() { return _Fnish; }

		void Compelete_Pierce();

	private:
		class Animator* at = nullptr;
		class RigidBody* _rigidbody = nullptr;
		class Collider2D* _collider = nullptr;
		Transform* tr = nullptr;

		int	_Dir = 1;
		bool	_SwitchOn = false;
		bool	_Fnish = false;
	};
}