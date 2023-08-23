#pragma once
#include "Include_Common.h"
#include "Monster_BigEnt_EnergeBall.h"
#include "Monster_GiganticEnt_Stamp.h"

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

		float	_distance = 0.f;			// 플레이어와의 거리 체크
		bool	_Ground_check = false;		// 땅체크시에 쓰이고 있는 변수
		float	_time = 0.f;				// 공격시 사용중
		float	_attack_time = 0.f;
		int		_choiceattack = 0;			// 공격종류의 선택을 할수 있도록 설정하는 변수
		bool	_attack_Col = false;

	private:
		void attack_idle();
		void energeball_attack();
		void set_energeball_pos();
		void set_energeball_Vellocity();
	};
}