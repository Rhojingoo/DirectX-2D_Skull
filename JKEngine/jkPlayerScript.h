#pragma once
#include "..\\Engine_SOURCE\\jkScript.h"
#include "..\\Engine_SOURCE\\jkCamera.h"
#include "Include_Common.h"

namespace jk
{
	class PlayerScript : public Script
	{
	public:
		virtual void Update() override;

		//virtual void OnCollisionEnter(Collider2D* other) override;
		//virtual void OnCollisionStay(Collider2D* other) override;
		//virtual void OnCollisionExit(Collider2D* other) override;

	private:

	};
}