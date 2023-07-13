#pragma once
#include "Include_Common.h"
#include "jkPlayScene.h"

namespace jk
{
	class Castle_Area : public PlayScene
	{
	public:
		Castle_Area();
		virtual ~Castle_Area();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}
