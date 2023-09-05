#pragma once
#include "Include_Common.h"
#include "Monster.h"
#include "Player_Hp_Bar.h"
#include "Monster_Hit_Effect.h"
#include "Monster_Death_Effect.h"
#include "Monster_Tackle_Flash_Effect.h"
#include "Monster_Hammer_Effect.h"

namespace jk
{
	class Monster_GoldHammer : public Monster
	{
	public:
		Monster_GoldHammer();
		virtual ~Monster_GoldHammer();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;


		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		//static GameObject SetoWner(GameObject* ac) { oWner = ac; }

		enum class Monster_GoldHammer_State
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

		Monster_GoldHammer_State GetState() { return _state; }

	private:
		float _MaxHp = 200;
		float _CurrenHp = 200;

	private:
		Monster_GoldHammer_State _state = {};
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
		Player_Hp_Bar* Player_Hp = nullptr;
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


		float	_distance = 0.f;			// 플레이어와의 거리 체크
		float   _walkdistance = 0.f;		// 자신의 첫위치와 의 거리 체크

		bool	_Ground_check = false;		// 땅체크시에 쓰이고 있는 변수


		float	_time = 0.f;				// 공격시 사용중
		float	_attacktime = 0.f;
		int		_AttackCheck = 0;			// 공격종류의 선택을 할수 있도록 설정하는 변수
		bool	_attack_Col = false;

	private:
		void Complete_attack();
		void SetDirection();
		void SetEffect_pos();
	};
}