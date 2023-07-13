#pragma once
#include "Include_Common.h"


namespace jk
{
	class Devil_Castle : public BG
	{
	public:
		Devil_Castle();
		virtual ~Devil_Castle();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};

}