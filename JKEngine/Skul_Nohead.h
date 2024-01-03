//#pragma once
//#include "Include_Common.h"
//
//
//namespace jk
//{
//	class Animator;
//	class Skul_Nohead : public Player
//	{
//	public:
//		Skul_Nohead();
//		virtual ~Skul_Nohead();
//
//		virtual void Initialize()	override;
//		virtual void Update()		override;
//		virtual void LateUpdate()	override;
//		virtual void Render()		override;
//
//		enum class Skul_Nohead_State
//		{
//			Idle,
//			Move,
//			Jump,
//			Falling,
//			Dash,
//			Attack_A,
//			Attack_B,
//			JumpAttack,
//			Skill_A,
//			Skill_B,
//			Death,
//		};
//
//		void idle();
//		void move();
//		void jump();
//		void falling();
//		void dash();
//		void attack_a();
//		void attack_b();
//		void jumpattack();
//		void skill_a();
//		void skill_b();
//		void death();
//
//
//		virtual void OnCollisionEnter(Collider2D* other) override;
//		virtual void OnCollisionStay(Collider2D* other) override;
//		virtual void OnCollisionExit(Collider2D* other) override;
//
//	private:
//		Skul_Nohead_State _State;
//		Animator* at;
//		int _Dir;
//		float _time;
//		bool _attack;
//		void attack_choice();
//		void dash_check();
//	};
//}