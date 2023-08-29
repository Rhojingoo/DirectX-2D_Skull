#include "jkStage1_2.h"

namespace jk
{
	Stage1_2::Stage1_2()
	{
	}
	Stage1_2::~Stage1_2()
	{
	}
	void Stage1_2::Initialize()
	{




	#pragma region BG	
			{
				Back_ground* Fore_S1_1_color = object::Instantiate<Back_ground>(Vector3(50.f, 50.f, 105.f), eLayerType::Fore_Ground, L"Stage1_Fore_GR_Color");
				Fore_S1_1_color->GetComponent<Transform>()->SetScale(Vector3(960.f*1.5, 800.f, 0.f));	Fore_S1_1_color->SetName(L"s1_1_fore_gr_color");

				Back_ground* Fore_S1_1_tree = object::Instantiate<Back_ground>(Vector3(50.f, -150.f, 103.f), eLayerType::Fore_Ground, L"Stage1_Fore_GR_Tree");
				Fore_S1_1_tree->GetComponent<Transform>()->SetScale(Vector3(960.f*1.5, 800.f, 0.f));	Fore_S1_1_tree->SetName(L"s1_1_fore_gr_tree");

				Back_ground* Mid_S1_1 = object::Instantiate<Back_ground>(Vector3(50.f, 0.f, 101.f), eLayerType::Fore_Ground, L"Stage1_Mid_GR1_1");
				Mid_S1_1->GetComponent<Transform>()->SetScale(Vector3(960.f*1.5, 800.f, 0.f));	Mid_S1_1->SetName(L"Mid_S1_1");


				Back_ground* Back_GR06 = object::Instantiate<Back_ground>(Vector3(50.f, 120.f, 99.f), eLayerType::Fore_Ground, L"Stage1_Back_GR14");
				Back_GR06->GetComponent<Transform>()->SetScale(Vector3(785.f, 190.f, 0.f));	Back_GR06->SetName(L"back_gr06");

				Back_ground* Back_GR07 = object::Instantiate<Back_ground>(Vector3(-420.f, -150.f, 99.f), eLayerType::Fore_Ground, L"Stage1_Back_GR02");
				Back_GR07->GetComponent<Transform>()->SetScale(Vector3(125.f, 172.f, 0.f));	Back_GR07->SetName(L"back_gr07");
		
				Back_ground* Back_GR08 = object::Instantiate<Back_ground>(Vector3(325.f, -150.f, 99.f), eLayerType::Fore_Ground, L"Stage1_Back_GR02");
				Back_GR08->GetComponent<Transform>()->SetScale(Vector3(145.f, 172.f, 0.f));	Back_GR08->SetName(L"back_gr08");

				Back_ground* Back_GR09 = object::Instantiate<Back_ground>(Vector3(470.f, -150.f, 99.f), eLayerType::Fore_Ground, L"Stage1_Back_GR02");
				Back_GR09->GetComponent<Transform>()->SetScale(Vector3(145.f, 172.f, 0.f));	Back_GR09->SetName(L"back_gr09");

			}
	#pragma endregion

	#pragma region tile_map & Ground_COL
			{
				Ground_Map* MinibossMap = object::Instantiate<Ground_Map>(Vector3(-560.f, -80.f, -205.f), eLayerType::BACK_GROUND);
				MinibossMap->GetComponent<Transform>()->SetScale(Vector3(155, 25, 0.f));	MinibossMap->SetName(L"Miniboss_ground00");

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
				static int Tile_Colum = 40;
				static int Tile_Row = 30;

				static Tile_Ground* Tile_map = object::Instantiate<Tile_Ground>(eLayerType::BACK_GROUND);
				Tile_map->SetName(L"tile_stage1_2");
				Transform* tr = Tile_map->GetComponent<Transform>();
				//tr->SetPositionZ(-200.f);
				tr->AddPositionY(0.f);
				tr->SetPositionX(0.f);
				tr->SetScale(Vector3(Tile_Colum * TileSize.x, Tile_Row * TileSize.y, 0.f));

				TileMap::TileMap_Setting(Tile_map, L"Stage1_2Tile", TileSize, Tile_Colum, Tile_Row, L"\\Resources\\Metadata\\TileMap\\Stage1_2.xml");
			}
	#pragma endregion	


	#pragma region Cam & Mouse& Grid
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
			cameraComp_ui->TurnLayerMask(eLayerType::Camera, false);
			cameraComp_ui->TurnLayerMask(eLayerType::Item, false);
			cameraComp_ui->TurnLayerMask(eLayerType::BACK_GROUND, false);
			cameraComp_ui->TurnLayerMask(eLayerType::Fore_Ground, false);
			cameraComp_ui->TurnLayerMask(eLayerType::Mid_Ground, false);
			cameraComp_ui->TurnLayerMask(eLayerType::Map_Effect, false);
			cameraComp_ui->TurnLayerMask(eLayerType::Camera, false);
			renderer::cameras.push_back(cameraComp_ui);

			//UI_Mouse
			//UI_Mouse* cursor = object::Instantiate<UI_Mouse>(Vector3(Vector3::One), eLayerType::Camera);
			//cursor->SetName(L"Catle_Cursor_UI");
			//cursor->GetComponent<Transform>()->SetScale(Vector3(42.f, 42.f, -250.f));
			//cursor->SetName(L"Mouse_UI"); cursor->SetCamera(UI_camera);

			//Grid
			//Grid* grid = object::Instantiate<Grid>(Vector3(Vector3::One), eLayerType::Grid);
			//grid->SetName(L"Catle_Grid");
			//GridScript* gridSc = grid->AddComponent<GridScript>();
			//gridSc->SetCamera(cameraComp);
#pragma endregion	

	}
	void Stage1_2::Update()
	{
		Scene::Update();

		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(L"Stage1_Boss"); 
		}
	}
	void Stage1_2::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void Stage1_2::Render()
	{
		Scene::Render();
	}
}
