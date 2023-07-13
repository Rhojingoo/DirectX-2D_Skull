#pragma once
#include "Include_Common.h"


namespace jk
{
	class UI : public GameObject
	{
	public:
		UI();
		virtual ~UI();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;
	};
}