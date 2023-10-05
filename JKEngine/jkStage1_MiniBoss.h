#pragma once
#include "Include_Common.h"
#include "..\Engine_SOURCE\jkScene.h"
#include "jkPlayScene.h"
#include "Monster_ObjPool.h"
#include "MiniBoss_ObjCreate.h"
#include "Stge_Manager.h"
#include "Mini_Boss.h"

#include "..\Engine_SOURCE\jkAudioSource.h"
#include "Sound.h"


namespace jk
{
	class Stage1_MiniBoss : public Scene
	{
	public:
		Stage1_MiniBoss();
		virtual ~Stage1_MiniBoss();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter();
		virtual void OnExit();

		void CamareShooting();

		void CreateMiniboss(int stage);
		int random(int a, int b);
		bool AreAllMiniBossDead(const std::vector<Mini_Boss*>& monsterGroup);

	private:
		AudioSource* as = nullptr;
		Sound* _BGSound = nullptr;

	private:
		Camera* cameraComp = nullptr;
		Player* _player = nullptr;
		Mini_Boss* Mboss = nullptr;
		Stage1_Door* Door1 = nullptr;


		MiniBoss_ObjCreate* OBJPOOL = nullptr;
		std::vector<Mini_Boss*> mBossGroup;

		bool _first_groundturch = false;;
		bool _MiniBoss_groundturch = false;
		bool _MiniBoss_Create = false;;
		bool _MiniBoss_Dead = false;;
		bool _Door_Open = false;
		int _Randomcheck = 0;
	};
}
