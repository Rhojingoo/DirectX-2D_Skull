#pragma once
#include "Include_Common.h"
#include "Layana_HpFrame.h"

namespace jk
{
	class Layana_Sisters : public Boss
	{
	public:
		Layana_Sisters();
		virtual ~Layana_Sisters();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		enum class Layana_Sisters_State
		{
			Idle,
			Intro_Dash,
			Intro_Fall,
			Intro_Landing,
			Intro_Landing_End,

			Sisters_Attack_Set,
			Sisters_Attack_FlyDash,
			Sisters_Attack_Fall,


			Sisters_Attack_A_Ready,
			Sisters_Attack_A_LandingDash,
			Sisters_Attack_A,
			Sisters_Attack_A_End,


			Sisters_Attack_B_Ready,
			Sisters_Attack_B_BulletCreate,
			Sisters_Attack_B,
			Sisters_Attack_B_End,


			Sisters_Attack_C_Ready,
			Sisters_Attack_C,
			Sisters_Attack_C_Landing,
			Sisters_Attack_C_End,		


			Sisters_Attack_D,		
		};

		enum class LayanaSisters_List
		{
			LonaHair,
			ShortHair,
			Awaken_Darkmode,
			End,
		};

		void idle();


		void Intro_Dash();
		void Intro_Landing();
		void Intro_Landing_End();
		void Intro_Fall();


		void Sisters_Attack_Set();
		void Sisters_Attack_FlyDash();
		void Sisters_Attack_Fall();


		void Sisters_Attack_A_Ready();	
		void Sisters_Attack_A_LandingDash();
		void Sisters_Attack_A();
		void Sisters_Attack_A_End();


		void Sisters_Attack_B_Ready();
		void Sisters_Attack_B_BulletCreate();
		void Sisters_Attack_B();
		void Sisters_Attack_B_End();


		void Sisters_Attack_C_Ready();
		void Sisters_Attack_C();
		void Sisters_Attack_C_Landing();
		void Sisters_Attack_C_End();

		void Sisters_Attack_D();

	
		void longhair_change();
		void shorthair_change();
		void AttackSwap();
		int random(int a, int b);

		static void SetLayana_List(LayanaSisters_List change, LayanaSisters_List current, bool ckeck, int direction)
		{Layana_select = change, Layana_check = current, _Layana_change = ckeck, BossDir = direction;}

		static void SetPos(Vector3 set) { AwakenDarkmode_Pos = set; }
		static void SetPlayerPos(Vector3 set) { _playerpos = set; }
		static Vector3 GetPlayerPos() { return _playerpos; }		
		float CalculateVelocity(float distance, float time) {return distance / time;}
		
	public:
		static Layana_Sisters_State _state;	
		static LayanaSisters_List Layana_select;
		static LayanaSisters_List Layana_check;
		static bool Joint_Operation;
		static bool LongHair_Operation;
		static bool LongHair_First_moving;
		static bool ShortHair_Operation;
		static bool ShortHair_First_moving;
		static int BossDir;

	public:
		static Vector3 LongHairPos;
		static Vector3 ShortHairPos;
		static Vector3 AwakenDarkmode_Pos;
		//static Vector3 BossPos;


	private:
		GameObject* _Gobjs[3];
		float _time = 0.f;
		float _Attacktime = 0.f;

	public:
		static bool _Intro_On;
		static bool _Intro_Dash_LongHair;
		static bool _Intro_Dash_ShortHair;
		static bool _Intro_Fall_LongHair;
		static bool _Intro_Fall_ShortHair;
		static bool _Intro_Land_LongHair;
		static bool _Intro_Land_ShortHair;

		static bool _Intro_LandEnd_LongHair;
		static bool _Intro_LandEnd_ShortHair;

		static bool _Intro_LongHair_END;
		static bool _Intro_ShortHair_END;

	public:
		static bool _First_Die;
		static bool _LongHair_Die;
		static bool _ShortHair_Die;
		static bool _DarkLayana_Die;
		static bool _ShortHair_Awaken;
		static bool _LongHair_Awaken;
		static bool _Layana_change;
		static bool	_Awaken_Switch;


	public:
		bool _Sisters_Attack_On = false;
		static int _Sisters_AttackType;

	public:		
		static int _SistersAttack_Number;
		static bool _SistersAttack_Set_LongHair;
		static bool _SistersAttack_Set_ShortHair;
		static bool _SistersAttack_FlyDash_LongHair;
		static bool _SistersAttack_FlyDash_ShortHair;

		static bool	_Sisters_Attack_A_Switch;	//= false;
		static bool	_Sisters_Attack_B_Switch;	//= false;
		static bool	_Sisters_Attack_C_Switch;	//= false;
		static bool	_Sisters_Attack_D_Switch;	//= false;


	public:
		bool _Sisters_Attack_A_On = false;
		static bool _SistersAttack_A_IntroReady_LongHair;
		static bool _SistersAttack_A_IntroReadyShortHair;
		static bool _SistersAttack_A_Ready_LongHair;
		static bool _SistersAttack_A_Ready_ShortHair;
		static bool _SistersAttack_A_DashOn;
		static bool _SistersAttack_A_DashOn_LongHair;
		static bool _SistersAttack_A_DashOn_ShortHair;
		static bool _SistersAttack_A_LongHair_END;
		static bool _SistersAttack_A_ShortHair_END;

	public:
		bool _Sisters_Attack_B_On = false;
		static bool _SistersAttack_B_IntroReady_LongHair;
		static bool _SistersAttack_B_IntroReadyShortHair;
		static bool _SistersAttack_B_Ready_LongHair;
		static bool _SistersAttack_B_Ready_ShortHair;
		static bool _SistersAttack_B_BulletOn_LongHair;
		static bool _SistersAttack_B_BulletOn_ShortHair;
		static bool _SistersAttack_B_LongHair_END;
		static bool _SistersAttack_B_ShortHair_END;


	public:
		static bool _SistersAttack_C_IntroReady_LongHair;
		static bool _SistersAttack_C_IntroReadyShortHair;
		static bool _SistersAttack_C_Ready_LongHair;
		static bool _SistersAttack_C_Ready_ShortHair;
		static bool _SistersAttack_C_DashOn_LongHair;
		static bool _SistersAttack_C_DashOn_ShortHair;
		static bool _SistersAttack_C_LongHair_LAND;
		static bool _SistersAttack_C_ShortHair_LAND;


	public:
		static Layana_HpFrame* _HpBarFrame;
	private:
		float _FrameDown = 230;

	public:
		static float _Max_LongHair_Hp;
		static float _Curren_LongHair_Hp;
		static float _MaxHp_LongHair_scale;
		static float _CurrenHp_LongHair_scale;


		static float _Max_ShortHair_Hp;
		static float _Curren_ShortHair_Hp;
		static float _MaxHp_ShortHair_scale;
		static float _CurrenHp_ShortHair_scale;


		static float _Max_Dark_Awaken_Hp;
		static float _Curren_Dark_Awaken_Hp;
		static float _MaxHp_Dark_Awaken_scale;
		static float _CurrenHp_Dark_Awaken_scale;
	};
}