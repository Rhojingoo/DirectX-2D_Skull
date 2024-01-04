#pragma once
#include "Mini_Boss.h"
#include "Monster_GoldHammer.h"
#include "Monster_Hammer.h"

namespace jk
{
	class Knight_male : public Mini_Boss
	{
	public:
		Knight_male();
		virtual ~Knight_male();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;


		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		enum class Knight_State
		{
			Idle,
			Dash,
			BackDash,
			Jump,
			JumpAttack,
			Die,
			Attack_A,
			Attack_B,
			Attack_C,
			Attack_D,
			Attack_E,
			EnergeBall,
			Explosion_Loop_Ready,
			Explosion_Loop,

			Finishing_Move_Ready,
			Finishing_Move_Succes,
			Finishing_Move_Fail,
			Finishing_Move,

			Groggy,
			Hit, 
			Intro,
			Potion,
			Stinger,
			Stinger_Ready,
		};

		void idle();
		void dash();
		void backdash();
		void jump();
		void jumpattack();
		void die();
		void attack_a();
		void attack_b();
		void attack_c();
		void attack_d();
		void attack_e();
		void energeball();
		void explosion_loop_ready();
		void explosion_loop();
		void Finishing_Move_Ready();
		void Finishing_Move_Succes();
		void Finishing_Move_Fail();
		void Finishing_Move();
		void Groggy();
		void hit();
		void intro();
		void potion();
		void stinger();
		void stinger_Ready();
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
		Knight_State _state;
		class Animator* at = nullptr;
		class AudioSource* as = nullptr;
		class RigidBody* _rigidbody = nullptr;
		class Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		Vector3 pos = Vector3(0.f, 0.f, 0.f);	
		Vector2 _velocity = Vector2(0.f, 0.f);


	private:
		class HitBox_Knight* Hit_Box = nullptr;
		class Monster_Hit_Effect* _Hit_Effect = nullptr;
		class Player_Hit_Effect* _Hit_Effect_player = nullptr;
		class Hit_Sword* _Hit_Sword = nullptr;
		class Hit_Critical_Middle* _Critical_Middle = nullptr;
		class Hit_Critical_High* _Critical_High = nullptr;
		class Monster_Death_Effect* _Death_Effect = nullptr;
		Monster_Hammer::Monster_Hammer_State hammer_st = {};
		Monster_GoldHammer::Monster_GoldHammer_State Goldham_st = {};


	private:
		static int			mDir;
		static bool			_switch;
		int		_attackdir = 1;
		bool	_attack_Col = false;


		float	_distance = 0.f;			// 플레이어와의 거리 체크
		bool	_Ground_check = false;		// 땅체크시에 쓰이고 있는 변수
		bool	_dash = false;
		float	_time = 0.f;				// 공격시 사용중
		bool	_attack = false;			// 공격에서 idle로 보내는 스위치 변수
		int		_number_of_attack = 0;		// 공격횟수에 따라 idle로 보내는데, 공격횟수를 체크하는 변수
		int		_number_of_hit = 0;			// 타격횟수에 따라 행동을 설정(그로기, 백대쉬, ultimate아우라취소등)하기위한 변수
		int		_attackorder = 0;			// 콤보공격의 경우 순서가 정해져 있어 해당 순서에 진행하도록 설정하는 변수 
		int		_choicecombo = 0;			// 공격종류의 선택을 할수 있도록 설정하는 변수
		int		_HitType = 0;



		float	_Attacktime = 0.f;				
		bool    _hit_switch = false;
		bool	_Ultimate = false;
		bool	_Ultimate_Skill = false;
		bool	_BackDash = false;
		bool	_Intro = false;
		//int _fallcheck = 0;

	private:
		class Knight_male_EnergeBall* Bullet = nullptr;
		class Knight_EnergyBall_StartEffect* Bullet_effect = nullptr;
		class Knight_Energe_Blast* Energe_Blast = nullptr;
		class Public_Ultimate_Aura* Ultimate_Aura = nullptr;
		class Public_Ultimate_AuraSmoke* Ultimate_AuraSmoke = nullptr;
		class Public_UltimateSkill_Effect_Complete* UltimateSkill_Effect_Complete = nullptr;
		class Public_UltimateSkill_Effect_Fail* UltimateSkill_Effect_Fail = nullptr;
		class Knight_UltimateSkill_Projectile* UltimateSkill_Projectile = nullptr;

	private:
		void SetDirection();
		void Particle_Control();
		void Hpcontrol();
		void Effect_Control();


	private:
		void choicecombo();
		void combo();
		void energyball();
		void explosionloop();
		void finishingmove_set();
		void complete_ultimate();
		void complete_gloggy();
		void complete_hit();
		void complete_Intro();
		void complete_Attack_A();
		void complete_Attack_B();
		void complete_Attack_C();
};
}