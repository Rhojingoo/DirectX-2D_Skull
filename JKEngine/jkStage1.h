#pragma once
//#include <jkScene.h>
#include "jkPlayScene.h"

namespace jk
{
	class jkStage1 : public PlayScene
	{
	public:
		jkStage1();
		virtual ~jkStage1();

		virtual void Initialize(HWND hWnd) override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}
