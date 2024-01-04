#pragma once
#include "jkPlayScene.h"


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
		class AudioSource* as = nullptr;
		class Sound* _BGSound = nullptr;
		class Stage1_Door* Door1 = nullptr;
		class Camera* cameraComp = nullptr;
		class Player* _player = nullptr;
		class Monster_ObjPool* OBJPOOL = nullptr;
		class Stage_Manager* StageMn = nullptr;


	private:
		bool _changecheck = false;
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
