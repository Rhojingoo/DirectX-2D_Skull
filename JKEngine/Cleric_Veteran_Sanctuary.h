#pragma once
#include "Bullet.h"

namespace jk
{
	class Cleric_Veteran_Sanctuary : public Bullet
	{
	public:
		Cleric_Veteran_Sanctuary();
		virtual ~Cleric_Veteran_Sanctuary();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void complete();

		bool _bullet_On = false;

	private:
		class Animator* at = nullptr;
		class RigidBody* _rigidbody = nullptr;
		class Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		float _attackatime = 0.f;
		int _dir = 1;

	};
}