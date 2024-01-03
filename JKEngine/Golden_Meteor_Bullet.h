#pragma once
#include "Bullet.h"

namespace jk
{
	class Golden_Meteor_Bullet : public Bullet
	{
	public:
		Golden_Meteor_Bullet();
		virtual ~Golden_Meteor_Bullet();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;


		 void SetDirection(int set) { _Dir = set; }
		 void SetSwitch(bool set) { _effect_switch = set; }


	private:
		class Animator* at = nullptr;
		class RigidBody* _rigidbody = nullptr;
		class Collider2D* _collider = nullptr;
		Transform* tr = nullptr;

	private:
		int	_Dir = 1;
		bool _effect_switch = false;
	};
}