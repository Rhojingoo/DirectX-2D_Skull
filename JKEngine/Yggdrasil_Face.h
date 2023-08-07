#pragma once
#include "Include_Common.h"

namespace jk
{
	class Yggdrasil_Face : public Yggdrasil
	{
	public:
		Yggdrasil_Face();
		virtual ~Yggdrasil_Face();

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
		static Vector3 _pos;
		Vector3 Yggdrasil_pos = Vector3(0.f, 0.f, 0.f);
		//Vector3 _playerpos = Vector3(0.f, 0.f, 0.f);
		Vector2 _velocity = Vector2(0.f, 0.f);
		Yggdrasil_State _state;

	private:
		static int			mDir;
		static bool			_switch;
		float	_time = 0.f;						// ���ݽ� �����
		float	_distance = 0.f;					// �÷��̾���� �Ÿ� üũ
		bool	_Ground_check = false;				// ��üũ�ÿ� ���̰� �ִ� ����
	};
}