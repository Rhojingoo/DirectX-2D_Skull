#pragma once
#include "Include_Common.h"

namespace jk
{
	class Monster_Hammer : public Monster
	{
	public:
		Monster_Hammer();
		virtual ~Monster_Hammer();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;


		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		//static GameObject SetoWner(GameObject* ac) { oWner = ac; }

		enum class Monster_Hammer_State
		{
			Idle,
			Attack,
			Tackle,
			Walk,
			Dead,
		};

		void idle();
		void attack();
		void tackle();
		void walk();
		void dead();


	private:
		Monster_Hammer_State _state;
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		Vector3 pos = Vector3(0.f, 0.f, 0.f);
		Vector2 _velocity = Vector2(0.f, 0.f);

	private:
		static int			mDir;
		static bool			_switch;

		float	_distance = 0.f;			// 플레이어와의 거리 체크
		bool	_Ground_check = false;		// 땅체크시에 쓰이고 있는 변수
		float	_time = 0.f;				// 공격시 사용중
		int		_AttackCheck = 0;			// 공격종류의 선택을 할수 있도록 설정하는 변수

	private:
		void attack_idle();
	};
}