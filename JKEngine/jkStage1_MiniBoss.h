#pragma once
#include "..\Engine_SOURCE\jkScene.h"

namespace jk
{
	class Mini_Boss;
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

		void CreateMiniboss();
		int random(int a, int b);
		bool AreAllMiniBossDead(const std::vector<Mini_Boss*>& monsterGroup);

	private:
		class AudioSource* as = nullptr;
		class Sound* _BGSound = nullptr;
		class Camera* cameraComp = nullptr;
		class Player* _player = nullptr;
		class Mini_Boss* Mboss = nullptr;
		class Stage1_Door* Door1 = nullptr;


	private:
		bool _changecheck = false;
		std::vector<Mini_Boss*> mBossGroup = {};
		bool _first_groundtouch = false;;
		bool _MiniBoss_groundtouch = false;
		bool _MiniBoss_Create = false;;
		bool _MiniBoss_Dead = false;;
		bool _Door_Open = false;
		int _Randomcheck = 0;
	};
}
