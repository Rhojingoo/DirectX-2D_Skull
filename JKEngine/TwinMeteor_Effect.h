#pragma once
#include "Include_Common.h"
#include "Bullet.h"
#include "Hit_Critical_Middle.h"


namespace jk
{
	class TwinMeteor_Effect : public Bullet
	{
	public:
		TwinMeteor_Effect();
		virtual ~TwinMeteor_Effect();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		static void SetDirection(int set) { mDir = set; }
		static int	mDir;
		static bool	_SwitchOn;
		static bool	_SwitchOff;

		void Compelete_Pierce();

	private:
		Transform* _tr = nullptr;
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		Hit_Critical_Middle* _Critical_Middle = nullptr;
	};
}