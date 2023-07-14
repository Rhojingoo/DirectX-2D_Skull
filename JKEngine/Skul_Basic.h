#pragma once
#include "Include_Common.h"

namespace jk
{
	class Skul_Basic : public Player
	{
	public:

		Skul_Basic();
		virtual ~Skul_Basic();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;
	};
}