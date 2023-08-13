#pragma once
#include "Include_Common.h"
#include "Layana_Sisters.h"
#include "Homing_Pierce.h"

namespace jk
{
	class Layana_LongHair : public Layana_Sisters
	{
	public:
		Layana_LongHair();
		virtual ~Layana_LongHair();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void idle();

		void Rushready();
		void Rush_A();
		void Rush_B();
		void Rush_C();
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

	public:
		void Rush_Combo();
		void Meteor_Cross_Combo();
		void Meteor_Ground_Combo();
		void Meteor_Vertical_Combo();

	public:
		void CreateHoming();
		void SettingHoming(Transform* set,int angle_of_number);

	private:
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		Homing_Pierce* Homing[3];


	private:
		Vector3	_Playerdistance = Vector3(0.f, 0.f, 0.f);
		Vector3	_Playerpos = Vector3(0.f, 0.f, 0.f);
		Vector3 _pos = Vector3(0.f, 0.f, 0.f);
		Vector3 _BodyRotation = Vector3(0.f, 0.f, 0.f);
		Vector2 _velocity = Vector2(0.f, 0.f);
		Vector3 _LongHairCreatepos = Vector3(0.f, 0.f, 0.f);
		Vector2 _HomingEditPOS = Vector2(0.f, 0.f);

	private:
		int		_Dir = 1;							// 방향설정
		float	_time = 0.f;						// 공격패턴시 사용중	
		float	_Attacktime = 0.f;					// 공격패턴시 보조사용중
		bool	_Ground_check = false;				// 땅체크시에 쓰이고 있는 변수
		int		_Rushnumber = 0;					// 러쉬 공격시 1번 = a, 2번 = b, 3번 =c , 0 = 대기상태


	private:
		bool	_RushSwitch = false;

		bool	_CrossMeteorSwitch = false;
		bool	_CrossMeteorLanding = false;

		bool	_GroundMeteorSwitch = false;
		bool	_GroundMeteorLanding = false;
		bool	_GroundMeteorAttack_Right = false;
		bool	_GroundMeteorAttack_Left = false;

		bool	_VerticalMeteorSwitch = false;
		bool	_VerticalMeteorLanding = false;

		bool	_SkillA_Switch = false;
		bool	_SkillA_Landing = false;
		bool	_SkillHomingON = false;
		bool    _SkillHomingFire = false;
		int		_HomingNumber = 0;
		float   _HomingAngle[3];

		int		_SelectAttack = 0;
	};

}