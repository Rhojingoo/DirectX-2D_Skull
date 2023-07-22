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
	//Main Camera
		GameObject* camera = new GameObject();
		AddGameObject(eLayerType::Player, camera);
		camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		camera->AddComponent<CameraScript>();

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

	#pragma region tile_map		
			{
				static Vector2 TileSize = Vector2(32.f, 32.f);
				static int Tile_Colum = 40;
				static int Tile_Row = 30;

				static GameObject* Tile_map = object::Instantiate<GameObject>(eLayerType::BACK_GROUND);
				Tile_map->SetName(L"tile_stage1_2");
				Transform* tr = Tile_map->GetComponent<Transform>();
				//tr->SetPositionZ(-200.f);
				tr->AddPositionY(0.f);
				tr->SetPositionX(0.f);
				tr->SetScale(Vector3(Tile_Colum * TileSize.x, Tile_Row * TileSize.y, 0.f));

				TileMap::TileMap_Setting(Tile_map, L"Stage1_2Tile", TileSize, Tile_Colum, Tile_Row, L"\\Resources\\Metadata\\TileMap\\Stage1_2.xml");
			}
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
