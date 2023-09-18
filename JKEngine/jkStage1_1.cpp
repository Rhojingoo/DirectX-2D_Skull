#include "jkStage1_1.h"
#include "jkParticleSystem.h"
#include "jkPaintShader.h"

namespace jk
{
	Stage1_1::Stage1_1()
	{
	}
	Stage1_1::~Stage1_1()
	{
	}
	void Stage1_1::Initialize()	{


		//PlayScene::Initialize();
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
		
		//ui
		{
			//UI
			//Player_State_UI* Player_State = object::Instantiate<Player_State_UI>(Vector3(-700.f, -300.f, 1.f), eLayerType::UI);
			//Player_State->GetComponent<Transform>()->SetScale(Vector3(168.f, 66.f, 0.f));
			//Player_State->SetName(L"playyer_state_inventory");

			//Player_Hp_Bar* Player_Hp = object::Instantiate<Player_Hp_Bar>(Vector3(0.085f, -0.25f, -2.f), eLayerType::UI);
			////Player_Hp->GetComponent<Transform>()->SetScale(Vector3(0.68f, 0.185f, 0.f));
			//Player_Hp->SetName(L"player_hp_bar");
			//Player_Hp->GetComponent<Transform>()->SetParent(Player_State->GetComponent<Transform>());
		}

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
						ParticleSystem* mr = Back_GR03->AddComponent<ParticleSystem>(Vector3(300.f, 350.f, 98.f)); mr->Initialize();

						Back_ground* Back_GR04 = object::Instantiate<Back_ground>(Vector3(-245.f, 350.f, 98.f), eLayerType::Fore_Ground, L"Stage1_Back_GR18");
						Back_GR04->GetComponent<Transform>()->SetScale(Vector3(341.f, 249.f, 0.f));	Back_GR04->SetName(L"back_gr04");
						ParticleSystem* mr2 = Back_GR04->AddComponent<ParticleSystem>(Vector3(-245.f, 350.f, 98.f)); mr2->Initialize();


						Back_ground* Back_GR05 = object::Instantiate<Back_ground>(Vector3(-605.f, -75.f, 98.f), eLayerType::Fore_Ground, L"Stage1_Back_GR18");
						Back_GR05->GetComponent<Transform>()->SetScale(Vector3(341.f, 249.f, 0.f));	Back_GR05->SetName(L"back_gr05");
						ParticleSystem* mr3 = Back_GR05->AddComponent<ParticleSystem>(Vector3(-605.f, -75.f, 98.f)); mr3->Initialize();
					}
					//Back_ground* Ground_Assistment = object::Instantiate<Back_ground>(Vector3(-100.f, 32.f, -199.f), eLayerType::Fore_Ground, L"Map1_1");
					//Ground_Assistment->GetComponent<Transform>()->SetScale(Vector3(1920.f, 1024.f, 0.f));	Ground_Assistment->SetName(L"Map1_1_assist");



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

		_player = object::Instantiate<Player>(Vector3(-700.f, -150.f, -250.f), eLayerType::Player);
		_player->SetName(L"player_select");

		//Monster* testmonster = object::Instantiate<Monster>(Vector3(0.f, 0.f, -250.f), eLayerType::Monster);
		//testmonster->SetName(L"test_monster"); 
	}

	void Stage1_1::Update()
	{
		Transform* PlayerTR = _player->GetComponent<Transform>();
		Vector3 player_pos = PlayerTR->GetPosition();
		

		if (player_pos.x < -450 )
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

		//if (player_pos.x >= 330 && player_pos.y < -90)
		//	cameraComp->SetCameraY = false;


		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(L"Stage1_mBoss");
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
	}
}