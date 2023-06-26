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
		static void Release();


		static Scene* GetActiveScene() { return mActiveScene; }
		static Scene* LoadScene(std::wstring name);

	private:
		static Scene* mActiveScene;
		static Scene* mActiveScene2;
		static Scene* mActiveScene3;
		static std::map<std::wstring, Scene*> mScenes;

	};
}
