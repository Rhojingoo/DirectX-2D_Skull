#pragma once
#include "jkGameObject.h"


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