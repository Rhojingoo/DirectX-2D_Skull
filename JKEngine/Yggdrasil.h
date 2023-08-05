#pragma once
#include "Include_Common.h"

namespace jk
{
	class Yggdrasil : public Boss
	{
	public:
		Yggdrasil();
		virtual ~Yggdrasil();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		enum class Yggdrasil_State
		{
			Idle,
			Die,
			Attack_A,
			Attack_B,
			Attack_C,
			Intro,
		};

		void idle();
		void die();
		void attack_a();
		void attack_b();
		void attack_c();
		void intro();

		static void SetPlayerPos(Vector3 set) { _playerpos = set; }
		static Vector3 GetPlayerPos() { return _playerpos; }
		static void SetPos(Vector3 set) { _pos = set; }
		static Vector3 GetPos() { return _pos; }
		static Yggdrasil_State _state;
		static Vector3 _playerpos;
		Vector3	_Playerdistance = Vector3(0.f, 0.f, 0.f);
		int	mDir = 1;
		static float _time;

	private:
		GameObject* _Gobjs[5];
		static Vector3 _pos;
	};
}