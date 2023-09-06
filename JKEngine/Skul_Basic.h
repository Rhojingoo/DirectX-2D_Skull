#pragma once
#include "Include_Common.h"
#include "Skul_head.h"
#include "Player_Hit_Effect.h"
#include "HitBox_Monster.h"
#include "Monster_Hammer.h"
#include "Monster_GoldHammer.h"

namespace jk
{
	class Animator;
	class Skul_Basic : public Player
	{
	public:
		Skul_Basic();
		virtual ~Skul_Basic();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		enum class Skul_Basic_State
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

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		static void SetDirection(int dir, bool sw) { mDir = dir, _switch = sw; }
		static int GetDirection() { return mDir; }
		Skul_Basic_State Get_Skul_state() { return _State; }

	private:
		Player_Hit_Effect* _Hit_Effect = nullptr;
		Monster_Hammer::Monster_Hammer_State hammer_st = {};
		Monster_GoldHammer::Monster_GoldHammer_State Goldham_st = {};
		
			
	private:
		Skul_Basic_State _State;
		Skul_head* Skul_Head;
		GameObject* Attack_Skul;
		GameObject* Hit_Box;
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;	
		Vector3 pos = Vector3(0.f, 0.f, 0.f);
		Vector3 _skulheadtemp = Vector3(0.f, 0.f, 0.f);
		Vector2 _velocity = Vector2(0.f, 0.f);
		
		
		int ColID = 0;

	private:
		static int mDir;
		static bool _switch;
		
		float _time = 0.f;
		float _attack_time = 0.f;
		bool _attack = false;
		int _jump = 0;
		bool _Skulhead = false;
		int _fallcheck = 0;
		bool _Ground_check = false;
		bool _SkyGround_check = false;
		bool _Wall_check = false;
		bool _Rightmove_Lock = false;
		bool _Leftmove_Lock = false;

		bool _attack_Acheck = false;				//캐릭터의 어택상황을 체크하기 위해 필요한 변수
		bool _attack_Bcheck = false;


	private:
		void attack_choice();
		void Input_move();
		void switch_on_off();
	};
}