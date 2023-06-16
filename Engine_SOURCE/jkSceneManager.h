#pragma once
#include "jkScene.h"

namespace jk
{
	class SceneManager
	{
	public:
		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render();


	private:
		static Scene* mActiveScene;

		//std::map<std::wstring, Scene*> mScenes;
	};
}
