#pragma once
#include "Include_Common.h"
#include "Attack_HitBox.h"


namespace jk
{
	class HitBox_Mage : public Attack_HitBox
	{
	public:
		HitBox_Mage();
		virtual ~HitBox_Mage();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void SetSize(Vector2 set) { _Size = set; }
		void SetCenter(Vector3 set) { _Center = set; }

	private:
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;

		Vector2 _Size = Vector2(150.f, 150.f);
		Vector3 _Center = Vector3(0.f, 0.f, -250.f);

	};
}