#pragma once
#include "Layana_Sisters.h"


namespace jk
{
	class Layana_ShortHair : public Layana_Sisters
	{
	public:
		Layana_ShortHair();
		virtual ~Layana_ShortHair();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		enum class Layana_ShortHair_State
		{
			Idle,

			Rush_Ready,
			RushA,
			RushB,
			RushC,
			RushC1,
			RushC2,
			RushC3,
			RushC4,
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
		};

		enum class Layana_Short_Background
		{
			Idle,
			FlyDash,
			BackGround_Idle,
			BackGround_Enter,	
			BackGround_Exit,
			Die,
		};


		void idle();

		void BackGround_Idle();
		void BackGround_Enter();
		void BackGround_Exit();

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



		void Rushready();
		void Rush_A();
		void Rush_B();
		void Rush_C();
		void Rush_C1();
		void Rush_C2();
		void Rush_C3();
		void Rush_C4();
		void Rush_End();
		void Dash();
		void FlyDash();
		void LandingDash();
		void BackStep();


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

		void Awaken();
		void AwakenJump();
		void AwakenReady();

		void die();

	public:
		void Complete_Rush();
		void Complete_RushReady();

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

		void Complete_IntroLanding();
		void Complete_IntroLanding_END();


		void Complete_Awaken_Ready();
		void Complete_Awaken();

	public:
		void Rush_Combo();
		void Meteor_Cross_Combo();
		void Meteor_Ground_Combo();
		void Meteor_Vertical_Combo();
		void Skill_A_Combo();
		void Skill_B_Combo();
		void Skill_C_Combo();
		void Intro_Combo();
		void Awaken_Combo();
		void BackGround_Combo();
		void HitEffect();

	public:
		void CreateHoming();
		void SettingHoming(Transform* set, int angle_of_number);
		float Getposition_X() { return _pos.x; }
		static Layana_ShortHair_State _ShortHair_state;
		static Layana_Short_Background Background_state;


	private:
		class Animator* at = nullptr;
		class AudioSource* as = nullptr;
		class RigidBody* _rigidbody = nullptr;
		class Collider2D* _collider = nullptr;
		class Transform* tr = nullptr;
		class HitBox_Layana* Hit_Box = nullptr;
		bool _HitBox_Attack_On = false;
		int _HitBox_Dir = 1;

	private:
		class Homing_Pierce_ShortHair* Homing[3] = {};
		class Homing_Impact* Homing_EF[3] = {};
		Transform* bullet_tr1 = nullptr;
		Transform* bullet_tr2 = nullptr;
		Transform* bullet_tr3 = nullptr;
		class RigidBody* bullet_rb1 = nullptr;
		class RigidBody* bullet_rb2 = nullptr;
		class RigidBody* bullet_rb3 = nullptr;


	private:
		class Rising_Pierce* Rising[19] = {};
		Transform* Risingbullet_tr[19] = {};
		class RigidBody* risingbullet_rb[19] = {};

	private:
		class Dimension_Pierce_BossEffect* Dimension_boss_effect = nullptr;
		class Dimension_Pierce* Dimension_Bullet = nullptr;
		class Dimension_Pierce_BulletEffect* Dimension_BulletEffect = nullptr;
		class TwinMeteor_Effect* TwinMeteor_Impact = nullptr;
		class TwinMeteor_Boss* TwinMeteor_BossEffect = nullptr;
		class Intro_Somke* Intro_SM = nullptr;
		class Intro_Aura_Layana* Intro_Ar = nullptr;
		class Layana_Dash_Smoke* Dash_SM = nullptr;
		class Layana_Meteor_GR_Smoke* MeteorGR_SM = nullptr;
		class RisingPierce_Ready* RisingPierce_EF = nullptr;
		class Golden_Meteor_Bullet* Golden_Meteor_Bl = nullptr;
		class Golden_Meteor_Effect_End* Golden_Meteor_Ef = nullptr;


	private://체인지용 이펙트모음
		class Awaken_Ready_ElectricA* Awaken_Rd_ElectricA = nullptr;
		class Awaken_Ready_ElectricB* Awaken_Rd_ElectricB = nullptr;
		class Awaken_SmokeEffect* Awaken_Smoke_EF = nullptr;
		class Awaken_Electric* Awaken_Elec_EF = nullptr;
		bool _ChangeFadein = false;
		bool _Fadecheck = false;
		float _Fadetime = 0.f;


	private:
		Vector3	_Playerdistance = Vector3(0.f, 0.f, 0.f);
		Vector3	_Playerpos = Vector3(0.f, 0.f, 0.f);
		Vector3 _pos = Vector3(0.f, 0.f, 0.f);
		Vector3 _BodyRotation = Vector3(0.f, 0.f, 0.f);
		Vector2 _velocity = Vector2(0.f, 0.f);
		Vector3 _ShortHairCreatepos = Vector3(0.f, 0.f, 0.f);
		Vector2 _HomingEditPOS = Vector2(0.f, 0.f);


	private:
		int		_Dir = 1;							// 방향설정
		float	_time = 0.f;						// 공격패턴시 사용중	
		float	_Attacktime = 0.f;					// 공격패턴시 보조사용중
		bool	_Ground_check = false;				// 땅체크시에 쓰이고 있는 변수
		bool	_BackGround_check = true;			// 백그라운드 아이들시 사용되는 변수
		int		_Rushnumber = 0;					// 러쉬 공격시 1번 = a, 2번 = b, 3번 =c , 0 = 대기상태
		int		_bulletcheck = 0;


	public:
		static bool _AttackStageON;				// FLyDash의 경우 나가있는지 안에 있는지 확인할수 있는변 나가있는상태라면 위치 셋팅하여 안으로 들어오게 도와주는 역할의 변수 


	public:
		static int	_HitType;
		static float _Damage;
		static	class Monster_Hp_Bar* ShortHair_Hp;
		static	class Monster_Hp_Bar* ShortHair_Hp_Damage;

	public:
		static class Monster_Hit_Effect* _Hit_Effect;
		static class Player_Hit_Effect* _Hit_Effect_player;
		static class Hit_Sword* _Hit_Sword;
		static class Hit_Critical_Middle* _Critical_Middle;
		static class Hit_Critical_High* _Critical_High;
		static class Monster_Death_Effect* _Death_Effect;



	private:
	
		bool	_Sisters_Attack_A = false;
		bool	_Sisters_Attack_B = false;
		//bool	_Sisters_Attack_C_Switch = false;
		//bool	_Sisters_Attack_D_Switch = false;
		bool	_Bullet_Switch[3] = {};

		bool	_RushSwitch = false;

		bool	_CrossMeteorSwitch = false;
		bool	_CrossMeteorLanding = false;

		bool	_GroundMeteorSwitch = false;
		bool	_GroundMeteorLanding = false;
		bool	_GroundMeteorAttack_Right = false;
		bool	_GroundMeteorAttack_Left = false;

		bool	_VerticalMeteorSwitch = false;
		bool	_VerticalMeteorLanding = false;
		bool	_VerticalMeteorLandingSM = false;
		bool	_VerticalMeteor_Bullet = false;


		bool	_SkillA_Switch = false;
		bool	_SkillA_Landing = false;
		bool	_SkillHomingON = false;
		bool    _SkillHomingFire = false;
		int		_HomingNumber = 0;
		float   _HomingAngle[3];
		Vector2   _HomingVector[3];

		bool	_SkillB_Switch = false;
		bool	_SkillB_Dash = false;

		bool	_SkillC_Switch = false;

		bool	_Intro_Switch = false;
		bool	_Intro_Landing = false;

		bool	_Awaken_Switch = false;
		bool	_Awaken_Ready = false;
		int		_Awaken_Dir = 1;

		bool	_BackGround_Switch = false;
		bool	_BackGround_Idle = false;

		bool	_Joint_Attack = false;

		int		_SelectAttack = 0;

		bool	_DieOn = false;



	};
}