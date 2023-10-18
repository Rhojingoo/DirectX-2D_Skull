#include "jkStage2_2.h"
#include "Sofa_Spring.h"

namespace jk
{
	Stage2_2::Stage2_2()
	{
	}
	Stage2_2::~Stage2_2()
	{
		delete OBJPOOL;
		OBJPOOL = nullptr;

		monsterGroup1.clear();
		monsterGroup2.clear();
		monsterGroup3.clear();
	}
	void Stage2_2::Initialize()
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

			OBJPOOL = new Monster_ObjPool(2, 0, 10, 8);

			SetMonOBJ();


			_BGSound = object::Instantiate<Sound>(Vector3(0.f, -150.f, -250.f), eLayerType::Player);
			as = _BGSound->AddComponent<AudioSource>();
			as->SetClip(Resources::Load<AudioClip>(L"Chapter2", L"..\\Resources\\Sound\\Chapter2\\Chapter2.wav", "Chapter2"));
			as->SetLoop(true);

			_player = object::Instantiate<Player>(Vector3(-770.f, -90.f, -250.f), eLayerType::Player);
			_player->SetName(L"player_select");


		#pragma region Door
			Door1 = object::Instantiate<Stage2_Door>(Vector3(550.f, 80.f, -249.f), eLayerType::BACK_GROUND);
			Door1->Set_Door_Allow(true); Door1->Set_Stage2_Door(7);	Door1->Set_NextStage(L"Stage2_Boss");

			Stage_end_wall* Door_Wall = object::Instantiate<Stage_end_wall>(Vector3(550.f, 80.f, -248.f), eLayerType::BACK_GROUND);
			Door_Wall->Set_Wall_Allow(true);  Door_Wall->Set_Wall_Stage(1);
		#pragma endregion	

		Sofa_Spring* Spring = object::Instantiate<Sofa_Spring>(Vector3(220.f, -205.f, -249.f), eLayerType::Monster);

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
								Back_ground* Back_Ground = object::Instantiate<Back_ground>(Vector3(0.f, 80.f, 49.f), eLayerType::Fore_Ground, L"Miniboss_02");
								Back_Ground->GetComponent<Transform>()->SetScale(Vector3(1849.f, 668.f, 0.0f));
							}

					#pragma region Tile	
									{
										Ground_Map* MinibossMap = object::Instantiate<Ground_Map>(Vector3(40.f, -310.f, -205.f), eLayerType::BACK_GROUND);
										MinibossMap->GetComponent<Transform>()->SetScale(Vector3(3000, 180.f, 0.f));	MinibossMap->SetName(L"Stage2_ground00");

										Ground_Map* MinibossMap1 = object::Instantiate<Ground_Map>(Vector3(605.f, 32.f, -205.f), eLayerType::BACK_GROUND);
										MinibossMap1->GetComponent<Transform>()->SetScale(Vector3(700, 15.f, 0.f));	MinibossMap1->SetName(L"Stage2_ground01");

										Ground_Map* MinibossMap2 = object::Instantiate<Ground_Map>(Vector3(-365.f, 32.f, -205.f), eLayerType::BACK_GROUND);
										MinibossMap2->GetComponent<Transform>()->SetScale(Vector3(220, 15.f, 0.f));	MinibossMap2->SetName(L"Stage2_ground02");

										Ground_Map* MinibossMap3 = object::Instantiate<Ground_Map>(Vector3(-520.f, -64.f, -205.f), eLayerType::BACK_GROUND);
										MinibossMap3->GetComponent<Transform>()->SetScale(Vector3(100, 15.f, 0.f));	MinibossMap3->SetName(L"Stage2_ground03");

										Ground_Map* MinibossMap4 = object::Instantiate<Ground_Map>(Vector3(-760.f, -160.f, -205.f), eLayerType::BACK_GROUND);
										MinibossMap4->GetComponent<Transform>()->SetScale(Vector3(400, 15.f, 0.f));	MinibossMap4->SetName(L"Stage2_ground04");


			
										Ground_and_Wall* MinibossWall = object::Instantiate<Ground_and_Wall>(Vector3(-370.f, -130.f, -205.f), eLayerType::BACK_GROUND);
										MinibossWall->GetComponent<Transform>()->SetScale(Vector3(220, 300.f, 0.f));	MinibossWall->SetName(L"Stage2_Wall00");

										Ground_and_Wall* MinibossWall1 = object::Instantiate<Ground_and_Wall>(Vector3(-520.f, -125, -205.f), eLayerType::BACK_GROUND);
										MinibossWall1->GetComponent<Transform>()->SetScale(Vector3(100, 100.f, 0.f));	MinibossWall1->SetName(L"Stage2_Wall01");

										Ground_and_Wall* MinibossWall2 = object::Instantiate<Ground_and_Wall>(Vector3(390.f, -120.f, -205.f), eLayerType::BACK_GROUND);
										MinibossWall2->GetComponent<Transform>()->SetScale(Vector3(250, 300.f, 0.f));	MinibossWall2->SetName(L"Stage2_Wall02");


										Sky_Ground* SkyGround = object::Instantiate<Sky_Ground>(Vector3(0.f, 30, -205.f), eLayerType::BACK_GROUND);
										SkyGround->GetComponent<Transform>()->SetScale(Vector3(520*1.8, 15.f, 0.f));	SkyGround->SetName(L"SkyGround01");



										static Vector2 TileSize = Vector2(32.f, 32.f);
										static int Tile_Colum = 60;
										static int Tile_Row = 25;

										static Tile_Ground* Tile_map = object::Instantiate<Tile_Ground>(eLayerType::BACK_GROUND);
										Tile_map->SetName(L"Stage2_MiniBoss");
										Transform* tr = Tile_map->GetComponent<Transform>();
										tr->SetPositionZ(-200.f);
										tr->AddPositionY(0.f);
										tr->SetScale(Vector3(Tile_Colum * TileSize.x, Tile_Row * TileSize.y, 0.f));
										TileMap::TileMap_Setting(Tile_map, L"Stage2_Tile", TileSize, Tile_Colum, Tile_Row, L"\\Resources\\Metadata\\TileMap\\Stage2_2.xml");
									}
					#pragma endregion
			#pragma endregion 
	}
	void Stage2_2::Update()
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
			SceneManager::LoadScene(L"Stage2_Boss");
		}
		Scene::Update();
	}
	void Stage2_2::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void Stage2_2::Render()
	{
		Scene::Render();
	}
	void Stage2_2::OnEnter()
	{
		as->Play("Chapter2");
		Transform* PlayerTR = _player->GetComponent<Transform>();
		Vector3 player_pos = PlayerTR->GetPosition();
		_player->SetPlayer_Pos(player_pos);
		_player->SetSwitch(true);
		_changecheck = true;

		_player->firstGroundcheck = false;

		#pragma region Camera & Grid

		//Main Camera
		Main_Camera* camera = object::Instantiate<Main_Camera>(Vector3(0.f, 0.f, -10.f), eLayerType::Camera);
		cameraComp = camera->AddComponent<Camera>();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		camera->AddComponent<CameraScript>();
		renderer::cameras.push_back(cameraComp);
		renderer::mainCamera = cameraComp;
		cameraComp->SetCamera = true;
		Transform* camTR = camera->GetComponent<Transform>();
		camTR->SetPosition(Vector3(player_pos.x + 180, player_pos.y, -10.f));
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
		//renderer::cameras.push_back(cameraComp_ui);

		Grid* grid = object::Instantiate<Grid>(Vector3(Vector3::One), eLayerType::Grid);
		grid->SetName(L"Catle_Grid");
		GridScript* gridSc = grid->AddComponent<GridScript>();
		gridSc->SetCamera(cameraComp);
#pragma endregion 
	}
	void Stage2_2::OnExit()
	{
		as->Stop("Chapter2");
	}

	void Stage2_2::CamareShooting()
	{
		Transform* PlayerTR = _player->GetComponent<Transform>();
		Vector3 player_pos = PlayerTR->GetPosition();

		if (first_groundtouch == true)
		{
			if (player_pos.x >= -580)
			{
				cameraComp->SetTarget(_player);
				cameraComp->SetCameraXY = true;			
				_CamFirstSet = true;
			}
		}

		
		if (player_pos.x >= -50)
		{
			cameraComp->Set_MinPlayerX(-600.f);

			_Monster_Start = true;
		}
	}
	void Stage2_2::SetMonOBJ()
	{		//monsterGroup1
		for (int i = 0; i < 10; i++)
		{
			Monster* _warrior = OBJPOOL->Get_Goldwarrior();
			_warrior->Initialize();
			Transform* ttr = _warrior->GetComponent<Transform>();
			ttr->SetPosition(Vector3(-210.f + i * 50.f, -165.f, -249.f));
			AddMonster(_warrior);
			_warrior->SetState(GameObject::eState::Paused);
			monsterGroup1.push_back(_warrior);
		}
		for (int i = 0; i < 3; i++)
		{
			Monster* _warrior = OBJPOOL->Get_GoldHammer();
			_warrior->Initialize();
			Transform* ttr = _warrior->GetComponent<Transform>();
			ttr->SetPosition(Vector3(-150.f + i * 100.f, -165.f, -249.f));
			AddMonster(_warrior);
			_warrior->SetState(GameObject::eState::Paused);
			monsterGroup1.push_back(_warrior);
		}
		for (int i = 0; i < 3; i++)
		{
			Monster* _warrior = OBJPOOL->Get_LionWizard();
			_warrior->Initialize();
			Transform* ttr = _warrior->GetComponent<Transform>();
			ttr->SetPosition(Vector3(-210.f + i * 200.f, 165.f, -249.f));
			AddMonster(_warrior);
			_warrior->SetState(GameObject::eState::Paused);
			monsterGroup1.push_back(_warrior);
		}


		//monsterGroup2
		for (int i = 0; i < 3; i++)
		{
			Monster* _warrior = OBJPOOL->Get_GoldHammer();
			_warrior->Initialize();
			Transform* ttr = _warrior->GetComponent<Transform>();
			ttr->SetPosition(Vector3(-150.f + i * 100.f, -165.f, -249.f));
			AddMonster(_warrior);
			_warrior->SetState(GameObject::eState::Paused);
			monsterGroup2.push_back(_warrior);
		}
		for (int i = 0; i < 3; i++)
		{
			Monster* newMonster = OBJPOOL->Get_LionWarrior();
			newMonster->Initialize();
			Transform* ttr = newMonster->GetComponent<Transform>();
			ttr->SetPosition(Vector3(-40.f + i * 50.f, -165.f, -249.f));
			AddMonster(newMonster);
			newMonster->SetState(GameObject::eState::Paused);
			monsterGroup2.push_back(newMonster);
		}
		for (int i = 0; i < 3; i++)
		{
			Monster* newMonster = OBJPOOL->Get_LionSpear();
			newMonster->Initialize();
			Transform* ttr = newMonster->GetComponent<Transform>();
			ttr->SetPosition(Vector3(-100.f + i * 50.f, -165.f, -249.f));
			AddMonster(newMonster);
			newMonster->SetState(GameObject::eState::Paused);
			monsterGroup2.push_back(newMonster);
		}



		//monsterGroup3
		for (int i = 0; i < 2; i++)
		{
			Monster* _warrior = OBJPOOL->Get_GoldHammer();
			_warrior->Initialize();
			Transform* ttr = _warrior->GetComponent<Transform>();
			ttr->SetPosition(Vector3(-150.f + i * 100.f, -165.f, -249.f));
			AddMonster(_warrior);
			_warrior->SetState(GameObject::eState::Paused);
			monsterGroup3.push_back(_warrior);
		}
		for (int i = 0; i < 5; i++)
		{
			Monster* newMonster = OBJPOOL->Get_LionWarrior();
			newMonster->Initialize();
			Transform* ttr = newMonster->GetComponent<Transform>();
			ttr->SetPosition(Vector3(-60.f + i * 50.f, -165.f, -249.f));
			AddMonster(newMonster);
			newMonster->SetState(GameObject::eState::Paused);
			monsterGroup3.push_back(newMonster);
		}
		for (int i = 0; i < 5; i++)
		{
			Monster* newMonster = OBJPOOL->Get_LionSpear();
			newMonster->Initialize();
			Transform* ttr = newMonster->GetComponent<Transform>();
			ttr->SetPosition(Vector3(-120.f + i * 45.f, -165.f, -249.f));
			AddMonster(newMonster);
			newMonster->SetState(GameObject::eState::Paused);
			monsterGroup3.push_back(newMonster);
		}
		for (int i = 0; i < 3; i++)
		{
			Monster* _warrior = OBJPOOL->Get_LionWizard();
			_warrior->Initialize();
			Transform* ttr = _warrior->GetComponent<Transform>();
			ttr->SetPosition(Vector3(-150.f + i * 200.f, 165.f, -249.f));
			AddMonster(_warrior);
			_warrior->SetState(GameObject::eState::Paused);
			monsterGroup3.push_back(_warrior);
		}

	}
	bool Stage2_2::AreAllMonstersDead(const std::vector<Monster*>& monsterGroup, bool check)
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