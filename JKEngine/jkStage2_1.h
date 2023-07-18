#pragma once
#include "Include_Common.h"
#include "jkPlayScene.h"

namespace jk
{
	class Stage2_1 : public PlayScene
	{
	public:
		Stage2_1();
		virtual ~Stage2_1();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}
