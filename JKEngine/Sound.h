#pragma once
#include "jkGameObject.h"

namespace jk
{
	class Sound : public GameObject
	{
	public:
		Sound();
		virtual ~Sound();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;
	};
}