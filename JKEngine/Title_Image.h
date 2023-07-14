#pragma once
#include "Include_Common.h"

namespace jk
{
	class Title_Image : public BG
	{
	public:
		Title_Image();
		virtual ~Title_Image();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

	};
}