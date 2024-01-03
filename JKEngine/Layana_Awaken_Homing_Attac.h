#pragma once
#include "Bullet.h"

namespace jk
{
	class Layana_Awaken_Homing_Attac : public Bullet
	{
	public:
		Layana_Awaken_Homing_Attac();
		virtual ~Layana_Awaken_Homing_Attac();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;


		void SetDirection(int set) { mDir = set; }
		int	mDir = 1;
		bool _effect_switch = false;
		bool _bulletoff = false;
		void Compelete_Pierce();


	private:
		class Animator* at = nullptr;
		class RigidBody* _rigidbody = nullptr;
		class Collider2D* _collider = nullptr;
		Transform* tr = nullptr;

	private:
		float _attackatime = 0.f;
	};
}