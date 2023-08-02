#pragma once
#include "Include_Common.h"

namespace jk
{
	class Knight_male : public Mini_Boss
	{
	public:
		Knight_male();
		virtual ~Knight_male();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;


		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		static GameObject SetoWner(GameObject* ac) { oWner = ac; }

		enum class Knight_State
		{
			Idle,
			Dash,
			BackDash,
			Jump,
			JumpAttack,
			Die,
			Attack_A,
			Attack_B,
			Attack_C,
			Attack_D,
			Attack_E,
			EnergeBall,
			Explosion_Loop,
			Glorggy,
			Hit, 
			Intro,
			Potion,
			Stinger,
			Stinger_Ready,
		};

		void idle();
		void dash();
		void backdash();
		void jump();
		void jumpattack();
		void die();
		void attack_a();
		void attack_b();
		void attack_c();
		void attack_d();
		void attack_e();
		void energeball();
		void explosion_loop();
		void glorggy();
		void hit();
		void intro();
		void potion();
		void stinger();
		void stinger_Ready();

	private:
		Knight_State _state;
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		Vector3 pos = Vector3(0.f, 0.f, 0.f);
		Vector3 _playerpos = Vector3(0.f, 0.f, 0.f);
		Vector2 _velocity = Vector2(0.f, 0.f);

	private:
		static int mDir;
		static bool _switch;
		static GameObject* oWner;
		float _time = 0.f;
		bool _attack = false;
		int _jump = 0;
		int _fallcheck = 0;
		bool _Ground_check = false;
		int _choicecombo = 0;
		int _attackorder = 0;

	private:
		void choicecombo();
		void combo1();
	};
}