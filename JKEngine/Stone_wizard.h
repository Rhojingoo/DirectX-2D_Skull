#pragma once
#include "Monster.h"

namespace jk
{
	class Stone_wizard : public Monster
	{
	public:
		Stone_wizard();
		virtual ~Stone_wizard();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;


		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		//static GameObject SetoWner(GameObject* ac) { oWner = ac; }

		enum class Stone_wizard_State
		{
			Idle,
			Attack_Ready,
			Attack,
			Hit,
			Teleport_In,
			Teleport_Out,
			Dead,
		};

		void idle();
		void attack_ready();
		void attack();
		void hit();
		void dead();
		void teleport_in();
		void teleport_out();



	private:
		float _MaxHp = 100;
		float _CurrenHp = 100;
		int	_bulletcheck = 0;

	private:
		Stone_wizard_State _state;
		class Animator* at = nullptr;
		class AudioSource* as = nullptr;
		class RigidBody* _rigidbody = nullptr;
		class Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		Transform* Effect_tr = nullptr;
		Vector3 pos = Vector3(0.f, 0.f, 0.f);
		Vector2 _velocity = Vector2(0.f, 0.f);

	private:
		class HitBox_Monster* Hit_Box = nullptr;
		class Monster_Hit_Effect* _Hit_Effect = nullptr;
		class Monster_Death_Effect* _Death_Effect = nullptr;
		GameObject* Hit_Particle = nullptr;

	private:
		
		class HP_Frame* Hpbar_Frame = nullptr;
		class Monster_Hp_Bar* Monster_Hp = nullptr;
		class Monster_Hp_Bar* Monster_DamegeHp = nullptr;
		float _Damage = 0.f;
		bool _Hp_control = false;
		float _Hp_time = 0.f;


	private:
		class Monster_StoneWizard_Teleport* Wizard_Teleport = nullptr;
		class Monster_StoneWizard_Icicle_Effect* Icicle_Effect = nullptr;
		class Monster_Stone_wizard_IcicleBullet* Icicle_Bullet = nullptr;


	private:
		static int			mDir;

		float	_distance = 0.f;			// �÷��̾���� �Ÿ� üũ
		bool	_Ground_check = false;		// ��üũ�ÿ� ���̰� �ִ� ����
		float	_time = 0.f;				// ���ݽ� �����
		float	_attacktime = 0.f;
		float	_particletime = 0.f;
	
	private:	
		bool	_teleportCheck = false;			// �ڷ����� �ξƿ��� �Ҽ� �ֵ��� �����ϴ� ����
		bool	_attack_ready = false;
		bool	_attack = false;
		bool	_hit_particle = false;


	private:
		void SetDirection();
		void Particle_Control();
		void Hpcontrol();
		void Effect_Control();
		void complete_telleport_in();
		void complete_telleport_out();

		void complete_attack_ready();
		void complete_attack();
	};
}