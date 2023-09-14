#pragma once
#include "Include_Common.h"
#include "..\Engine_SOURCE\jkScene.h"
#include "Player.h"

namespace jk
{
	class PlayScene : public Scene
	{
	public:
		PlayScene();
		virtual ~PlayScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		//void SetPlayer(Player* set) { _player = set; }
		//Player* GetPlayer() { return _player; }

	private:
		//static Player* _player;
	};
}
