#include "LoadScenes.h"
#include "Include_Common.h"
#include "jkLoadingScene.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\x64\\Debug\\JKEngine.lib")
#else
#pragma comment(lib, "..\\x64\\Release\\JKEngine.lib")
#endif

namespace jk
{
	Player* jk::Player_INFO = nullptr;
	//Stage_Manager* jk::Stage_MN = nullptr;

	void SettingOBJ()
	{
		Player_INFO = new Player();
		Player_INFO->SetState(GameObject::eState::Paused);
		//Stage_MN = new Stage_Manager(Obj);
	}
	void InitializeScenes()
	{
		SettingOBJ();

		
		//Scene			

		SceneManager::CreateScene<jkTitleScene>(L"TitleScene");	
		SceneManager::CreateScene<jkLoadingScene>(L"LoadingScene");
		SceneManager::FindScene(L"LoadingScene");
		//SceneManager::SetActiveScene(SceneManager::LoadScene(L"TitleScene"));		
	}
	void InitializeScenes_Second()
	{
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
	}
	void Release()
	{
		delete Player_INFO;
		Player_INFO = nullptr;
	}
}


