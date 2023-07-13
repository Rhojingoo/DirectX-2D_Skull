#pragma once
#include "Include_Common.h"


namespace jk
{
	class Grid : public GameObject
	{
	public:
		Grid();
		virtual ~Grid();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;
	};
}