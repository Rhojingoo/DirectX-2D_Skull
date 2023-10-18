#include "jkStage2_1.h"

namespace jk
{
	Stage2_1::Stage2_1()
	{
	}

	Stage2_1::~Stage2_1()
	{
		delete OBJPOOL;
		OBJPOOL = nullptr;

		monsterGroup1.clear();
		monsterGroup2.clear();
		monsterGroup3.clear();
	}

	void Stage2_1::Initialize()
	{

		OBJPOOL = new Monster_ObjPool(2, 10, 20, 10);

		SetMonOBJ();

		_BGSound = object::Instantiate<Sound>(Vector3(0.f, -150.f, -250.f), eLayerType::Player);
		as = _BGSound->AddComponent<AudioSource>();
		as->SetClip(Resources::Load<AudioClip>(L"Chapter2", L"..\\Resources\\Sound\\Chapter2\\Chapter2.wav", "Chapter2"));
		as->SetLoop(true);

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

			_player = object::Instantiate<Player>(Vector3(-820.f, 150.f, -250.f), eLayerType::Player);
			_player->SetName(L"player_select");



		#pragma region Door
					Door1 = object::Instantiate<Stage2_Door>(Vector3(567.f, 65.f, -249.f), eLayerType::BACK_GROUND);
					Door1->Set_Door_Allow(true); Door1->Set_Stage2_Door(6);	Door1->Set_NextStage(L"Stage2_mBoss");


					Stage2_Door* Door2 = object::Instantiate<Stage2_Door>(Vector3(837.f, 65.f, -249.f), eLayerType::BACK_GROUND);
					Door2->Set_Door_Allow(true); Door2->Set_Stage2_Door(9); Door2->Set_NextStage(L"Stage2_mBoss");


					Stage_end_wall* Door_Wall = object::Instantiate<Stage_end_wall>(Vector3(700.f, 65.f, -248.f), eLayerType::BACK_GROUND);
					Door_Wall->Set_Wall_Allow(true);  Door_Wall->Set_Wall_Stage(1);
		#pragma endregion	



		#pragma region BackGround &Tile
			#pragma region BackGround	
					{
						Back_ground* Back_Ground = object::Instantiate<Back_ground>(Vector3(0.f, 0.f, 105.f), eLayerType::Fore_Ground, L"ForeGround_Stage2_00");
						Back_Ground->GetComponent<Transform>()->SetScale(Vector3(1920.f, 800.f, 0.0f));
					}
					{
						Back_ground* Back_Ground = object::Instantiate<Back_ground>(Vector3(-500.f, -200.f, 103.f), eLayerType::Fore_Ground, L"Stage1_Back_GR12");
						Back_Ground->GetComponent<Transform>()->SetScale(Vector3(718.f, 380.f, 0.0f));
					}
					{
						Back_ground* Back_Ground = object::Instantiate<Back_ground>(Vector3(0.f, -250.f, 102.f), eLayerType::Fore_Ground, L"Stage1_Back_GR14");
						Back_Ground->GetComponent<Transform>()->SetScale(Vector3(780.f, 189.f, 0.0f));
					}
					{
						Back_ground* Back_Ground = object::Instantiate<Back_ground>(Vector3(500.f, -230.f, 103.f), eLayerType::Fore_Ground, L"Stage1_Back_GR12");
						Back_Ground->GetComponent<Transform>()->SetScale(Vector3(718.f, 380.f, 0.0f));
					}
					{
						Cloud* cloud = object::Instantiate<Cloud>(Vector3(0.f, 0.f, 104.f), eLayerType::Map_Effect, L"Stage2_Cloud");
						cloud->GetComponent<Transform>()->SetScale(Vector3(1860.f, 222.f, 0.f)); cloud->SetName(L"stage2_cloud"); 
					}
					{
						Cloud* cloud = object::Instantiate<Cloud>(Vector3(0.f, 200.f, 104.f), eLayerType::Map_Effect, L"Stage2_Cloud");
						cloud->GetComponent<Transform>()->SetScale(Vector3(1860.f, 222.f, 0.f)); cloud->SetName(L"stage2_cloud");
					}
					{	
						Back_ground* Back_Ground = object::Instantiate<Back_ground>(Vector3(0.f, 0.f, 50.f), eLayerType::Fore_Ground, L"BackGround_Stage2_01");
						Back_Ground->GetComponent<Transform>()->SetScale(Vector3(1920.f, 800.f, 0.0f));
					}	

					{
						Back_ground* Back_Ground = object::Instantiate<Back_ground>(Vector3(85.f, 0.f, 42.f), eLayerType::Fore_Ground, L"BackGround_Stage2_03");
						Back_Ground->GetComponent<Transform>()->SetScale(Vector3(1676.f, 960.f, 0.0f));
					}

					{
						Back_ground* Back_Ground = object::Instantiate<Back_ground>(Vector3(0.f, 0.f, 41.f), eLayerType::Fore_Ground, L"BackGround_Stage2_05");
						Back_Ground->GetComponent<Transform>()->SetScale(Vector3(1920.f, 800.f, 0.0f));
					}



			#pragma endregion
			#pragma region Tile & Ground_Col
					{
						Ground_Map* MinibossMap = object::Instantiate<Ground_Map>(Vector3(-80.f, -410.f, -205.f), eLayerType::BACK_GROUND);
						MinibossMap->GetComponent<Transform>()->SetScale(Vector3(3000, 320.f, 0.f));	MinibossMap->SetName(L"Stage2_ground00");

						Ground_Map* MinibossMap1 = object::Instantiate<Ground_Map>(Vector3(-830.f, 65.f, -205.f), eLayerType::BACK_GROUND);
						MinibossMap1->GetComponent<Transform>()->SetScale(Vector3(250, 15.f, 0.f));	MinibossMap1->SetName(L"Stage2_ground01");

						Ground_Map* MinibossMap2 = object::Instantiate<Ground_Map>(Vector3(720.f, 0.f, -205.f), eLayerType::BACK_GROUND);
						MinibossMap2->GetComponent<Transform>()->SetScale(Vector3(475, 15.f, 0.f));	MinibossMap2->SetName(L"Stage2_ground02");



						Ground_and_Wall* MinibossWall = object::Instantiate<Ground_and_Wall>(Vector3(-850.f,250.f, -205.f), eLayerType::BACK_GROUND);
						MinibossWall->GetComponent<Transform>()->SetScale(Vector3(230, 80.f, 0.f));	MinibossWall->SetName(L"Stage2_Wall00");

						Ground_and_Wall* MinibossWall1 = object::Instantiate<Ground_and_Wall>(Vector3(-320.f, 250, -205.f), eLayerType::BACK_GROUND);
						MinibossWall1->GetComponent<Transform>()->SetScale(Vector3(250, 80.f, 0.f));	MinibossWall1->SetName(L"Stage2_Wall01");

						Ground_and_Wall* MinibossWall2 = object::Instantiate<Ground_and_Wall>(Vector3(190.f, 250, -205.f), eLayerType::BACK_GROUND);
						MinibossWall2->GetComponent<Transform>()->SetScale(Vector3(250, 80.f, 0.f));	MinibossWall2->SetName(L"Stage2_Wall02");

						Ground_and_Wall* MinibossWall3 = object::Instantiate<Ground_and_Wall>(Vector3(700.f, 250, -205.f), eLayerType::BACK_GROUND);
						MinibossWall3->GetComponent<Transform>()->SetScale(Vector3(240, 80.f, 0.f));	MinibossWall3->SetName(L"Stage2_Wall03");

						Ground_and_Wall* MinibossWall4 = object::Instantiate<Ground_and_Wall>(Vector3(-830.f, 20.f, -205.f), eLayerType::BACK_GROUND);
						MinibossWall4->GetComponent<Transform>()->SetScale(Vector3(250, 70.f, 0.f));	MinibossWall4->SetName(L"Stage2_Wall04");

						Ground_and_Wall* MinibossWall5 = object::Instantiate<Ground_and_Wall>(Vector3(720.f, -140, -205.f), eLayerType::BACK_GROUND);
						MinibossWall5->GetComponent<Transform>()->SetScale(Vector3(470, 250.f, 0.f));	MinibossWall5->SetName(L"Stage2_Wall05");



						Sky_Ground* SkyGround = object::Instantiate<Sky_Ground>(Vector3(-640.f, -125, -205.f), eLayerType::BACK_GROUND);
						SkyGround->GetComponent<Transform>()->SetScale(Vector3(120, 15.f, 0.f));	SkyGround->SetName(L"SkyGround01");

						Sky_Ground* SkyGround1 = object::Instantiate<Sky_Ground>(Vector3(415.f, -125, -205.f), eLayerType::BACK_GROUND);
						SkyGround1->GetComponent<Transform>()->SetScale(Vector3(120, 15.f, 0.f));	SkyGround1->SetName(L"SkyGround02");

	



						static Vector2 TileSize = Vector2(32.f, 32.f);
						static int Tile_Colum = 60;
						static int Tile_Row = 25;

						static Tile_Ground* Tile_map = object::Instantiate<Tile_Ground>(eLayerType::BACK_GROUND);
						Tile_map->SetName(L"Stage2_1");
						Transform* tr = Tile_map->GetComponent<Transform>();					
						tr->SetPositionZ(-200.f);
						tr->AddPositionY(0.f);
						tr->SetScale(Vector3(Tile_Colum * TileSize.x, Tile_Row * TileSize.y, 0.f));
						TileMap::TileMap_Setting(Tile_map, L"Stage2_Tile", TileSize, Tile_Colum, Tile_Row, L"\\Resources\\Metadata\\TileMap\\Stage2_1.xml");
					}
			#pragma endregion
		#pragma endregion 	
	}

	void Stage2_1::Update()
	{
		Transform* PlayerTR = _player->GetComponent<Transform>();
		Vector3 player_pos = PlayerTR->GetPosition();


		if (_player->firstGroundcheck == true)
		{
			if (first_groundtouch == false)
			{
				first_groundtouch = true;
			}
		}

		CamareShooting();

		if (_Monster_Start == true)
		{
			if (first_MonsterCreate == false)
			{
				for (Monster* mon : monsterGroup1)
				{
					mon->SetState(GameObject::eState::Active);
				}
				first_MonsterCreate = true;
			}
		}
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
				change_monster3 = true;
			}
		}
		if (change_monster3 == true)
		{
			Door1->Set_Door_Allow(true);
			Door1->Set_Stage2_Door(2);
		}


		if (_changecheck == true)
		{
			_player->SetPlayer_Pos(player_pos);
			_player->SetPlay_List(_player->GetCurrentPlay_List(), _player->GetPlay_List(), true, _player->GetDirection());
			_changecheck = false;
		}


		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(L"Stage2_mBoss");
		}

		Scene::Update();
	}
	void Stage2_1::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void Stage2_1::Render()
	{
		Scene::Render();
	}
	void Stage2_1::OnEnter()
	{	
		as->Play("Chapter2");
		Transform* PlayerTR = _player->GetComponent<Transform>();
		Vector3 player_pos = PlayerTR->GetPosition();
		_player->SetPlayer_Pos(player_pos);
		_player->SetSwitch(true);
		_changecheck = true;

		_player->firstGroundcheck = false;

		#pragma region Cam & Mouse& Grid
		//Main Camera			
		Main_Camera* camera = object::Instantiate<Main_Camera>(Vector3(0.f, 0.f, -10.f), eLayerType::Camera);
		cameraComp = camera->AddComponent<Camera>();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		camera->AddComponent<CameraScript>();
		renderer::cameras.push_back(cameraComp);
		renderer::mainCamera = cameraComp;
		cameraComp->SetCamera = true;
		Transform* camTR = camera->GetComponent<Transform>();
		camTR->SetPosition(Vector3(player_pos.x+180, player_pos.y, -10.f));
		cameraComp->Set_MaxPlayerX(600.f);
		cameraComp->Set_MinPlayerX(-650.f);
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
	void Stage2_1::OnExit()
	{
		as->Stop("Chapter2");
		//_player->SettingPlay_List(jk::Player_INFO->GetCurrentPlay_List());
	}
	void Stage2_1::CamareShooting()
	{
		Transform* PlayerTR = _player->GetComponent<Transform>();
		Vector3 player_pos = PlayerTR->GetPosition();

		if (first_groundtouch == true)
		{
			if (_CamFirstSet == false)
			{
				cameraComp->SetTarget(_player);
				cameraComp->SetCameraY = true;
				_CamFirstSet = true;
				
			}
		}

		if (player_pos.x <= -450 && player_pos.y <= -220)
		{
			cameraComp->Set_MinPlayerX(-600.f);
			cameraComp->SetCameraX = true;
			_Monster_Start = true;
		}
	
	}
	void Stage2_1::SetMonOBJ()
	{
		//monsterGroup1
		for (int i = 0; i < 7; i++)
		{
			Monster* _warrior = OBJPOOL->Get_Goldwarrior();
			_warrior->Initialize();
			Transform* ttr = _warrior->GetComponent<Transform>();
			ttr->SetPosition(Vector3(-460 + i * 120, -190, -249));
			AddMonster(_warrior);
			_warrior->SetState(GameObject::eState::Paused);
			monsterGroup1.push_back(_warrior);
		}
		for (int i = 0; i < 3; i++)
		{
			Monster* _warrior = OBJPOOL->Get_GoldHammer();
			_warrior->Initialize();
			Transform* ttr = _warrior->GetComponent<Transform>();
			ttr->SetPosition(Vector3(-350 + i * 300, -190, -249));
			AddMonster(_warrior);
			_warrior->SetState(GameObject::eState::Paused);
			monsterGroup1.push_back(_warrior);
		}
		for (int i = 0; i < 3; i++)
		{
			Monster* _warrior = OBJPOOL->Get_wizard();
			_warrior->Initialize();
			Transform* ttr = _warrior->GetComponent<Transform>();
			ttr->SetPosition(Vector3( -100+ i * 200, -190, -249));
			AddMonster(_warrior);
			_warrior->SetState(GameObject::eState::Paused);
			monsterGroup1.push_back(_warrior);
		}


		//monsterGroup2
		for (int i = 0; i < 3; i++)
		{
			Monster* newMonster = OBJPOOL->Get_Goldwarrior();
			newMonster->Initialize();
			Transform* ttr = newMonster->GetComponent<Transform>();
			ttr->SetPosition(Vector3(-400 + i * 100, -190, -249));
			AddMonster(newMonster);
			newMonster->SetState(GameObject::eState::Paused);
			monsterGroup2.push_back(newMonster);
		}
		for (int i = 0; i < 4; i++)
		{
			Monster* newMonster = OBJPOOL->Get_wizard();
			newMonster->Initialize();
			Transform* ttr = newMonster->GetComponent<Transform>();
			ttr->SetPosition(Vector3(-100 + i * 150, -190, -249));
			AddMonster(newMonster);
			newMonster->SetState(GameObject::eState::Paused);
			monsterGroup2.push_back(newMonster);
		}
		for (int i = 0; i < 2; i++)
		{
			Monster* newMonster = OBJPOOL->Get_GoldHammer();
			newMonster->Initialize();
			Transform* ttr = newMonster->GetComponent<Transform>();
			ttr->SetPosition(Vector3(0 + i * 150, -190, -249));
			AddMonster(newMonster);
			newMonster->SetState(GameObject::eState::Paused);
			monsterGroup2.push_back(newMonster);
		}
		for (int i = 0; i < 2; i++)
		{
			Monster* newMonster = OBJPOOL->Get_LionSpear();
			newMonster->Initialize();
			Transform* ttr = newMonster->GetComponent<Transform>();
			ttr->SetPosition(Vector3(0 + i * 150, -190, -249));
			AddMonster(newMonster);
			newMonster->SetState(GameObject::eState::Paused);
			monsterGroup2.push_back(newMonster);
		}

		//monsterGroup3
		for (int i = 0; i < 10; i++)
		{
			Monster* newMonster = OBJPOOL->Get_Goldwarrior();
			newMonster->Initialize();
			Transform* ttr = newMonster->GetComponent<Transform>();
			ttr->SetPosition(Vector3(-400 + i * 75, -190, -249));
			AddMonster(newMonster);
			newMonster->SetState(GameObject::eState::Paused);
			monsterGroup3.push_back(newMonster);
		}
		for (int i = 0; i < 3; i++)
		{
			Monster* newMonster = OBJPOOL->Get_LionSpear();
			newMonster->Initialize();
			Transform* ttr = newMonster->GetComponent<Transform>();
			ttr->SetPosition(Vector3(-300 + i * 300, -190, -249));
			AddMonster(newMonster);
			newMonster->SetState(GameObject::eState::Paused);
			monsterGroup3.push_back(newMonster);
		}
		for (int i = 0; i < 3; i++)
		{
			Monster* newMonster = OBJPOOL->Get_LionWarrior();
			newMonster->Initialize();
			Transform* ttr = newMonster->GetComponent<Transform>();
			ttr->SetPosition(Vector3(-150 + i * 150, -190, -249));
			AddMonster(newMonster);
			newMonster->SetState(GameObject::eState::Paused);
			monsterGroup3.push_back(newMonster);
		}


	}
	bool Stage2_1::AreAllMonstersDead(const std::vector<Monster*>& monsterGroup, bool check)
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