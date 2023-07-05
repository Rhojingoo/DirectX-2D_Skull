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

		template <typename T>
		static bool CreateScene(std::wstring name)
		{
			T* scene = new T();

			std::map<std::wstring, Scene*>::iterator iter
				= mScenes.find(name);

			if (iter != mScenes.end())
				return false;

			mScenes.insert(std::make_pair(name, scene));
			mActiveScene = scene;
			scene->Initialize();
			return true;
		}

		static Scene* LoadScene(std::wstring name);
		static Scene* GetActiveScene() { return mActiveScene; }

	private:
		static Scene* mActiveScene;
		static Scene* mActiveScene2;
		static Scene* mActiveScene3;

		static std::map<std::wstring, Scene*> mScenes;

	};
}
