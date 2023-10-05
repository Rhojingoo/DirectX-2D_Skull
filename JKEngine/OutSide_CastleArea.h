#pragma once
#include "Include_Common.h"
#include "..\Engine_SOURCE\jkScene.h"
#include "jkPlayScene.h"
#include "..\Engine_SOURCE\jkAudioSource.h"
#include "Sound.h"

namespace jk
{
	class OutSide_CastleArea : public Scene
	{
	public:
		OutSide_CastleArea();
		virtual ~OutSide_CastleArea();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter();
		virtual void OnExit();


	private:
		Player* _player = nullptr;
		Camera* cameraComp = nullptr;
		AudioSource* as = nullptr; 
		Sound* _BGSound = nullptr;
		Alpha_Blend* _Alpha = nullptr;
		Stage1_Door* Door1 = nullptr;

	private:
		float _time = 0.f;
		bool _Fadecheck = false;
		bool _changecheck = false;
	};
}
