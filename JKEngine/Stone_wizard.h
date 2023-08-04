
#pragma once
#include "Include_Common.h"

namespace jk
{
	class Stone_wizard : public Monster
	{
	public:
		Stone_wizard();
		virtual ~Stone_wizard();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;


		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		//static GameObject SetoWner(GameObject* ac) { oWner = ac; }

		enum class Stone_wizard_State
		{
			Idle,
			Attack,
			Hit,
			Teleport_In,
			Teleport_Out,
		};

		void idle();
		void attack();
		void hit();
		void teleport_in();
		void teleport_out();

	private:
		Stone_wizard_State _state;
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		Vector3 pos = Vector3(0.f, 0.f, 0.f);
		Vector2 _velocity = Vector2(0.f, 0.f);

	private:
		static int			mDir;
		static bool			_switch;

		float	_distance = 0.f;			// �÷��̾���� �Ÿ� üũ
		bool	_Ground_check = false;		// ��üũ�ÿ� ���̰� �ִ� ����
		float	_time = 0.f;				// ���ݽ� �����
		bool	_teleportCheck = false;			// �ڷ����� �ξƿ��� �Ҽ� �ֵ��� �����ϴ� ����

	private:
		void teleport_change();
		void attack_complete();
	};
}