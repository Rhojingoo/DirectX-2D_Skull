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
		SceneManager::CreateScene<Stage2_1>(L"Stage2_1");
		SceneManager::CreateScene<Stage1_Boss>(L"Stage1_Boss");
		SceneManager::CreateScene<Stage1_2>(L"Stage1_2");		
		SceneManager::CreateScene<Stage1_MiniBoss>(L"Stage1_mBoss");
		SceneManager::CreateScene<Stage1_1>(L"Stage1_1");
		SceneManager::CreateScene<Castle_Area>(L"Start_Scene"); 
		SceneManager::CreateScene<jkTitleScene>(L"TitleScene");

	}
}