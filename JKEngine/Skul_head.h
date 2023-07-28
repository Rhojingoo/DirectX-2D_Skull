#pragma once
#include "Include_Common.h"


namespace jk
{
	class Animator;
	class Skul_head : public GameObject
	{
	public:
		Skul_head();
		virtual ~Skul_head();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		enum class Skul_Head_State
		{
			Idle,
			Move,	
			Attack,	
		};

		void idle();
		void move();
		void attack();

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		static void SetDirection(int dir) { mDir = dir; }
		static void Setattack(bool check) { _attack = check; }

	private:
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		Vector3 pos = Vector3(0.f, 0.f, 0.f);
		Vector2 _velocity = Vector2(0.f, 0.f);

	private:
		Skul_Head_State _state;
		static int mDir;
		float _time = 0.f;
		static bool _attack;
		bool _Ground_check = false;
	};
}