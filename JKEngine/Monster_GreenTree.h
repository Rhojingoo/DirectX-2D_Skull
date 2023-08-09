#pragma once
#include "Include_Common.h"

namespace jk
{
	class Monster_GreenTree : public Monster
	{
	public:
		Monster_GreenTree();
		virtual ~Monster_GreenTree();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;


		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		enum class Monster_GreenTree_State
		{
			Idle,
			Attack,
			Dead,
			Hit,
			WalkR,
			WalkL,
		};

		void idle();
		void attack();
		void dead();
		void hit();
		void walk_R();
		void walk_L();

	private:
		Monster_GreenTree_State _state;
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		Vector3 _pos = Vector3(0.f, 0.f, 0.f);
		Vector3 _first_place = Vector3(0.f, 0.f, 0.f);
		Vector2 _velocity = Vector2(0.f, 0.f);

	private:
		static int			mDir;
		static bool			_switch;
		int _walkdir = 1;

		float	_distance = 0.f;			// 플레이어와의 거리 체크
		float   _walkdistance = 0.f;		// 자신의 첫위치와 의 거리 체크
		bool	_Ground_check = false;		// 땅체크시에 쓰이고 있는 변수
		float	_time = 0.f;				// 공격시 사용중
		int		_choiceattack = 0;			
		bool	_attackcheck = false;

	private:
		void attack_idle();
	};
}