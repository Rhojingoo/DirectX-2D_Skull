#pragma once
#include "Include_Common.h"
#include "jkPlayScene.h"

namespace jk
{
	class Stage1_1 : public PlayScene
	{
	public:
		Stage1_1();
		virtual ~Stage1_1();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}
