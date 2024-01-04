#pragma once
#include "Bullet.h"

namespace jk
{
	class Monster_Bullet : public Bullet
	{
	public:
		Monster_Bullet();
		virtual ~Monster_Bullet();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;
		
		void Setsound(int set) { _bulletsound = set; }
		int Getsound() {return _bulletsound;}

		int _bulletsound = 0;

	};
}