#pragma once
#include "Include_Common.h"
#include "Yggdrasil_BasicBullet.h"
#include "Yggdrasil_Energy_Bomb.h"
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

		static Vector3 FaceGetpos() { return _pos; }

		void idle();
		void die();
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
		void attack_c();
		void attack_c_finish();
		void groggy_start();
		void groggy_end();
		void intro();
		void basicattack();
		void set_basicbuulet();
		void Energy_Bombattack();
		void groggy_down();
		void groggy_up();


	private:
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		static Vector3 _pos;
		Vector2 _velocity = Vector2(0.f, 0.f);
		Vector3 Yggdrasil_pos = Vector3(0.f, 0.f, 0.f);
		Vector3 Yggdrasil_rotation = Vector3(0.f, 0.f, 0.f);

	private:
		Vector2 basic_pos[8];
		Vector3 basic_save_pos = Vector3(0.f, 0.f, 0.f);

	private:
		float	_time = 0.f;						// ���ݽ� �����
		float	_distance = 0.f;					// �÷��̾���� �Ÿ� üũ
		bool	_Ground_check = false;				// ��üũ�ÿ� ���̰� �ִ� ����
		int    _NumberofAttack = 0;					// ����Ƚ��üũ

		Yggdrasil_BasicBullet* Bullet[8];
		Yggdrasil_Energy_Bomb* Energy_Bomb;
		//GameObject* _Gobjs[5];
	};
}