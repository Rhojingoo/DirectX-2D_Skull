#pragma once
#include "Include_Common.h"
#include "jkPlayScene.h"

namespace jk
{
	class Stage1_Boss : public PlayScene
	{
	public:
		Stage1_Boss();
		virtual ~Stage1_Boss();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter();
		virtual void OnExit();

		void CamareShooting();

	private:
		Camera* cameraComp = nullptr;
		Player* _player = nullptr;
		Yggdrasil* _Stage1_Boss = nullptr;
		bool _first_groundturch = false;;
		bool _Boss_Create = false;;
		bool _Boss_Dead = false;;
	};
}
