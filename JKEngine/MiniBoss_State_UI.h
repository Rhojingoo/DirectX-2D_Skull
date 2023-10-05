#pragma once
#include "Include_Common.h"

namespace jk
{
	class MiniBoss_State_UI : public GameObject
	{
	public:
		MiniBoss_State_UI();
		virtual ~MiniBoss_State_UI();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;
	};
}