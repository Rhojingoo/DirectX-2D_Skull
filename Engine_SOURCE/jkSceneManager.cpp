#include "jkSceneManager.h"


namespace jk
{
	Scene* SceneManager::mActiveScene = nullptr;
	Scene* SceneManager::mActiveScene2 = nullptr;
	Scene* SceneManager::mActiveScene3 = nullptr;
	std::map<std::wstring, Scene*> SceneManager::mScenes;
	
	void SceneManager::Initialize()
	{
		//mActiveScene = new jkTitleScene();
		//mScenes.insert(std::make_pair(L"TitleScene", mActiveScene));

		//mActiveScene2 = new PlayScene();
		//mScenes.insert(std::make_pair(L"PlayScene", mActiveScene2));

		//mActiveScene3 = new jkStage1();
		//mScenes.insert(std::make_pair(L"Stage1", mActiveScene3));


		//for (auto& scenePair : mScenes)
		//{
		//	Scene* scene = scenePair.second;
		//	scene->Initialize();
		//}

		////mActiveScene->Initialize();
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

	void SceneManager::Release()
	{
		for (auto& iter : mScenes)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}

	//bool SceneManager::CreateScene(std::wstring name, Scene* scene)
	//{
	//	std::map<std::wstring, Scene*>::iterator iter
	//		= mScenes.find(name);

	//	if (iter != mScenes.end())
	//		return false;

	//	mScenes.insert(std::make_pair(name, scene));
	//	scene->Initialize();
	//	return true;
	//}

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
