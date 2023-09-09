#pragma once
#include "Include_Common.h"
#include "jkPlayScene.h"

namespace jk
{
	class OutSide_CastleArea : public PlayScene
	{
	public:
		OutSide_CastleArea();
		virtual ~OutSide_CastleArea();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter();
		virtual void OnExit();

	private:
		Player* _player = nullptr;
		Camera* cameraComp = nullptr;
	};
}
