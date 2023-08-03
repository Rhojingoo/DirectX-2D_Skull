
#pragma once
#include "Include_Common.h"

namespace jk
{
	class Ice_wizard : public Monster
	{
	public:
		Ice_wizard();
		virtual ~Ice_wizard();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;


		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		//static GameObject SetoWner(GameObject* ac) { oWner = ac; }

		enum class Ice_wizard_State
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
		Ice_wizard_State _state;
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		Vector3 pos = Vector3(0.f, 0.f, 0.f);
		//Vector3 _playerpos = Vector3(0.f, 0.f, 0.f);
		Vector2 _velocity = Vector2(0.f, 0.f);

	private:
		static int			mDir;
		static bool			_switch;



		float	_distance = 0.f;			// 플레이어와의 거리 체크
		bool	_Ground_check = false;		// 땅체크시에 쓰이고 있는 변수

		bool	_dash = false;
		float	_time = 0.f;				// 공격시 사용중
		bool	_attack = false;			// 공격에서 idle로 보내는 스위치 변수
		int		_number_of_attack = 0;		// 공격횟수에 따라 idle로 보내는데, 공격횟수를 체크하는 변수
		int		_attackorder = 0;			// 콤보공격의 경우 순서가 정해져 있어 해당 순서에 진행하도록 설정하는 변수 
		int		_choicecombo = 0;			// 공격종류의 선택을 할수 있도록 설정하는 변수
		//bool _jump = 0;
		//int _fallcheck = 0;

	private:


	};
}