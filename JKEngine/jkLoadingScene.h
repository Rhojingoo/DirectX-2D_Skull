#pragma once
#include "..\Engine_SOURCE\jkScene.h"

namespace jk
{
	class jkLoadingScene : public Scene
	{
	public:
		jkLoadingScene();
		~jkLoadingScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter();
		virtual void OnExit();

	protected:

	private:
		class Alpha_Blend* _Alpha = nullptr;
		class AudioSource* as = nullptr;
		bool _Fadecheck = false;
		float _time = 0.f;
	};
}

