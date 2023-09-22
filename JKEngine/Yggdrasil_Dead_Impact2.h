#pragma once
#include "Include_Common.h"

namespace jk
{
	class Yggdrasil_Dead_Impact2 : public Effect
	{
	public:
		Yggdrasil_Dead_Impact2();
		virtual ~Yggdrasil_Dead_Impact2();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;
		void complete();

	private:
		Animator* at = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
	};
}