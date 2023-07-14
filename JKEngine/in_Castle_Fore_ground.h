#pragma once
#include "Include_Common.h"

namespace jk
{
	class in_Castle_Fore_ground : public BG
	{
	public:
		in_Castle_Fore_ground();
		virtual ~in_Castle_Fore_ground();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	};
}