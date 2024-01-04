#pragma once
#include "..\Engine_SOURCE\jkScene.h"


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
		class Alpha_Blend* _Alpha = nullptr;
		class AudioSource* as = nullptr;
		bool _Fadecheck = false;
		float _time = 0.f;
	};
}
