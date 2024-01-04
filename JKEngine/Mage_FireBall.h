#pragma once
#include "Bullet.h"


namespace jk
{
	class Mage_FireBall : public Bullet
	{
	public:
		Mage_FireBall();
		virtual ~Mage_FireBall();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void complete();
		void SetDirection(int set) { _dir = set; }
		
	public:
		bool _bullet_animation = false;
		bool _bullet_On = false;
		bool _rotationswitch = false;

	private:
		class Fireball_Projectile_Hit* Bullet_Effect;


	private:
		class Animator* at = nullptr;
		class AudioSource* as = nullptr;
		class RigidBody* _rigidbody = nullptr;
		class Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		float _Lifetime = 0.f;
		int _dir = 1;
	};
}