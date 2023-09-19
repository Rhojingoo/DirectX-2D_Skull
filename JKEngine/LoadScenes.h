#pragma once
//#include "..\Engine_SOURCE\jkSceneManager.h"
#include "Include_Common.h"
#include "Monster_ObjPool.h"
#include "Stge_Manager.h"

namespace jk
{
	//extern Monster_ObjPool* Obj; 
	//extern Stage_Manager* Stage_MN;
	//Monster_ObjPool* Obj;
	//Stage_Manager* Stage_MN;

	void SettingOBJ();
	void InitializeScenes();
	void Release();
	//Stage_Manager* GetStage_MN() { return Stage_MN; }
	//Monster_ObjPool* GetObjPool() { return Obj; }
}