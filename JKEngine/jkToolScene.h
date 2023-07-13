#pragma once
#include "Include_Common.h"
#include "..\Engine_SOURCE\jkScene.h"

namespace jk
{
	class ToolScene : public Scene
	{
	public:
		ToolScene();
		virtual ~ToolScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}
