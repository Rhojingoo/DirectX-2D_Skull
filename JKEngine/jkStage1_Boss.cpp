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

		S1_King_BG* Kingbg = object::Instantiate<S1_King_BG>(Vector3(40.f, 120.f, -100.f), eLayerType::BACK_GROUND);				
		Kingbg->GetComponent<Transform>()->SetScale(Vector3(900.f*2, 560.0f*2, 0.0f));

#pragma region tile_map		
		{
			GameObject* Tile_map = object::Instantiate<GameObject>(eLayerType::BACK_GROUND);
			Tile_map->SetName(L"tile_stage1");
			Transform* tr = Tile_map->GetComponent<Transform>();
			//tr->SetPositionZ(-200.f);
			tr->AddPositionY(0.f);
			tr->SetPositionX(0.f);
			tr->SetScale(Vector3(60 * 32.f, 30 * 32.f, 0.f));

			TileMap* tilemap = Tile_map->AddComponent<TileMap>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"Stage1_MiniBoss");

			tilemap->SetMaterial(material);
			tilemap->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			tilemap->SetAtlasTex(material->GetTexture());
			tilemap->SetTileSize(Vector2(32.f, 32.f));
			tilemap->SetTileMapCount(60, 30);

			bool xmlTest = false;
			XmlParser* testParser = new XmlParser;
			xmlTest = testParser->LoadFile(L"\\Resources\\Metadata\\TileMap\\Stage1_Boss.xml");
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