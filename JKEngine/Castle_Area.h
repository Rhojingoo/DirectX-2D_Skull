#pragma once
#include "..\Engine_SOURCE\jkScene.h"


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
		class Player* _player = nullptr;
		class Sound* _BGSound = nullptr;
		class Alpha_Blend* _Alpha = nullptr;
		class Back_ground* Castle_wall_Back = nullptr;
		class Ground_Map* out_GroundMap = nullptr;
		class Camera* cameraComp = nullptr;
		class AudioSource* as = nullptr;
		float _time = 0.f;
		bool _Fadecheck = false;
		bool _BGsOUND = false;

		bool first_groundturch = false;
	};
}
