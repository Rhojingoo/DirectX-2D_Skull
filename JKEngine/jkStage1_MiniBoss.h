#pragma once
#include "Include_Common.h"
#include "..\Engine_SOURCE\jkScene.h"
#include "jkPlayScene.h"
#include "Monster_ObjPool.h"
#include "Stge_Manager.h"
#include "Mini_Boss.h"

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
		void SetMonOBJ();
		bool AreAllMonstersDead(const std::vector<Monster*>& monsterGroup);


	private:
		Mini_Boss* Mboss = nullptr;

		Monster_ObjPool* OBJPOOL = nullptr;
		Stage_Manager* StageMn = nullptr;
		std::vector<Monster*> monsterGroup1;
		std::vector<Monster*> monsterGroup2;
		bool test = false;
		bool test2 = false;
		bool Monsters_check = false;
		bool firstMonsters = false;
		float time = 0.f;
	};
}
