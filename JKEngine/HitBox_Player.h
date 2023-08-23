#pragma once
#include "Include_Common.h"
#include "Attack_HitBox.h"


namespace jk
{
	class HitBox_Player : public Attack_HitBox
	{
	public:
		HitBox_Player();
		virtual ~HitBox_Player();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;


		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;


	private:
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		Vector3 pos = Vector3(0.f, 0.f, 0.f);

	};
}