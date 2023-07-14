#pragma once
#include "Include_Common.h"

namespace jk
{
	class S1_King_BG : public BG
	{
	public:
		S1_King_BG();
		virtual ~S1_King_BG();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};
}