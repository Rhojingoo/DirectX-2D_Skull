#pragma once
#include "jkPlayScene.h"


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
		class Player* _player = nullptr;
		class Camera* cameraComp = nullptr;
		class AudioSource* as = nullptr;
		class Sound* _BGSound = nullptr;
		class Alpha_Blend* _Alpha = nullptr;
		class Stage2_Door* Door1 = nullptr;
		class Monster_ObjPool* OBJPOOL = nullptr;
		class Stage_Manager* StageMn = nullptr;

	private:
		float _time = 0.f;
		bool _Fadecheck = false;
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
		bool first_groundtouch = false;;
		bool first_MonsterCreate = false;;
		bool _Monster_Start = false;
		bool _CamFirstSet = false;
	};
}
