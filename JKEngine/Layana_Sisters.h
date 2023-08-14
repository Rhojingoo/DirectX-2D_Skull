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

	
			Intro_Dash,
			Intro_Fall,
			Intro_Landing,

			BackGround_Idle,
			BackGround_Move,



			Awaken,
			AwakenJump,
			AwakenReady,
			Die,
		};

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

		void Skill_B();
		void Skill_B_End();

		void Skill_C();


		void Intro_Dash();
		void Intro_Landing();
		void Intro_Fall();


		void die();

		int random(int a, int b);

		static void SetPlayerPos(Vector3 set) { _playerpos = set; }
		static Vector3 GetPlayerPos() { return _playerpos; }
		static void SetPos(Vector3 set) { _pos = set; }
		static Vector3 GetPos() { return _pos; }
		static void SetRotation(Vector3 set) { _Rotation = set; }
		static Vector3 GetRotations() { return _Rotation; }
		
		
	public:
		static Layana_Sisters_State _state;
		static int	mDir;
		static float _time;
		static Vector3 GroundAttackpos_Right;
		static Vector3 GroundAttackpos_Left;

	private:
		GameObject* _Gobjs[3];
		static Vector3 _pos;
		static Vector3 _Rotation;
		Vector3	_Playerdistance = Vector3(0.f, 0.f, 0.f);
	};
}