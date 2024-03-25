#pragma once
#include "Mini_Boss.h"
#include "Skul_Basic.h"

namespace jk
{
	class Cleric : public Mini_Boss
	{
	public:
		Cleric();
		virtual ~Cleric();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;


		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		enum class Cleric_State
		{
			Idle,	
			Attack_A_Ready,
			Attack_A,
			Attack_B_Ready,
			Attack_B,
			Attack_C_Ready,
			Attack_C,

			Finishing_Move_Ready,
			Finishing_Move_Succes,
			Finishing_Move_Fail,
			Finishing_Move,
			Casting,

			Die,
			Groggy,
			Hit,
			Intro,
			Potion,
			Teleport_In,
			Teleport_Out
		};

		void idle();
		void attack_a_ready();
		void attack_a();
		void attack_b_ready();
		void attack_b();
		void attack_c_ready();
		void attack_c();


		void Finishing_Move_Ready();
		void Finishing_Move_Succes();
		void Finishing_Move_Fail();
		void Finishing_Move();



		void casting();
		void die();
		void groggy();
		void hit();
		void intro();
		void potion();
		void teleport_in();
		void teleport_out();
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
		class HitBox_Monster* Hit_Box = nullptr;
		class Monster_Hit_Effect* _Hit_Effect = nullptr;
		class Hit_Sword* _Hit_Sword = nullptr;
		class Hit_Critical_Middle* _Critical_Middle = nullptr;
		class Hit_Critical_High* _Critical_High = nullptr;
		class Monster_Death_Effect* _Death_Effect = nullptr;
		bool _followskul = false;


	private:
		class Cleric_Attack_Sign* _Attack_Sign = nullptr;
		class Cleric_HolyThunder* _GraceOfLeonia_Attack_A = nullptr;//  공격이미지 변경해야함
		class Cleric_Veteran_Sanctuary* _Veteran_Sanctuary_AtaackB = nullptr; 

	private:
		class Public_Ultimate_Aura* Ultimate_Aura = nullptr;
		class Public_Ultimate_AuraSmoke* Ultimate_AuraSmoke = nullptr;
		class Public_UltimateSkill_Effect_Complete* UltimateSkill_Effect_Complete = nullptr;
		class Public_UltimateSkill_Effect_Fail* UltimateSkill_Effect_Fail = nullptr;
		class Cleric_Ultimate_SkillEffect* Ultimate_SkillEffect = nullptr;			//필살기 사람모형 이펙트
		class Public_Heal_Effect* Ultimate_Heal_Effect = nullptr;						//필살기 힐 이펙트


	private:
		Cleric_State _state;
		class Animator* at = nullptr;
		class RigidBody* _rigidbody = nullptr;
		class Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		Vector3 pos = Vector3(0.f, 0.f, 0.f);
		Vector2 _velocity = Vector2(0.f, 0.f);
		Vector3 _first_place = Vector3(0.f, 0.f, 0.f);
		Vector3 _Attack_pos = Vector3(0.f, 0.f, 0.f);

	private:
		static int mDir;
		int _attackDir = 1;
		float	_time = 0.f;						// 공격시 사용중
		float	_attack_time = 0.f;
		float	_distance = 0.f;					// 플레이어와의 거리 체크
		bool	_Ground_check = false;				// 땅체크시에 쓰이고 있는 변수
		int		_hit = 0;							// 공격받은 후 텔레포트하기 위한 변수
		bool    _hit_switch = false;
		int		_lotationplay = 0;
		bool	_Teleport = false;
		int		_HitType = 0;
		int		_Dammege = 0;


	private:
		bool _attack_sign = false;
		bool	_Ultimate = false;
		bool	_Ultimate_Skill = false;
		bool	_Intro = false;

	private:
		Skul_Basic::Skul_Basic_State Skul_BasicState;


	private:
		void SetDirection();
		void Particle_Control();
		void Hpcontrol();
		void Effect_Control();


	private:
		void complete_attack_a();
		void complete_attack_b();
		void complete_ultimate_skill();

		void complete_intro();
		void complete_teleport_in();
		void complete_teleport_out();
		void complete_hit();
	};
}