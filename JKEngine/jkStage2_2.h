#pragma once
#include "Include_Common.h"
#include "jkPlayScene.h"
#include "Stage2_Door.h"

#include "Monster_ObjPool.h"

namespace jk
{
	class Stage2_2 : public PlayScene
	{
	public:
		Stage2_2();
		virtual ~Stage2_2();

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
		Player* _player = nullptr;
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
	private:
		bool first_groundturch = false;;
		bool first_MonsterCreate = false;;
	};
}
