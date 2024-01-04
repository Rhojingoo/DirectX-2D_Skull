#pragma once
#include "jkGameObject.h"


namespace jk
{
	class Player_State_UI : public GameObject
	{
	public:
		Player_State_UI();
		virtual ~Player_State_UI();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;
	};
}