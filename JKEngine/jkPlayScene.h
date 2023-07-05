#pragma once
//#include <jkScene.h>
#include "..\Engine_SOURCE\jkScene.h"

namespace jk
{
	class PlayScene : public Scene
	{
	public:
		PlayScene();
		virtual ~PlayScene();

		virtual void Initialize(HWND hWnd) override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
		HWND mHwnd;
		HDC mHdc;

	};
}
