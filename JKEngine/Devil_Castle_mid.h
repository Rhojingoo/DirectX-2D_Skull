#pragma once
#include "Include_Common.h"


namespace jk
{
	class Devil_Castle_mid : public BG
	{
	public:
		Devil_Castle_mid();
		virtual ~Devil_Castle_mid();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};
}