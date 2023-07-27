#pragma once
#include "Include_Common.h"

namespace jk
{
	class BG : public GameObject
	{
	public:
		BG();
		virtual ~BG();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;
		

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

	};
}