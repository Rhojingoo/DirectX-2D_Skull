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
		float	_time = 0.f;						// 공격시 사용중
		float	_attack_time = 0.f;
		bool	_attack = false;					// 공격에서 idle로 보내는 스위치 변수
		float	_distance = 0.f;					// 플레이어와의 거리 체크


	private:
		//무빙시사용변수들
		int		_swich_checkpoint = 0;				// 공격횟수에 따라 모션설정 0 = 무빙, 1= 어택A, 2= 어택B, 3 = 필살기
		int		_movechoice = 1;					// 무빙시 이용
		float   _maxright = 250;
		float   _maxleft = -250;
		float   _movetime = 0.f;
		int     _mtime = 0;
		int		_hit = 0;							// 공격받은 횟수 Check


	private:
		int     _flyswich = 0;						// 하늘 날아다니는 변수
		bool    _sky = true;
		int     _landingswich = 0;					// 어택C의 랜딩임
		bool	_Ground_check = false;				// 땅체크시에 쓰이고 있는 변수			
		bool    _ground = false;


	private:		
		int		_attackA = 0;						// 어택 A 여러번 진행(어택A 변수)	
		float   _attacktB_time = 0;					// 어택 B 공격시간 체크	(어택B 변수)		
		int		_attackC = 0;						// 어택 B 여러번 진행(어택C 변수)


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