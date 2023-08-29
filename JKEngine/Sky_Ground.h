#pragma once
#include "Include_Common.h"


namespace jk
{
	class Sky_Ground : public BG
	{
	public:
		Sky_Ground();
		virtual ~Sky_Ground();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;


		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		Collider2D* _collider = nullptr;
	};

}