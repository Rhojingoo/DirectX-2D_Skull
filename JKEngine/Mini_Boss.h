#pragma once
#include "Include_Common.h"

namespace jk
{
	class Mini_Boss : public GameObject
	{
	public:
		Mini_Boss();
		virtual ~Mini_Boss();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;


		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

	};
}