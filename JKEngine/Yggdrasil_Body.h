#pragma once
#include "Include_Common.h"

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
		void die();
		void attack_a_ready();
		void attack_a_right();
		void attack_a_left();
		void attack_b_ready();
		void attack_b_left();
		void attack_b_right();
		void attack_c();
		void intro();

	private:
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		Vector3 _pos = Vector3(0.f, 0.f, 0.f);
		Vector2 _velocity = Vector2(0.f, 0.f);

	private:
		Yggdrasil_State _state;
		float	_time = 0.f;						// 공격시 사용중	
		bool	_Ground_check = false;				// 땅체크시에 쓰이고 있는 변수
	};
}