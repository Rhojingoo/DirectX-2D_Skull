#include "jkStage1_MiniBoss.h"

namespace jk
{
	Stage1_MiniBoss::Stage1_MiniBoss()
	{
	}
	Stage1_MiniBoss::~Stage1_MiniBoss()
	{
	}
	void Stage1_MiniBoss::Initialize()
	{
		//Main Camera
		GameObject* camera = new GameObject();
		AddGameObject(eLayerType::Player, camera);
		camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		camera->AddComponent<CameraScript>();

		#pragma region BG	
				{
					Back_ground* Fore_S1_1_color = object::Instantiate<Back_ground>(Vector3(0.f, 50.f, 105.f), eLayerType::Fore_Ground, L"Stage1_Fore_GR_Color");
					Fore_S1_1_color->GetComponent<Transform>()->SetScale(Vector3(960.f * 1.5, 800.f, 0.f));	Fore_S1_1_color->SetName(L"s1_1_fore_gr_color");

					Back_ground* Fore_S1_1_tree = object::Instantiate<Back_ground>(Vector3(0.f, -200.f, 103.f), eLayerType::Fore_Ground, L"Stage1_Fore_GR_Tree");
					Fore_S1_1_tree->GetComponent<Transform>()->SetScale(Vector3(960.f * 1.5, 800.f, 0.f));	Fore_S1_1_tree->SetName(L"s1_1_fore_gr_tree");

					Back_ground* Mid_S1_1 = object::Instantiate<Back_ground>(Vector3(0.f, 0.f, 101.f), eLayerType::Fore_Ground, L"Stage1_Mid_GR1_1");
					Mid_S1_1->GetComponent<Transform>()->SetScale(Vector3(960.f * 1.5, 800.f, 0.f));	Mid_S1_1->SetName(L"Mid_S1_1");

					Back_ground* Back_GR03 = object::Instantiate<Back_ground>(Vector3(50.f, -150.f, 99.f), eLayerType::Fore_Ground, L"Stage1_Back_GR12");
					Back_GR03->GetComponent<Transform>()->SetScale(Vector3(718.f, 380.f, 0.f));	Back_GR03->SetName(L"back_gr00");

					Back_ground* Back_GR04 = object::Instantiate<Back_ground>(Vector3(-450.f, -90.f, 99.f), eLayerType::Fore_Ground, L"Stage1_Back_GR02");
					Back_GR04->GetComponent<Transform>()->SetScale(Vector3(145.f, 172.f, 0.f));	Back_GR04->SetName(L"back_gr01");

					Back_ground* Back_GR05 = object::Instantiate<Back_ground>(Vector3(420.f, -80.f, 99.f), eLayerType::Fore_Ground, L"Stage1_Back_GR02");
					Back_GR05->GetComponent<Transform>()->SetScale(Vector3(145.f, 172.f, 0.f));	Back_GR05->SetName(L"back_gr02");
				}
		#pragma endregion


		#pragma region tile_map		
				{
					static Vector2 TileSize = Vector2(32.f, 32.f);
					static int Tile_Colum = 40;
					static int Tile_Row = 30;

					static GameObject* Tile_map = object::Instantiate<GameObject>(eLayerType::BACK_GROUND);
					Tile_map->SetName(L"tile_stage1_miniboss");
					Transform* tr = Tile_map->GetComponent<Transform>();
					//tr->SetPositionZ(-200.f);
					tr->AddPositionY(0.f);
					tr->SetPositionX(0.f);
					tr->SetScale(Vector3(Tile_Colum * TileSize.x, Tile_Row * TileSize.y, 0.f));

					TileMap::TileMap_Setting(Tile_map, L"Stage1_MiniBoss", TileSize, Tile_Colum, Tile_Row, L"\\Resources\\Metadata\\TileMap\\Stage1_MiniBoss.xml");
				}
		#pragma endregion	

	}
	void Stage1_MiniBoss::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(L"Stage1_2");
		}
		Scene::Update();
	}
	void Stage1_MiniBoss::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void Stage1_MiniBoss::Render()
	{
		Scene::Render();
	}
}