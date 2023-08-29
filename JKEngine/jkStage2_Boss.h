#pragma once
#include "Include_Common.h"
#include "jkPlayScene.h"

namespace jk
{
	class Stage2_Boss : public PlayScene
	{
	public:
		Stage2_Boss();
		virtual ~Stage2_Boss();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}
