#include "jkSceneManager.h"


namespace jk
{
	Scene* SceneManager::mActiveScene = nullptr;
	Scene* SceneManager::mInitializeScene = nullptr;
	Scene* SceneManager::mActiveScene3 = nullptr;
	bool SceneManager::Scenebegin = false;
	std::map<std::wstring, Scene*> SceneManager::mScenes;
	
	void SceneManager::Initialize()
	{

	}
	void SceneManager::Update()
	{
		mActiveScene->Update();
	}
	void SceneManager::LateUpdate()
	{
		mActiveScene->LateUpdate();
	}
	void SceneManager::Render()
	{
		mActiveScene->Render();
	}

	void SceneManager::Destroy()
	{
		mActiveScene->Destroy();
	}

	void SceneManager::Release()
	{
		for (auto& iter : mScenes)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}



	Scene* SceneManager::LoadScene(std::wstring name)
	{
		std::map<std::wstring, Scene*>::iterator iter
			= mScenes.find(name);

		if (iter == mScenes.end())
			return nullptr;

		mActiveScene->OnExit();
		mActiveScene = iter->second;
		mActiveScene->OnEnter();

		return iter->second;
	}

	Scene* SceneManager::FindScene(std::wstring name)
	{
		std::map<std::wstring, Scene*>::iterator iter
			= mScenes.find(name);

		if (iter == mScenes.end())
			return nullptr;

		mActiveScene = iter->second;

		return iter->second;
	}
}
