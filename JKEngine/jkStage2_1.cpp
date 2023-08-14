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

		//#pragma region CollisionManager
		//		CollisionManager::SetLayer(eLayerType::Player, eLayerType::BACK_GROUND, true);
		//		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Item, true);
		//		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::BACK_GROUND, true);
		//		CollisionManager::SetLayer(eLayerType::MiniBoss, eLayerType::BACK_GROUND, true);
		//		CollisionManager::SetLayer(eLayerType::Bullet, eLayerType::BACK_GROUND, true);
		//		CollisionManager::SetLayer(eLayerType::Boss, eLayerType::BACK_GROUND, true);
		//		CollisionManager::SetLayer(eLayerType::Item, eLayerType::BACK_GROUND, true);
		//		CollisionManager::SetLayer(eLayerType::Player, eLayerType::MiniBoss, true);
		//		CollisionManager::SetLayer(eLayerType::MiniBoss, eLayerType::Hitbox, true);
		//#pragma endregion 


		//Player* _player = object::Instantiate<Player>(Vector3(0.f, -100.f, -250.f), eLayerType::Player);
		//_player->SetName(L"player_select");

		Layana_Sisters* testboss = object::Instantiate<Layana_Sisters>(Vector3(0.f, 0.f, -250.f), eLayerType::Boss);
		testboss->SetName(L"test_BOSS");



		#pragma region BackGround

					{
						Back_ground* Back_Ground = object::Instantiate<Back_ground>(Vector3(0.f, 0.f, 10.f), eLayerType::BACK_GROUND, L"Layana_Sisters_Map");
						Back_Ground->GetComponent<Transform>()->SetScale(Vector3(900.f, 400.0f, 0.0f)); 
					}
					{	
						Back_ground* Back_Ground = object::Instantiate<Back_ground>(Vector3(0.f, 0.f, -101.f), eLayerType::BACK_GROUND, L"Layana_Sisters_Stairs");
						Back_Ground->GetComponent<Transform>()->SetScale(Vector3(825, 279.0f, 0.0f));
						Collider2D* cd = Back_Ground->AddComponent<Collider2D>();
						cd->SetSize(Vector2(0.28f, 0.08f));
						cd->SetCenter(Vector2(0.f, -10.5f));
					}
					{	
						Back_ground* Back_Ground = object::Instantiate<Back_ground>(Vector3(0.f, -100.f, -102.f), eLayerType::BACK_GROUND, L"Layana_Sisters_Steps");
						Back_Ground->GetComponent<Transform>()->SetScale(Vector3(187.f, 66.0f, 0.0f));
					}

			#pragma region Tile		
					{
						static Vector2 TileSize = Vector2(32.f, 32.f);
						static int Tile_Colum = 50;
						static int Tile_Row = 2;

						static Tile_Ground* Tile_map = object::Instantiate<Tile_Ground>(eLayerType::BACK_GROUND);
						Tile_map->SetName(L"Layana_Stage");
						Transform* tr = Tile_map->GetComponent<Transform>();
						Collider2D* cd = Tile_map->AddComponent<Collider2D>();
						tr->SetPositionZ(-200.f);
						tr->AddPositionY(-185.f);
						tr->SetScale(Vector3(Tile_Colum * TileSize.x, Tile_Row * TileSize.y, 0.f));
						TileMap::TileMap_Setting(Tile_map, L"Stage2_Boss", TileSize, Tile_Colum, Tile_Row, L"\\Resources\\Metadata\\TileMap\\Layana_Sisters_BossMaP.xml");
					}
			#pragma endregion
		#pragma endregion 

		//Main Camera
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			camera->AddComponent<CameraScript>();


			Grid* grid = object::Instantiate<Grid>(Vector3(Vector3::One), eLayerType::Grid);
			grid->SetName(L"Catle_Grid");
			GridScript* gridSc = grid->AddComponent<GridScript>();
			gridSc->SetCamera(cameraComp);
	}

	void Stage2_1::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(L"TitleScene");
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