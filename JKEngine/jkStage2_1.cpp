#include "jkStage2_1.h"

namespace jk
{
	Stage2_1::Stage2_1()
	{
	}

	Stage2_1::~Stage2_1()
	{
	}

	void Stage2_1::Initialize()
	{

		#pragma region CollisionManager
				CollisionManager::SetLayer(eLayerType::Player, eLayerType::BACK_GROUND, true);
				CollisionManager::SetLayer(eLayerType::Player, eLayerType::Item, true);
				CollisionManager::SetLayer(eLayerType::Monster, eLayerType::BACK_GROUND, true);
				CollisionManager::SetLayer(eLayerType::MiniBoss, eLayerType::BACK_GROUND, true);
				CollisionManager::SetLayer(eLayerType::Bullet, eLayerType::BACK_GROUND, true);
				CollisionManager::SetLayer(eLayerType::Boss, eLayerType::BACK_GROUND, true);
				CollisionManager::SetLayer(eLayerType::Item, eLayerType::BACK_GROUND, true);
				CollisionManager::SetLayer(eLayerType::Player, eLayerType::MiniBoss, true);
				CollisionManager::SetLayer(eLayerType::MiniBoss, eLayerType::Hitbox, true);
		#pragma endregion 



				//Player* _player = object::Instantiate<Player>(Vector3(0.f, -100.f, -250.f), eLayerType::Player);
				//_player->SetName(L"player_select");

				//Layana_Sisters* testboss = object::Instantiate<Layana_Sisters>(Vector3(0.f, 0.f, -250.f), eLayerType::Boss);
				//testboss->SetName(L"test_BOSS");



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

	void Stage2_1::Update()
	{
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
}