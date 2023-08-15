#pragma once
#include "Include_Common.h"
#include "Layana_Sisters.h"

namespace jk
{
	class Layana_ShortHair : public Layana_Sisters
	{
	public:
		Layana_ShortHair();
		virtual ~Layana_ShortHair();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void idle();
		void die();



	private:
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;

	private:
		Homing_Pierce* Homing[3];
		Transform* bullet_tr1 = nullptr;
		Transform* bullet_tr2 = nullptr;
		Transform* bullet_tr3 = nullptr;
		RigidBody* bullet_rb1 = nullptr;
		RigidBody* bullet_rb2 = nullptr;
		RigidBody* bullet_rb3 = nullptr;


	private:
		Rising_Pierce* Rising[19];
		Transform* Risingbullet_tr[19];
		RigidBody* risingbullet_rb[19];

	private:
		Dimension_Pierce_BossEffect* Dimension_boss_effect = nullptr;
		Dimension_Pierce* Dimension_Bullet = nullptr;
		Dimension_Pierce_BulletEffect* Dimension_BulletEffect = nullptr;


	private:
		Vector3	_Playerdistance = Vector3(0.f, 0.f, 0.f);
		Vector3	_Playerpos = Vector3(0.f, 0.f, 0.f);
		Vector3 _pos = Vector3(0.f, 0.f, 0.f);
		Vector3 _BodyRotation = Vector3(0.f, 0.f, 0.f);
		Vector2 _velocity = Vector2(0.f, 0.f);
		Vector3 _ShortHairCreatepos = Vector3(0.f, 0.f, 0.f);
		Vector2 _HomingEditPOS = Vector2(0.f, 0.f);


	private:
		int		_Dir = 1;							// ���⼳��
		float	_time = 0.f;						// �������Ͻ� �����	
		float	_Attacktime = 0.f;					// �������Ͻ� ���������
		bool	_Ground_check = false;				// ��üũ�ÿ� ���̰� �ִ� ����
		bool	_BackGround_check = true;
		int		_Rushnumber = 0;					// ���� ���ݽ� 1�� = a, 2�� = b, 3�� =c , 0 = ������


	private:
		bool	_RushSwitch = false;

		bool	_CrossMeteorSwitch = false;
		bool	_CrossMeteorLanding = false;

		bool	_GroundMeteorSwitch = false;
		bool	_GroundMeteorLanding = false;
		bool	_GroundMeteorAttack_Right = false;
		bool	_GroundMeteorAttack_Left = false;

		bool	_VerticalMeteorSwitch = false;
		bool	_VerticalMeteorLanding = false;

		bool	_SkillA_Switch = false;
		bool	_SkillA_Landing = false;
		bool	_SkillHomingON = false;
		bool    _SkillHomingFire = false;
		int		_HomingNumber = 0;
		float   _HomingAngle[3];

		bool	_SkillB_Switch = false;

		bool	_SkillC_Switch = false;

		bool	_Intro_Switch = false;
		bool	_Intro_Landing = false;

		bool	_Awaken_Switch = false;
		bool	_Awaken_Ready = false;

		bool	_BackGround_Switch = false;
		bool	_BackGround_Idle = false;

		int		_SelectAttack = 0;



	};
}