#pragma once
#include "Monster.h"


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
		float _MaxHp = 350;
		float _CurrenHp = 350;

	private:
		class HP_Frame* Hpbar_Frame = nullptr;
		class Monster_Hp_Bar* Monster_Hp = nullptr;
		class Monster_Hp_Bar* Monster_DamegeHp = nullptr;
		float _Damage = 0.f;
		bool _Hp_control = false;
		float _Hp_time = 0.f;


	private:
		GameObject* Hit_Particle = nullptr;
		bool	_hit_particle = false;
		float	_particletime = 0.f;

	private:
		Monster_GoldHammer_State _state = {};
		class Animator* at = nullptr;
		class AudioSource* as = nullptr;
		class RigidBody* _rigidbody = nullptr;
		class Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		Transform* Effect_tr = nullptr;
		Vector3 _pos = Vector3(0.f, 0.f, 0.f);
		Vector3 _Effect_pos = Vector3(0.f, 0.f, 0.f);
		Vector3 _first_place = Vector3(0.f, 0.f, 0.f);
		Vector2 _velocity = Vector2(0.f, 0.f);

	private:
		class HitBox_Monster* Hit_Box = nullptr;
		class Monster_Hit_Effect* _Hit_Effect = nullptr;
		class Monster_Death_Effect* _Death_Effect = nullptr;
		class Monster_Tackle_Flash_Effect* Tackle_Flash = nullptr;
		class Monster_Hammer_Effect* _Hammer_Effect = nullptr;
		bool _followskul = false;

	private:
		int		_Dir = 1;
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
		void SetDirection();
		void Particle_Control();
		void Hpcontrol();
		void Effect_Control();
		void Complete_attack();
	};
}