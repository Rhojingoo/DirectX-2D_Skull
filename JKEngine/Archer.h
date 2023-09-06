#pragma once
#include "Include_Common.h"
#include "Archer_Arrow.h"
#include "Archer_Arrow_Upward_Sign.h"
#include "Archer_Upward_Impact_Bullet.h"
#include "Archer_Arrow_Bye.h"
#include "Archer_Trap.h"
#include "Public_Ultimate_Aura.h"
#include "Public_Ultimate_AuraSmoke.h"
#include "Public_UltimateSkill_Effect_Complete.h"
#include "Public_UltimateSkill_Effect_Fail.h"
#include "Archer_Utimate_Sign.h"

#include "Player_Hp_Bar.h"
#include "Monster_Hit_Effect.h"
#include "Monster_Death_Effect.h"


namespace jk
{
	class Archer : public Mini_Boss
	{
	public:
		Archer();
		virtual ~Archer();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;


		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		enum class Archer_State
		{
			Idle,		
			BackDash,
			Die,
			Attack_A_Ready,
			Attack_A,
			Attack_A_End,
			Attack_B_Ready,
			Attack_B,
			Attack_B_End,			
			Attack_C,

			Finishing_Move_Ready,
			Finishing_Move_Succes,
			Finishing_Move_Fail,
			Finishing_Move,

			Groggy,
			Hit,
			Intro,
			Potion,
		};

		void idle();
		void backdash();
		void die();
		void attack_a_ready();
		void attack_a();
		void attack_a_end();


		void attack_b_ready();
		void attack_b();
		void attack_b_end();

		void attack_c();
		
		
		void Finishing_Move_Ready();
		void Finishing_Move_Succes();
		void Finishing_Move_Fail();
		void Finishing_Move();


		
		void groggy();
		void hit();
		void intro();
		void potion();

	private:
		float _MaxHp = 2000;
		float _CurrenHp = 2000;
		float _MaxHp_scale = 0;
		float _CurrenHp_scale = 0;
		int	_bulletcheck = 0;



	private:
		Archer_State _state;
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* _tr = nullptr;
		Vector3 pos = Vector3(0.f, 0.f, 0.f);	
		Vector2 _velocity = Vector2(0.f, 0.f);
		Vector3 Ultimate_Skill_pos = Vector3(0.f, 0.f, 0.f);


	private:
		HitBox_Monster* Hit_Box = nullptr;
		Player_Hp_Bar* Player_Hp = nullptr;
		Monster_Hit_Effect* _Hit_Effect = nullptr;
		Hit_Sword* _Hit_Sword = nullptr;
		Hit_Critical_Middle* _Critical_Middle = nullptr;
		Hit_Critical_High* _Critical_High = nullptr;
		Monster_Death_Effect* _Death_Effect = nullptr;
		bool _followskul = false;


	private:
		Archer_Arrow* _archer_arrow = nullptr;
		Archer_Arrow_Upward_Sign* Upward_Sign = nullptr;
		Archer_Upward_Impact_Bullet* Upward_Impact_Bullet = nullptr;
		Archer_Arrow_Bye* Arrow_Bye_effect = nullptr;
		Archer_Trap* Bullet_Trap[6];


	private:
		Public_Ultimate_Aura* Ultimate_Aura = nullptr;
		Public_Ultimate_AuraSmoke* Ultimate_AuraSmoke = nullptr;
		Public_UltimateSkill_Effect_Complete* UltimateSkill_Effect_Complete = nullptr;
		Public_UltimateSkill_Effect_Fail* UltimateSkill_Effect_Fail = nullptr;
		Archer_Utimate_Sign* Utimate_Sign = nullptr;
		Archer_Upward_Impact_Bullet* Ultimate_Upward_ImpactBullet[40];
		Archer_Arrow_Bye* Ultimate_ArrowBye_effect[40];



	private:
		static int			mDir;
		int _attackDir = 1;
		static bool			_switch;


	private:
		float	_time = 0.f;						// 공격시 사용중
		float	_attack_time = 0.f;
		bool	_attack = false;					// 공격에서 idle로 보내는 스위치 변수
		int		_number_of_attack = 0;				// 공격횟수에 따라 idle로 보내는데, 공격횟수를 체크하는 변수
		int		_choicecombo = 0;					// 공격종류의 선택을 할수 있도록 설정하는 변수
		float	_distance = 0.f;					// 플레이어와의 거리 체크
		bool	_Ground_check = false;				// 땅체크시에 쓰이고 있는 변수
		int		_hit = 0;							// 공격받은 후 회피하기 위한 변수
		bool    _hit_switch = false;
		int		_Numberof_BackDash = 0;
		int		_HitType = 0;
		int		_Dammege = 0;
		

	private:
		bool    _BackDash = true;
		bool	_player_attack_check = false;		// 플레이어가 공격시 콜라이더 처리를 확실하게 하는것.
		bool	_attack_a = false;
		bool	_attack_b_sign = false;
		bool	_attack_b = false;
		bool	_Ultimate = false;
		bool	_Ultimate_Skill = false;
		bool	_Intro = false;
		bool	_hitend = false;

	private:
		Skul_Basic::Skul_Basic_State Skul_BasicState;

	private:
		float ground_distance_L = 0.f;
		float ground_distance_R = 0.f;

	private:
		void choicecombo();
		void shootbow_forward();
		void shootbow_upward();
		void dash_combo();
		void pushaway();
		void ultimate();
		void complete_hit();
		void complete_attackA();
		void CompleteArcherIntro();
	};
}