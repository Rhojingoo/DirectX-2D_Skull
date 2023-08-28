#pragma once
#include "Include_Common.h"
#include "Layana_Sisters.h"
#include "Layana_Awken_Rush_Sign.h"
#include "Latana_Awake_Rush_Bullet.h"
#include "Layana_Awaken_Meteoreffect.h"
#include "Layana_Awaken_Ground_Sign.h"
#include "Layana_Awaken_Ground_Thunder_Sign.h"
#include "Layana_Awake_Ground_DashSmoke.h"
#include "Layana_Ground_Thunder.h"
#include "Layana_Awaken_GoldenMeteor_Effect.h"
#include "Layana_Awaken_Meteor_Electric.h"
#include "Layana_Awaken_Meteor_Projectile.h"
#include "Layana_Dark_HomingPierce.h"
#include "Layana_Dark_HomingPierce_Effect.h"

namespace jk
{
	class Layana_Dark_Awaken : public Layana_Sisters
	{
	public:
		Layana_Dark_Awaken();
		virtual ~Layana_Dark_Awaken();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		enum class Layana_Dark_Awaken_State
		{
			Idle,

			Awaken_End,

			Telleport_In,
			Telleport_Out,

			Dash,
			FlyDash,
			LandingDash,
			BackStep,

			Rush_Ready,
			RushA,
			RushB,
			RushC_1,
			RushC_2,
			RushC_3,
			RushC_4,
			RushC_5,
			RushC_6,
			RushC_7,
			RushC_8,
			Rush_End,

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

			Die,
		};

		void idle();

		void Awaken_End();

		void Telleport_In();
		void Telleport_Out();

		void Dash();
		void FlyDash();
		void LandingDash();
		void BackStep();


		void Rushready();
		void Rush_A();
		void Rush_B();
		void Rush_C_1();
		void Rush_C_2();
		void Rush_C_3();
		void Rush_C_4();
		void Rush_C_5();
		void Rush_C_6();
		void Rush_C_7();
		void Rush_C_8();

		void Rush_End();


		void CrossReady();
		void CrossJump();
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


		void die();
		void death();

	public:
		void Complete_Telleport_In();
		void Complete_Telleport_Out();

		void Complete_RushReady();
		void Complete_Rush_C1();
		void Complete_Rush_C2();
		void Complete_Rush_C3();
		void Complete_Rush_C4();
		void Complete_Rush_C5();
		void Complete_Rush_C6();
		void Complete_Rush_C7();


		void Complete_CrossJump();
		void Complete_CrossLanding();
		void Complete_CrossEnd();

		void Complete_GroundLanding();
		void Complete_GroundEnd();

		void Complete_VerticalJump();
		void Complete_VerticalReady();
		void Complete_VerticalEnd();

		void Complete_Skill_A();
		void Complete_Skill_B();



	public:
		void Rush_Combo();
		void Meteor_Cross_Combo();
		void Meteor_Ground_Combo();
		void Meteor_Vertical_Combo();
		void Skill_A_Combo();
		void Skill_B_Combo();
		void Skill_C_Combo();
		void Awaken_Combo();




	public:
		void CreateHoming();
		void SettingHoming(Transform* set, int angle_of_number);

	public:
		static Layana_Dark_Awaken_State _DarkMode_state;


	private:
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;

	private:
		Layana_Awken_Rush_Sign* Rush_Sign[7] = {};
		Latana_Awake_Rush_Bullet* Rush_Bullet[7] = {};
		Layana_Awaken_Meteoreffect* _Meteoreffect = nullptr;
		Layana_Awaken_Ground_Sign* _Ground_Sign = nullptr;
		Latana_Awake_Rush_Bullet* _Ground_Attack = nullptr;	
		Layana_Awaken_Ground_Thunder_Sign* _Ground_Thunder_Sign[7] = {};
		Layana_Awake_Ground_DashSmoke* _Ground_DashSmoke = nullptr;
		Layana_Ground_Thunder* _Ground_Thunder[7] = {};
		Layana_Awaken_GoldenMeteor_Effect* _GoldenMeteor_Effect = nullptr;
		Layana_Awaken_Meteor_Electric* _Meteor_Electric = nullptr;
		Layana_Awaken_Meteor_Projectile* _Meteor_Projectile[2] = {};
		Layana_Dark_HomingPierce* _Dark_HomingPierce[5] = {};
		Layana_Dark_HomingPierce_Effect* _HomingPierce_Effect[5] = {};
		Latana_Awake_Rush_Bullet* _HomingPierce_Attack[5] = {};


	private:
		//Rising_Pierce* Rising[19];
		//Transform* Risingbullet_tr[19];
		//RigidBody* risingbullet_rb[19];

	private:
		//Dimension_Pierce_BossEffect* Dimension_boss_effect = nullptr;
		//Dimension_Pierce* Dimension_Bullet = nullptr;
		//Dimension_Pierce_BulletEffect* Dimension_BulletEffect = nullptr;
		//TwinMeteor_Effect* TwinMeteor_Impact = nullptr;
		//TwinMeteor_Boss* TwinMeteor_BossEffect = nullptr;

	private:
		Vector3	_Playerdistance = Vector3(0.f, 0.f, 0.f);
		Vector3	_Playerpos = Vector3(0.f, 0.f, 0.f);
		Vector3 _pos = Vector3(0.f, 0.f, 0.f);
		Vector3 _BodyRotation = Vector3(0.f, 0.f, 0.f);
		Vector2 _velocity = Vector2(0.f, 0.f);
		Vector3 _Createpos = Vector3(0.f, 0.f, 0.f);
		Vector2 _HomingEditPOS = Vector2(0.f, 0.f);


	private:
		int		_Dir = 1;							// 방향설정
		int		_BulletDir = 1;
		float	_time = 0.f;						// 공격패턴시 사용중	
		float	_Attacktime = 0.f;					// 공격패턴시 보조사용중
		bool	_Ground_check = false;				// 땅체크시에 쓰이고 있는 변수
		bool	_BackGround_check = true;			// 백그라운드 아이들시 사용되는 변수
		int		_Rushnumber = 0;					// 러쉬 공격시 1번 = a, 2번 = b, 3번 =c , 0 = 대기상태
		bool	_teleport_Rush = false;				// 텔레포드 인아웃을 할수 있도록 설정하는 변수
		bool	_teleport_Cross = false;
		bool	_teleport_Ground = false;
		bool	_teleport_Vertical = false;

	public:
		static bool _AttackStageON;				// FLyDash의 경우 나가있는지 안에 있는지 확인할수 있는변 나가있는상태라면 위치 셋팅하여 안으로 들어오게 도와주는 역할의 변수 

	private:
		bool	_Bullet_Switch[3] = {};

		bool	_RushSwitch = false;
		int		_Rush_C_Number = 0;

		bool	_CrossMeteorSwitch = false;
		bool	_CrossMeteorLanding = false;

		bool	_GroundMeteorSwitch = false;
		bool	_GroundMeteorLanding = false;
		bool	_GroundMeteorAttack_Right = false;
		bool	_GroundMeteorAttack_Left = false;

		bool	_VerticalMeteorSwitch = false;
		bool	_VerticalMeteorLanding = false;

		bool	_SkillB_Switch = false;

		bool	_SkillC_Switch = false;

		bool	_Intro_Switch = false;
		bool	_Intro_Landing = false;

		bool	_Awaken_Switch = false;
		bool	_Awaken_Ready = false;

		bool	_BackGround_Switch = false;
		bool	_BackGround_Idle = false;

		bool	_Joint_Attack = false;

		int		_SelectAttack = 0;
	};
}