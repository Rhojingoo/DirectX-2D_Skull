#pragma once
#include "Include_Common.h"
#include "Ultimate_OnFire_Ready.h"
#include "Ultimate_OnFire.h"
#include "Ultimate_On_Fire_Projectile.h"
#include "Ultimate_OnFire_Fire.h"


namespace jk
{
	class Mage : public Mini_Boss
	{
	public:
		Mage();
		virtual ~Mage();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;


		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		enum class Mage_State
		{
			Idle,			
			Die,
			Attack_A,
			Attack_A_Ready,
			Attack_B,
			Attack_B_Ready,
			Attack_C,
			Attack_C_Run,
			Attack_C_Ready,
			Attack_D,
			Attack_D_Ready,


			Finishing_Move_Ready,
			Finishing_Move_Succes,
			Finishing_Move_Fail,
			Finishing_Move,
			Casting,


			Fly,
			Groggy,
			Hit,
			Intro,
			Potion,
			WalkBack_R,
			WalkBack_L,
			WalkFront_R,
			WalkFront_L,
		};

		void idle();
		void die();
		void attack_a();
		void attack_a_ready();
		void attack_b();
		void attack_b_ready();
		void attack_c();
		void attack_c_run();
		void attack_c_ready();
		void attack_d();
		void attack_d_ready();
		void fly();

		void Finishing_Move_Ready();
		void Finishing_Move_Succes();
		void Finishing_Move_Fail();
		void Finishing_Move();
		void casting();

		void groggy();
		void hit();
		void intro();
		void potion();
		void walkBack_R();
		void walkBack_L();
		void WalkFront_R();
		void WalkFront_L();

		
	private:
		Mage_State _state;
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		Vector3 pos = Vector3(0.f, 0.f, 0.f);
		Vector2 _velocity = Vector2(0.f, 0.f);
		Vector3 _first_place = Vector3(0.f, 0.f, 0.f);


	private:
		Public_Ultimate_Aura* Ultimate_Aura = nullptr;
		Public_Ultimate_AuraSmoke* Ultimate_AuraSmoke = nullptr;
		Public_UltimateSkill_Effect_Complete* UltimateSkill_Effect_Complete = nullptr;
		Public_UltimateSkill_Effect_Fail* UltimateSkill_Effect_Fail = nullptr;

	private:
		Ultimate_OnFire_Ready* _OnFire_Ready[3];
		Ultimate_OnFire* _OnFire[3];
		Ultimate_On_Fire_Projectile* On_Fire_Projectile[9];
		Ultimate_OnFire_Fire* OnFire_Fire[9];


	private:
		int		mDir = 1;
		float	_time = 0.f;						// ���ݽ� �����
		float	_attack_time = 0.f;
		bool	_attack = false;					// ���ݿ��� idle�� ������ ����ġ ����
		float	_distance = 0.f;					// �÷��̾���� �Ÿ� üũ


	private:
		//�����û�뺯����
		int		_swich_checkpoint = 0;				// ����Ƚ���� ���� ��Ǽ��� 0 = ����, 1= ����A, 2= ����B, 3 = �ʻ��
		int		_movechoice = 1;					// ������ �̿�
		float   _maxright = 250;
		float   _maxleft = -250;
		float   _movetime = 0.f;
		int     _mtime = 0;
		int		_hit = 0;							// ���ݹ��� Ƚ�� Check


	private:
		int     _flyswich = 0;						// �ϴ� ���ƴٴϴ� ����
		bool    _sky = true;
		int     _landingswich = 0;					// ����C�� ������
		bool	_Ground_check = false;				// ��üũ�ÿ� ���̰� �ִ� ����			
		bool    _ground = false;


	private:		
		int		_attackA = 0;						// ���� A ������ ����(����A ����)	
		float   _attacktB_time = 0;					// ���� B ���ݽð� üũ	(����B ����)		
		int		_attackC = 0;						// ���� B ������ ����(����C ����)


	private:
		bool	_UltimateSet = false;
		bool	_Ultimate_Skill = false;



	private:
		Skul_Basic::Skul_Basic_State Skul_BasicState;

	private:
		void Fire_Projectile(int i);
		void Fire_Projectile_Rotation(Transform* tr, Vector3 bulletpos, int i);

	private:
		void attack_a_complete();
		void attack_b_complete();
		void attack_c_complete();
		void attack_d_complete();
		void attack_a_ready_complete();
		void attack_b_ready_complete();
		void attack_c_ready_complete();
		void attack_d_ready_complete();
		void complete_hit();

		void complete_ultimate_set();
		void complete_ultimate_fire();

		int randomcount(int a, int b);



	};
}