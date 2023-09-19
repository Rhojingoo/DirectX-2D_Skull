#include "LoadScenes.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\x64\\Debug\\JKEngine.lib")
#else
#pragma comment(lib, "..\\x64\\Release\\JKEngine.lib")
#endif

namespace jk
{
	Monster_ObjPool* jk::Obj = nullptr;
	Stage_Manager* jk::Stage_MN = nullptr;

	void SettingOBJ()
	{
		Obj = new Monster_ObjPool(135, 15, 30, 10);
		Stage_MN = new Stage_Manager(Obj);
	}
	void InitializeScenes()
	{
		//Scene
		SettingOBJ();
		SceneManager::CreateScene<Stage2_Boss>(L"Stage2_Boss");
		SceneManager::CreateScene<Stage2_2>(L"Stage2_2");
		SceneManager::CreateScene<Stage2_MiniBoss>(L"Stage2_mBoss");
		SceneManager::CreateScene<Stage2_1>(L"Stage2_1");
		SceneManager::CreateScene<Stage1_Boss>(L"Stage1_Boss");
		SceneManager::CreateScene<Stage1_2>(L"Stage1_2");
		SceneManager::CreateScene<Stage1_MiniBoss>(L"Stage1_mBoss");
		SceneManager::CreateScene<Stage1_1>(L"Stage1_1");
		SceneManager::CreateScene<OutSide_CastleArea>(L"OutSide_Castle");
		SceneManager::CreateScene<Castle_Area>(L"Start_Scene");
		SceneManager::CreateScene<jkTitleScene>(L"TitleScene");	
	}
	void Release()
	{
		delete Obj;
		Obj = nullptr;
		delete Stage_MN;
		Stage_MN = nullptr;
	}
}


