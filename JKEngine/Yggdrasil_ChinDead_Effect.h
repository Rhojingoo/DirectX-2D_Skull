#pragma once
#include "Include_Common.h"

namespace jk
{
	class Yggdrasil_ChinDead_Effect : public Effect
	{
	public:
		Yggdrasil_ChinDead_Effect();
		virtual ~Yggdrasil_ChinDead_Effect();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

	private:
		Animator* at = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;

	private:
		float mTime = 0.f;
	};
}