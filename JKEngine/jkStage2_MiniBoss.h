#pragma once
#include "jkPlayScene.h"


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
		class Player* _player = nullptr;
		class Mini_Boss* Mboss = nullptr;
		class Camera* cameraComp = nullptr;
		class AudioSource* as = nullptr;
		class Sound* _BGSound = nullptr;
		class Alpha_Blend* _Alpha = nullptr;
		class Stage2_Door* Door1 = nullptr;
		class MiniBoss_ObjCreate* OBJPOOL = nullptr;


	private:
		float _time = 0.f;
		bool _Fadecheck = false;
		bool _changecheck = false;
		bool _mbosscreate = false;
		std::vector<Mini_Boss*> mBossGroup;
		bool _first_groundtouch = false;;
		bool _MiniBoss_groundtouch = false;
		bool _MiniBoss_Create = false;;
		bool _MiniBoss_Dead = false;;
		bool _Door_Open = false;
		int _Randomcheck = 0;
	};	
}
