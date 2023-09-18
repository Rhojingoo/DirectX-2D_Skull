#include "jkStage2_2.h"


namespace jk
{
	Stage2_2::Stage2_2()
	{
	}
	Stage2_2::~Stage2_2()
	{
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

							Ground_and_Wall* MinibossWall2 = object::Instantiate<Ground_and_Wall>(Vector3(390.f, -110.f, -205.f), eLayerType::BACK_GROUND);
							MinibossWall2->GetComponent<Transform>()->SetScale(Vector3(250, 300.f, 0.f));	MinibossWall2->SetName(L"Stage2_Wall02");


							Sky_Ground* SkyGround = object::Instantiate<Sky_Ground>(Vector3(0.f, 32, -205.f), eLayerType::BACK_GROUND);
							SkyGround->GetComponent<Transform>()->SetScale(Vector3(520, 15.f, 0.f));	SkyGround->SetName(L"SkyGround01");



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





				//Player* _player = object::Instantiate<Player>(Vector3(0.f, -100.f, -250.f), eLayerType::Player);
				//_player->SetName(L"player_select");

				//Layana_Sisters* testboss = object::Instantiate<Layana_Sisters>(Vector3(0.f, 0.f, -250.f), eLayerType::Boss);
				//testboss->SetName(L"test_BOSS");

				

#pragma region BackGround

				//{
				//	Back_ground* Back_Ground = object::Instantiate<Back_ground>(Vector3(0.f, 0.f, 10.f), eLayerType::BACK_GROUND, L"Layana_Sisters_Map");
				//	Back_Ground->GetComponent<Transform>()->SetScale(Vector3(900.f, 400.0f, 0.0f));
				//}
				//{
				//	Back_ground* Back_Ground = object::Instantiate<Back_ground>(Vector3(0.f, 0.f, -101.f), eLayerType::BACK_GROUND, L"Layana_Sisters_Stairs");
				//	Back_Ground->GetComponent<Transform>()->SetScale(Vector3(825, 279.0f, 0.0f));
				//	Collider2D* cd = Back_Ground->AddComponent<Collider2D>();
				//	cd->SetSize(Vector2(0.28f, 0.08f));
				//	cd->SetCenter(Vector2(0.f, -10.5f));
				//}
				//{
				//	Back_ground* Back_Ground = object::Instantiate<Back_ground>(Vector3(0.f, -100.f, -102.f), eLayerType::BACK_GROUND, L"Layana_Sisters_Steps");
				//	Back_Ground->GetComponent<Transform>()->SetScale(Vector3(187.f, 66.0f, 0.0f));
				//}

#pragma region Tile		
				{
					//static Vector2 TileSize = Vector2(32.f, 32.f);
					//static int Tile_Colum = 50;
					//static int Tile_Row = 2;

					//static Tile_Ground* Tile_map = object::Instantiate<Tile_Ground>(eLayerType::BACK_GROUND);
					//Tile_map->SetName(L"Layana_Stage");
					//Transform* tr = Tile_map->GetComponent<Transform>();
					//Collider2D* cd = Tile_map->AddComponent<Collider2D>();
					//tr->SetPositionZ(-200.f);
					//tr->AddPositionY(-185.f);
					//tr->SetScale(Vector3(Tile_Colum * TileSize.x, Tile_Row * TileSize.y, 0.f));
					//TileMap::TileMap_Setting(Tile_map, L"Stage2_Boss", TileSize, Tile_Colum, Tile_Row, L"\\Resources\\Metadata\\TileMap\\Layana_Sisters_BossMaP.xml");
				}
#pragma endregion
#pragma endregion 



	}
	void Stage2_2::Update()
	{
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
#pragma region Camera & Grid

		//Main Camera
		Main_Camera* camera = object::Instantiate<Main_Camera>(Vector3(0.f, 0.f, -10.f), eLayerType::Camera);
		Camera* cameraComp = camera->AddComponent<Camera>();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		camera->AddComponent<CameraScript>();
		renderer::cameras.push_back(cameraComp);
		renderer::mainCamera = cameraComp;

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
	}
}