#pragma once
#include "Include_Common.h"
#include "Yggdrasil_FistSlam_Effect.h"
#include "Yggdrasil_Sweeping.h"

namespace jk
{
	class Yggdrasil_Hand_Right : public Yggdrasil
	{
	public:
		Yggdrasil_Hand_Right();
		virtual ~Yggdrasil_Hand_Right();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void idle();
		void attack_a_set();
		void attack_a_ready();
		void attack_a_right();
		void attack_a_left();
		void attack_a_loading();
		void attack_a_finish();
		void attack_b_set();
		void attack_b_ready();
		void attack_b_left();
		void attack_b_right();
		void attack_b_finish();
		void attack_c_set();
		void attack_c_ready();
		void attack_c();
		void attack_c_finish();
		void groggy_start();
		void groggy_end();
		void attack_d_set();
		void attack_d_ready();
		void attack_d();
		void attack_d_loading();
		void attack_d_finish();

		void intro_set_right();
		void intro_set_left();
		void intro_ready();
		void intro();
		void intro_end();

		void change_set();
		void change_ready();
		void change();
		void change_end();

		void die_set();
		void die_ready();
		void die();

		void hand_intro_up();

	public:
		static bool			_Attackswitch;
		static int			mDir;

	private:
		Yggdrasil_FistSlam_Effect* FistSlam_Smoke = nullptr;
		Yggdrasil_Sweeping* _Sweeping = nullptr;

	private:
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		Vector3 _pos = Vector3(0.f, 0.f, 0.f);
		Vector3 _Savepointpos = Vector3(0.f, 0.f, 0.f);		// 본체좌표
		Vector3	_Yggdrasildistance = Vector3(0.f, 0.f, 0.f);	// 본체와의 거리 체크
		Vector3	_Playerdistance = Vector3(0.f, 0.f, 0.f);		// 플레이어와의 거리 체크
		Vector2 _velocity = Vector2(0.f, 0.f);

		Vector3 _AttackA_SavePos = Vector3(0.f, 0.f, 0.f);
		Vector3 _AttackB_SavePos = Vector3(0.f, 0.f, 0.f);

	private:
		float	_time = 0.f;							// 공격시 사용중
		bool	_Ground_check = false;					// 땅체크시에 쓰이고 있는 변수
		bool _attackready = false;
		bool _attackon = false;
		void attackb_setting();
	};
}