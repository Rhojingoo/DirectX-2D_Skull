#pragma once
//#include "..\Engine_SOURCE\jkSceneManager.h"
#include "Include_Common.h"



#ifdef _DEBUG
#pragma comment(lib, "..\\x64\\Debug\\JKEngine.lib")
#else
#pragma comment(lib, "..\\x64\\Release\\JKEngine.lib")
#endif




namespace jk
{
	void InitializeScenes()
	{		
		//Tool 
		//SceneManager::CreateScene<ToolScene>(L"ToolScene");
		
		
		
		//Scene
		SceneManager::CreateScene<Stage2>(L"Stage2");
		SceneManager::CreateScene<jkStage1>(L"Stage1");		
		SceneManager::CreateScene<Castle_Area>(L"Start_Scene"); 
		SceneManager::CreateScene<jkTitleScene>(L"TitleScene");

	}
}