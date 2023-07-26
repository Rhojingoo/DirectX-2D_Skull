#pragma once
#include "Include_Common.h"

namespace jk
{
	class Animator;
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
			Falling,
			Dash,
			Attack_A,
			Attack_B,
			Attack_C,
			JumpAttack,
			Skill_A,
			Skill_B,
			Death,
		};

		void idle();
		void move();
		void jump();
		void falling();
		void dash();
		void attack_a();
		void attack_b();
		void attack_c();
		void jumpattack();
		void skill_a();
		void skill_b();
		void death();

	private:
		Skul_Spear_State _State;
		Animator* at;
		int mDir;
		float _time;
		bool _attack;
		void attack_choice();
		void dash_check();
	};
}