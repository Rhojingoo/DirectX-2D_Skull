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
		void die();
		void attack_a_ready();
		void attack_a_right();
		void attack_a_left();
		void attack_b_ready();
		void attack_b_left();
		void attack_b_right();
		void attack_c();
		void intro();

		void Lmove_up();
		void Lmove_down();

	private:
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		Vector3 _pos = Vector3(0.f, 0.f, 0.f);
		Vector3 Yggdrasil_pos = Vector3(0.f, 0.f, 0.f);

		//Vector3 _playerpos = Vector3(0.f, 0.f, 0.f);
		Vector2 _velocity = Vector2(0.f, 0.f);
		Yggdrasil_State _state;

	private:
		static int			mDir;
		//static bool			_switch;
		float	_time = 0.f;						// 공격시 사용중
		float	_distance = 0.f;					// 플레이어와의 거리 체크
		bool	_Ground_check = false;				// 땅체크시에 쓰이고 있는 변수

	private:
		Vector3 mCenterpos = Vector3(0.f, 0.f, 0.f);
		float fDist = 0.f;
		float _maxdistance = 5.f;
		float _chinspeed = 20.f;

	};
}