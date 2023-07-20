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
			Fore_GR_1_1* Fore_S1_1 = object::Instantiate<Fore_GR_1_1>(Vector3(0.f, 0.f, 101.f), eLayerType::Fore_Ground);
			Fore_S1_1->GetComponent<Transform>()->SetScale(Vector3(1800.f, 800.f, 0.f));	Fore_S1_1->SetName(L"Fore_S1_1");

			Mid_GR_1_1* Mid_S1_1 = object::Instantiate<Mid_GR_1_1>(Vector3(0.f, 150.f, 100.f), eLayerType::Mid_Ground);
			Mid_S1_1->GetComponent<Transform>()->SetScale(Vector3(951*5.f, 345*1.5f, 0.f));	Mid_S1_1->SetName(L"Mid_S1_1");

			Back_GR_1_1* Back_S1_1 = object::Instantiate<Back_GR_1_1>(Vector3(0.f, -230.f, -100.f), eLayerType::BACK_GROUND);
			Back_S1_1->GetComponent<Transform>()->SetScale(Vector3(780.f, 189.f, 0.f));	Back_S1_1->SetName(L"Back_S1_1");
		}
		#pragma endregion



		#pragma region tile_map		
		{
			GameObject* Tile_map = object::Instantiate<GameObject>(eLayerType::BACK_GROUND);
			Tile_map->SetName(L"tile_stage1");
			Transform* tr = Tile_map->GetComponent<Transform>();
			//tr->SetPositionZ(-200.f);
			tr->AddPositionY(0.f);
			tr->SetPositionX(-100.f);
			tr->SetScale(Vector3(30 * 32.f, 30 * 32.f, 0.f));

			TileMap* tilemap = Tile_map->AddComponent<TileMap>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"Stage1_1Tile");

			tilemap->SetMaterial(material);
			tilemap->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			tilemap->SetAtlasTex(material->GetTexture());
			tilemap->SetTileSize(Vector2(32.f, 32.f));
			tilemap->SetTileMapCount(30, 30);

			bool xmlTest = false;
			XmlParser* testParser = new XmlParser;
			xmlTest = testParser->LoadFile(L"\\Resources\\Metadata\\TileMap\\Stage1_1.xml");
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