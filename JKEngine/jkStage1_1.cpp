#include "jkStage1_1.h"


namespace jk
{
	Stage1_1::Stage1_1()
	{
	}
	Stage1_1::~Stage1_1()
	{
	}
	void Stage1_1::Initialize()
	{
			
		//Main Camera
		GameObject* camera = new GameObject();
		AddGameObject(eLayerType::Player, camera);
		camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		camera->AddComponent<CameraScript>();

		#pragma region BG	
		{	
			Back_ground* Fore_S1_1 = object::Instantiate<Back_ground>(Vector3(0.f, 0.f, 101.f), eLayerType::Fore_Ground, L"Fore_GR1_1");
			Fore_S1_1->GetComponent<Transform>()->SetScale(Vector3(1800.f, 800.f, 0.f));	Fore_S1_1->SetName(L"Fore_S1_1");

			Cloud* Mid_S1_1 = object::Instantiate<Cloud>(Vector3(0.f, 150.f, 100.f), eLayerType::Mid_Ground, L"Mid_GR1_1");
			Mid_S1_1->GetComponent<Transform>()->SetScale(Vector3(951*5.f, 345*1.5f, 0.f));	Mid_S1_1->SetName(L"Mid_S1_1");

			Back_ground* Back_S1_1 = object::Instantiate<Back_ground>(Vector3(0.f, -230.f, -100.f), eLayerType::BACK_GROUND, L"Back_GR1_1");
			Back_S1_1->GetComponent<Transform>()->SetScale(Vector3(780.f, 189.f, 0.f));	Back_S1_1->SetName(L"Back_S1_1");
		}
		#pragma endregion

		#pragma region tile_map		
		{
			static Vector2 TileSize = Vector2(32.f, 32.f);
			static int Tile_Colum = 30;
			static int Tile_Row = 30;

			static GameObject* Tile_map = object::Instantiate<GameObject>(eLayerType::BACK_GROUND);
			Tile_map->SetName(L"tile_stage1");
			Transform* tr = Tile_map->GetComponent<Transform>();
			//tr->SetPositionZ(-200.f);
			tr->AddPositionY(0.f);
			tr->SetPositionX(-100.f);
			tr->SetScale(Vector3(Tile_Colum * TileSize.x, Tile_Row * TileSize.y, 0.f));

			TileMap::TileMap_Setting(Tile_map, L"Stage1_1Tile", TileSize, Tile_Colum, Tile_Row, L"\\Resources\\Metadata\\TileMap\\Stage1_1.xml");
		}
		#pragma endregion	
	}

	void Stage1_1::Update()
	{
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
}