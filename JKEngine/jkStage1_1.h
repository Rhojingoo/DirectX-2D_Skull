#pragma once
#include "Include_Common.h"
#include "..\Engine_SOURCE\jkScene.h"
#include "jkPlayScene.h"
#include "Monster_ObjPool.h"
#include "Stge_Manager.h"
#include "..\Engine_SOURCE\jkAudioSource.h"
#include "Sound.h"


namespace jk
{
	class Stage1_1 : public Scene
	{
	public:
		Stage1_1();
		virtual ~Stage1_1();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter();
		virtual void OnExit();

		void CamareShooting();
		void SetMonOBJ();
		bool AreAllMonstersDead(const std::vector<Monster*>& monsterGroup, bool check);


		bool Monsters_check = false;
		float time = 0.f;

	private:
		AudioSource* as = nullptr;
		Sound* _BGSound = nullptr;

	private:
		Camera* cameraComp = nullptr;
		Player* _player = nullptr;		
		bool _changecheck = false;


		Stage1_Door* Door1 = nullptr;
		bool first_groundturch = false;;
		bool first_MonsterCreate = false;;

	private:
		Monster_ObjPool* OBJPOOL = nullptr;
		Stage_Manager* StageMn = nullptr;
		bool firstMonsters = false;
		bool secondMonsters = false;
		bool thirdMonsters = false;
		bool fourthMonsters = false;
		std::vector<Monster*> monsterGroup1;
		std::vector<Monster*> monsterGroup2;
		std::vector<Monster*> monsterGroup3;
		std::vector<Monster*> monsterGroup4;
		bool change_monster1 = false;
		bool change_monster2 = false;
		bool change_monster3 = false;
		bool change_monster4 = false;
	};


}
