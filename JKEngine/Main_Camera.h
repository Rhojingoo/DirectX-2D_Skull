#pragma once
#include "jkGameObject.h"

namespace jk
{
	class Main_Camera : public GameObject
	{
	public:
		Main_Camera();
		virtual ~Main_Camera();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;


	};
}