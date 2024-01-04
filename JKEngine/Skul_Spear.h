#pragma once
#include "Player.h"

namespace jk
{
	class Skul_Spear : public Player
	{
	public:
		Skul_Spear();
		virtual ~Skul_Spear();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		enum class Skul_Spear_State
		{
			Idle,
			Move,
			Jump,
			Fall,
			Falling,
			Dash,
			Attack_A,
			Attack_B,
			Attack_C,
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
		void attack_c();
		void jumpattack();
		void skill_a();
		void skill_b();
		void change();
		void death();

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		static void SetDirection(int dir, bool sw) { mDir = dir, _switch = sw; }


	private:
		Skul_Spear_State _State;
		class Animator* at = nullptr;
		class RigidBody* _rigidbody = nullptr;
		class Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		Vector3 pos = Vector3(0.f, 0.f, 0.f);
		Vector2 _velocity = Vector2(0.f, 0.f);


	private:
		class Player_AfterImage* AfterImage_TEST[10] = {};
		float timeSinceLastImage = 0.0f; 
		const float delayBetweenImages = 0.03f;


	private:
		static int mDir;
		static bool _switch;
		float _time = 0.f;
		bool _attack = false;
		int _jump = 0;
		int _fallcheck = 0;
		bool _dash = false;
		bool _Ground_check = false;
		bool _Wall_check = false;
		bool _Rightmove_Lock = false;
		bool _Leftmove_Lock = false;


	private:
		void attack_choice();
		void dash_check();
		void Input_move();
		void switch_on_off();
	};
}