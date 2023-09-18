#pragma once
#include "Include_Common.h"


namespace jk
{
	class Blosome : public GameObject
	{
	public:
		Blosome();
		virtual ~Blosome();

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
		int	mDir = 1;

	};
}