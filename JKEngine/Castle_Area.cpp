#include "Castle_Area.h"

namespace jk
{
	Castle_Area::Castle_Area()
	{
	}
	Castle_Area::~Castle_Area()
	{
	}
	void Castle_Area::Initialize()
	{

		//GameObject* Zelda
		//	= object::Instantiate<GameObject>(Vector3(0.0f, -50.0f, -700.f), eLayerType::Monster);
		//Zelda->SetName(L"Zelda");
		//Collider2D* cd = Zelda->AddComponent<Collider2D>();
		//MeshRenderer* mr = Zelda->AddComponent<MeshRenderer>();
		//mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));
		//const float pi = 3.141592f;
		//float degree = pi / 8.0f;
		//Zelda->GetComponent<Transform>()->SetPosition(Vector3(-200.0f, 0.0f, -250.f));
		//Zelda->GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0f, degree));
		//Zelda->GetComponent<Transform>()->SetScale(Vector3(140.f, 130.f, 0.f));

#pragma region UI	
		Player_State_UI* Player_State = object::Instantiate<Player_State_UI>(Vector3(-700.f, -300.f, 1.f), eLayerType::UI);
		Player_State->GetComponent<Transform>()->SetScale(Vector3(168.f, 66.f, 0.f));
		Player_State->SetName(L"playyer_state_inventory");

		Player_Hp_Bar* Player_Hp = object::Instantiate<Player_Hp_Bar>(Vector3(0.085f, -0.25f, -2.f), eLayerType::UI);
		Player_Hp->GetComponent<Transform>()->SetScale(Vector3(0.68f, 0.185f, 0.f));
		Player_Hp->SetName(L"player_hp_bar");
		Player_Hp->GetComponent<Transform>()->SetParent(Player_State->GetComponent<Transform>());

		Face_UI* Player_Face = object::Instantiate<Face_UI>(Vector3(-0.33f, 0.23f, -2.1f), eLayerType::UI);
		Player_Face->GetComponent<Transform>()->SetScale(Vector3(0.324f, 0.824f, 0.f));
		Player_Face->SetName(L"player_head");
		Player_Face->GetComponent<Transform>()->SetParent(Player_State->GetComponent<Transform>());

#pragma endregion	

#pragma region Player	
		Skul_Basic* Basic_Skul = object::Instantiate<Skul_Basic>(Vector3(0.f, -100.f, -250.f), eLayerType::Player);
		Basic_Skul->GetComponent<Transform>()->SetScale(Vector3(40.f, 30.f, 0.f));	Basic_Skul->SetName(L"Basic_Skul");
		Collider2D* cd = Basic_Skul->AddComponent<Collider2D>();
		Basic_Skul->AddComponent<PlayerScript>();
		Basic_Skul->AddComponent<CameraScript>();
#pragma endregion

#pragma region Npc	

#pragma endregion

#pragma region CASTLE

		in_Castle_Fore_ground* in_Catle_Back = object::Instantiate<in_Castle_Fore_ground>(Vector3(0.f, 0.f, 100.f), eLayerType::Fore_Ground);
		in_Catle_Back->GetComponent<Transform>()->SetScale(Vector3(1280.f, 720.f, 0.f));	in_Catle_Back->SetName(L"in_Catle_Back");

		out_Castle_Fore_ground* out_Catle_Back = object::Instantiate<out_Castle_Fore_ground>(Vector3(1200.f, 0.f, 101.f), eLayerType::Fore_Ground);
		out_Catle_Back->GetComponent<Transform>()->SetScale(Vector3(1200.f, 2204.f, 0.f));	out_Catle_Back->SetName(L"out_Catle_Back");

		Devil_Castle* Castle_wall_Back = object::Instantiate<Devil_Castle>(Vector3(0.f, 0.f, -100.f), eLayerType::BACK_GROUND);
		Castle_wall_Back->GetComponent<Transform>()->SetScale(Vector3(950, 350.f, 0.f)); Castle_wall_Back->SetName(L"Catle_Back");

		Devil_Castle_mid* Castle_wall = object::Instantiate<Devil_Castle_mid>(Vector3(0.0f, -880.f, -150.f), eLayerType::BACK_GROUND);
		Castle_wall->GetComponent<Transform>()->SetScale(Vector3(1966.f, 2306.f, 0.f));	Castle_wall->SetName(L"Catle_front");

		Decil_chair* _chair = object::Instantiate<Decil_chair>(Vector3(-695.f, 0.1f, -200.f), eLayerType::BACK_GROUND);
		_chair->GetComponent<Transform>()->SetScale(Vector3(447.f, 322.f, 0.f)); _chair->SetName(L"Devil_chair");

		Cloud* cloud = object::Instantiate<Cloud>(Vector3(500.f, -750.f, 90.f), eLayerType::Map_Effect);
		cloud->GetComponent<Transform>()->SetScale(Vector3(1120.f * 5, 2204.f, 0.f)); cloud->SetName(L"Castle_cloud");

#pragma endregion				

#pragma region Cam & Mouse& Grid
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
		cameraComp_ui->TurnLayerMask(eLayerType::BACK_GROUND, false);
		cameraComp_ui->TurnLayerMask(eLayerType::Fore_Ground, false);
		cameraComp_ui->TurnLayerMask(eLayerType::Mid_Ground, false);
		cameraComp_ui->TurnLayerMask(eLayerType::Map_Effect, false);
		cameraComp_ui->TurnLayerMask(eLayerType::Camera, false);
		//renderer::cameras.push_back(cameraComp_ui);

		//UI_Mouse
		UI_Mouse* cursor = object::Instantiate<UI_Mouse>(Vector3(Vector3::One), eLayerType::Camera);
		cursor->SetName(L"Catle_Cursor_UI");
		cursor->GetComponent<Transform>()->SetScale(Vector3(42.f, 42.f, -250.f));
		cursor->SetName(L"Mouse_UI"); cursor->SetCamera(UI_camera);

		//Grid
		Grid* grid = object::Instantiate<Grid>(Vector3(Vector3::One), eLayerType::Grid);
		grid->SetName(L"Catle_Grid");
		GridScript* gridSc = grid->AddComponent<GridScript>();
		gridSc->SetCamera(cameraComp);
#pragma endregion	

#pragma region tile_map		
		{
			GameObject* Tile_map = object::Instantiate<GameObject>(eLayerType::BACK_GROUND);
			Tile_map->SetName(L"Tile_Map");
			Transform* tr = Tile_map->GetComponent<Transform>();
			tr->SetPositionZ(-200.f);
			tr->AddPositionY(-280.f);
			tr->SetPositionX(-300.f);
			tr->SetScale(Vector3(60*32.f, 8*32.f, 0.f));

			TileMap* tilemap = Tile_map->AddComponent<TileMap>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"Devil_castle_tile");

			tilemap->SetMaterial(material);
			tilemap->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			tilemap->SetAtlasTex(material->GetTexture());
			tilemap->SetTileSize(Vector2(32.f, 32.f));
			tilemap->SetTileMapCount(60, 8);

			bool xmlTest = false;
			XmlParser* testParser = new XmlParser;
			xmlTest = testParser->LoadFile(L"\\Resources\\Metadata\\TileMap\\Devil_castle_Tile.xml");
			if (xmlTest)
			{
				xmlTest = testParser->FindElem(L"map");
				testParser->IntoElem();
				xmlTest = testParser->FindElem(L"layer");
				testParser->IntoElem();
				xmlTest = testParser->FindElem(L"data");
				testParser->IntoElem();

				int tileIdx = 0;
				while (testParser->FindElem("tile"))
				{
					if (testParser->HasAttribute("gid"))
					{
						int imgIdx = testParser->GetIntAttribute("gid") - 1;
						tilemap->SetTileData(tileIdx, imgIdx);
					}
					tileIdx++;
				}
			}
		}

#pragma endregion

#pragma region º¸·ù
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

	}

	void Castle_Area::Update()
	{
		Scene::Update();
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(L"Stage1_1");
		}
	}

	void Castle_Area::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void Castle_Area::Render()
	{
		Scene::Render();
	}
}