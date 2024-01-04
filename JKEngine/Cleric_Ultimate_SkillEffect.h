#pragma once
#include "Effect.h"

namespace jk
{
	class Cleric_Ultimate_SkillEffect : public Effect
	{
	public:
		Cleric_Ultimate_SkillEffect();
		virtual ~Cleric_Ultimate_SkillEffect();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;


		void Compelete1();
		void Compelete2();


		bool _effect_On = false;


	private:
		class Animator* at = nullptr;
		class RigidBody* _rigidbody = nullptr;
		class Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		float _Lifetime = 0.f;
	};
}