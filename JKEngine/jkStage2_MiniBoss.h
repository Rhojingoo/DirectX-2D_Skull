#pragma once
#include "Include_Common.h"
#include "jkPlayScene.h"
#include "Stage2_Door.h"

#include "Monster_ObjPool.h"
#include "MiniBoss_ObjCreate.h"

namespace jk
{
	class Stage2_MiniBoss : public PlayScene
	{
	public:
		Stage2_MiniBoss();
		virtual ~Stage2_MiniBoss();

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
		Player* _player = nullptr;
		Mini_Boss* Mboss = nullptr;
		Camera* cameraComp = nullptr;
		AudioSource* as = nullptr;
		Sound* _BGSound = nullptr;
		Alpha_Blend* _Alpha = nullptr;
		Stage2_Door* Door1 = nullptr;

	private:
		float _time = 0.f;
		bool _Fadecheck = false;
		bool _changecheck = false;

	private:
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
