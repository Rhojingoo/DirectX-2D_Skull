#pragma once
#include "Include_Common.h"
#include "jkPlayScene.h"
#include "Alpha_Blend.h"

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


		virtual void OnEnter();
		virtual void OnExit();

	private:
		Player* _player = nullptr;
		Alpha_Blend* _Alpha = nullptr;
		Back_ground* Castle_wall_Back = nullptr;
		Camera* cameraComp = nullptr;
	};
}
