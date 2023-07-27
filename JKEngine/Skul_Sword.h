#pragma once
class Skul_Sword
{
};

#pragma once
#include "Include_Common.h"

namespace jk
{
	class Animator;
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

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;
	private:
		Skul_Sword_State _State;
		Animator* at;
		int mDir;
		float _time;
		bool _attack;
		void attack_A_choice();
		void attack_B_choice();
		void dash_check();
	};
}