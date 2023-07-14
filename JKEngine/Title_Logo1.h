#pragma once
#include "Include_Common.h"

namespace jk
{
	class Title_Logo1 : public BG
	{
	public:
		Title_Logo1();
		virtual ~Title_Logo1();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

	};
}