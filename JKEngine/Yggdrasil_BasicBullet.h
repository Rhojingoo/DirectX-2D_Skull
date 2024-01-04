#pragma once
#include "Bullet.h"


namespace jk
{
	class Yggdrasil_BasicBullet : public Bullet
	{
	public:
		Yggdrasil_BasicBullet();
		virtual ~Yggdrasil_BasicBullet();

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
		int	_Dir = 1;

		class Yggdrasil_basicBullet_Effect* BulletEffect = nullptr;

	private:
		static Vector3 _pos;
		bool _EffectSwitch = true;
		float _attackatime = 0.f;
	};
}