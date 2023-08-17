#pragma once
#include "Include_Common.h"

namespace jk
{	
	class Yggdrasil_Chin : public Yggdrasil
	{
	public:
		Yggdrasil_Chin();
		virtual ~Yggdrasil_Chin();

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
		void attack_c_up();
		void attack_c();
		void attack_c_down();
		void attack_c_finish();
		void groggy_start();
		void groggy_end();

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


		void Lmove_up();
		void Lmove_down();
		void Intro_chinplay();
		void change_chinplay();
		void groggy_down();
		void groggy_up();
		void Die_Down();
	private:
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		Vector3 _pos = Vector3(0.f, 0.f, 0.f);
		Vector3 Yggdrasil_pos = Vector3(0.f, 0.f, 0.f);
		Vector3 YggdrasilFace_pos = Vector3(0.f, 0.f, 0.f);
		Vector3 Yggdrasil_rotation = Vector3(0.f, 0.f, 0.f);

	private:
		static int			mDir;
		float	_time = 0.f;						// 공격시 사용중
		float	_distance = 0.f;					// 플레이어와의 거리 체크
		bool	_Ground_check = false;				// 땅체크시에 쓰이고 있는 변수
		bool	_Firstbullet = false;

	private:
		Vector3 mCenterpos = Vector3(0.f, 0.f, 0.f);
		float fDist = 0.f;
		float _maxdistance = 5.f;
		float _chinspeed = 1.f;

	public:
		static bool _introchin;
		static bool _introchinup;

	};
}