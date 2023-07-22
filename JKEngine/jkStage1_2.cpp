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
				Cloud* Mid_S1_2 = object::Instantiate<Cloud>(Vector3(0.f, 230.f, 70.f), eLayerType::Mid_Ground, L"Cloud_S1_2");
				Mid_S1_2->GetComponent<Transform>()->SetScale(Vector3(718.f*5, 280.f, 0.f));	Mid_S1_2->SetName(L"Mid_S1_2");	

				Back_ground* Fore_S1_2 = object::Instantiate<Back_ground>(Vector3(0.f, 0.f, 101.f), eLayerType::Fore_Ground, L"Fore_GR1_2");
				Fore_S1_2->GetComponent<Transform>()->SetScale(Vector3(1800.f, 800.f, 0.f));	Fore_S1_2->SetName(L"Fore_S1_2");	

				Back_ground* Tree = object::Instantiate<Back_ground>(Vector3(0.f, -50.f, 50.f), eLayerType::Mid_Ground, L"Mid_GR1_22");
				Tree->GetComponent<Transform>()->SetScale(Vector3(718 * 3.f, 380 * 3.f, 0.f));	Tree->SetName(L"tree");

				Back_ground* Back_S1_2 = object::Instantiate<Back_ground>(Vector3(0.f, 50.f, 30.f), eLayerType::BACK_GROUND, L"Back_GR1_1");
				Back_S1_2->GetComponent<Transform>()->SetScale(Vector3(718 * 2.f, 380 * 2.f, 0.f));	Back_S1_2->SetName(L"Back_S1_2");
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
