#pragma once
#include "Include_Common.h"
#include "Archer_Arrow.h"

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
			Attack_A,
			Attack_B,
			Attack_C,
			Groggy,
			Hit,
			Intro,
			Potion,
		};

		void idle();
		void backdash();
		void die();
		void attack_a();
		void attack_b();
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
		Transform* tr = nullptr;
		Vector3 pos = Vector3(0.f, 0.f, 0.f);
		//Vector3 _playerpos = Vector3(0.f, 0.f, 0.f);
		Vector2 _velocity = Vector2(0.f, 0.f);

	private:
		Archer_Arrow* _archer_arrow = nullptr;
	private:
		static int			mDir;
		static bool			_switch;
		float	_time = 0.f;						// ���ݽ� �����
		bool	_attack = false;					// ���ݿ��� idle�� ������ ����ġ ����
		int		_number_of_attack = 0;				// ����Ƚ���� ���� idle�� �����µ�, ����Ƚ���� üũ�ϴ� ����
		float	_distance = 0.f;					// �÷��̾���� �Ÿ� üũ
		bool	_Ground_check = false;				// ��üũ�ÿ� ���̰� �ִ� ����
		int		_choicecombo = 0;					// ���������� ������ �Ҽ� �ֵ��� �����ϴ� ����
		int		_hit = 0;							// ���ݹ��� �� ȸ���ϱ� ���� ����
		bool    _hit_switch = false;
		bool	_player_attack_check = false;		// �÷��̾ ���ݽ� �ݶ��̴� ó���� Ȯ���ϰ� �ϴ°�.

	private:
		Skul_Basic::Skul_Basic_State Skul_BasicState;

	private:
		void choicecombo();
		void shootbow_forward();
		void shootbow_upward();
		void pushaway();
		void complete_hit();

	};
}