#pragma once
#include "Include_Common.h"
#include "jkPlayScene.h"
#include "Mini_Boss.h"

namespace jk
{
	class Stage1_MiniBoss : public PlayScene
	{
	public:
		Stage1_MiniBoss();
		virtual ~Stage1_MiniBoss();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter();
		virtual void OnExit();

	private:
		Mini_Boss* Mboss = nullptr;
	};
}
