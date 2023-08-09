#pragma once
#include "Include_Common.h"

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
			Attack_A,
			Attack_B_Ready,
			Attack_B,
			Attack_C,
			Attack_D,
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
		void attack_a();
		void attack_b_ready();
		void attack_b();
		void attack_c();
		void attack_d();
		void casting();
		void die();
		void groggy();
		void hit();
		void intro();
		void potion();
		void teleport_in();
		void teleport_out();


	private:
		Cleric_State _state;
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		Vector3 pos = Vector3(0.f, 0.f, 0.f);
		Vector2 _velocity = Vector2(0.f, 0.f);
		Vector3 _first_place = Vector3(0.f, 0.f, 0.f);

	private:
		static int mDir;
		float	_time = 0.f;						// 공격시 사용중
		float	_distance = 0.f;					// 플레이어와의 거리 체크
		bool	_Ground_check = false;				// 땅체크시에 쓰이고 있는 변수
		int		_hit = 0;							// 공격받은 후 텔레포트하기 위한 변수
		int		_lotationplay = 0;
		bool	_Teleport = false;


	private:
		Skul_Basic::Skul_Basic_State Skul_BasicState;

	private:
		void complete_attack_a();
		void complete_attack_b();
		void complete_attack_b_ready();
		void complete_attack_c();
		void complete_attack_d();
		void complete_teleport_in();
		void complete_teleport_out();
	};
}