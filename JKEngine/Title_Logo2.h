#pragma once
#include "Include_Common.h"

namespace jk
{
	class Title_Logo2 : public BG
	{
	public:
		Title_Logo2();
		virtual ~Title_Logo2();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

	};
}