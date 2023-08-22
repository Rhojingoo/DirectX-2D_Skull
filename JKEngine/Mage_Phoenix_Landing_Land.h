#pragma once
#include "Include_Common.h"

namespace jk
{
	class Mage_Phoenix_Landing_Land : public Effect
	{
	public:
		Mage_Phoenix_Landing_Land();
		virtual ~Mage_Phoenix_Landing_Land();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void Compelete();
		void SetDirection(int set) { _dir = set; }


		bool _effect_On = true;
		bool _effect_Animation = false;


	private:
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		float _Lifetime = 0.f;
		int _dir = 1;
	};
}