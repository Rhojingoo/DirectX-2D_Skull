#pragma once
#include "Include_Common.h"
#include "Player_Hp_Bar.h"


namespace jk
{
	class Monster_Goldwarrior : public Monster
	{
	public:
		Monster_Goldwarrior();
		virtual ~Monster_Goldwarrior();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;


		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		enum class Monster_Goldwarrior_State
		{
			Idle,
			Attack,
			Attack_Ready,
			Dead,
			Hit,
			Walk,
			WalkR,
			WalkL,
		};

		void idle();
		void attack();
		void attack_ready();
		void dead();
		void hit();
		void walk();
		void walk_R();
		void walk_L();

	private:
		float _Hp = 100;




	private:
		Monster_Goldwarrior_State _state;
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* _tr = nullptr;
		Vector3 _pos = Vector3(0.f, 0.f, 0.f);
		Vector3 _first_place = Vector3(0.f, 0.f, 0.f);
		Vector2 _velocity = Vector2(0.f, 0.f);

	private:
		HitBox_Monster* Hit_Box = nullptr;
		Player_Hp_Bar* Player_Hp = nullptr;
		bool _followskul = false;

	private:
		int		mDir = 1;
		int		_attackdir = 1;
		int		_walkdir = 1;
		float	_distance = 0.f;			// �÷��̾���� �Ÿ� üũ
		float   _walkdistance = 0.f;		// �ڽ��� ù��ġ�� �� �Ÿ� üũ
		bool	_Ground_check = false;		// ��üũ�ÿ� ���̰� �ִ� ����
		float	_time = 0.f;				// ���ݽ� �����
		float	_attacktime = 0.f;
		bool	_attack_Col = false;

	private:
		void complete_attack();
		void complete_hit();
	};
}