#pragma once
#include "Include_Common.h"
#include "HitBox_Player.h"


#include "Player_AfterImage.h"
#include "Monster_Hammer.h"
#include "Monster_GoldHammer.h"

#include "Hit_Sword.h"
#include "Hit_Critical_Middle.h"
#include "Hit_Critical_High.h"
#include "Hit_DarkPaladin.h"
#include "Slash_Effect.h"
#include "Mushroom_Spring.h"
#include "Sofa_Spring.h"

#include "..\Engine_SOURCE\jkAudioSource.h"

namespace jk
{
	class Animator;
	class Skul_Wolf : public Player
	{
	public:
		Skul_Wolf();
		virtual ~Skul_Wolf();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		enum class Skul_Wolf_State
		{
			Idle,
			Move,
			Jump,
			Fall,
			Falling,
			Dash,
			Attack_A,
			Attack_B,
			JumpAttack,
			Skill_A,
			Skill_B,
			Switch,
			Death,
			Stun,
			Hit,
		};

		void idle();
		void move();
		void jump();
		void fall();
		void falling();
		void dash();
		void attack_a();
		void attack_b();
		void jumpattack();
		void skill_a();
		void skill_b();
		void change();
		void death();
		void stun();
		void hit();

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;
			
		static void SetDirection(int dir, bool sw) { mDir = dir, _switch = sw; }

	private:
		Skul_Wolf_State _State;
		HitBox_Player* Hit_Box;
		Animator* at = nullptr;
		AudioSource* as = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		Vector3 pos = Vector3(0.f, 0.f, 0.f);
		Vector2 _velocity = Vector2(0.f, 0.f);

	private:
		Player_Hit_Effect* _Hit_Effect = nullptr;
		Hit_Sword* _Hit_Sword = nullptr;
		Hit_Critical_Middle* _Critical_Middle = nullptr;
		Hit_Critical_High* _Critical_High = nullptr;
		Slash_Effect* _Knight_Slash = nullptr;
		Hit_DarkPaladin* _DarkKnight = nullptr;
		GameObject* Hit_Particle = nullptr;

		Monster_Hammer::Monster_Hammer_State hammer_st = {};
		Monster_GoldHammer::Monster_GoldHammer_State Goldham_st = {};


	private:
		Player_AfterImage* AfterImage_TEST[10] = {};
		float timeSinceLastImage = 0.0f;
		const float delayBetweenImages = 0.03f;
		
	private:
		static int mDir;
		int HitDir = 1;
		static bool _switch;
		float _time = 0.f;
		float _attack_time = 0.f;
		bool _attack = false;
		int _jump = 0;
		int _fallcheck = 0;
		bool _dash = false;
		bool _Ground_check = false;
		bool _Wall_check = false;
		bool _Rightmove_Lock = false;
		bool _Leftmove_Lock = false;
		bool _Firsrt_Ground = false;

	private:
		bool _attack_Acheck = false;				//캐릭터의 어택상황을 체크하기 위해 필요한 변수
		bool _attack_Bcheck = false;
		bool _attack_Ccheck = false;
		bool _hit = false;

	private:
		void attack_choice();
		void dash_check();
		void Input_move();
	};
}