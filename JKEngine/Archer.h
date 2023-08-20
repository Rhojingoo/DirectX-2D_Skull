#pragma once
#include "Include_Common.h"
#include "Archer_Arrow.h"
#include "Archer_Arrow_Upward_Sign.h"
#include "Archer_Upward_Impact_Bullet.h"
#include "Archer_Arrow_Bye.h"
#include "Archer_Trap.h"


namespace jk
{
	class Archer : public Mini_Boss
	{
	public:
		Archer();
		virtual ~Archer();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;


		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		enum class Archer_State
		{
			Idle,		
			BackDash,
			Die,
			Attack_A_Ready,
			Attack_A,
			Attack_A_End,
			Attack_B_Ready,
			Attack_B,
			Attack_B_End,
			
			Attack_C,
			Groggy,
			Hit,
			Intro,
			Potion,
		};

		void idle();
		void backdash();
		void die();
		void attack_a_ready();
		void attack_a();
		void attack_a_end();


		void attack_b_ready();
		void attack_b();
		void attack_b_end();


		void attack_c();
		void groggy();
		void hit();
		void intro();
		void potion();



	private:
		Archer_State _state;
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* _tr = nullptr;
		Vector3 pos = Vector3(0.f, 0.f, 0.f);	
		Vector2 _velocity = Vector2(0.f, 0.f);

	private:
		Archer_Arrow* _archer_arrow = nullptr;
		Archer_Arrow_Upward_Sign* Upward_Sign = nullptr;
		Archer_Upward_Impact_Bullet* Upward_Impact_Bullet = nullptr;
		Archer_Arrow_Bye* Arrow_Bye_effect = nullptr;
		Archer_Trap* Bullet_Trap[6];

	private:
		static int			mDir;
		static bool			_switch;
		float	_time = 0.f;						// ���ݽ� �����
		float	_attack_time = 0.f;
		bool	_attack = false;					// ���ݿ��� idle�� ������ ����ġ ����
		int		_number_of_attack = 0;				// ����Ƚ���� ���� idle�� �����µ�, ����Ƚ���� üũ�ϴ� ����
		int		_choicecombo = 0;					// ���������� ������ �Ҽ� �ֵ��� �����ϴ� ����
		float	_distance = 0.f;					// �÷��̾���� �Ÿ� üũ
		bool	_Ground_check = false;				// ��üũ�ÿ� ���̰� �ִ� ����
		int		_hit = 0;							// ���ݹ��� �� ȸ���ϱ� ���� ����
		bool    _hit_switch = false;
		int		_Numberof_BackDash = 0;
		

		
		bool    _BackDash = true;
		bool	_player_attack_check = false;		// �÷��̾ ���ݽ� �ݶ��̴� ó���� Ȯ���ϰ� �ϴ°�.
		bool	_attack_a = false;
		bool	_attack_b_sign = false;
		bool	_attack_b = false;

	private:
		Skul_Basic::Skul_Basic_State Skul_BasicState;

	private:
		void choicecombo();
		void shootbow_forward();
		void shootbow_upward();
		void pushaway();
		void complete_hit();
		void complete_attackA();
	};
}