#pragma once
#include "Include_Common.h"
#include "Player_Hp_Bar.h"
#include "Monster_Hp_Bar.h"
#include "HP_Frame.h"

#include "Monster_Hit_Effect.h"
#include "Monster_Death_Effect.h"

namespace jk
{
	class Monster_LionSpear : public Monster
	{
	public:
		Monster_LionSpear();
		virtual ~Monster_LionSpear();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;


		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		enum class Monster_Lion_State
		{
			Idle,
			AttackA,
			AttackA_Ready,
			AttackB,
			AttackB_Ready,
			Dead,
			Hit,
			Walk,
			WalkR,
			WalkL,
		};

		void idle();
		void attackA();
		void attackA_ready();
		void attackB();
		void attackB_ready();
		void dead();
		void hit();
		void walk();
		void walk_R();
		void walk_L();

	private:
		float _MaxHp = 350;
		float _CurrenHp = 350;
		int	_bulletcheck = 0;

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
		Monster_Lion_State _state;
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* _tr = nullptr;
		Vector3 _pos = Vector3(0.f, 0.f, 0.f);
		Vector3 _first_place = Vector3(0.f, 0.f, 0.f);
		Vector2 _velocity = Vector2(0.f, 0.f);

	private:
		HitBox_Monster* Hit_Box = nullptr;
		Monster_Hit_Effect* _Hit_Effect = nullptr;
		Monster_Death_Effect* _Death_Effect = nullptr;
		bool _followskul = false;

	private:
		int		_AttackSellect = 0;
		int		mDir = 1;
		int		_attackdir = 1;
		int		_walkdir = 1;
		float	_distance = 0.f;			// �÷��̾���� �Ÿ� üũ
		float   _walkdistance = 0.f;		// �ڽ��� ù��ġ�� �� �Ÿ� üũ
		bool	_Ground_check = false;		// ��üũ�ÿ� ���̰� �ִ� ����
		float	_time = 0.f;				// ���ݽ� �����
		float	_attacktime = 0.f;
		bool	_attack_ColA = false;
		bool	_attack_ColB = false;

	private:
		void SetDirection();
		void Particle_Control();
		void Hpcontrol();
		void Effect_Control();


		void complete_attack();
		void complete_hit();
	};
}