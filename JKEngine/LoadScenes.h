#pragma once
//#include "..\Engine_SOURCE\jkSceneManager.h"
//#include "Include_Common.h"
#include "Monster_Objmanagerl.h"
#include "Stge_Manager.h"
#include "Player.h"

namespace jk
{
	extern Player* Player_INFO;
	//extern Stage_Manager* Stage_MN;
	//Monster_ObjManager* Obj;
	//Stage_Manager* Stage_MN;

	void SettingOBJ();
	void InitializeScenes();
	void Release();
	//Stage_Manager* GetStage_MN() { return Stage_MN; }
	//Monster_ObjManager* GetObjPool() { return Obj; }
}