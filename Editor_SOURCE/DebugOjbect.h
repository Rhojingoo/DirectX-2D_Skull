#pragma once
#include "..\\Engine_SOURCE\\jkGameObject.h"

namespace gui
{
	class DebugOjbect : public jk::GameObject
	{
	public:
		DebugOjbect();
		~DebugOjbect();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
	};
}
