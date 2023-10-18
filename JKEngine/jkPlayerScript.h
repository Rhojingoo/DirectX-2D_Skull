#pragma once
#include "..\\Engine_SOURCE\\jkScript.h"
#include "..\\Engine_SOURCE\\jkCamera.h"
#include "Include_Common.h"

namespace jk
{
	class PlayerScript : public Script
	{
	public:
		PlayerScript();
		~PlayerScript();


		virtual void Initialize() override;
		virtual void Update() override;

		void Complete();
	};
}