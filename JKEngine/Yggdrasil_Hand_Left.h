#pragma once
#include "Include_Common.h"

namespace jk
{
	class Yggdrasil_Hand_Left : public Yggdrasil
	{
	public:
		Yggdrasil_Hand_Left();
		virtual ~Yggdrasil_Hand_Left();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void idle();
		void die();
		void attack_a_set();
		void attack_a_ready();
		void attack_a_right();
		void attack_a_left();
		void attack_a_finish();
		void attack_b_set();
		void attack_b_ready();
		void attack_b_left();
		void attack_b_right();
		void attack_b_finish();
		void attack_c();
		void intro();

	public:
		static bool			_Attackswitch;
		static int			mDir;

	private:
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		Vector3 _pos = Vector3(0.f, 0.f, 0.f);
		Vector3 _Savepointpos = Vector3(0.f, 0.f, 0.f);			// ��ü��ǥ
		Vector3	_Yggdrasildistance = Vector3(0.f, 0.f, 0.f);	// ��ü���� �Ÿ� üũ
		Vector3	_Playerdistance = Vector3(0.f, 0.f, 0.f);		// �÷��̾���� �Ÿ� üũ
		Vector2 _velocity = Vector2(0.f, 0.f);

		Vector3 _AttackB_SavePos = Vector3(0.f, 0.f, 0.f);

	private:
		float	_time = 0.f;							// ���ݽ� �����
		bool	_Ground_check = false;					// ��üũ�ÿ� ���̰� �ִ� ����
		bool _attackready = false;
		bool _attackon = false;
		void attackb_setting();
	};
}