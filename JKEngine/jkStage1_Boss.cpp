#include "jkStage1_Boss.h"


namespace jk
{
	Stage1_Boss::Stage1_Boss()
	{
	}
	Stage1_Boss::~Stage1_Boss()
	{
	}
	void Stage1_Boss::Initialize()
	{		//Main Camera
		GameObject* camera = new GameObject();
		AddGameObject(eLayerType::Player, camera);
		camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		camera->AddComponent<CameraScript>();

		Back_ground* Kingbg = object::Instantiate<Back_ground>(Vector3(40.f, 120.f, -100.f), eLayerType::BACK_GROUND, L"Stage_king1");
		Kingbg->GetComponent<Transform>()->SetScale(Vector3(900.f*2, 560.0f*2, 0.0f));

		#pragma region tile_map		
		{
			static Vector2 TileSize = Vector2(32.f, 32.f);
			static int Tile_Colum = 60;
			static int Tile_Row = 30;

			static GameObject* Tile_map = object::Instantiate<GameObject>(eLayerType::BACK_GROUND);
			Tile_map->SetName(L"tile_stage1_boss");
			Transform* tr = Tile_map->GetComponent<Transform>();
			//tr->SetPositionZ(-200.f);
			tr->AddPositionY(0.f);
			tr->SetPositionX(0.f);
			tr->SetScale(Vector3(Tile_Colum * TileSize.x, Tile_Row * TileSize.y, 0.f));

			TileMap::TileMap_Setting(Tile_map, L"Stage1_MiniBoss", TileSize, Tile_Colum, Tile_Row, L"\\Resources\\Metadata\\TileMap\\Stage1_Boss.xml");
		}
	#pragma endregion	
	}
	void Stage1_Boss::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(L"Stage2_1");
		}
		Scene::Update();
	}
	void Stage1_Boss::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void Stage1_Boss::Render()
	{
		Scene::Render();
	}
}