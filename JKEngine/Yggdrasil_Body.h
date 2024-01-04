#pragma once
#include "Yggdrasil.h"


namespace jk
{
	class Yggdrasil_Body : public Yggdrasil
	{
	public:
		Yggdrasil_Body();
		virtual ~Yggdrasil_Body();

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
		void attack_c_down();
		void attack_c();
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
		void die_waiting();
		void die_ready();
		void die();

		void body_down();
		void body_up();

		void move_up();
		void move_down();
		float UpdateVibration(float originalX, float amplitude, float frequency, float timeElapsed);

	public:
		static bool Attack_C_Boddy_Ready;
		static bool Boddy_BulletReady;


	private:
		class Animator* at = nullptr;
		class RigidBody* _rigidbody = nullptr;
		class Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		Vector3 _pos = Vector3(0.f, 0.f, 0.f);
		Vector3 _BodyRotation = Vector3(0.f, 0.f, 0.f);
		Vector3 _savepos = Vector3(0.f, 0.f, 0.f);
		Vector2 _velocity = Vector2(0.f, 0.f);

	private:
		class Yggdrasil_BoddyDead_Effect* _Dead_Effect = nullptr;

	private:
		Vector3 mCenterpos = Vector3(0.f, 0.f, 0.f);
		float fDist = 0.f;
		bool _Turn_up = false;
		float _maxdistance = 10.f;
		float _chinspeed = 10.f;


	private:	
		float	_time = 0.f;						// 공격시 사용중	
		float	_readytime = 0.f;
		bool	_Ground_check = false;				// 땅체크시에 쓰이고 있는 변수
		bool    _groggy_body = false;
		bool    _idle_bodyon = false;
		float   _falldown = 0.f;

		int introbody_ordernumber = 0;
	};
}