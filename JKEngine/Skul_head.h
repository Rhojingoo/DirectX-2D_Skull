#pragma once
#include "jkGameObject.h"

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

		int random(int a, int b);
		void SetDirection(int dir) { _Dir = dir; }
		void Setattack(bool check) { _attack = check; }
		class RigidBody* Getrigidbody() {return _rigidbody;}
		void Setgroundcheck(bool check) { _Ground_check = check; }
		void SetBeforeAttackPos(Vector3 set) { _Before_Attack_Pos = set; }


		bool SetHead = false;
		bool _Head_Rotation = false;
		bool _Head_Boom = false;
		bool _Head_Attack = false;
		bool Head_Life = false;
		bool _Ground_check = false;

		float GetDamage() { return _Damage; }
		bool Geteffect() { return attack; }
		bool Geteffect_Mid() { return attack_Cri_Mid; }
		bool Geteffect_Hight() { return attack_Cri_High; }
		void Seteffect(bool set) { attack = set; }
		void Seteffect_Mid(bool set) { attack_Cri_Mid = set; }
		void Seteffect_Hight(bool set) { attack_Cri_High = set; }


	private:
		class Animator* at = nullptr;
		class RigidBody* _rigidbody = nullptr;
		class Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		Vector3 pos = Vector3(0.f, 0.f, 0.f);
		Vector3 _Before_Attack_Pos = Vector3(0.f, 0.f, 0.f);
		Vector2 _velocity = Vector2(0.f, 0.f);

	private:
		int _Dir = 1;
		float _time = 0.f;
		bool _attack = false;
		int		_HitType = 0;
		float	_Damage = 0.f;
		bool attack = false;
		bool attack_Cri_Mid = false;
		bool attack_Cri_High = false;

	};
}