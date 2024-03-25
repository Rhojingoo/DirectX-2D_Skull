#pragma once
#include "Bullet.h"

namespace jk
{
	class Transform;
	class Collider2D;
	class RigidBody;
	class Animator;
	class AudioSource;
	class Hit_Critical_Middle;
	class Homing_Pierce_LongHair : public Bullet
	{
	public:
		Homing_Pierce_LongHair();
		virtual ~Homing_Pierce_LongHair();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		static void SetPos(Vector3 set) { _pos = set; }
		static Vector3 GetPos() { return _pos; }
		static void SetDirection(int set) { _Dir = set; }
		static int	_Dir;

	

	private:
		Transform* _tr = nullptr;
		Animator* at = nullptr;
		AudioSource* as = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Hit_Critical_Middle* _Critical_Middle = nullptr;

	private:
		static Vector3 _pos;
		static bool _effect_switch;
		float _attackatime = 0.f;
	};
}