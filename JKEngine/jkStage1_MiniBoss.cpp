#include "jkStage1_MiniBoss.h"
#include "jkParticleSystem.h"
#include "jkComputeShader.h"
#include "LoadScenes.h"
#include "jkPaintShader.h"
#include <iostream>
#include <random>
#include "Include_Common.h"
#include "jkPlayScene.h"
#include "Monster_Objmanagerl.h"
#include "Knight_male.h"
#include "Archer.h"
#include "Mage.h"
#include "Cleric.h"
#include "Stge_Manager.h"
#include "Mini_Boss.h"
#include "..\Engine_SOURCE\jkAudioSource.h"
#include "Sound.h"

namespace jk
{
	Stage1_MiniBoss::Stage1_MiniBoss()
	{
	}
	Stage1_MiniBoss::~Stage1_MiniBoss()
	{
		mBossGroup.clear();
	}


	void Stage1_MiniBoss::Initialize()
	{
#pragma region CollisionManager
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::BACK_GROUND, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Item, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Player, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::BACK_GROUND, true);
		CollisionManager::SetLayer(eLayerType::MiniBoss, eLayerType::BACK_GROUND, true);
		CollisionManager::SetLayer(eLayerType::Bullet, eLayerType::BACK_GROUND, true);
		CollisionManager::SetLayer(eLayerType::Boss, eLayerType::BACK_GROUND, true);
		CollisionManager::SetLayer(eLayerType::Item, eLayerType::BACK_GROUND, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::MiniBoss, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Hitbox, true);
		CollisionManager::SetLayer(eLayerType::MiniBoss, eLayerType::Hitbox, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Hitbox, true);
#pragma endregion 

		
		CreateMiniboss();

		_BGSound = object::Instantiate<Sound>(Vector3(0.f, -150.f, -250.f), eLayerType::Player);
		as = _BGSound->AddComponent<AudioSource>();
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Adventurer\\Adventurer.wav", "Adventurer");
		as->SetLoop(true);
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Chapter1\\Chapter1.wav", "Chapter1");
		as->SetLoop(true);


		_player = object::Instantiate<Player>(Vector3(-600.f, -50.f, -250.f), eLayerType::Player);
		_player->SetName(L"player_select");

#pragma region Door
		Door1 = object::Instantiate<Stage1_Door>(Vector3(415.f, -125.f, -245.f), eLayerType::BACK_GROUND);
		Door1->Set_Door_Allow(true); Door1->Set_Stage1_Door(5);	Door1->Set_NextStage(L"Stage1_2");


		Stage1_Door* Door2 = object::Instantiate<Stage1_Door>(Vector3(685.f, -125.f, -245.f), eLayerType::BACK_GROUND);
		Door2->Set_Door_Allow(true); Door2->Set_Stage1_Door(8); Door2->Set_NextStage(L"Stage1_2");


		Stage_end_wall* Door_Wall = object::Instantiate<Stage_end_wall>(Vector3(548.f, -125.f, -244.f), eLayerType::BACK_GROUND);
		Door_Wall->Set_Wall_Allow(true);  Door_Wall->Set_Wall_Stage(0);


		Back_ground* Ch1_Gate_Table = object::Instantiate<Back_ground>(Vector3(548.f, -155.f, -245.f), eLayerType::BACK_GROUND, L"Ch1_Gate_Table");
		Ch1_Gate_Table->GetComponent<Transform>()->SetScale(Vector3(90.f, 19.f, 0.f));	Ch1_Gate_Table->SetName(L"Ch1_Gate_Table1");
#pragma endregion	

#pragma region BG	
		{
			Back_ground* Fore_S1_1_color = object::Instantiate<Back_ground>(Vector3(0.f, 50.f, 105.f), eLayerType::Fore_Ground, L"Stage1_Fore_GR_Color");
			Fore_S1_1_color->GetComponent<Transform>()->SetScale(Vector3(960.f * 2.5, 800.f, 0.f));	Fore_S1_1_color->SetName(L"s1_1_fore_gr_color");

			Back_ground* Fore_S1_1_tree = object::Instantiate<Back_ground>(Vector3(0.f, -200.f, 103.f), eLayerType::Fore_Ground, L"Stage1_Fore_GR_Tree");
			Fore_S1_1_tree->GetComponent<Transform>()->SetScale(Vector3(960.f * 2.5, 800.f, 0.f));	Fore_S1_1_tree->SetName(L"s1_1_fore_gr_tree");

			Back_ground* Mid_S1_1 = object::Instantiate<Back_ground>(Vector3(0.f, 0.f, 101.f), eLayerType::Fore_Ground, L"Stage1_Mid_GR1_1");
			Mid_S1_1->GetComponent<Transform>()->SetScale(Vector3(960.f * 2.5, 800.f, 0.f));	Mid_S1_1->SetName(L"Mid_S1_1");

			Back_ground* Back_GR03 = object::Instantiate<Back_ground>(Vector3(50.f, -150.f, 99.f), eLayerType::Fore_Ground, L"Stage1_Back_GR12");
			Back_GR03->GetComponent<Transform>()->SetScale(Vector3(718.f, 380.f, 0.f));	Back_GR03->SetName(L"back_gr00");

			Back_ground* Back_GR04 = object::Instantiate<Back_ground>(Vector3(-450.f, -90.f, 99.f), eLayerType::Fore_Ground, L"Stage1_Back_GR02");
			Back_GR04->GetComponent<Transform>()->SetScale(Vector3(145.f, 172.f, 0.f));	Back_GR04->SetName(L"back_gr01");

			Back_ground* Back_GR05 = object::Instantiate<Back_ground>(Vector3(420.f, -80.f, 99.f), eLayerType::Fore_Ground, L"Stage1_Back_GR02");
			Back_GR05->GetComponent<Transform>()->SetScale(Vector3(145.f, 172.f, 0.f));	Back_GR05->SetName(L"back_gr02");
		}
#pragma endregion

#pragma region tile_map & Ground_COL
		{
			Ground_Map* MinibossMap = object::Instantiate<Ground_Map>(Vector3(0.f, -450.f, -205.f), eLayerType::BACK_GROUND);
			MinibossMap->GetComponent<Transform>()->SetScale(Vector3(1000, 320.f, 0.f));	MinibossMap->SetName(L"Miniboss_ground00");

			Ground_Map* MinibossMap1 = object::Instantiate<Ground_Map>(Vector3(-645.f, -180.f, -206.f), eLayerType::BACK_GROUND);
			MinibossMap1->GetComponent<Transform>()->SetScale(Vector3(630, 35.f, 0.f));	MinibossMap1->SetName(L"Miniboss_ground01");

			Ground_Map* MinibossMap2 = object::Instantiate<Ground_Map>(Vector3(645.f, -180.f, -207.f), eLayerType::BACK_GROUND);
			MinibossMap2->GetComponent<Transform>()->SetScale(Vector3(630, 35.f, 0.f));	MinibossMap2->SetName(L"Miniboss_ground02");

			Ground_and_Wall* MinibossWall = object::Instantiate<Ground_and_Wall>(Vector3(-340.f, -235.f, -208.f), eLayerType::BACK_GROUND);
			MinibossWall->GetComponent<Transform>()->SetScale(Vector3(30, 130.f, 0.f));	MinibossWall->SetName(L"Miniboss_Wall00");

			Ground_and_Wall* MinibossWall1 = object::Instantiate<Ground_and_Wall>(Vector3(340.f, -235.f, -209.f), eLayerType::BACK_GROUND);
			MinibossWall1->GetComponent<Transform>()->SetScale(Vector3(30, 130.f, 0.f));	MinibossWall1->SetName(L"Miniboss_Wall01");



			static Vector2 TileSize = Vector2(32.f, 32.f);
			static int Tile_Colum = 60;
			static int Tile_Row = 30;
			static Tile_Ground* Tile_map = object::Instantiate<Tile_Ground>(eLayerType::BACK_GROUND);
			Tile_map->SetName(L"tile_stage1_miniboss");
			Transform* tr = Tile_map->GetComponent<Transform>();
			tr->AddPositionY(0.f);
			tr->SetPositionX(0.f);
			tr->SetScale(Vector3(Tile_Colum * TileSize.x, Tile_Row * TileSize.y, 0.f));

			TileMap::TileMap_Setting(Tile_map, L"Stage1_MiniBoss", TileSize, Tile_Colum, Tile_Row, L"\\Resources\\Metadata\\TileMap\\Stage1_MiniBoss.xml");
		}
#pragma endregion	
	}
	void Stage1_MiniBoss::Update()
	{
		Transform* PlayerTR = _player->GetComponent<Transform>();
		Vector3 player_pos = PlayerTR->GetPosition();

		if (_player->firstGroundcheck == true)
		{
			if (_first_groundtouch == false)
			{
				_first_groundtouch = true;
			}
		}

		if (_first_groundtouch == true)
		{
			if (_MiniBoss_groundtouch == true)
			{
				if (_MiniBoss_Create == false)
				{
					for (Mini_Boss* mon : mBossGroup)
					{
						as->Play("Adventurer");
						mon->SetState(GameObject::eState::Active);
					}
					_MiniBoss_Create = true;
				}
			}
		}

		AreAllMiniBossDead(mBossGroup);
		if (_MiniBoss_Dead == true)
		{
			if (_Door_Open == false)
			{
				as->Stop("Adventurer");
				as->Play("Chapter1Sound");
				cameraComp->SetCameraXY = true;
				Door1->Set_Door_Allow(true);
				Door1->Set_Stage1_Door(1);
				_Door_Open = true;
				int a = 0;
			}
		}

		CamareShooting();


		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(L"Stage1_2");
		}

		if (_changecheck == true)
		{
			_player->SetPlayer_Pos(player_pos);
			_player->SetPlay_List(_player->GetCurrentPlay_List(), _player->GetPlay_List(), true, _player->GetDirection());
			_changecheck = false;
		}

		Scene::Update();
	}
	void Stage1_MiniBoss::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void Stage1_MiniBoss::Render()
	{
		Scene::Render();
	}


	void Stage1_MiniBoss::OnEnter()
	{
		Transform* PlayerTR = _player->GetComponent<Transform>();
		Vector3 player_pos = PlayerTR->GetPosition();
		_player->SetPlayer_Pos(player_pos);
		_player->SetSwitch(true);
		_changecheck = true;
		_player->firstGroundcheck = false;

		Mini_Boss::Left_Ground = (Vector3(-320.f, 0.f, 0.f));
		Mini_Boss::Right_Ground = (Vector3(320.f, 0.f, 0.f));

#pragma region Cam & Mouse& Grid
		//Main Camera			
		Main_Camera* camera = object::InstantiateActive<Main_Camera>(Vector3(0.f, 0.f, -10.f), eLayerType::Camera);
		cameraComp = camera->AddComponent<Camera>();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		renderer::cameras.push_back(cameraComp);
		renderer::mainCamera = cameraComp;
		cameraComp->SetTarget(_player);
		cameraComp->SetCamera = true;
		cameraComp->SetCameraXY = true;
		cameraComp->Set_MaxPlayerX(700.f);
		cameraComp->Set_MinPlayerX(-840.f);
		cameraComp->Set_MaxPlayerY(400.f);
		cameraComp->Set_MinPlayerY(-360.f);


		//UI Camera		
		UI_Camera* UI_camera = object::InstantiateActive<UI_Camera>(Vector3(0.f, 0.f, -10.f), eLayerType::Camera);
		Camera* cameraComp_ui = UI_camera->AddComponent<Camera>();
		cameraComp_ui->TurnLayerMask(eLayerType::Player, false);
		cameraComp_ui->TurnLayerMask(eLayerType::Monster, false);
		cameraComp_ui->TurnLayerMask(eLayerType::MiniBoss, false);
		cameraComp_ui->TurnLayerMask(eLayerType::Boss, false);
		cameraComp_ui->TurnLayerMask(eLayerType::Bullet, false);
		cameraComp_ui->TurnLayerMask(eLayerType::Effect, false);
		cameraComp_ui->TurnLayerMask(eLayerType::Camera, false);
		cameraComp_ui->TurnLayerMask(eLayerType::Item, false);
		cameraComp_ui->TurnLayerMask(eLayerType::Hitbox, false);
		cameraComp_ui->TurnLayerMask(eLayerType::BACK_GROUND, false);
		cameraComp_ui->TurnLayerMask(eLayerType::Fore_Ground, false);
		cameraComp_ui->TurnLayerMask(eLayerType::Mid_Ground, false);
		cameraComp_ui->TurnLayerMask(eLayerType::Map_Effect, false);
		cameraComp_ui->TurnLayerMask(eLayerType::Camera, false);
		renderer::cameras.push_back(cameraComp_ui);

		//UI_Mouse
		UI_Mouse* cursor = object::InstantiateActive<UI_Mouse>(Vector3(Vector3::One), eLayerType::Camera);
		cursor->SetName(L"Catle_Cursor_UI");
		cursor->GetComponent<Transform>()->SetScale(Vector3(42.f, 42.f, -250.f));
		cursor->SetName(L"Mouse_UI"); cursor->SetCamera(UI_camera);

		//Grid
		Grid* grid = object::InstantiateActive<Grid>(Vector3(Vector3::One), eLayerType::Grid);
		grid->SetName(L"Catle_Grid");
		GridScript* gridSc = grid->AddComponent<GridScript>();
		gridSc->SetCamera(cameraComp);
#pragma endregion	

	}
	void Stage1_MiniBoss::OnExit()
	{
		_player->SettingPlay_List(jk::Player_INFO->GetCurrentPlay_List());
		//as->Stop();
	}


	void Stage1_MiniBoss::CamareShooting()
	{
		Transform* PlayerTR = _player->GetComponent<Transform>();
		Vector3 player_pos = PlayerTR->GetPosition();
		if (player_pos.x <= -610)
			cameraComp->SetCameraXY = false;

		if (_MiniBoss_Create == false)
		{
			if (player_pos.x > -610 && player_pos.x <= -240)
				cameraComp->SetCameraXY = true;
			if (player_pos.x > -10)
			{
				cameraComp->SetCameraXY = false;
				_MiniBoss_groundtouch = true;
			}
		}
	}
	void Stage1_MiniBoss::CreateMiniboss()
	{
		Scene* scene = SceneManager::GetInitializeScene();
		_Randomcheck = Mboss->random(0, 2);
		_Randomcheck = 1;
		if (_Randomcheck == 0)
		{
			Mini_Boss* _Gobjs = new Knight_male();
			_Gobjs->Initialize();			
			scene->AddGameObject(eLayerType::MiniBoss, _Gobjs);
			_Gobjs->SetState(GameObject::eState::Paused);
			Transform* tr = _Gobjs->GetComponent<Transform>();
			tr->SetPosition(Vector3(200.f, -200.f, -250.f));
			mBossGroup.push_back(_Gobjs);
		}
		if (_Randomcheck == 1)
		{
			Mini_Boss* _Gobjs = new Archer();
			_Gobjs->Initialize();
			scene->AddGameObject(eLayerType::MiniBoss, _Gobjs);
			_Gobjs->SetState(GameObject::eState::Paused);
			Transform* tr = _Gobjs->GetComponent<Transform>();
			tr->SetPosition(Vector3(200.f, -200.f, -250.f));
			mBossGroup.push_back(_Gobjs);
		}
		if (_Randomcheck == 2)
		{
			Mini_Boss* _Gobjs = new Mage();
			_Gobjs->Initialize();
			scene->AddGameObject(eLayerType::MiniBoss, _Gobjs);
			_Gobjs->SetState(GameObject::eState::Paused);
			Transform* tr = _Gobjs->GetComponent<Transform>();
			tr->SetPosition(Vector3(200.f, -200.f, -250.f));
			mBossGroup.push_back(_Gobjs);
		}
		if (_Randomcheck == 3)
		{
			Mini_Boss* _Gobjs = new Cleric();
			_Gobjs->Initialize();
			scene->AddGameObject(eLayerType::MiniBoss, _Gobjs);
			_Gobjs->SetState(GameObject::eState::Paused);
			Transform* tr = _Gobjs->GetComponent<Transform>();
			tr->SetPosition(Vector3(200.f, -200.f, -250.f));
			mBossGroup.push_back(_Gobjs);
		}		
	}

	int Stage1_MiniBoss::random(int a, int b)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> distribution(a, b);
		int answer_random = distribution(gen);
		return answer_random;
	}
	bool Stage1_MiniBoss::AreAllMiniBossDead(const std::vector<Mini_Boss*>& monsterGroup)
	{
		for (const Mini_Boss* monster : monsterGroup)
		{
			if (!monster->_Die)
			{
				_MiniBoss_Dead = false;
				// 하나라도 살아있는 몬스터가 있으면 false 반환
				return _MiniBoss_Dead;
			}
		}
		// 모든 몬스터가 죽었다면 true 반환
		_MiniBoss_Dead = true;
		return _MiniBoss_Dead;
	}
}