#include "jkStage1_1.h"
#include "jkParticleSystem.h"
#include "jkPaintShader.h"
#include "LoadScenes.h"

#include "Mushroom_Spring.h"

namespace jk
{
	Stage1_1::Stage1_1()
	{
	}
	Stage1_1::~Stage1_1()
	{
		delete OBJPOOL;
		OBJPOOL = nullptr;

		monsterGroup1.clear();
		monsterGroup2.clear();
		monsterGroup3.clear();		
		monsterGroup4.clear();
	}
	void Stage1_1::Initialize()
	{
		OBJPOOL = new Monster_ObjPool(1, 15, 30, 10);

		SetMonOBJ();


		_BGSound = object::Instantiate<Sound>(Vector3(0.f, -150.f, -250.f), eLayerType::Player);
		as = _BGSound->AddComponent<AudioSource>();
		as->SetClip(Resources::Load<AudioClip>(L"Chapter1", L"..\\Resources\\Sound\\Chapter1\\Chapter1.wav", "Chapter1"));
		as->SetLoop(true);

		_player = object::Instantiate<Player>(Vector3(-700.f, -150.f, -250.f), eLayerType::Player);
		_player->SetName(L"player_select");


		Mushroom_Spring* Spring = object::Instantiate<Mushroom_Spring>(Vector3(600.f, -85.f, -249.f), eLayerType::Monster);

		#pragma region Door
				Door1 = object::Instantiate<Stage1_Door>(Vector3(-70.f, 290.f, -245.f), eLayerType::BACK_GROUND);
				Door1->Set_Door_Allow(true); Door1->Set_Stage1_Door(6);	Door1->Set_NextStage(L"Stage1_mBoss");


				Stage1_Door* Door2 = object::Instantiate<Stage1_Door>(Vector3(200.f, 290.f, -245.f), eLayerType::BACK_GROUND);
				Door2->Set_Door_Allow(true); Door2->Set_Stage1_Door(8); Door2->Set_NextStage(L"Stage1_mBoss");


				Stage_end_wall* Door_Wall = object::Instantiate<Stage_end_wall>(Vector3(63.f, 290.f, -244.f), eLayerType::BACK_GROUND);
				Door_Wall->Set_Wall_Allow(true);  Door_Wall->Set_Wall_Stage(0);


				Back_ground* Ch1_Gate_Table = object::Instantiate<Back_ground>(Vector3(63.f, 260.f, -245.f), eLayerType::BACK_GROUND, L"Ch1_Gate_Table");
				Ch1_Gate_Table->GetComponent<Transform>()->SetScale(Vector3(90.f, 19.f, 0.f));	Ch1_Gate_Table->SetName(L"Ch1_Gate_Table1");
		#pragma endregion	


		#pragma region BG	
				{
					Back_ground* Fore_S1_1_color = object::Instantiate<Back_ground>(Vector3(-100.f, 150.f, 105.f), eLayerType::Fore_Ground, L"Stage1_Fore_GR_Color");
					Fore_S1_1_color->GetComponent<Transform>()->SetScale(Vector3(960.f * 2.5, 800.f * 1.5, 0.f));	Fore_S1_1_color->SetName(L"s1_1_fore_gr_color");

					Back_ground* Fore_S1_1_tree = object::Instantiate<Back_ground>(Vector3(-100.f, 50.f, 103.f), eLayerType::Fore_Ground, L"Stage1_Fore_GR_Tree");
					Fore_S1_1_tree->GetComponent<Transform>()->SetScale(Vector3(960.f * 2.5, 800.f * 1.5, 0.f));	Fore_S1_1_tree->SetName(L"s1_1_fore_gr_tree");

					Back_ground* Mid_S1_1 = object::Instantiate<Back_ground>(Vector3(-100.f, 100.f, 101.f), eLayerType::Fore_Ground, L"Stage1_Mid_GR1_1");
					Mid_S1_1->GetComponent<Transform>()->SetScale(Vector3(960.f * 2.5, 800.f * 1.5, 0.f));	Mid_S1_1->SetName(L"Mid_S1_1");

					Back_ground* Back_GR00 = object::Instantiate<Back_ground>(Vector3(50.f, -235.f, 99.f), eLayerType::Fore_Ground, L"Stage1_Back_GR00");
					Back_GR00->GetComponent<Transform>()->SetScale(Vector3(785.f, 190.f, 0.f));	Back_GR00->SetName(L"back_gr00");

					Back_ground* Back_GR01 = object::Instantiate<Back_ground>(Vector3(-100.f, 300.f, 99.f), eLayerType::Fore_Ground, L"Stage1_Back_GR02");
					Back_GR01->GetComponent<Transform>()->SetScale(Vector3(145.f, 172.f, 0.f));	Back_GR01->SetName(L"back_gr01");

					Back_ground* Back_GR02 = object::Instantiate<Back_ground>(Vector3(45.f, 300.f, 99.f), eLayerType::Fore_Ground, L"Stage1_Back_GR02");
					Back_GR02->GetComponent<Transform>()->SetScale(Vector3(145.f, 172.f, 0.f));	Back_GR02->SetName(L"back_gr02");

				//파티클 나무
				{
					Back_ground* Back_GR03 = object::Instantiate<Back_ground>(Vector3(300.f, 350.f, 98.f), eLayerType::Fore_Ground, L"Stage1_Back_GR17");
					Back_GR03->GetComponent<Transform>()->SetScale(Vector3(359.f, 308.f, 0.f));	Back_GR03->SetName(L"back_gr03");
					ParticleSystem* mr = Back_GR03->AddComponent<ParticleSystem>(Vector3(300.f, 350.f, 98.f));

					Back_ground* Back_GR04 = object::Instantiate<Back_ground>(Vector3(-245.f, 350.f, 98.f), eLayerType::Fore_Ground, L"Stage1_Back_GR18");
					Back_GR04->GetComponent<Transform>()->SetScale(Vector3(341.f, 249.f, 0.f));	Back_GR04->SetName(L"back_gr04");
					ParticleSystem* mr2 = Back_GR04->AddComponent<ParticleSystem>(Vector3(-245.f, 350.f, 98.f));


					Back_ground* Back_GR05 = object::Instantiate<Back_ground>(Vector3(-605.f, -75.f, 98.f), eLayerType::Fore_Ground, L"Stage1_Back_GR18");
					Back_GR05->GetComponent<Transform>()->SetScale(Vector3(341.f, 249.f, 0.f));	Back_GR05->SetName(L"back_gr05");
					ParticleSystem* mr3 = Back_GR05->AddComponent<ParticleSystem>(Vector3(-605.f, -75.f, 98.f));
				}
				}
		#pragma endregion


		#pragma region tile_map		
				{
					Ground_Map* MinibossMap = object::Instantiate<Ground_Map>(Vector3(-80.f, -485.f, -205.f), eLayerType::BACK_GROUND);
					MinibossMap->GetComponent<Transform>()->SetScale(Vector3(3000, 320.f, 0.f));	MinibossMap->SetName(L"Miniboss_ground00");

					Ground_Map* MinibossMap1 = object::Instantiate<Ground_Map>(Vector3(-780.f, -215.f, -205.f), eLayerType::BACK_GROUND);
					MinibossMap1->GetComponent<Transform>()->SetScale(Vector3(630, 35.f, 0.f));	MinibossMap1->SetName(L"Miniboss_ground01");

					Ground_and_Wall* MinibossWall = object::Instantiate<Ground_and_Wall>(Vector3(-475.f, -265.f, -205.f), eLayerType::BACK_GROUND);
					MinibossWall->GetComponent<Transform>()->SetScale(Vector3(30, 130.f, 0.f));	MinibossWall->SetName(L"Miniboss_Wall00");

					Ground_and_Wall* MinibossWall1 = object::Instantiate<Ground_and_Wall>(Vector3(80.f, 175, -205.f), eLayerType::BACK_GROUND);
					MinibossWall1->GetComponent<Transform>()->SetScale(Vector3(790, 80.f, 0.f));	MinibossWall1->SetName(L"SkyGround00");

					Sky_Ground* SkyGround = object::Instantiate<Sky_Ground>(Vector3(90.f, 235, -205.f), eLayerType::BACK_GROUND);
					SkyGround->GetComponent<Transform>()->SetScale(Vector3(820, 30.f, 0.f));	SkyGround->SetName(L"SkyGround00");

					Sky_Ground* SkyGround1 = object::Instantiate<Sky_Ground>(Vector3(570.f, -105, -205.f), eLayerType::BACK_GROUND);
					SkyGround1->GetComponent<Transform>()->SetScale(Vector3(125, 15.f, 0.f));	SkyGround1->SetName(L"SkyGround01");

					Sky_Ground* SkyGround2 = object::Instantiate<Sky_Ground>(Vector3(315.f, -200, -205.f), eLayerType::BACK_GROUND);
					SkyGround2->GetComponent<Transform>()->SetScale(Vector3(190, 15.f, 0.f));	SkyGround2->SetName(L"SkyGround02");

					Sky_Ground* SkyGround3 = object::Instantiate<Sky_Ground>(Vector3(540.f, -200, -205.f), eLayerType::BACK_GROUND);
					SkyGround3->GetComponent<Transform>()->SetScale(Vector3(190, 15.f, 0.f));	SkyGround3->SetName(L"SkyGround03");


					static Vector2 TileSize = Vector2(32.f, 32.f);
					static int Tile_Colum = 60;
					static int Tile_Row = 32;

					static Tile_Ground* Tile_map = object::Instantiate<Tile_Ground>(eLayerType::BACK_GROUND);
					Tile_map->SetName(L"tile_stage1");
					Transform* tr = Tile_map->GetComponent<Transform>();
					tr->AddPositionZ(-200.f);
					tr->AddPositionY(32.f);
					tr->SetPositionX(-100.f);
					tr->SetScale(Vector3(Tile_Colum * TileSize.x, Tile_Row * TileSize.y, 0.f));

					TileMap::TileMap_Setting(Tile_map, L"Stage1_1Tile", TileSize, Tile_Colum, Tile_Row, L"\\Resources\\Metadata\\TileMap\\Stage1_1.xml");
				}
		#pragma endregion	
	}

	void Stage1_1::Update()
	{
		Transform* PlayerTR = _player->GetComponent<Transform>();
		Vector3 player_pos = PlayerTR->GetPosition();

		if (_player->firstGroundcheck == true)
		{
			if (first_groundturch == false)
			{			
				first_groundturch = true;
			}
		}

		CamareShooting();

		if (first_groundturch == true)
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
			for (Monster* mon : monsterGroup4)
			{
				mon->SetState(GameObject::eState::Active);
			}
		}
				

		fourthMonsters = AreAllMonstersDead(monsterGroup4, fourthMonsters);
		if (fourthMonsters == true)
		{
			Door1->Set_Door_Allow(true);
			Door1->Set_Stage1_Door(2);
		}


		if (_changecheck == true)
		{
			_player->SetPlayer_Pos(player_pos);
			_player->SetPlay_List(_player->GetCurrentPlay_List(), _player->GetPlay_List(), true, _player->GetDirection());
			_changecheck = false;
		}


		Scene::Update();
	}

	void Stage1_1::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void Stage1_1::Render()
	{
		Scene::Render();
	}

	void Stage1_1::OnEnter()
	{
		as->Play("Chapter1");
		Transform* PlayerTR = _player->GetComponent<Transform>();
		Vector3 player_pos = PlayerTR->GetPosition();
		_player->SetPlayer_Pos(player_pos);
		_player->SetSwitch(true);
		_changecheck = true;
		_player->firstGroundcheck = false;

		#pragma region CollisionManager
				CollisionManager::SetLayer(eLayerType::Player, eLayerType::BACK_GROUND, true);
				CollisionManager::SetLayer(eLayerType::Player, eLayerType::Item, true);
				CollisionManager::SetLayer(eLayerType::Player, eLayerType::Player, true);
				CollisionManager::SetLayer(eLayerType::Player, eLayerType::Bullet, true);
				CollisionManager::SetLayer(eLayerType::Monster, eLayerType::BACK_GROUND, true);
				CollisionManager::SetLayer(eLayerType::MiniBoss, eLayerType::BACK_GROUND, true);
				CollisionManager::SetLayer(eLayerType::Bullet, eLayerType::BACK_GROUND, true);
				CollisionManager::SetLayer(eLayerType::Boss, eLayerType::BACK_GROUND, true);
				CollisionManager::SetLayer(eLayerType::Item, eLayerType::BACK_GROUND, true);
				CollisionManager::SetLayer(eLayerType::Player, eLayerType::MiniBoss, true);
				CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
				CollisionManager::SetLayer(eLayerType::Player, eLayerType::Hitbox, true);
				CollisionManager::SetLayer(eLayerType::MiniBoss, eLayerType::Hitbox, true);
				CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Hitbox, true);
		#pragma endregion 

		#pragma region Cam & Mouse& Grid
				//Main Camera			
				Main_Camera* camera = object::Instantiate<Main_Camera>(Vector3(0.f, 0.f, -10.f), eLayerType::Camera);
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
	void Stage1_1::OnExit()
	{
		as->Stop("Chapter1");
	}
	void Stage1_1::CamareShooting()
	{
		Transform* PlayerTR = _player->GetComponent<Transform>();
		Vector3 player_pos = PlayerTR->GetPosition();
		if (player_pos.x < -450)
			cameraComp->SetCameraX = true;

		if (player_pos.x >= -450 && player_pos.x <= -380)
		{
			cameraComp->SetCameraX = false;
			cameraComp->SetCameraXY = true;
		}

		if (player_pos.x > -380)
		{
			cameraComp->SetCameraX = true;
			cameraComp->SetCameraXY = false;
		}

		if (player_pos.x < 330)
		{
			cameraComp->SetCameraX = true;
			cameraComp->SetCameraY = false;
		}

		if (player_pos.x >= 330)
		{
			cameraComp->SetCameraX = false;
		}

		if (player_pos.x >= 330 && player_pos.y >= -90)
			cameraComp->SetCameraY = true;

		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(L"Stage1_mBoss");
		}
	}
	void Stage1_1::SetMonOBJ()
	{	
		//monsterGroup1
		for (int i = 0; i < 7; i++)
		{
			Monster_warrior* _warrior = OBJPOOL->Get_Monster_warrior();
			_warrior->Initialize();
			Transform* ttr = _warrior->GetComponent<Transform>();
			ttr->SetPosition(Vector3(-400 + i * 50, -270, -249));
			AddMonster(_warrior);
			_warrior->SetState(GameObject::eState::Paused);
			monsterGroup1.push_back(_warrior);				
		}
		for (int i = 0; i < 3; i++)
		{
			Stone_wizard* _warrior = OBJPOOL->Get_wizard();
			_warrior->Initialize();
			Transform* ttr = _warrior->GetComponent<Transform>();
			ttr->SetPosition(Vector3(-200 + i * 100, -270, -249));
			AddMonster(_warrior);
			_warrior->SetState(GameObject::eState::Paused);
			monsterGroup1.push_back(_warrior);
		}
		

		//monsterGroup2
		for (int i = 0; i < 5; i++)
		{
			Monster* newMonster = OBJPOOL->Get_Monster_warrior();
			newMonster->Initialize();
			Transform* ttr = newMonster->GetComponent<Transform>();
			ttr->SetPosition(Vector3(-400 + i * 50, -270, -249));
			AddMonster(newMonster);
			newMonster->SetState(GameObject::eState::Paused);
			monsterGroup2.push_back(newMonster);
		}
		for (int i = 0; i < 3; i++)
		{
			Monster* newMonster = OBJPOOL->Get_wizard();
			newMonster->Initialize();
			Transform* ttr = newMonster->GetComponent<Transform>();
			ttr->SetPosition(Vector3(-200 + i * 150, -270, -249));
			AddMonster(newMonster);
			newMonster->SetState(GameObject::eState::Paused);
			monsterGroup2.push_back(newMonster);
		}
		for (int i = 0; i < 2; i++)
		{
			Monster* newMonster = OBJPOOL->Get_Hammer();
			newMonster->Initialize();
			Transform* ttr = newMonster->GetComponent<Transform>();
			ttr->SetPosition(Vector3(-200 + i * 150, -270, -249));
			AddMonster(newMonster);
			newMonster->SetState(GameObject::eState::Paused);
			monsterGroup2.push_back(newMonster);
		}
	

		//monsterGroup3
		for (int i = 0; i < 10; i++)
		{
			Monster* newMonster = OBJPOOL->Get_Monster_warrior();
			newMonster->Initialize();
			Transform* ttr = newMonster->GetComponent<Transform>();
			ttr->SetPosition(Vector3(-400 + i * 50, -280, -249));
			AddMonster(newMonster);
			newMonster->SetState(GameObject::eState::Paused);
			monsterGroup3.push_back(newMonster);
		}
		for (int i = 0; i < 3; i++)
		{
			Monster* newMonster = OBJPOOL->Get_Hammer();
			newMonster->Initialize();
			Transform* ttr = newMonster->GetComponent<Transform>();
			ttr->SetPosition(Vector3(-400 + i * 50, -280, -249));
			AddMonster(newMonster);
			newMonster->SetState(GameObject::eState::Paused);
			monsterGroup3.push_back(newMonster);
		}
		

		//monsterGroup4
		for (int i = 0; i < 2; i++)
		{
			Monster* newMonster = OBJPOOL->Get_Monster_warrior();
			newMonster->Initialize();
			Transform* ttr = newMonster->GetComponent<Transform>();
			ttr->SetPosition(Vector3(-230 + i * 50, 330, -249));
			AddMonster(newMonster);
			newMonster->SetState(GameObject::eState::Paused);
			monsterGroup4.push_back(newMonster);
		}
		for (int i = 0; i < 1; i++)
		{
			Monster* newMonster = OBJPOOL->Get_Hammer();
			newMonster->Initialize();
			Transform* ttr = newMonster->GetComponent<Transform>();
			ttr->SetPosition(Vector3(-230 + i * 50, 330, -249));
			AddMonster(newMonster);
			newMonster->SetState(GameObject::eState::Paused);
			monsterGroup4.push_back(newMonster);
		}
		for (int i = 0; i < 1; i++)
		{
			Monster* newMonster = OBJPOOL->Get_BigEnt();
			newMonster->Initialize();
			Transform* ttr = newMonster->GetComponent<Transform>();
			ttr->SetPosition(Vector3(-230 + i * 100, 330, -249));
			AddMonster(newMonster);
			newMonster->SetState(GameObject::eState::Paused);
			monsterGroup4.push_back(newMonster);
		}
		for (int i = 0; i < 3; i++)
		{
			Monster* newMonster = OBJPOOL->Get_Blossom();
			newMonster->Initialize();
			Transform* ttr = newMonster->GetComponent<Transform>();
			ttr->SetPosition(Vector3(-230 + i * 50, 330, -249));
			AddMonster(newMonster);
			newMonster->SetState(GameObject::eState::Paused);
			monsterGroup4.push_back(newMonster);
		}
		for (int i = 0; i < 3; i++)
		{
			Monster* newMonster = OBJPOOL->Get_GreenTree();
			newMonster->Initialize();
			Transform* ttr = newMonster->GetComponent<Transform>();
			ttr->SetPosition(Vector3(-230 + i * 50, 330, -249));
			AddMonster(newMonster);
			newMonster->SetState(GameObject::eState::Paused);
			monsterGroup4.push_back(newMonster);
		}
	}

	bool Stage1_1::AreAllMonstersDead(const std::vector<Monster*>& monsterGroup, bool check)
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