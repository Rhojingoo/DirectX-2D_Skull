#pragma once
#include "jkScene.h"
#include "jkPlayScene.h"

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
