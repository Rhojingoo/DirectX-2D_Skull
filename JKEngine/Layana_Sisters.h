#pragma once
#include "Include_Common.h"

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

			Sisters_Attack_FlyDash,
			Sisters_Attack_Fall,

			Sisters_Attack_A_Ready,
			Sisters_Attack_A_LandingDash,
			Sisters_Attack_A,
			Sisters_Attack_A_End,


			Sisters_Attack_B_Ready,
			Sisters_Attack_B_LandingDash,
			Sisters_Attack_B,
			Sisters_Attack_B_End,

	
			Sisters_Attack_C,
			Sisters_Attack_D,


			BackGround_Idle,
			BackGround_Move,

			Rush_Ready,
			RushA,
			RushB,
			RushC,
			Rush_End,

			Dash,
			FlyDash,
			LandingDash,
			BackStep,

			Meteor_Cross_Ready,
			Meteor_Cross_Jump,
			Meteor_Cross_Attack,
			Meteor_Cross_Landing,
			Meteor_Cross_End,

			Meteor_Ground_Ready,
			Meteor_Ground_Attack,
			Meteor_Ground_Landing,
			Meteor_Ground_End,

			Meteor_Vertical_Jump,
			Meteor_Vertical_Ready,
			Meteor_Vertical_Attack,
			Meteor_Vertical_Landing,
			Meteor_Vertical_End,

			Skill_A_Bullet_Ready,
			Skill_A_Bullet,
			Skill_A_Bullet_End,

			Skill_B_RisingPierce,
			Skill_B_RisingPierce_End,

			Skill_C_DimensionPierce,



			Awaken,
			AwakenJump,
			AwakenReady,

			Die,
		};

		void idle();

		void Sisters_Attack_A_Ready();
		void Sisters_Attack_FlyDash();
		void Sisters_Attack_Fall();
		void Sisters_Attack_A_LandingDash();
		void Sisters_Attack_A();
		void Sisters_Attack_A_End();


		void Sisters_Attack_B_Ready();
		void Sisters_Attack_B_LandingDash();
		void Sisters_Attack_B();
		void Sisters_Attack_B_End();




		void Sisters_Attack_C();
		void Sisters_Attack_D();


		void Dash();
		void FlyDash();
		void LandingDash();
		void BackStep();


		void Rushready();
		void Rush_A();
		void Rush_B();
		void Rush_C();
		void Rush_End();



		void CrossJump();
		void CrossReady();
		void CrossAttack();
		void CrossLanding();
		void CrossEnd();

		void GroundReady();
		void GroundAttack();
		void GroundLanding();
		void GroundEnd();

		void Vertical_Jump();
		void Vertical_Ready();
		void Vertical_Attack();
		void Vertical_Landing();
		void Vertical_End();

		void Skill_A_Ready();
		void Skill_A();
		void Skill_A_End();

		void Skill_B();
		void Skill_B_End();

		void Skill_C();


		void Intro_Dash();
		void Intro_Landing();
		void Intro_Fall();


		void Awaken();
		void AwakenJump();
		void AwakenReady();

		void BackGround_Idle();
		void BackGround_Move();


		void die();

		int random(int a, int b);

		static void SetPlayerPos(Vector3 set) { _playerpos = set; }
		static Vector3 GetPlayerPos() { return _playerpos; }		
		
	public:
		static Layana_Sisters_State _state;	

	private:
		GameObject* _Gobjs[3];
		float _time;


	public:
		static bool _Intro_On;
		static bool _Intro_Dash_LongHair;
		static bool _Intro_Dash_ShortHair;
		static bool _Intro_Fall_LongHair;
		static bool _Intro_Fall_ShortHair;
		static bool _Intro_Land_LongHair;
		static bool _Intro_Land_ShortHair;
		static bool _Intro_LongHair_END;
		static bool _Intro_ShortHair_END;

	public:
		bool _Sisters_Attack_On = false;
		static int _Sisters_AttackType;

	public:		
		static bool _SistersAttack_FlyDash_LongHair;
		static bool _SistersAttack_FlyDash_ShortHair;

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
		static bool _SistersAttack_B_Ready_LongHair;
		static bool _SistersAttack_B_Ready_ShortHair;
		static bool _SistersAttack_B_DashOn;
		static bool _SistersAttack_B_DashOn_LongHair;
		static bool _SistersAttack_B_DashOn_ShortHair;
		static bool _SistersAttack_B_LongHair_END;
		static bool _SistersAttack_B_ShortHair_END;

	};
}