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

		//S1_King_BG* player = object::Instantiate<S1_King_BG>(Vector3(0.f, 0.f, -100.f), eLayerType::BACK_GROUND);				
		//player->GetComponent<Transform>()->SetScale(Vector3(900.f, 560.0f, 0.0f));			

	//Main Camera
		GameObject* camera = new GameObject();
		AddGameObject(eLayerType::Player, camera);
		camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		camera->AddComponent<CameraScript>();


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
			XmlParser* testParser = new XmlParser;
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
