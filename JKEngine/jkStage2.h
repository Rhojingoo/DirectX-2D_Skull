#pragma once
#include "Include_Common.h"
#include "jkPlayScene.h"

namespace jk
{
	class Stage2 : public PlayScene
	{
	public:
		Stage2();
		virtual ~Stage2();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}
