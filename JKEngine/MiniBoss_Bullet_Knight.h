#pragma once
#include "Bullet.h"


namespace jk
{
	class MiniBoss_Bullet_Knight : public Bullet
	{
	public:
		MiniBoss_Bullet_Knight();
		virtual ~MiniBoss_Bullet_Knight();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

	};
}