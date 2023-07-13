#pragma once
#include "Include_Common.h"

namespace jk
{	
	class Player : public GameObject
	{
	public:

		Player();
		virtual ~Player();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;
	};
}