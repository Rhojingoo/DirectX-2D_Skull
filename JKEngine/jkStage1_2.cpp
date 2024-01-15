#include "jkStage1_2.h"
#include "LoadScenes.h"
#include "Include_Common.h"
#include "Monster_Objmanagerl.h"
#include "Stge_Manager.h"
#include "..\Engine_SOURCE\jkAudioSource.h"
#include "Sound.h"

namespace jk
{
	Stage1_2::Stage1_2()
	{
	}
	Stage1_2::~Stage1_2()
	{
		delete OBJPOOL;
		OBJPOOL = nullptr;

		monsterGroup1.clear();
		monsterGroup2.clear();
		monsterGroup3.clear();
	}
	void Stage1_2::Initialize()
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

		OBJPOOL = new Monster_ObjManager(1, 15, 20, 10);

		SetMonOBJ();

		_BGSound = object::Instantiate<Sound>(Vector3(0.f, -150.f, -250.f), eLayerType::Player);
		as = _BGSound->AddComponent<AudioSource>();
		as->SetClip(Resources::Load<AudioClip>(L"Chapter1", L"..\\Resources\\Sound\\Chapter1\\Chapter1.wav", "Chapter1"));
		as->SetLoop(true);

		_player = object::Instantiate<Player>(Vector3(-590.f, 50.f, -250.f), eLayerType::Player);
		_player->SetName(L"player_select");

		for (Monster* mon : monsterGroup1)
		{
			mon->SetState(GameObject::eState::Active);
		}

	#pragma region Door
			Door1 = object::Instantiate<Stage1_Door>(Vector3(60.f, 70.f, -245.f), eLayerType::BACK_GROUND);
			Door1->Set_Door_Allow(true); Door1->Set_Stage1_Door(7); Door1->Set_NextStage(L"Stage1_Boss");


			Stage_end_wall* Door_Wall = object::Instantiate<Stage_end_wall>(Vector3(63.f, 70.f, -244.f), eLayerType::BACK_GROUND);
			Door_Wall->Set_Wall_Allow(true);  Door_Wall->Set_Wall_Stage(0);
	#pragma endregion	

	#pragma region BG	
			{
				Back_ground* Fore_S1_1_color = object::Instantiate<Back_ground>(Vector3(50.f, 50.f, 105.f), eLayerType::Fore_Ground, L"Stage1_Fore_GR_Color");
				Fore_S1_1_color->GetComponent<Transform>()->SetScale(Vector3(960.f*2.5, 800.f, 0.f));	Fore_S1_1_color->SetName(L"s1_1_fore_gr_color");

				Back_ground* Fore_S1_1_tree = object::Instantiate<Back_ground>(Vector3(50.f, -150.f, 103.f), eLayerType::Fore_Ground, L"Stage1_Fore_GR_Tree");
				Fore_S1_1_tree->GetComponent<Transform>()->SetScale(Vector3(960.f*2.5, 800.f, 0.f));	Fore_S1_1_tree->SetName(L"s1_1_fore_gr_tree");

				Back_ground* Mid_S1_1 = object::Instantiate<Back_ground>(Vector3(50.f, 0.f, 101.f), eLayerType::Fore_Ground, L"Stage1_Mid_GR1_1");
				Mid_S1_1->GetComponent<Transform>()->SetScale(Vector3(960.f*2.5, 800.f, 0.f));	Mid_S1_1->SetName(L"Mid_S1_1");


				Back_ground* Back_GR06 = object::Instantiate<Back_ground>(Vector3(50.f, 120.f, 99.f), eLayerType::Fore_Ground, L"Stage1_Back_GR14");
				Back_GR06->GetComponent<Transform>()->SetScale(Vector3(785.f, 190.f, 0.f));	Back_GR06->SetName(L"back_gr06");

				Back_ground* Back_GR07 = object::Instantiate<Back_ground>(Vector3(-420.f, -150.f, 99.f), eLayerType::Fore_Ground, L"Stage1_Back_GR02");
				Back_GR07->GetComponent<Transform>()->SetScale(Vector3(125.f, 172.f, 0.f));	Back_GR07->SetName(L"back_gr07");
		
				Back_ground* Back_GR08 = object::Instantiate<Back_ground>(Vector3(325.f, -150.f, 99.f), eLayerType::Fore_Ground, L"Stage1_Back_GR02");
				Back_GR08->GetComponent<Transform>()->SetScale(Vector3(145.f, 172.f, 0.f));	Back_GR08->SetName(L"back_gr08");

				Back_ground* Back_GR09 = object::Instantiate<Back_ground>(Vector3(470.f, -150.f, 99.f), eLayerType::Fore_Ground, L"Stage1_Back_GR02");
				Back_GR09->GetComponent<Transform>()->SetScale(Vector3(145.f, 172.f, 0.f));	Back_GR09->SetName(L"back_gr09");


				Back_ground* Ground_Assistment = object::Instantiate<Back_ground>(Vector3(45.f, -100.f, -199.f), eLayerType::Fore_Ground, L"Map1_2");
				Ground_Assistment->GetComponent<Transform>()->SetScale(Vector3(1920.f, 960.f, 0.f));	Ground_Assistment->SetName(L"Map1_2_assist");
			}
	#pragma endregion

	#pragma region tile_map & Ground_COL
			{
				Ground_Map* MinibossMap = object::Instantiate<Ground_Map>(Vector3(-740.f, -80.f, -205.f), eLayerType::BACK_GROUND);
				MinibossMap->GetComponent<Transform>()->SetScale(Vector3(500, 25, 0.f));	MinibossMap->SetName(L"Miniboss_ground00");

				Ground_Map* MinibossMap1 = object::Instantiate<Ground_Map>(Vector3(-345.f, -240.f, -205.f), eLayerType::BACK_GROUND);
				MinibossMap1->GetComponent<Transform>()->SetScale(Vector3(290, 25.f, 0.f));	MinibossMap1->SetName(L"Miniboss_ground01");

				Ground_Map* MinibossMap2 = object::Instantiate<Ground_Map>(Vector3(0.f, -335.f, -205.f), eLayerType::BACK_GROUND);
				MinibossMap2->GetComponent<Transform>()->SetScale(Vector3(700, 25, 0.f));	MinibossMap2->SetName(L"Miniboss_ground02");

				Ground_Map* MinibossMap3 = object::Instantiate<Ground_Map>(Vector3(30.f, -240.f, -205.f), eLayerType::BACK_GROUND);
				MinibossMap3->GetComponent<Transform>()->SetScale(Vector3(185, 25, 0.f));	MinibossMap3->SetName(L"Miniboss_ground03");

				Ground_Map* MinibossMap4 = object::Instantiate<Ground_Map>(Vector3(445.F, -240.f, -205.f), eLayerType::BACK_GROUND);
				MinibossMap4->GetComponent<Transform>()->SetScale(Vector3(380, 25, 0.f));	MinibossMap4->SetName(L"Miniboss_ground04");



				Ground_and_Wall* MinibossWall = object::Instantiate<Ground_and_Wall>(Vector3(-210.f, -288.f, -205.f), eLayerType::BACK_GROUND);
				MinibossWall->GetComponent<Transform>()->SetScale(Vector3(30, 70, 0.f));	MinibossWall->SetName(L"Miniboss_Wall00");

				Ground_and_Wall* MinibossWall1 = object::Instantiate<Ground_and_Wall>(Vector3(-12.f, -288.f, -205.f), eLayerType::BACK_GROUND);
				MinibossWall1->GetComponent<Transform>()->SetScale(Vector3(30, 70.f, 0.f));	MinibossWall1->SetName(L"Miniboss_Wall01");

				Ground_and_Wall* MinibossWall2 = object::Instantiate<Ground_and_Wall>(Vector3(80.f, -288.f, -205.f), eLayerType::BACK_GROUND);
				MinibossWall2->GetComponent<Transform>()->SetScale(Vector3(30, 70, 0.f));	MinibossWall2->SetName(L"Miniboss_Wall02");

				Ground_and_Wall* MinibossWall3 = object::Instantiate<Ground_and_Wall>(Vector3(270.f, -288.f, -205.f), eLayerType::BACK_GROUND);
				MinibossWall3->GetComponent<Transform>()->SetScale(Vector3(30, 70, 0.f));	MinibossWall3->SetName(L"Miniboss_Wall03");

				Ground_and_Wall* MinibossWall4 = object::Instantiate<Ground_and_Wall>(Vector3(-500.f, -165.f, -205.f), eLayerType::BACK_GROUND);
				MinibossWall4->GetComponent<Transform>()->SetScale(Vector3(30, 135, 0.f));	MinibossWall4->SetName(L"Miniboss_Wall04");


				Sky_Ground* SkyGround = object::Instantiate<Sky_Ground>(Vector3(-255.f, -105, -205.f), eLayerType::BACK_GROUND);
				SkyGround->GetComponent<Transform>()->SetScale(Vector3(125, 15.f, 0.f));	SkyGround->SetName(L"SkyGround00");

				Sky_Ground* SkyGround1 = object::Instantiate<Sky_Ground>(Vector3(325.f, -105, -205.f), eLayerType::BACK_GROUND);
				SkyGround1->GetComponent<Transform>()->SetScale(Vector3(125, 15.f, 0.f));	SkyGround1->SetName(L"SkyGround00");

				Sky_Ground* SkyGround2 = object::Instantiate<Sky_Ground>(Vector3(17.f, 22, -205.f), eLayerType::BACK_GROUND);
				SkyGround2->GetComponent<Transform>()->SetScale(Vector3(800, 15.f, 0.f));	SkyGround2->SetName(L"SkyGround00");



				static Vector2 TileSize = Vector2(32.f, 32.f);
				static int Tile_Colum = 60;
				static int Tile_Row = 30;

				static Tile_Ground* Tile_map = object::Instantiate<Tile_Ground>(eLayerType::BACK_GROUND);
				Tile_map->SetName(L"tile_stage1_2");
				Transform* tr = Tile_map->GetComponent<Transform>();
				tr->SetPositionZ(-200.f);
				tr->AddPositionY(0.f);
				tr->SetPositionX(0.f);
				tr->SetScale(Vector3(Tile_Colum * TileSize.x, Tile_Row * TileSize.y, 0.f));

				TileMap::TileMap_Setting(Tile_map, L"Stage1_2Tile", TileSize, Tile_Colum, Tile_Row, L"\\Resources\\Metadata\\TileMap\\Stage1_2.xml");
			}
	#pragma endregion	
	}

	void Stage1_2::Update()
	{
		Transform* PlayerTR = _player->GetComponent<Transform>();
		Vector3 player_pos = PlayerTR->GetPosition();

		CamareShooting();


		firstMonsters = AreAllMonstersDead(monsterGroup1, firstMonsters);
		if (firstMonsters == true)
		{
			if (change_monster1 == false)
			{
				for (Monster* mon : monsterGroup2)
				{
					mon->SetState(GameObject::eState::Active);
				}
				change_monster1 = true;
			}
		}
		secondMonsters = AreAllMonstersDead(monsterGroup2, secondMonsters);
		if (secondMonsters == true)
		{
			if (change_monster2 == false)
			{
				for (Monster* mon : monsterGroup3)
				{
					mon->SetState(GameObject::eState::Active);
				}
				change_monster2 = true;
			}
		}

		thirdMonsters = AreAllMonstersDead(monsterGroup3, thirdMonsters);
		if (thirdMonsters == true)
		{
			if (change_monster3 == false)
			{
				Door1->Set_Door_Allow(true);
				Door1->Set_Stage1_Door(3);
				change_monster3 = true;
			}
		}

		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(L"Stage1_Boss"); 
		}

		if (_changecheck == true)
		{
			_player->SetPlayer_Pos(player_pos);
			//_player->SetPlay_List(_player->GetCurrentPlay_List(), true, _player->GetDirection());
			_player->SetPlay_List(_player->GetCurrentPlay_List(), _player->GetPlay_List(), true, _player->GetDirection());

			_changecheck = false;
		}

		Scene::Update();
	}

	void Stage1_2::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void Stage1_2::Render()
	{
		Scene::Render();
	}

	void Stage1_2::OnEnter()
	{
		as->Play("Chapter1");
		Transform* PlayerTR = _player->GetComponent<Transform>();
		Vector3 player_pos = PlayerTR->GetPosition();
		_player->SetPlayer_Pos(player_pos);
		_player->SetSwitch(true);
		_changecheck = true;

		#pragma region Cam & Mouse& Grid
		//Main Camera			
		Main_Camera* camera = object::Instantiate<Main_Camera>(Vector3(0.f, 0.f, -10.f), eLayerType::Camera);
		cameraComp = camera->AddComponent<Camera>();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		camera->AddComponent<CameraScript>();
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
		UI_Camera* UI_camera = object::Instantiate<UI_Camera>(Vector3(0.f, 0.f, -10.f), eLayerType::Camera);
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
		UI_Mouse* cursor = object::Instantiate<UI_Mouse>(Vector3(Vector3::One), eLayerType::Camera);
		cursor->SetName(L"Catle_Cursor_UI");
		cursor->GetComponent<Transform>()->SetScale(Vector3(42.f, 42.f, -250.f));
		cursor->SetName(L"Mouse_UI"); cursor->SetCamera(UI_camera);


		//Grid
		Grid* grid = object::Instantiate<Grid>(Vector3(Vector3::One), eLayerType::Grid);
		grid->SetName(L"Catle_Grid");
		GridScript* gridSc = grid->AddComponent<GridScript>();
		gridSc->SetCamera(cameraComp);
#pragma endregion	
	}

	void Stage1_2::OnExit()
	{
		_player->SettingPlay_List(jk::Player_INFO->GetCurrentPlay_List());
		as->Stop("Chapter1");
	}

	void Stage1_2::CamareShooting()
	{
		Transform* PlayerTR = _player->GetComponent<Transform>();
		Vector3 player_pos = PlayerTR->GetPosition();

		if (player_pos.x < -600)	
			cameraComp->SetCameraXY = false;		
		else		
			cameraComp->SetCameraXY = true;	

		if (player_pos.x >= -380 && player_pos.x <= 420)
		{
			if (player_pos.y > 40)
			{
				cameraComp->SetCameraXY = false;
				cameraComp->SetCameraX = true;
			}
			else
			{
				cameraComp->SetCameraXY = true;
				cameraComp->SetCameraX = false;
			}
		}
		else		
			cameraComp->SetCameraXY = true;
		
		if (player_pos.y < 40)
		{
			if (player_pos.x > 310)							
				cameraComp->SetCameraXY = false;			
			else			
				cameraComp->SetCameraXY = true;			
		}
	}
	void Stage1_2::SetMonOBJ()
	{
		//monsterGroup1
		for (int i = 0; i < 1; i++)
		{
			Monster* newMonster = OBJPOOL->Get_BigEnt();
			newMonster->Initialize();
			Transform* ttr = newMonster->GetComponent<Transform>();
			ttr->SetPosition(Vector3(25, -110, -249));
			AddMonster(newMonster);
			newMonster->SetState(GameObject::eState::Paused);
			monsterGroup1.push_back(newMonster);
		}		
		{
			Monster* newMonster = OBJPOOL->Get_BigEnt();
			newMonster->Initialize();
			Transform* ttr = newMonster->GetComponent<Transform>();
			ttr->SetPosition(Vector3(-255, -55, -249));
			AddMonster(newMonster);
			newMonster->SetState(GameObject::eState::Paused);
			monsterGroup1.push_back(newMonster);
		}
		{
			Monster* newMonster = OBJPOOL->Get_BigEnt();
			newMonster->Initialize();
			Transform* ttr = newMonster->GetComponent<Transform>();
			ttr->SetPosition(Vector3(320, -55, -249));
			AddMonster(newMonster);
			newMonster->SetState(GameObject::eState::Paused);
			monsterGroup1.push_back(newMonster);
		}	




		//monsterGroup2
		for (int i = 0; i < 7; i++)
		{
			Monster_warrior* _warrior = OBJPOOL->Get_Monster_warrior();
			//_warrior->Initialize();
			Transform* ttr = _warrior->GetComponent<Transform>();
			ttr->SetPosition(Vector3(-150.f + i * 50.f, 70.f, -249.f));
			//AddMonster(_warrior);
			//_warrior->SetState(GameObject::eState::Paused);
			monsterGroup2.push_back(_warrior);
		}
		for (int i = 0; i < 3; i++)
		{
			Stone_wizard* _warrior = OBJPOOL->Get_wizard();
			_warrior->Initialize();
			Transform* ttr = _warrior->GetComponent<Transform>();
			ttr->SetPosition(Vector3(-200.f + i * 100.f, 70.f, -249.f));
			AddMonster(_warrior);
			_warrior->SetState(GameObject::eState::Paused);
			monsterGroup2.push_back(_warrior);
		}
		for (int i = 0; i < 2; i++)
		{
			Monster* newMonster = OBJPOOL->Get_Blossom();
			newMonster->Initialize();
			Transform* ttr = newMonster->GetComponent<Transform>();
			ttr->SetPosition(Vector3(120.f + i * 75.f,70.f, -249.f));
			AddMonster(newMonster);
			newMonster->SetState(GameObject::eState::Paused);
			monsterGroup2.push_back(newMonster);
		}
		for (int i = 0; i < 2; i++)
		{
			Monster* newMonster = OBJPOOL->Get_GreenTree();
			newMonster->Initialize();
			Transform* ttr = newMonster->GetComponent<Transform>();
			ttr->SetPosition(Vector3(80.f + i * 50.f, 70.f, -249.f));
			AddMonster(newMonster);
			newMonster->SetState(GameObject::eState::Paused);
			monsterGroup2.push_back(newMonster);
		}



		//monsterGroup3
		for (int i = 0; i < 5; i++)
		{
			Monster* newMonster = OBJPOOL->Get_Monster_warrior();
			//newMonster->Initialize();
			Transform* ttr = newMonster->GetComponent<Transform>();
			ttr->SetPosition(Vector3(0.f + i * 50.f, 70.f, -249.f));
			//AddMonster(newMonster);
			//newMonster->SetState(GameObject::eState::Paused);
			monsterGroup3.push_back(newMonster);
		}
		for (int i = 0; i < 3; i++)
		{
			Monster* newMonster = OBJPOOL->Get_wizard();
			newMonster->Initialize();
			Transform* ttr = newMonster->GetComponent<Transform>();
			ttr->SetPosition(Vector3(-200.f + i * 150.f, 70.f, -249.f));
			AddMonster(newMonster);
			newMonster->SetState(GameObject::eState::Paused);
			monsterGroup3.push_back(newMonster);
		}
		for (int i = 0; i < 1; i++)
		{
			Monster* newMonster = OBJPOOL->Get_Hammer();
			newMonster->Initialize();
			Transform* ttr = newMonster->GetComponent<Transform>();
			ttr->SetPosition(Vector3(-100.f + i * 150.f, 70.f, -249.f));
			AddMonster(newMonster);
			newMonster->SetState(GameObject::eState::Paused);
			monsterGroup3.push_back(newMonster);
		}
		for (int i = 0; i < 2; i++)
		{
			Monster* newMonster = OBJPOOL->Get_Blossom();
			newMonster->Initialize();
			Transform* ttr = newMonster->GetComponent<Transform>();
			ttr->SetPosition(Vector3(-100.f + i * 75.f, 70.f, -249.f));
			AddMonster(newMonster);
			newMonster->SetState(GameObject::eState::Paused);
			monsterGroup3.push_back(newMonster);
		}
		for (int i = 0; i < 2; i++)
		{
			Monster* newMonster = OBJPOOL->Get_GreenTree();
			newMonster->Initialize();
			Transform* ttr = newMonster->GetComponent<Transform>();
			ttr->SetPosition(Vector3(-200.f + i * 80.f, 70.f, -249.f));
			AddMonster(newMonster);
			newMonster->SetState(GameObject::eState::Paused);
			monsterGroup3.push_back(newMonster);
		}
	}
	bool Stage1_2::AreAllMonstersDead(const std::vector<Monster*>& monsterGroup, bool check)
	{
		for (const Monster* monster : monsterGroup)
		{
			if (!monster->_Die)
			{
				check = false;
				// 하나라도 살아있는 몬스터가 있으면 false 반환
				return check;
			}
		}
		// 모든 몬스터가 죽었다면 true 반환
		check = true;
		return check;
	}
}
