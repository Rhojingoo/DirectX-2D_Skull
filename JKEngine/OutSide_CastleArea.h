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
		Alpha_Blend* _Alpha = nullptr;
		float _time = 0.f;
		bool _Fadecheck = false;
		Stage1_Door* Door1 = nullptr;
	};
}