#pragma once
#include "jkGameObject.h"

namespace jk
{
	class Item_OBJ : public GameObject
	{
	public:
		Item_OBJ();
		virtual ~Item_OBJ();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

	};
}