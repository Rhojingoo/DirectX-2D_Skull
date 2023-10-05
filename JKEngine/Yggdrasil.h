#pragma once
#include "Include_Common.h"
#include "Player_Hp_Bar.h"
#include "Yggdrasil_Dead_Impact1.h"
#include "Yggdrasil_Dead_Impact2.h"

#include "Yggdrasil_HpFrame.h"
#include "Monster_Hp_Bar.h"
#include "HP_Frame.h"


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
			Attack_C_UP,
			Attack_C,
			Attack_C_Down,
			Attack_C_Finish,
			Groggy_Start,
			Groggy_End,
			Attack_D_Set,
			Attack_D_Ready,
			Attack_D,
			Attack_D_Loading,
			Attack_D_Finish,
			Intro_Set_Right,
			Intro_Set_Left,
			Intro_Ready,
			Intro,
			Intro_End,
			Change_Wating,
			Change_Set,
			Change_Ready,
			Change,
			Change_End,
			DieSet,
			Die_Waiting,
			DieReady,
			Die,
		};

		void idle();
	
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
		void attack_c_up();
		void attack_c();
		void attack_c_down();
		void attack_c_finish();

		void groggy_start();
		void groggy_end();

		void attack_d_set();
		void attack_d_ready();
		void attack_d();
		void attack_d_loading();
		void attack_d_finish();

		void intro_set_right();
		void intro_set_left();
		void intro_ready();
		void intro();
		void intro_end();

		void change_wating();
		void change_set();
		void change_ready();
		void change();
		void change_end();

		void die_set();
		void die_waiting();
		void die_ready();
		void die();

		int random(int a, int b);
		void Hpcontrol();

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
		static int	_Attack_Dir;
		static float _time;
		static void SetChange_Yggdrasil(bool check) { _Change = check; }


		static Monster_Hit_Effect* _Hit_Effect; 
		static Player_Hit_Effect* _Hit_Effect_player;
		static Hit_Sword* _Hit_Sword; 
		static Hit_Critical_Middle* _Critical_Middle; 
		static Hit_Critical_High* _Critical_High; 
		static Monster_Death_Effect* _Death_Effect; 


			
		static	Yggdrasil_HpFrame* _HpFrame; 
		static	Monster_Hp_Bar* Monster_Hp;
		static	Monster_Hp_Bar* Monster_Hp_Second;
		static	Monster_Hp_Bar* Monster_DamegeHp;
		static	Monster_Hp_Bar* Monster_DamegeHp_Second;
		static float _Damage;
		static bool _Hp_control;
		static float _Hp_time;
		static bool _First_Hp_on;
	private:	
		float _FrameDown = 230;



	public:
		static int	_HitType;
		static bool _FirstDie;
		static int _Diecheck;			
		static bool _DieON;
		static bool _BossDie;
		int Attack_Sellect = 0;
		static int    _NumberofAttack;


		static bool _Intro;
		static bool _Intro_SetR;
		static bool _Intro_SetL;
		static bool _Intro_Ready;
		static bool _Intro_StartCHIN;
		static bool _Intro_StartR;
		static bool _Intro_StartL;
		static bool _Intro_EndR;
		static bool _Intro_EndL;


		static bool _SetattackA_r;
		static bool _SetattackA_l;
		static bool _AttackA_Readyr;
		static bool _AttackA_Readyl;
		static bool _AttackA_Boddy;	
		static bool _AttackA_Chin;
		static bool _AttackA_LoadingR;
		static bool _AttackA_LoadingL;
		static bool _AttackA_FinishR;
		static bool _AttackA_FinishL;


		static bool _SetattackB_r;
		static bool _SetattackB_l;
		static bool _AttackB_Ready_Boddy;
		static bool _AttackB_Readyr;
		static bool _AttackB_Readyl;
		static bool _AttackB_Boddy;
		static bool _AttackB_Finishr;
		static bool _AttackB_Finishl;
		static bool _AttackB_FinishBoddy;


		static bool _SetattackC_r;
		static bool _SetattackC_l;
		static bool _SetattackC_face;
		static bool _SetattackC_chin;
		static bool _SetattackC_boddy;
		static bool _AttackC_Readyr;
		static bool _AttackC_Readyl;

		static bool _AttackC_Face;
		static bool _AttackC_Boddy;


		static bool _AttackC_Finish;


		static bool _SetattackD_r;
		static bool _SetattackD_l;
		static bool _AttackD_Readyr;
		static bool _AttackD_Readyl;
		static bool _AttackD_Loadingr;
		static bool _AttackD_Loadingl;
		static bool _AttackD_Finishr;
		static bool _AttackD_Finishl;


		static bool _Change;
		static bool _SetChange_r;
		static bool _SetChange_l;
		static bool _SetChange_face;
		static bool _SetChange_chin;
		static bool _SetChange_boddy;
		static bool _Change_Readyr;
		static bool _Change_Readyl;
		static bool _Change_Chin;
		static bool _Change_Face;
		static bool _Change_Body;
		static bool _Change_HandR;
		static bool _Change_HandL;
		static bool _Changeon;
		static bool _Change_FinishR;
		static bool _Change_FinishL;
		static bool _Change_Finish;		
		
		static bool _Groggy_Bulletready;
		static bool _Groggy_Body_Down;
		static bool _Groggy_Face_Down;
		static bool _Groggy_Chin_Down;
		static bool _Groggy_Body_Up;
		static bool _Groggy_Face_Up;
		static bool _Groggy_Chin_Up;
		static bool _Groggy_RightHand_Up;
		static bool _Groggy_LeftHand_Up;

		static bool _Die_SetR;
		static bool _Die_SetL;
		static bool _Die_SetFace;
		static bool _Die_SetChin;
		static bool _Die_SetBoddy;

		static bool _Die_Waiting_R;
		static bool _Die_Waiting_L;
		static bool _Die_Waiting_Face;
		static bool _Die_Waiting_Chin;
		static bool _Die_Waiting_Boddy;


		static bool _Die_READY_R;
		static bool _Die_READY_L;
		static bool _Die_Body_Down;
		static bool _Die_Face_Down;
		static bool _Die_Chin_Down;





	public:
		static float _MaxHp;
		static float _CurrenHp;
		static float _MaxHp_scale;
		static float _CurrenHp_scale; 
		static int	_bulletcheck;


	private:
		GameObject* _Gobjs[5];	
		static Vector3 _pos;
		static Vector3 _Rotation;
		float _attackatime = 0.f;
		int test = 0;
		

	private:
		float _Fadetime = 0.f;
		float _FadeAssistantTime = 0.f;
		float _Dietime = 0.f;
		bool _Fadecheck = false;
		bool _ChangeFadein = false;
		bool _DieFadein = false;
		bool _DiewaitingFadein = false;
		GameObject* Particle[3] = {};
		Yggdrasil_Dead_Impact1* DieImpact_first[2] = {};
		Yggdrasil_Dead_Impact2* DieImpact_second = nullptr;


	};
}