#pragma once
#include "Attack_HitBox.h"

namespace jk
{
	class HitBox_Layana : public Attack_HitBox
	{
	public:
		HitBox_Layana();
		virtual ~HitBox_Layana();

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
		class Collider2D* _collider = nullptr;
		Transform* tr = nullptr;

		Vector2 _Size = Vector2(150.f, 150.f);
		Vector3 _Center = Vector3(0.f, 0.f, -250.f);

	};
}