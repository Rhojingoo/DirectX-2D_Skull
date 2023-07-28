#pragma once
#include "Include_Common.h"
#include "Skul_head.h"


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
		void death();

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		static void SetDirection(int dir) { mDir = dir; }
		static int GetDirection() { return mDir; }

	private:
		Skul_Basic_State _State;
		Skul_head* Skul_Head;
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;	
		Vector3 pos = Vector3(0.f, 0.f, 0.f);
		Vector2 _velocity = Vector2(0.f, 0.f);

	private:
		static int mDir;
		float _time = 0.f;
		bool _attack = false;
		int _jump = 0;
		int _fallcheck = 0;
		bool _Ground_check = false;
		bool _Skulhead = false;

	private:
		void attack_choice();
		void Input_move();

	};
}