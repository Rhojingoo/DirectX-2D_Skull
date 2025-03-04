#pragma once
#include "Monster.h"


namespace jk
{
	class Monster_GreenTree : public Monster
	{
	public:
		Monster_GreenTree();
		virtual ~Monster_GreenTree();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;


		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		enum class Monster_GreenTree_State
		{
			Idle,
			Attack_Ready,
			Attack,
			Attack_End,
			Dead,
			Hit,
			WalkR,
			WalkL,
		};

		void idle();
		void attack_ready();
		void attack();
		void attack_end();
		void dead();
		void hit();
		void walk_R();
		void walk_L();

	private:
		float _MaxHp = 100;
		float _CurrenHp = 100;
		int	_bulletcheck = 0;

	private:
		class HP_Frame* Hpbar_Frame = nullptr;
		class Monster_Hp_Bar* Monster_Hp = nullptr;
		class Monster_Hp_Bar* Monster_DamegeHp = nullptr;
		float _Damage = 0.f;
		bool _Hp_control = false;
		float _Hp_time = 0.f;


	private:
		class Monster_Hit_Effect* _Hit_Effect = nullptr;
		class Monster_Death_Effect* _Death_Effect = nullptr;
	
	private:
		GameObject* Hit_Particle = nullptr;
		bool	_hit_particle = false;
		float	_particletime = 0.f;

	private:
		Monster_GreenTree_State _state;
		class Animator* at = nullptr;
		class AudioSource* as = nullptr;
		class RigidBody* _rigidbody = nullptr;
		class Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		Vector3 _pos = Vector3(0.f, 0.f, 0.f);
		Vector3 _first_place = Vector3(0.f, 0.f, 0.f);
		Vector2 _velocity = Vector2(0.f, 0.f);

	private:
		class Monster_GroundAttack_Sign* GroundAttack_Sign = nullptr;
		class Monster_Ent_GroundAttack* GroundAttack = nullptr;
		Vector3 _AttackSign_place = Vector3(0.f, 0.f, 0.f);
		Vector3 _Attack_place = Vector3(0.f, 0.f, 0.f);


	private:
		int	mDir = 1;
		int _walkdir = 1;
		int _attackdir = 1;

		float	_distance = 0.f;			// 플레이어와의 거리 체크
		float   _walkdistance = 0.f;		// 자신의 첫위치와 의 거리 체크
		bool	_Ground_check = false;		// 땅체크시에 쓰이고 있는 변수
		float	_time = 0.f;				// 공격시 사용중
		float	_attacktime = 0.f;
		int		_choiceattack = 0;			
		bool	_attackcheck = false;
		bool	_followskul = false;

	private:
		void SetDirection();
		void Particle_Control();
		void Hpcontrol();
		void Effect_Control();
		void Complete_Attack();
	};
}