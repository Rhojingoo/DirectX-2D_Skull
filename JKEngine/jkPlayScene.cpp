#include "jkPlayScene.h"
//#include "Monster_ObjPool.h"

namespace jk
{
	//Player* PlayScene::_player = nullptr;
	PlayScene::PlayScene()
	{
	}
	PlayScene::~PlayScene()
	{
	}

	void PlayScene::Initialize()
	{
		//Monster_ObjPool* Obj = new Monster_ObjPool(105,15,10);

		Scene::Initialize();
	}

	void PlayScene::Update()
	{
		Scene::Update();
	}

	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void PlayScene::Render()
	{
		Scene::Render();
	}
}



#pragma region before playscene
//Devil_Castle* Castle_wall_Back = object::Instantiate<Devil_Castle>(Vector3(0.f, 0.f, -100.f), eLayerType::BACK_GROUND);
//Castle_wall_Back->GetComponent<Transform>()->SetScale(Vector3(950, 350.f, 0.f));
//Castle_wall_Back->SetName(L"Catle_Back");
//
//Devil_Castle_front* Castle_wall = object::Instantiate<Devil_Castle_front>(Vector3(0.0f, 0.35f, -150.f), eLayerType::BACK_GROUND);
//Castle_wall->GetComponent<Transform>()->SetScale(Vector3(1890.f, 548.f, 0.f));
//Castle_wall->SetName(L"Catle_front");
//
//Decil_chair* _chair = object::Instantiate<Decil_chair>(Vector3(-695.f, 0.1f, -200.f), eLayerType::BACK_GROUND);
//_chair->GetComponent<Transform>()->SetScale(Vector3(447.f, 322.f, 0.f));
//_chair->SetName(L"Devil_chair");
//
//Cloud* cloud = object::Instantiate<Cloud>(Vector3(500.f, -750.f, 190.f), eLayerType::Map_Effect);
//cloud->GetComponent<Transform>()->SetScale(Vector3(1120.f * 5, 2204.f, 0.f));
//cloud->SetName(L"Castle_cloud");
//#pragma endregion					
//
//#pragma region UI	
//Player_State_UI* Player_UI = object::Instantiate<Player_State_UI>(Vector3(-750.5f, -350.4f, 1.0f), eLayerType::UI);
//Player_UI->GetComponent<Transform>()->SetScale(Vector3(68.f, 68.f, 0.f));
//Player_UI->SetName(L"Devil_chair");
//#pragma endregion		
//
//#pragma region Cam & Mouse& Grid
////Main Camera			
//Main_Camera* camera = object::Instantiate<Main_Camera>(Vector3(0.f, 0.f, -10.f), eLayerType::Camera);
//Camera* cameraComp = camera->AddComponent<Camera>();
//cameraComp->TurnLayerMask(eLayerType::UI, false);
//camera->AddComponent<CameraScript>();
//renderer::cameras.push_back(cameraComp);
//
////UI Camera		
//UI_Camera* UI_camera = object::Instantiate<UI_Camera>(Vector3(0.f, 0.f, -10.f), eLayerType::Camera);
//Camera* cameraComp_ui = UI_camera->AddComponent<Camera>();
//cameraComp_ui->TurnLayerMask(eLayerType::Player, false);
//cameraComp_ui->TurnLayerMask(eLayerType::BACK_GROUND, false);
//cameraComp_ui->TurnLayerMask(eLayerType::Fore_Ground, false);
//cameraComp_ui->TurnLayerMask(eLayerType::Mid_Ground, false);
//cameraComp_ui->TurnLayerMask(eLayerType::Map_Effect, false);
//cameraComp_ui->TurnLayerMask(eLayerType::Camera, false);
//
////UI_Mouse
//UI_Mouse* cursor = object::Instantiate<UI_Mouse>(Vector3(Vector3::One), eLayerType::Camera);
//cursor->GetComponent<Transform>()->SetScale(Vector3(42.f, 42.f, -10.f));
//cursor->SetName(L"Mouse_UI");
//cursor->SetCamera(UI_camera);
//
////Grid
//Grid* grid = object::Instantiate<Grid>(Vector3(Vector3::One), eLayerType::Grid);
//grid->SetName(L"Grid");
//GridScript* gridSc = grid->AddComponent<GridScript>();
//gridSc->SetCamera(cameraComp);
//#pragma endregion	
//
//#pragma region tile_map		
//{
//	GameObject* Tile_map = object::Instantiate<GameObject>(eLayerType::BACK_GROUND);
//	Tile_map->SetName(L"Tile_Map");
//	Transform* tr = Tile_map->GetComponent<Transform>();
//	tr->SetPositionZ(5.f);
//	tr->AddPositionY(64.f);
//	tr->SetScale(Vector3(500.f, 500.f, 10.f));
//
//	TileMap* tilemap = Tile_map->AddComponent<TileMap>();
//	std::shared_ptr<Material> material = Resources::Find<Material>(L"DG_Tile");
//
//	tilemap->SetMaterial(material);
//	tilemap->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
//	tilemap->SetAtlasTex(material->GetTexture());
//	tilemap->SetTileSize(Vector2(64.f, 64.f));
//	tilemap->SetTileMapCount(114, 24);
//
//	bool xmlTest = false;
//	XmlParser* testParser = new XmlParser;
//	xmlTest = testParser->LoadFile(L"\\Resources\\Metadata\\TileMap\\00_Town.xml");
//	if (xmlTest)
//	{
//		xmlTest = testParser->FindElem(L"map");
//		testParser->IntoElem();
//		xmlTest = testParser->FindElem(L"layer");
//		testParser->IntoElem();
//		xmlTest = testParser->FindElem(L"data");
//		testParser->IntoElem();
//
//		int tileIdx = 0;
//		while (testParser->FindElem("tile"))
//		{
//			if (testParser->HasAttribute("gid"))
//			{
//				int imgIdx = testParser->GetIntAttribute("gid") - 1;
//				tilemap->SetTileData(tileIdx, imgIdx);
//			}
//			tileIdx++;
//		}
//	}
//}
//
//#pragma endregion
//
//#pragma region º¸·ù
//{
//	GameObject* player = new GameObject();
//	AddGameObject(eLayerType::Player, player);
//	MeshRenderer* mr = player->AddComponent<MeshRenderer>();
//	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
//	mr->SetMaterial(Resources::Find<Material>(L"Catle_wall_Front_04"));
//	player->GetComponent<Transform>()->SetScale(Vector3(0.7f, 2.5f, 0.f));
//	player->GetComponent<Transform>()->SetPosition(Vector3(-4.77f, 0.35f, 0.0f));
//	//player->AddComponent<CameraScript>();
//}
//{
//	GameObject* player = new GameObject();
//	AddGameObject(eLayerType::Player, player);
//	MeshRenderer* mr = player->AddComponent<MeshRenderer>();
//	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
//	mr->SetMaterial(Resources::Find<Material>(L"Catle_wall_Front_03"));
//	//player->GetComponent<Transform>()->SetScale(Vector3(10.25f, 5.0f, 0.0f));
//	player->GetComponent<Transform>()->SetPosition(Vector3(2.0f, 0.0f, 0.0f));
//	//player->AddComponent<CameraScript>();
//}
//{
//	GameObject* player = new GameObject();
//	AddGameObject(eLayerType::Player, player);
//	MeshRenderer* mr = player->AddComponent<MeshRenderer>();
//	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
//	mr->SetMaterial(Resources::Find<Material>(L"Catle_wall_Front_04"));
//	//player->GetComponent<Transform>()->SetScale(Vector3(10.25f, 5.0f, 0.0f));
//	player->GetComponent<Transform>()->SetPosition(Vector3(2.0f, 0.0f, 0.0f));
//	//player->AddComponent<CameraScript>();
//}
#pragma endregion