#pragma once
#include "..\Engine_SOURCE\jkScene.h"

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
		class AudioSource* as = nullptr;
		class Sound* _BGSound = nullptr;
		class Camera* cameraComp = nullptr;
		class Player* _player = nullptr;		
		class Stage1_Door* Door1 = nullptr;
		class Monster_ObjPool* OBJPOOL = nullptr;
		class Stage_Manager* StageMn = nullptr;


	private:
		bool _changecheck = false;
		bool first_groundturch = false;
		bool first_MonsterCreate = false;
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
