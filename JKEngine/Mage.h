#pragma once
#include "Include_Common.h"

namespace jk
{
	class Mage : public Mini_Boss
	{
	public:
		Mage();
		virtual ~Mage();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;


		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		enum class Mage_State
		{
			Idle,			
			Die,
			Attack_A,
			Attack_A_Ready,
			Attack_B,
			Attack_B_Ready,
			Attack_C,
			Attack_C_Run,
			Attack_C_Ready,
			Attack_D,
			Attack_D_Ready,
			Fly,
			Groggy,
			Hit,
			Intro,
			Potion,
			WalkBack_R,
			WalkBack_L,
			WalkFront_R,
			WalkFront_L,
		};

		void idle();
		void die();
		void attack_a();
		void attack_a_ready();
		void attack_b();
		void attack_b_ready();
		void attack_c();
		void attack_c_run();
		void attack_c_ready();
		void attack_d();
		void attack_d_ready();
		void fly();
		void groggy();
		void hit();
		void intro();
		void potion();
		void walkBack_R();
		void walkBack_L();
		void WalkFront_R();
		void WalkFront_L();

		
	private:
		Mage_State _state;
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		Vector3 pos = Vector3(0.f, 0.f, 0.f);
		Vector2 _velocity = Vector2(0.f, 0.f);
		Vector3 _first_place = Vector3(0.f, 0.f, 0.f);

	private:
		int		mDir = 1;
		float	_time = 0.f;						// ���ݽ� �����
		bool	_attack = false;					// ���ݿ��� idle�� ������ ����ġ ����
		float	_distance = 0.f;					// �÷��̾���� �Ÿ� üũ
		bool	_Ground_check = false;				// ��üũ�ÿ� ���̰� �ִ� ����	


		
		int		_swich_checkpoint = 0;				// ����Ƚ���� ���� ��Ǽ��� 0 = ����, 1= ����A, 2= ����B, 3 = �ʻ��
		int     _flyswich = 0;						// �ϴ� ���ƴٴϴ� ����
		int     _landingswich = 0;					// ����C�� ������
		bool    _sky = true;
		bool    _ground = false;

		//�����û�뺯����
		int		_movechoice = 1;					// ������ �̿�
		float   _maxright = 250;
		float   _maxleft = -250;
		float   _movetime = 0.f;
		int     _mtime = 0;

		//����A ����
		int		_attackA = 0;						// ���� A ������ ����	

		//����B ����
		float   _attacktB_time = 0;					// ���� B ���ݽð� üũ	

		//����C ����
		int		_attackC = 0;						// ���� B ������ ����	





	private:
		Skul_Basic::Skul_Basic_State Skul_BasicState;

	private:
		void attack_a_complete();
		void attack_b_complete();
		void attack_c_complete();
		void attack_d_complete();
		void attack_a_ready_complete();
		void attack_b_ready_complete();
		void attack_c_ready_complete();
		void attack_d_ready_complete();
		void complete_hit();
		int randomcount(int a, int b);

	};
}