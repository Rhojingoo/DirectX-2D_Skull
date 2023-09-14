#pragma once
#include "Include_Common.h"
#include "..\Engine_SOURCE\jkScene.h"
#include "Alpha_Blend.h"

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
		Alpha_Blend* _Alpha = nullptr;
		bool _Fadecheck = false;
		float _time = 0.f;
	};
}
