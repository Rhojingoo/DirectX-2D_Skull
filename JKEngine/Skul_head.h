#pragma once
#include "Include_Common.h"


namespace jk
{
	class Animator;
	class Skul_head : public GameObject
	{
	public:
		Skul_head();
		virtual ~Skul_head();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;


		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void SetDirection(int dir) { mDir = dir; }
		void Setattack(bool check) { _attack = check; }
		RigidBody* Getrigidbody() {return _rigidbody;}
		void Setgroundcheck(bool check) { _Ground_check = check; }
		void SetBeforeAttackPos(Vector3 set) { _Before_Attack_Pos = set; }

		bool SetHead = false;
		bool _Head_Rotation = false;
		bool _Head_Boom = false;
		bool _Head_Attack = false;
		bool Head_Life = false;
		bool _Ground_check = false;

	private:
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		Vector3 pos = Vector3(0.f, 0.f, 0.f);
		Vector3 _Before_Attack_Pos = Vector3(0.f, 0.f, 0.f);
		Vector2 _velocity = Vector2(0.f, 0.f);

	private:
		//Skul_Head_State _state = Skul_Head_State::Move;
		int mDir = 1;
		float _time = 0.f;
		bool _attack = false;
		//bool _Ground_check = false;
	};
}