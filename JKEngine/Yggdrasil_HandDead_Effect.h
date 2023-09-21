#pragma once
#include "Include_Common.h"

namespace jk
{
	class Yggdrasil_HandDead_Effect : public Effect
	{
	public:
		Yggdrasil_HandDead_Effect();
		virtual ~Yggdrasil_HandDead_Effect();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void SetDirection(int set) { _Dir = set; }
		void SetDirectionBool(bool set) { _DirectionSellect = set; }

	private:

		Animator* at = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;

	private:
		float mTime = 0.f;
		bool _DirectionSellect = false;
		int _Dir = 1;
	};
}