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
			Back_ground* Fore_S1_1_color = object::Instantiate<Back_ground>(Vector3(-100.f, 50.f, 105.f), eLayerType::Fore_Ground, L"Stage1_Fore_GR_Color");
			Fore_S1_1_color->GetComponent<Transform>()->SetScale(Vector3(960.f, 800.f, 0.f));	Fore_S1_1_color->SetName(L"s1_1_fore_gr_color");

			Back_ground* Fore_S1_1_tree = object::Instantiate<Back_ground>(Vector3(-100.f, -150.f, 103.f), eLayerType::Fore_Ground, L"Stage1_Fore_GR_Tree");
			Fore_S1_1_tree->GetComponent<Transform>()->SetScale(Vector3(960.f, 800.f, 0.f));	Fore_S1_1_tree->SetName(L"s1_1_fore_gr_tree");

			Back_ground* Mid_S1_1 = object::Instantiate<Back_ground>(Vector3(-100.f, 0.f, 101.f), eLayerType::Fore_Ground, L"Stage1_Mid_GR1_1");
			Mid_S1_1->GetComponent<Transform>()->SetScale(Vector3(960.f, 800.f, 0.f));	Mid_S1_1->SetName(L"Mid_S1_1");

			Back_ground* Back_GR00 = object::Instantiate<Back_ground>(Vector3(50.f, -235.f, 99.f), eLayerType::Fore_Ground, L"Stage1_Back_GR00");
			Back_GR00->GetComponent<Transform>()->SetScale(Vector3(785.f, 190.f, 0.f));	Back_GR00->SetName(L"back_gr00");

			Back_ground* Back_GR01 = object::Instantiate<Back_ground>(Vector3(-100.f, 300.f, 99.f), eLayerType::Fore_Ground, L"Stage1_Back_GR02");
			Back_GR01->GetComponent<Transform>()->SetScale(Vector3(145.f, 172.f, 0.f));	Back_GR01->SetName(L"back_gr01");

			Back_ground* Back_GR02 = object::Instantiate<Back_ground>(Vector3(45.f, 300.f, 99.f), eLayerType::Fore_Ground, L"Stage1_Back_GR02");
			Back_GR02->GetComponent<Transform>()->SetScale(Vector3(145.f, 172.f, 0.f));	Back_GR02->SetName(L"back_gr02");
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