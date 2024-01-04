#pragma once
#include "Bullet.h"



namespace jk
{
	class Yggdrasil_Energy_Bomb : public Bullet
	{
	public:
		Yggdrasil_Energy_Bomb();
		virtual ~Yggdrasil_Energy_Bomb();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		static void SetPos(Vector3 set) { _pos = set; }
		static Vector3 GetPos() { return _pos; }
		bool _effect_switch = true;

	private:
		class Animator* at = nullptr;
		class AudioSource* as = nullptr;
		class RigidBody* _rigidbody = nullptr;
		class Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		class Yggdrasil_EnergyBullet_Effect* BulletEffect = nullptr;

	private:
		static Vector3 _pos;
		float _attackatime = 0.f;
		bool _EffectSwitch = true;
	};
}