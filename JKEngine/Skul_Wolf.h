#pragma once
#include "Include_Common.h"

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

	private:
		Skul_Wolf_State _State;
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		Vector3 pos = Vector3(0.f, 0.f, 0.f);
		
	private:
		static int mDir;
		static bool _switch;
		float _time;
		bool _attack;


	private:
		void attack_choice();
		void dash_check();
		void Input_move();
	};
}