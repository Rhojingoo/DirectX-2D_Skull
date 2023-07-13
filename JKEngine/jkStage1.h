#pragma once
#include "Include_Common.h"
#include "jkPlayScene.h"

namespace jk
{
	class jkStage1 : public PlayScene
	{
	public:
		jkStage1();
		virtual ~jkStage1();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}
