#pragma once
#include "Include_Common.h"


namespace jk
{
	class Devil_Castle_front : public BG
	{
	public:
		Devil_Castle_front();
		virtual ~Devil_Castle_front();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	};
}