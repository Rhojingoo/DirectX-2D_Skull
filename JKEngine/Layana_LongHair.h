#pragma once
#include "Include_Common.h"
#include "Layana_Sisters.h"

namespace jk
{
	class Layana_LongHair : public Layana_Sisters
	{
	public:
		Layana_LongHair();
		virtual ~Layana_LongHair();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void idle();

		void Rushready();
		void Rush_A();
		void Rush_B();
		void Rush_C();
		void Rush_End();
		void Dash();

		void CrossJump();
		void CrossReady();
		void CrossAttack();
		void CrossLanding();
		void CrossEnd();


		void die();

	public:
		void Rush_Combo();
		void Complete_Rush();
		void Complete_RushReady();
		void Complete_CrossJump();
		void Complete_CrossLanding();
		void Complete_CrossEnd();

	private:
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
	private:
		Vector3	_Playerdistance = Vector3(0.f, 0.f, 0.f);
		Vector3	_Playerpos = Vector3(0.f, 0.f, 0.f);
		Vector3 _pos = Vector3(0.f, 0.f, 0.f);
		Vector3 _BodyRotation = Vector3(0.f, 0.f, 0.f);
		Vector2 _velocity = Vector2(0.f, 0.f);


	private:
		int		_Dir = 1;							// ���⼳��
		float	_time = 0.f;						// ���ݽ� �����	
		bool	_Ground_check = false;				// ��üũ�ÿ� ���̰� �ִ� ����
		int		_Rushnumber = 0;					// ���� ���ݽ� 1�� = a, 2�� = b, 3�� =c , 0 = ������


	private:
		bool	_RushSwitch = false;
		bool	_CrossMeteorSwitch = false;
		bool	_CrossMeteorLanding = false;

		int		_SelectAttack = 0;
	};

}