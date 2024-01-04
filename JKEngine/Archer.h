#pragma once
#include "Mini_Boss.h"


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
		void SetUIstate(int set) { _UIstate = set; }

	private:
		float _MaxHp = 2000;
		float _CurrenHp = 2000;
		float _MaxHp_scale = 0;
		float _CurrenHp_scale = 0;
		int	_bulletcheck = 0;
		

	private:
		class AdventureUI* _MbossFace = nullptr;
		class MiniBoss_State_UI* _State_UI = nullptr;
		class Monster_Hp_Bar* Monster_UIHp = nullptr;
		class Monster_Hp_Bar* Monster_UIDamegeHp = nullptr;
		class HP_Frame* Hpbar_Frame = nullptr;
		class Monster_Hp_Bar* Monster_Hp = nullptr;
		class Monster_Hp_Bar* Monster_DamegeHp = nullptr;
		float _Damage = 0.f;
		bool _Hp_control = false;
		float _Hp_time = 0.f;
		int _UIstate = 0;


	private:
		float ground_distance_L = 0.f;
		float ground_distance_R = 0.f;


	private:
		Archer_State _state;
		class Animator* at = nullptr;
		class AudioSource* as = nullptr;
		class RigidBody* _rigidbody = nullptr;
		class Collider2D* _collider = nullptr;
		Transform* _tr = nullptr;
		Vector3 pos = Vector3(0.f, 0.f, 0.f);	
		Vector2 _velocity = Vector2(0.f, 0.f);
		Vector3 Ultimate_Skill_pos = Vector3(0.f, 0.f, 0.f);


	private:
		class HitBox_Archer* Hit_Box = nullptr;
		class Monster_Hit_Effect* _Hit_Effect = nullptr;
		class Hit_Sword* _Hit_Sword = nullptr;
		class Hit_Critical_Middle* _Critical_Middle = nullptr;
		class Hit_Critical_High* _Critical_High = nullptr;
		class Monster_Death_Effect* _Death_Effect = nullptr;
		bool _followskul = false;


	private:
		class Archer_Arrow* _archer_arrow = nullptr;
		class Archer_Arrow_Upward_Sign* Upward_Sign = nullptr;
		class Archer_Upward_Impact_Bullet* Upward_Impact_Bullet = nullptr;
		class Archer_Arrow_Bye* Arrow_Bye_effect = nullptr;
		class Archer_Trap* Bullet_Trap[6];


	private:
		class Public_Ultimate_Aura* Ultimate_Aura = nullptr;
		class Public_Ultimate_AuraSmoke* Ultimate_AuraSmoke = nullptr;
		class Public_UltimateSkill_Effect_Complete* UltimateSkill_Effect_Complete = nullptr;
		class Public_UltimateSkill_Effect_Fail* UltimateSkill_Effect_Fail = nullptr;
		class Archer_Utimate_Sign* Utimate_Sign = nullptr;
		class Archer_Upward_Impact_Bullet* Ultimate_Upward_ImpactBullet[40];
		class Archer_Arrow_Bye* Ultimate_ArrowBye_effect[40];



	private:
		static int			_Dir;
		int _attackDir = 1;
		static bool			_switch;


	private:
		float	_time = 0.f;						// ���ݽ� �����
		float	_attack_time = 0.f;
		bool	_attack = false;					// ���ݿ��� idle�� ������ ����ġ ����
		int		_number_of_attack = 0;				// ����Ƚ���� ���� idle�� �����µ�, ����Ƚ���� üũ�ϴ� ����
		int		_choicecombo = 0;					// ���������� ������ �Ҽ� �ֵ��� �����ϴ� ����
		float	_distance = 0.f;					// �÷��̾���� �Ÿ� üũ
		bool	_Ground_check = false;				// ��üũ�ÿ� ���̰� �ִ� ����
		int		_hit = 0;							// ���ݹ��� �� ȸ���ϱ� ���� ����
		bool    _hit_switch = false;
		int		_Numberof_BackDash = 0;
		int		_HitType = 0;
		int		_Dammege = 0;
		

	private:
		bool    _BackDash = true;
		bool	_player_attack_check = false;		// �÷��̾ ���ݽ� �ݶ��̴� ó���� Ȯ���ϰ� �ϴ°�.
		bool	_attack_a = false;
		bool	_attack_b_sign = false;
		bool	_attack_b = false;
		bool	_Ultimate = false;
		bool	_Ultimate_Skill = false;
		bool	_Intro = false;
		bool	_hitend = false;
		bool	_PushAway = false;


	private:
		Skul_Basic::Skul_Basic_State Skul_BasicState;

	private:
		void SetDirection();
		void Particle_Control();
		void Hpcontrol();
		void Effect_Control();

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