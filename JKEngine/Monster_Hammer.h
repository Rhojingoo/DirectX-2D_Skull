#pragma once
#include "Include_Common.h"
#include "HitBox_Monster.h"
#include "Monster_Tackle_Flash_Effect.h"

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
			Tackle_Ready,
			Tackle,
			Tackle_End,
			Walk,
			WalkR,
			WalkL,
			Dead,
		};

		void idle();
		void attack();
		void tackle_ready();
		void tackle();
		void tackle_end();
		void walk();
		void walk_R();
		void walk_L();
		void dead();


	private:
		Monster_Hammer_State _state = {};
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		Transform* Effect_tr = nullptr;
		Vector3 _pos = Vector3(0.f, 0.f, 0.f);
		Vector3 _Effect_pos = Vector3(0.f, 0.f, 0.f);
		Vector3 _first_place = Vector3(0.f, 0.f, 0.f);
		Vector2 _velocity = Vector2(0.f, 0.f);

	private:
		HitBox_Monster* Hit_Box = nullptr;
		Monster_Tackle_Flash_Effect* Tackle_Flash = nullptr;
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
		int		_AttackCheck = 0;			// ���������� ������ �Ҽ� �ֵ��� �����ϴ� ����
		bool	_attack_Col= false;

	private:
		void Complete_attack();
		void SetDirection();
		void SetEffect_pos();
	};
}