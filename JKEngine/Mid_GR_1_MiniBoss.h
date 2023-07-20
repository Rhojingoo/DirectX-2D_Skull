#pragma once
#include "Include_Common.h"


namespace jk
{
	class Mid_GR_1_MiniBoss : public BG
	{
	public:
		Mid_GR_1_MiniBoss();
		virtual ~Mid_GR_1_MiniBoss();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};

}