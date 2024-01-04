#pragma once
#include "Effect.h"

namespace jk
{
	class Monster_StoneWizard_Icicle_Effect : public Effect
	{
	public:
		Monster_StoneWizard_Icicle_Effect();
		virtual ~Monster_StoneWizard_Icicle_Effect();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		
		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void SetDirection(int set) { _dir = set; }
		void Compelete();

		bool _effect_On = false;
		bool _endanimation = false;

	private:
		class Animator* at = nullptr;
		class RigidBody* _rigidbody = nullptr;
		class Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		float _attackatime = 0.f;
		int _dir = 1;
	};
}