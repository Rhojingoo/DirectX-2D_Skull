#pragma once
#include "Include_Common.h"

namespace jk
{
	class Player_Hp_Bar : public GameObject
	{
	public:
		Player_Hp_Bar();
		virtual ~Player_Hp_Bar();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;
	};
}