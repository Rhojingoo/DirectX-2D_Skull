#pragma once
#include "Include_Common.h"
#include "Bullet.h"
#include "Hit_Critical_Middle.h"
#include "..\Engine_SOURCE\jkAudioSource.h"


namespace jk
{
	class Homing_Pierce_ShortHair : public Bullet
	{
	public:
		Homing_Pierce_ShortHair();
		virtual ~Homing_Pierce_ShortHair();

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
		Transform* _tr = nullptr;
		Animator* at = nullptr;
		AudioSource* as = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		Hit_Critical_Middle* _Critical_Middle = nullptr;

	private:
		static Vector3 _pos;
		static bool _effect_switch;
		float _attackatime = 0.f;
	};
}