#pragma once
#include "jkPlayScene.h"


namespace jk
{
	class Stage2_Boss : public PlayScene
	{
	public:
		Stage2_Boss();
		virtual ~Stage2_Boss();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter();
		virtual void OnExit();

		void CamareShooting();

	private:
		class Camera* cameraComp = nullptr;
		class Player* _player = nullptr;
		class Layana_Sisters* _Layana_Boss = nullptr;
		class AudioSource* as = nullptr;
		class Sound* _BGSound = nullptr;

	private:
		float _time = 0.f;
		bool _Fadecheck = false;
		bool _changecheck = false;

	private:
		bool first_groundtouch = false;
		bool first_MonsterCreate = false;

	};
}
