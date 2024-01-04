#pragma once
#include "..\Engine_SOURCE\jkScene.h"


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
		class Player* _player = nullptr;
		class Camera* cameraComp = nullptr;
		class AudioSource* as = nullptr; 
		class Sound* _BGSound = nullptr;
		class Alpha_Blend* _Alpha = nullptr;
		class Stage1_Door* Door1 = nullptr;

	private:
		float _time = 0.f;
		bool _Fadecheck = false;
		bool _changecheck = false;
	};
}
