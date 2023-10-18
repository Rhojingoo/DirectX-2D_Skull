#pragma once
#include "Include_Common.h"
#include "jkPlayScene.h"

#include "..\Engine_SOURCE\jkAudioSource.h"
#include "Sound.h"

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
		Camera* cameraComp = nullptr;
		Player* _player = nullptr;
		Layana_Sisters* _Layana_Boss = nullptr;
		AudioSource* as = nullptr;
		Sound* _BGSound = nullptr;

	private:
		float _time = 0.f;
		bool _Fadecheck = false;
		bool _changecheck = false;

	private:
		bool first_groundtouch = false;
		bool first_MonsterCreate = false;

	};
}
