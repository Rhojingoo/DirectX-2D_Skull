#pragma once
#include "Include_Common.h"
#include "Bullet.h"


namespace jk
{
	class MiniBoss_Bullet : public Bullet
	{
	public:
		MiniBoss_Bullet();
		virtual ~MiniBoss_Bullet();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

	};
}