#pragma once
#include "..\Engine_SOURCE\jkSceneManager.h"
#include "jkPlayScene.h"
#include "jkTitleScene.h"
#include "jkStage1.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\x64\\Debug\\JKEngine.lib")
#else
#pragma comment(lib, "..\\x64\\Release\\JKEngine.lib")
#endif




namespace jk
{
	void InitializeScenes()
	{		
		SceneManager::CreateScene<jkStage1>(L"Stage1");
		SceneManager::CreateScene<PlayScene>(L"PlayScene"); 
		SceneManager::CreateScene<jkTitleScene>(L"TitleScene");
	}
}