#pragma once
#include "Include_Common.h"
#include "..\Engine_SOURCE\jkScene.h"
#include "Alpha_Blend.h"
#include "..\Engine_SOURCE\jkAudioSource.h"
#include "Sound.h"

namespace jk
{
	class Castle_Area : public Scene
	{
	public:
		Castle_Area();
		virtual ~Castle_Area();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;


		virtual void OnEnter();
		virtual void OnExit();

	private:
		Player* _player = nullptr;
		Sound* _BGSound = nullptr;
		Alpha_Blend* _Alpha = nullptr;
		Back_ground* Castle_wall_Back = nullptr;
		Ground_Map* out_GroundMap = nullptr;
		Camera* cameraComp = nullptr;
		AudioSource* as = nullptr;
		float _time = 0.f;
		bool _Fadecheck = false;
		bool _BGsOUND = false;

		bool first_groundturch = false;
	};
}
