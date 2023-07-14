#pragma once
#include "Include_Common.h"

namespace jk
{
	class S2_King_BG : public BG
	{
	public:
		S2_King_BG();
		virtual ~S2_King_BG();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};
}