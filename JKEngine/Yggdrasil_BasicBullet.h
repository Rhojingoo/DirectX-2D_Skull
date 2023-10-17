#pragma once
#include "Include_Common.h"
#include "Bullet.h"
#include "Yggdrasil_basicBullet_Effect.h"

#include "..\Engine_SOURCE\jkAudioSource.h"


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
		Animator* at = nullptr;
		AudioSource* as = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		int	mDir = 1;

		Yggdrasil_basicBullet_Effect* BulletEffect = nullptr;

	private:
		static Vector3 _pos;
		bool _EffectSwitch = true;
		float _attackatime = 0.f;
	};
}