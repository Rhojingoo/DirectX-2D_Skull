#pragma once
#include "Include_Common.h"
#include "jkPlayScene.h"
#include "Stge_Manager.h"
#include "Monster_ObjPool.h"
#include "Stge_Manager.h"

namespace jk
{
	class Stage1_1 : public PlayScene
	{
	public:
		Stage1_1();
		virtual ~Stage1_1();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter();
		virtual void OnExit();

		void CamareShooting();
		void SetMonOBJ();

	private:
		Camera* cameraComp = nullptr;
		Player* _player = nullptr;		

		Monster_ObjPool* OBJPOOL = nullptr;
		Stage_Manager* StageMn = nullptr;
	};
}
