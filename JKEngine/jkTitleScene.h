#pragma once
#include "Include_Common.h"
#include "..\Engine_SOURCE\jkScene.h"
#include "Alpha_Blend.h"
#include "..\Engine_SOURCE\jkAudioSource.h"



namespace jk
{
	class jkTitleScene : public Scene
	{
	public:
		jkTitleScene();
		virtual ~jkTitleScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter();
		virtual void OnExit();


	private:
		Alpha_Blend* _Alpha = nullptr;
		bool _Fadecheck = false;
		float _time = 0.f;
		AudioSource* as = nullptr;
	};
}
