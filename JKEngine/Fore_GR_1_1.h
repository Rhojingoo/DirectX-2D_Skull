#pragma once
#include "Include_Common.h"


namespace jk
{
	class Fore_GR_1_1 : public BG
	{
	public:
		Fore_GR_1_1();
		virtual ~Fore_GR_1_1();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};

}