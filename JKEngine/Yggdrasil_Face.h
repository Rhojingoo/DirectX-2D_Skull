#pragma once
#include "Yggdrasil.h"


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
		void attack_c_up();
		void attack_c();
		void attack_c_down();
		void attack_c_finish();
		void groggy_start();
		void groggy_end();
		void intro_set_right();
		void intro_set_left();
		void intro_ready();
		void intro();
		void intro_end();

		void change_set();
		void change_ready();
		void change();
		void change_end();

		void die_set();
		void die_waiting();
		void die_ready();
		void die();

		void basicattack();
		void set_basicbuulet();
		void Energy_Bombattack();
		void Energy_Corpsattack();
		void groggy_down();
		void groggy_up();
		void Die_DOWN();
		float UpdateVibration(float originalX, float amplitude, float frequency, float timeElapsed);

		void Facepos_Setting();
		void EffectSetting();


	private:
		class Animator* at = nullptr;
		class AudioSource* as = nullptr;
		class RigidBody* _rigidbody = nullptr;
		class Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		static Vector3 _pos;
		Vector2 _velocity = Vector2(0.f, 0.f);
		Vector3 Yggdrasil_pos = Vector3(0.f, 0.f, 0.f);
		Vector3 Yggdrasil_rotation = Vector3(0.f, 0.f, 0.f);
		Vector3 HitBospos = Vector3(0.f, 0.f, 0.f);
	

	private:
		Vector2 basic_pos[8] = {};
		Vector3 basic_save_pos = Vector3(0.f, 0.f, 0.f);

	private:
		float	_time = 0.f;						// ���ݽ� �����
		float	_distance = 0.f;					// �÷��̾���� �Ÿ� üũ
		bool	_Ground_check = false;				// ��üũ�ÿ� ���̰� �ִ� ����
	//	int    _NumberofAttack = 0;					// ����Ƚ��üũ

		class Yggdrasil_BasicBullet* Bullet[8] = {};
		class Yggdrasil_Energy_Bomb* Energy_Bomb = nullptr;
		class Yggdrsil_Energy_Corps* Energy_Corps[15] = {};
		class Yggdrasil_Effect* Yggdrasil_effect = nullptr;
		class Yggdrasil_EnergeBall_CreateEffect* Groggy_Begin_Efeect[15] = {};
		class Yggdrasil_Groggy_GroundEffect* Groggy_impact = nullptr;
		class Yggdrasil_EnergyCorps_Charging* EnergyCorps_Charging = nullptr;
		class Yggdrasil_EnergyCorps_Spark* EnergyCorps_Spark = nullptr;
		class Yggdraisl_Groggy_StartImpact* Groggy_Start = nullptr;
		class Yggdrasil_FaceDead_Effect* _Dead_Effect = nullptr;

		GameObject::eState check_state = {};
		float	_activetime = 0.f;
		float   _introtime =  0.f;
		bool	_FaceSet_of_Change = false;
		bool	_EnergyCorps_Spark_off = true;

	public:
		static bool	_Firstbullet;
		static bool	_BulletReady;
	
	};
}