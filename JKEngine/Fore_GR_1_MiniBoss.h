#pragma once
#include "Include_Common.h"


namespace jk
{
	class Fore_GR_1_MiniBoss : public BG
	{
	public:
		Fore_GR_1_MiniBoss();
		virtual ~Fore_GR_1_MiniBoss();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};

}