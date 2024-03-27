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
		static void Destroy();
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
			//mActiveScene = scene;
			mInitializeScene = scene;
			scene->Initialize();
			return true;
		}

		static Scene* FindScene(std::wstring name);
		static Scene* LoadScene(std::wstring name);
		static Scene* GetActiveScene() { return mActiveScene; }
		static void SetActiveScene(Scene* _Set) { mActiveScene = _Set; }
		static Scene* GetInitializeScene() { return mInitializeScene; }
		static void Setlnit_SC() { Scenebegin = !Scenebegin; }
		static bool Getlnit_SC() { return Scenebegin;}

	private:
		static Scene* mActiveScene;
		static Scene* mInitializeScene;
		static Scene* mActiveScene3;
		static bool Scenebegin; 
		static std::map<std::wstring, Scene*> mScenes;

	};
}
