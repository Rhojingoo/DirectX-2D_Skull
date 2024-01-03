#pragma once
#include "Effect.h"

namespace jk
{
	class Dimension_Pierce_BossEffect : public Effect
	{
	public:
		Dimension_Pierce_BossEffect();
		virtual ~Dimension_Pierce_BossEffect();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		 void SetDirection(int set) { _Dir = set; }
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