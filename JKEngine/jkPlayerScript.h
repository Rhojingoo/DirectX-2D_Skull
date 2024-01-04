#pragma once
#include "..\\Engine_SOURCE\\jkScript.h"


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