#include "jkSceneManager.h"
#include "jkPlayScene.h"


namespace jk
{
	Scene* SceneManager::mActiveScene = nullptr;
	std::map<std::wstring, Scene*> SceneManager::mScenes;
	
	void SceneManager::Initialize()
	{
		//PlayScene* test = new PlayScene();

		mActiveScene = new PlayScene();
		mActiveScene->Initialize();
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
}
