#pragma once
#include "Bullet.h"


namespace jk
{
	class Yggdrsil_Energy_Corps : public Bullet
	{
	public:
		Yggdrsil_Energy_Corps();
		virtual ~Yggdrsil_Energy_Corps();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;
		bool _effect_switch = true;

	private:
		class Animator* at = nullptr;
		class AudioSource* as = nullptr;
		class RigidBody* _rigidbody = nullptr;
		class Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		class Yggdrasil_EnergyBullet_Effect* BulletEffect = nullptr;

	private:

		float _attackatime = 0.f;
		int	_Dir = 1;
		bool _EffectSwitch = true;
	};
}