#pragma once
#include "Include_Common.h"
#include "jkPlayScene.h"

#include "Monster_ObjPool.h"
#include "Stge_Manager.h"
#include "..\Engine_SOURCE\jkAudioSource.h"
#include "Sound.h"

namespace jk
{
	class Stage1_2 : public PlayScene
	{
	public:
		Stage1_2();
		virtual ~Stage1_2();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter();
		virtual void OnExit();

		void CamareShooting();
		void SetMonOBJ();
		bool AreAllMonstersDead(const std::vector<Monster*>& monsterGroup, bool check);

	private:
		AudioSource* as = nullptr;
		Sound* _BGSound = nullptr;

	private:
		Stage1_Door* Door1 = nullptr;
		Camera* cameraComp = nullptr;
		Player* _player = nullptr;
		bool _changecheck = false;

	private:
		Monster_ObjPool* OBJPOOL = nullptr;
		Stage_Manager* StageMn = nullptr;
		bool firstMonsters = false;
		bool secondMonsters = false;
		bool thirdMonsters = false;

		std::vector<Monster*> monsterGroup1;
		std::vector<Monster*> monsterGroup2;
		std::vector<Monster*> monsterGroup3;
		bool change_monster1 = false;
		bool change_monster2 = false;
		bool change_monster3 = false;

	};
}
