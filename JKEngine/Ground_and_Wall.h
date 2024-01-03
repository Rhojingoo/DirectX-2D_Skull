#pragma once
#include "BG.h"


namespace jk
{
	class Ground_and_Wall : public BG
	{
	public:
		Ground_and_Wall();
		virtual ~Ground_and_Wall();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;


		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		class Collider2D* _collider = nullptr;
	};

}