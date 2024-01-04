#pragma once
#include "Monster.h"

namespace jk
{
	class Monster_BlossomEnt : public Monster
	{
	public:
		Monster_BlossomEnt();
		virtual ~Monster_BlossomEnt();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;


		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		enum class Monster_BlossomEnt_State
		{
			Idle,
			Attack_Ready,
			Attack,
			Dead,
			Hit,
			WalkR,
			WalkL,
		};

		void idle();
		void attack_ready();
		void attack();
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
		Monster_BlossomEnt_State _state;
		class Animator* at = nullptr;
		class AudioSource* as = nullptr;
		class RigidBody* _rigidbody = nullptr;
		class Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		Vector3 _pos = Vector3(0.f, 0.f, 0.f);
		Vector3 _first_place = Vector3(0.f, 0.f, 0.f);
		Vector2 _velocity = Vector2(0.f, 0.f);

	private:
		class Monster_Blossomeenct_Attack* Blossomeenct_Attack = nullptr;

	private:
		static int			mDir;
		static bool			_switch;
		int _walkdir = 1;

		float	_distance = 0.f;			// �÷��̾���� �Ÿ� üũ
		float   _walkdistance = 0.f;		// �ڽ��� ù��ġ�� �� �Ÿ� üũ
		bool	_Ground_check = false;		// ��üũ�ÿ� ���̰� �ִ� ����
		float	_Attackset = 0.f;			// ���ݽ� �����
		float	_time = 0.f;				// �ȱ�� �����
		bool	_attack = false;			// ���ݿ��� idle�� ������ ����ġ ����	


	private:
		void SetDirection();
		void Particle_Control();
		void Hpcontrol();
		void Effect_Control();

		void attack_setting();
		void attack_idle();
	};
}