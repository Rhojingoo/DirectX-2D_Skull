#pragma once
#include "jkPlayScene.h"


namespace jk
{
	class Stage1_Boss : public PlayScene
	{
	public:
		Stage1_Boss();
		virtual ~Stage1_Boss();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter();
		virtual void OnExit();

		void CamareShooting();

	private:
		class AudioSource* as = nullptr;
		class Sound* _BGSound = nullptr;
		class Back_ground* Kingbg = nullptr;
		class Camera* cameraComp = nullptr;
		class Player* _player = nullptr;
		class Yggdrasil* _Stage1_Boss = nullptr;
		class Stage1_BossDoor* _Door = nullptr;


	private:
		bool _first_groundturch = false;;
		bool _Boss_Create = false;;
		bool _Boss_Dead = false;;
		bool _changecheck = false;
		float _time = 0.f;
		bool _Fadein = false;
		bool _Fadeout = false;
		float _Fadetime = 0.f;
		
	};
}
