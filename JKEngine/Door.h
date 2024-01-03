#pragma once
#include "BG.h"

namespace jk
{
	class Door : public BG
	{
	public:
		Door();
		~Door();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;


	private:
		class MeshRenderer* _MeshRenderer;
		Transform* tr;
	};
}