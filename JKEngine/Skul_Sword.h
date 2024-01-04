#pragma once
#include "Player.h"

namespace jk
{
	class Skul_Sword : public Player
	{
	public:
		Skul_Sword();
		virtual ~Skul_Sword();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		enum class Skul_Sword_State
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
		Skul_Sword_State _State = {};
		class Animator* at = nullptr;
		class RigidBody* _rigidbody = nullptr;
		class Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		Vector3 pos = Vector3(0.f, 0.f, 0.f);
		Vector2 _velocity = Vector2(0.f, 0.f);

	private:
		static int mDir;
		static bool _switch;
		float _time = 0.f;
		bool _attackB = false;
		bool _attackC = false;
		int _jump = 0;
		int _fallcheck = 0;
		bool _dash = false;
		bool _Ground_check = false;


		void attack_A_choice();
		void attack_B_choice();
		void Input_move();
		void switch_on_off();
	};
}