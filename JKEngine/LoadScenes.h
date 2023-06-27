#pragma once
#include "jkSceneManager.h"
#include "jkPlayScene.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\x64\\Debug\\JKEngine.lib")
#else
#pragma comment(lib, "..\\x64\\Release\\JKEngine.lib")
#endif




namespace jk
{
	void InitializeScenes()
	{
		//PlayScene* playScene = new PlayScene();
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
	}
}