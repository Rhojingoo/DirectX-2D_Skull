#pragma once
#include "Include_Common.h"

namespace jk
{
	class out_Castle_Fore_ground : public BG
	{
	public:
		out_Castle_Fore_ground();
		virtual ~out_Castle_Fore_ground();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	};
}