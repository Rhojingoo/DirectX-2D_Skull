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

		//static GameObject SetoWner(GameObject* ac) { oWner = ac; }

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
		Vector2 _velocity = Vector2(0.f, 0.f);

	private:
		static int			mDir;
		static bool			_switch;



		float	_distance = 0.f;			// �÷��̾���� �Ÿ� üũ
		bool	_Ground_check = false;		// ��üũ�ÿ� ���̰� �ִ� ����

		bool	_dash = false;
		float	_time = 0.f;				// ���ݽ� �����
		bool	_attack = false;			// ���ݿ��� idle�� ������ ����ġ ����
		int		_number_of_attack = 0;		// ����Ƚ���� ���� idle�� �����µ�, ����Ƚ���� üũ�ϴ� ����
		int		_attackorder = 0;			// �޺������� ��� ������ ������ �־� �ش� ������ �����ϵ��� �����ϴ� ���� 
		int		_choicecombo = 0;			// ���������� ������ �Ҽ� �ֵ��� �����ϴ� ����
		//bool _jump = 0;
		//int _fallcheck = 0;

	private:
		void choicecombo();
		void combo();
		void energyball();
		void explosionloop();

	};
}