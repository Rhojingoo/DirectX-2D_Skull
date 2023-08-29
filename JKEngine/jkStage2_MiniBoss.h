#pragma once
#include "Include_Common.h"
#include "jkPlayScene.h"

namespace jk
{
	class Stage2_MiniBoss : public PlayScene
	{
	public:
		Stage2_MiniBoss();
		virtual ~Stage2_MiniBoss();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}
