#pragma once
#include "Include_Common.h"
#include "jkPlayScene.h"
#include "Stage1_BossDoor.h"

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
		Back_ground* Kingbg = nullptr;
		Camera* cameraComp = nullptr;
		Player* _player = nullptr;
		Yggdrasil* _Stage1_Boss = nullptr;
		Stage1_BossDoor* _Door = nullptr;
		bool _first_groundturch = false;;
		bool _Boss_Create = false;;
		bool _Boss_Dead = false;;

		float _time = 0.f;
		bool _Fadein = false;
		bool _Fadeout = false;
		float _Fadetime = 0.f;
		
	};
}
