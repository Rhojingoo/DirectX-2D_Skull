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
			Mid_GR_1_2* Mid_S1_2 = object::Instantiate<Mid_GR_1_2>(Vector3(0.f, 230.f, 70.f), eLayerType::Mid_Ground);
			Mid_S1_2->GetComponent<Transform>()->SetScale(Vector3(718.f*5, 280.f, 0.f));	Mid_S1_2->SetName(L"Mid_S1_2");	

			Fore_GR_1_2* Fore_S1_2 = object::Instantiate<Fore_GR_1_2>(Vector3(0.f, 0.f, 101.f), eLayerType::Fore_Ground);
			Fore_S1_2->GetComponent<Transform>()->SetScale(Vector3(1800.f, 800.f, 0.f));	Fore_S1_2->SetName(L"Fore_S1_2");

			GameObject* Tree = object::Instantiate<GameObject>(Vector3(0.0f, -50.0f, 50.f), eLayerType::Mid_Ground);
			Tree->SetName(L"tree");	MeshRenderer* mr = Tree->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh")); mr->SetMaterial(Resources::Find<Material>(L"Mid_GR1_22"));
			Tree->GetComponent<Transform>()->SetScale(Vector3(718*3.f, 380*3.f, 0.f));

			Back_GR_1_2* Back_S1_2 = object::Instantiate<Back_GR_1_2>(Vector3(0.f, 50.f, 30.f), eLayerType::BACK_GROUND);
			Back_S1_2->GetComponent<Transform>()->SetScale(Vector3(718 * 2.f, 380 * 2.f, 0.f));	Back_S1_2->SetName(L"Back_S1_2");

		}
#pragma endregion



#pragma region tile_map		
		{
			GameObject* Tile_map = object::Instantiate<GameObject>(eLayerType::BACK_GROUND);
			Tile_map->SetName(L"tile_stage1");
			Transform* tr = Tile_map->GetComponent<Transform>();
			//tr->SetPositionZ(-200.f);
			tr->AddPositionY(0.f);
			tr->SetPositionX(0.f);
			tr->SetScale(Vector3(40 * 32.f, 30 * 32.f, 0.f));

			TileMap* tilemap = Tile_map->AddComponent<TileMap>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"Stage1_2Tile");

			tilemap->SetMaterial(material);
			tilemap->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			tilemap->SetAtlasTex(material->GetTexture());
			tilemap->SetTileSize(Vector2(32.f, 32.f));
			tilemap->SetTileMapCount(40, 30);

			bool xmlTest = false;
			std::unique_ptr<XmlParser> testParser = std::make_unique<XmlParser>();
			xmlTest = testParser->LoadFile(L"\\Resources\\Metadata\\TileMap\\Stage1_2.xml");
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
