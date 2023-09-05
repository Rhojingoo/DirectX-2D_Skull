#pragma once
#include "Include_Common.h"
#include "Monster_StoneWizard_Teleport.h"
#include "Monster_StoneWizard_Icicle_Effect.h"
#include "Monster_Stone_wizard_IcicleBullet.h"
#include "Player_Hp_Bar.h"
#include "Monster_Hit_Effect.h"
#include "Monster_Death_Effect.h"


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
		void teleport_in();
		void teleport_out();

	private:
		float _MaxHp = 100;
		float _CurrenHp = 100;
		int	_bulletcheck = 0;


	private:
		Stone_wizard_State _state;
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		Transform* Effect_tr = nullptr;
		Vector3 pos = Vector3(0.f, 0.f, 0.f);
		Vector2 _velocity = Vector2(0.f, 0.f);

	private:
		HitBox_Monster* Hit_Box = nullptr;
		Player_Hp_Bar* Player_Hp = nullptr;
		Monster_Hit_Effect* _Hit_Effect = nullptr;
		Monster_Death_Effect* _Death_Effect = nullptr;


	private:
		Monster_StoneWizard_Teleport* Wizard_Teleport = nullptr;
		Monster_StoneWizard_Icicle_Effect* Icicle_Effect = nullptr;
		Monster_Stone_wizard_IcicleBullet* Icicle_Bullet = nullptr;


	private:
		static int			mDir;

		float	_distance = 0.f;			// 플레이어와의 거리 체크
		bool	_Ground_check = false;		// 땅체크시에 쓰이고 있는 변수
		float	_time = 0.f;				// 공격시 사용중
		float	_attacktime = 0.f;
	
	private:	
		bool	_teleportCheck = false;			// 텔레포드 인아웃을 할수 있도록 설정하는 변수
		bool	_attack_ready = false;
		bool	_attack = false;


	private:
		void SetDirection();
		void complete_telleport_in();
		void complete_telleport_out();

		void complete_attack_ready();
		void complete_attack();
	};
}