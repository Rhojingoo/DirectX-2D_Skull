#pragma once
#include "Include_Common.h"
#include "Monster_StoneWizard_Teleport.h"
#include "Monster_StoneWizard_Icicle_Effect.h"
#include "Monster_Stone_wizard_IcicleBullet.h"

#include "LionWizard_Bullet_Create.h"
#include "LionWizard_Bullet.h"

#include "Monster_Hp_Bar.h"
#include "HP_Frame.h"

#include "Monster_Hit_Effect.h"
#include "Monster_Death_Effect.h"


namespace jk
{
	class Monster_LionWizard : public Monster
	{
	public:
		Monster_LionWizard();
		virtual ~Monster_LionWizard();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		//static GameObject SetoWner(GameObject* ac) { oWner = ac; }

		enum class LionWizard_State
		{
			Idle,
			Attack_Ready,
			Attack_Waiting,
			Attack,
			Hit,
			Teleport_In,
			Teleport_Out,
			Dead,
		};

		void idle();
		void attack_ready();
		void attack_waiting();
		void attack();
		void hit();
		void dead();
		void teleport_in();
		void teleport_out();


	private:
		float _MaxHp = 250;
		float _CurrenHp = 250;
		int	_bulletcheck = 0;

	private:
		LionWizard_State _state;
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		Transform* Effect_tr = nullptr;
		Vector3 pos = Vector3(0.f, 0.f, 0.f);
		Vector2 _velocity = Vector2(0.f, 0.f);

	private:
		HitBox_Monster* Hit_Box = nullptr;
		Monster_Hit_Effect* _Hit_Effect = nullptr;
		Monster_Death_Effect* _Death_Effect = nullptr;
		GameObject* Hit_Particle = nullptr;

	private:

		HP_Frame* Hpbar_Frame = nullptr;
		Monster_Hp_Bar* Monster_Hp = nullptr;
		Monster_Hp_Bar* Monster_DamegeHp = nullptr;
		float _Damage = 0.f;
		bool _Hp_control = false;
		float _Hp_time = 0.f;


	private:
		Monster_StoneWizard_Teleport* Wizard_Teleport = nullptr;
		Monster_StoneWizard_Icicle_Effect* Icicle_Effect = nullptr;
		Monster_Stone_wizard_IcicleBullet* Icicle_Bullet = nullptr;

		LionWizard_Bullet_Create* BulletCreate = nullptr;
		LionWizard_Bullet* LionBullet[3] = {};

	private:
		int		mDir = 1;
		int		_AttackDir = 1;

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
		bool	_BulletFire = false;


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