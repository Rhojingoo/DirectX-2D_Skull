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
			Attack_A_Set,
			Attack_A_Ready,
			Attack_A_Right,
			Attack_A_Left,
			Attack_A_Loading,
			Attack_A_Finish,
			Attack_B_Set,
			Attack_B_Ready,
			Attack_B_Right,
			Attack_B_Left,
			Attack_B_Finish,
			Attack_C_Set,
			Attack_C_Ready,
			Attack_C,
			Attack_C_Finish,
			Groggy_Start,
			Groggy_End,

			Intro,
		};

		void idle();
		void die();
		void attack_a_set();
		void attack_a_ready();
		void attack_a_right();
		void attack_a_left();
		void attack_a_loading();
		void attack_a_finish();
		void attack_b_set();
		void attack_b_ready();
		void attack_b_left();
		void attack_b_right();
		void attack_b_finish();
		void attack_c_set();
		void attack_c_ready();
		void attack_c();
		void attack_c_finish();
		void groggy_start();
		void groggy_end();
		void intro();

		static void SetPlayerPos(Vector3 set) { _playerpos = set; }
		static Vector3 GetPlayerPos() { return _playerpos; }
		static void SetPos(Vector3 set) { _pos = set; }
		static Vector3 GetPos() { return _pos; }
		static void SetRotation(Vector3 set) { _Rotation = set; }
		static Vector3 GetRotations() { return _Rotation; }
		static Yggdrasil_State _state;
		static Vector3 _playerpos;
		Vector3	_Playerdistance = Vector3(0.f, 0.f, 0.f);
		static int	mDir;
		static float _time;


		static bool _SetattackA_r;
		static bool _SetattackA_l;
		static bool _AttackA_Readyr;
		static bool _AttackA_Readyl;
		static bool _SetattackB_r;
		static bool _SetattackB_l;
		static bool _AttackB_Readyr;
		static bool _AttackB_Readyl;
		static bool _SetattackC_r;
		static bool _SetattackC_l;
		static bool _AttackC_Readyr;
		static bool _AttackC_Readyl;
		static bool _AttackC_Finish;

		static bool _Groggy_Body_Down;
		static bool _Groggy_Face_Down;
		static bool _Groggy_Chin_Down;
		static bool _Groggy_Body_Up;
		static bool _Groggy_Face_Up;
		static bool _Groggy_Chin_Up;
		static bool _Groggy_RightHand_Up;
		static bool _Groggy_LeftHand_Up;


		static int _NumberofAttack;
		int Attack_Sellect = 0;

	private:
		GameObject* _Gobjs[5];
		static Vector3 _pos;
		static Vector3 _Rotation;
		float _attackatime = 0.f;
		int test = 0;
		
	};
}