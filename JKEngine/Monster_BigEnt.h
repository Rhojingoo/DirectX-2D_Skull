#pragma once
#include "Include_Common.h"
#include "Monster_BigEnt_EnergeBall.h"
#include "Monster_GiganticEnt_Stamp.h"
#include "Monster_Hit_Effect.h"
#include "Monster_Death_Effect.h"

namespace jk
{
	class Monster_BigEnt : public Monster
	{
	public:
		Monster_BigEnt();
		virtual ~Monster_BigEnt();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;


		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		enum class Monster_BigEnt_State
		{
			Idle,
			AttackA_Ready,
			AttackA,
			AttackA_End,
			AttackB_Ready,
			AttackB,
			Dead,
			Hit,
			Walk,
		};

		void idle();
		void attackA_ready();
		void attackA();
		void attackA_end();
		void attackB_ready();
		void attackB();
		void dead();
		void hit();
		void walk();

	private:
		float _MaxHp = 100;
		float _CurrenHp = 100;
		int	_bulletcheck = 0;

	private:
		Player_Hp_Bar* Player_Hp = nullptr;
		Monster_Hit_Effect* _Hit_Effect = nullptr;
		Monster_Death_Effect* _Death_Effect = nullptr;

	private:
		GameObject* Hit_Particle = nullptr;
		bool	_hit_particle = false;
		float	_particletime = 0.f;

	private:
		Monster_BigEnt_State _state = {};
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		Vector3 _pos = Vector3(0.f, 0.f, 0.f);
		Vector2 _velocity = Vector2(0.f, 0.f);
		Vector2 basic_pos[8] = {};


	private:
		HitBox_Monster* Hit_Box = nullptr;
		Monster_BigEnt_EnergeBall* Energe_Ball[8] = {};
		Monster_GiganticEnt_Stamp* Attack_Stamp = nullptr;

	private:
		static int			mDir;

		float	_distance = 0.f;			// �÷��̾���� �Ÿ� üũ
		bool	_Ground_check = false;		// ��üũ�ÿ� ���̰� �ִ� ����
		float	_time = 0.f;				// ���ݽ� �����
		float	_attack_time = 0.f;
		int		_choiceattack = 0;			// ���������� ������ �Ҽ� �ֵ��� �����ϴ� ����
		bool	_attack_Col = false;

	private:
		void attack_idle();
		void energeball_attack();
		void set_energeball_pos();
		void set_energeball_Vellocity();
	};
}