#pragma once
#include "Include_Common.h"

namespace jk
{
	class Monster_Hammer : public Monster
	{
	public:
		Monster_Hammer();
		virtual ~Monster_Hammer();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;


		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		//static GameObject SetoWner(GameObject* ac) { oWner = ac; }

		enum class Monster_Hammer_State
		{
			Idle,
			Attack,
			Tackle,
			Walk,
			Dead,
		};

		void idle();
		void attack();
		void tackle();
		void walk();
		void dead();


	private:
		Monster_Hammer_State _state;
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		Vector3 pos = Vector3(0.f, 0.f, 0.f);
		//Vector3 _playerpos = Vector3(0.f, 0.f, 0.f);
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