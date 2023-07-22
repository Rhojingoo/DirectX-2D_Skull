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
					Back_ground* Fore_S1_1 = object::Instantiate<Back_ground>(Vector3(0.f, 0.f, 101.f), eLayerType::Fore_Ground, L"Fore_GR1_MB");
					Fore_S1_1->GetComponent<Transform>()->SetScale(Vector3(1800.f, 800.f, 0.f));	Fore_S1_1->SetName(L"Fore_S1_mb");

					Back_ground* Mid_S1_1 = object::Instantiate<Back_ground>(Vector3(0.f, 150.f, 100.f), eLayerType::Mid_Ground, L"Mid_GR1_MB");
					Mid_S1_1->GetComponent<Transform>()->SetScale(Vector3(960 * 2.f, 800 * 1.5f, 0.f));	Mid_S1_1->SetName(L"Mid_S1_mb");

					Back_ground* Back_S1_mb = object::Instantiate<Back_ground>(Vector3(0.f, -150.f, -100.f), eLayerType::BACK_GROUND, L"Back_GR1_MB");
					Back_S1_mb->GetComponent<Transform>()->SetScale(Vector3(687.f, 281.f, 0.f));	Back_S1_mb->SetName(L"Back_S1_mb");
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