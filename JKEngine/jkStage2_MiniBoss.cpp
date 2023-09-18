#include "jkStage2_MiniBoss.h"

jk::Stage2_MiniBoss::Stage2_MiniBoss()
{
}

jk::Stage2_MiniBoss::~Stage2_MiniBoss()
{
}

void jk::Stage2_MiniBoss::Initialize()
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
					Ground_Map* MinibossMap = object::Instantiate<Ground_Map>(Vector3(40.f, -300.f, -205.f), eLayerType::BACK_GROUND);
					MinibossMap->GetComponent<Transform>()->SetScale(Vector3(3000, 170.f, 0.f));	MinibossMap->SetName(L"Stage2_ground00");

					Ground_Map* MinibossMap1 = object::Instantiate<Ground_Map>(Vector3(-720.f, -65.f, -205.f), eLayerType::BACK_GROUND);
					MinibossMap1->GetComponent<Transform>()->SetScale(Vector3(480, 15.f, 0.f));	MinibossMap1->SetName(L"Stage2_ground01");

					Ground_Map* MinibossMap2 = object::Instantiate<Ground_Map>(Vector3(720.f, -65.f, -205.f), eLayerType::BACK_GROUND);
					MinibossMap2->GetComponent<Transform>()->SetScale(Vector3(480, 15.f, 0.f));	MinibossMap2->SetName(L"Stage2_ground02");


					Ground_and_Wall* MinibossWall = object::Instantiate<Ground_and_Wall>(Vector3(-720.f, -145.f, -205.f), eLayerType::BACK_GROUND);
					MinibossWall->GetComponent<Transform>()->SetScale(Vector3(480, 150.f, 0.f));	MinibossWall->SetName(L"Stage2_Wall00");

					Ground_and_Wall* MinibossWall1 = object::Instantiate<Ground_and_Wall>(Vector3(720.f, -145, -205.f), eLayerType::BACK_GROUND);
					MinibossWall1->GetComponent<Transform>()->SetScale(Vector3(480, 150.f, 0.f));	MinibossWall1->SetName(L"Stage2_Wall01");




					static Vector2 TileSize = Vector2(32.f, 32.f);
					static int Tile_Colum = 60;
					static int Tile_Row = 25;

					static Tile_Ground* Tile_map = object::Instantiate<Tile_Ground>(eLayerType::BACK_GROUND);
					Tile_map->SetName(L"Stage2_MiniBoss");
					Transform* tr = Tile_map->GetComponent<Transform>();
					tr->SetPositionZ(-200.f);
					tr->AddPositionY(0.f);
					tr->SetScale(Vector3(Tile_Colum * TileSize.x, Tile_Row * TileSize.y, 0.f));
					TileMap::TileMap_Setting(Tile_map, L"Stage2_Tile", TileSize, Tile_Colum, Tile_Row, L"\\Resources\\Metadata\\TileMap\\Stage2_MiniBoss.xml");
				}
			#pragma endregion
		#pragma endregion 	
}

void jk::Stage2_MiniBoss::Update()
{
	if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
	{
		SceneManager::LoadScene(L"Stage2_2");
	}
	Scene::Update();
}

void jk::Stage2_MiniBoss::LateUpdate()
{
	Scene::LateUpdate();
}

void jk::Stage2_MiniBoss::Render()
{
	Scene::Render();
}

void jk::Stage2_MiniBoss::OnEnter()
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

void jk::Stage2_MiniBoss::OnExit()
{
}
