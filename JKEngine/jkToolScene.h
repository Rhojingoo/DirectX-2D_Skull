#pragma once
//#include <jkScene.h>
#include "..\Engine_SOURCE\jkScene.h"

namespace jk
{
	class ToolScene : public Scene
	{
	public:
		ToolScene();
		virtual ~ToolScene();

		virtual void Initialize(HWND hWnd) override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
		PAINTSTRUCT ps;
		HDC hdc;
	};
}
