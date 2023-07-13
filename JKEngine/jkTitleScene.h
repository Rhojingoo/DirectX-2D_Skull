#pragma once
#include "Include_Common.h"
#include "..\Engine_SOURCE\jkScene.h"


namespace jk
{
	class jkTitleScene : public Scene
	{
	public:
		jkTitleScene();
		virtual ~jkTitleScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}
