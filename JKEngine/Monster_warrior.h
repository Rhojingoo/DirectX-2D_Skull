#pragma once
#include "Include_Common.h"

namespace jk
{
	class Monster_warrior : public Monster
	{
	public:
		Monster_warrior();
		virtual ~Monster_warrior();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;


		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		enum class Monster_warrior_State
		{
			Idle,
			Attack,
			Dead,
			Hit,
			Walk,			
		};

		void idle();
		void attack();
		void dead();
		void hit();
		void walk();

	private:
		Monster_warrior_State _state;
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* _tr = nullptr;
		Vector3 _pos = Vector3(0.f, 0.f, 0.f);
		Vector2 _velocity = Vector2(0.f, 0.f);

	private:
		HitBox_Monster* Hit_Box = nullptr;


	private:
		static int			mDir;

		float	_distance = 0.f;			// �÷��̾���� �Ÿ� üũ
		bool	_Ground_check = false;		// ��üũ�ÿ� ���̰� �ִ� ����
		float	_time = 0.f;				// ���ݽ� �����
		bool	_attack_Col = false;

	private:
		void complete_attack();
	};
}