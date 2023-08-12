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

			Meteor_Cross_Ready,
			Meteor_Cross_Jump,
			Meteor_Cross_Attack,
			Meteor_Cross_Landing,
			Meteor_Cross_End,

			BackGround_Idle,
			BackGround_Move,
			BackStep,

			Meteor_Ground01_Ready,
			Meteor_Ground02_Attack,
			Meteor_Ground03_Landing,
			Meteor_Ground04_End,


			Meteor_Vertical00_Jump,
			Meteor_Vertical01_Ready,
			Meteor_Vertical02_Attack,
			Meteor_Vertical03_Landing,
			Meteor_Vertical04_End,		


			Skill_A_Bullet,
			Skill_A_Bullet_End,

			Skill_B_RisingPierce,

			Skill_C_DimensionPierce,

			Intro_Dash,
			Intro_Fall,
			Intro_Landing,

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

		void CrossJump();
		void CrossReady();
		void CrossAttack();
		void CrossLanding();
		void CrossEnd();


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


	private:
		GameObject* _Gobjs[3];
		static Vector3 _pos;
		static Vector3 _Rotation;
		Vector3	_Playerdistance = Vector3(0.f, 0.f, 0.f);
	};
}