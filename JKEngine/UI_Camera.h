#pragma once
#include "jkGameObject.h"

namespace jk
{
	class UI_Camera : public GameObject
	{
	public:
		UI_Camera();
		virtual ~UI_Camera();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;


	private:

	};
}