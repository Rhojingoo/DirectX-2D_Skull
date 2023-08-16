#pragma once
#include "Include_Common.h"
#include "Bullet.h"

namespace jk
{
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
		static void SetDirection(int set) { mDir = set; }
		static int	mDir;

	

	private:
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;

	private:
		static Vector3 _pos;
		static bool _effect_switch;
		float _attackatime = 0.f;
	};
}