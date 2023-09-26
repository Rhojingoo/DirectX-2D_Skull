#pragma once
#include "Include_Common.h"
#include "Monster.h"
#include "Monster_Hit_Effect.h"
#include "Monster_Death_Effect.h"
#include "Monster_Tackle_Flash_Effect.h"
#include "Monster_Hammer_Effect.h"

#include "Monster_Hp_Bar.h"
#include "HP_Frame.h"

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
		

		enum class Monster_Hammer_State
		{
			Idle,
			Attack_Ready,
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
		void attack_ready();
		void attack();
		void tackle_ready();
		void tackle();
		void tackle_end();
		void walk();
		void walk_R();
		void walk_L();
		void dead();

		Monster_Hammer_State GetState() { return _state; }

	private:
		float _MaxHp = 200;
		float _CurrenHp = 200;

	private:
		HP_Frame* Hpbar_Frame = nullptr;
		Monster_Hp_Bar* Monster_Hp = nullptr;
		Monster_Hp_Bar* Monster_DamegeHp = nullptr;
		float _Damage = 0.f;
		bool _Hp_control = false;
		float _Hp_time = 0.f;


	private:
		GameObject* Hit_Particle = nullptr;
		bool	_hit_particle = false;
		float	_particletime = 0.f;

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
		Monster_Hit_Effect* _Hit_Effect = nullptr;
		Monster_Death_Effect* _Death_Effect = nullptr;
		Monster_Tackle_Flash_Effect* Tackle_Flash = nullptr;
		Monster_Hammer_Effect* _Hammer_Effect = nullptr;
		bool _followskul = false;

	private:
		int		mDir = 1;
		int		_attackdir = 1;
		int		_walkdir = 1;
		int		_bulletcheck = 0;


		float	_distance = 0.f;			// �÷��̾���� �Ÿ� üũ
		float   _walkdistance = 0.f;		// �ڽ��� ù��ġ�� �� �Ÿ� üũ

		bool	_Ground_check = false;		// ��üũ�ÿ� ���̰� �ִ� ����


		float	_time = 0.f;				// ���ݽ� �����
		float	_attacktime = 0.f;
		int		_AttackCheck = 0;			// ���������� ������ �Ҽ� �ֵ��� �����ϴ� ����
		bool	_attack_Col= false;

	private:
		void SetDirection();
		void Particle_Control();
		void Hpcontrol();
		void Effect_Control();


		void Complete_attack();
		void SetEffect_pos();
	};
}