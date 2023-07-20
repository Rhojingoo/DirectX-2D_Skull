#pragma once
#include "Include_Common.h"


namespace jk
{
	class Fore_GR_1_2 : public BG
	{
	public:
		Fore_GR_1_2();
		virtual ~Fore_GR_1_2();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};

}