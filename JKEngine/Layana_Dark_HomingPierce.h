#pragma once
#include "Effect.h"

namespace jk
{
	class Layana_Dark_HomingPierce : public Effect
	{
	public:
		Layana_Dark_HomingPierce();
		virtual ~Layana_Dark_HomingPierce();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;


		void SetDirection(int set) { _Dir = set; }
		int	_Dir = 1;
		bool _effect_switch = false;
		bool _Create_ball = false;
		bool _bulletoff = false;
		void Compelete_Begin();
		void Compelete_Pierce();


	private:
		class Animator* at = nullptr;
		class RigidBody* _rigidbody = nullptr;
		class Collider2D* _collider = nullptr;
		Transform* tr = nullptr;

	private:
		float _attackatime = 0.f;
	};
}