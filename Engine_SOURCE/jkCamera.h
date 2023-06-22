#pragma once
#include "jkComponent.h"
#include "jkGraphics.h"

namespace jk
{
	class Camera : public Component
	{
	public:
		Camera();
		~Camera();

	private:
		static Matrix mView;
		static Matrix mProjection;
	};
}
