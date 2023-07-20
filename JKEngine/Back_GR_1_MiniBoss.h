#pragma once
#include "Include_Common.h"


namespace jk
{
	class Back_GR_1_MiniBoss : public BG
	{
	public:
		Back_GR_1_MiniBoss();
		virtual ~Back_GR_1_MiniBoss();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};

}