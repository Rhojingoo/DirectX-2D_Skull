#pragma once
#include "MiniBoss_Bullet_Archer.h"

namespace jk
{
	class Archer_Trap : public MiniBoss_Bullet_Archer
	{
	public:
		Archer_Trap();
		virtual ~Archer_Trap();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void complete();

		bool _Bullet_Life = false;

	private:
		class Animator* at = nullptr;
		class RigidBody* _rigidbody = nullptr;
		class Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		float _attackatime = 0.f;
	};
}