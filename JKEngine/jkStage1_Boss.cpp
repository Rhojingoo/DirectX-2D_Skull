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
	{	
		#pragma region CollisionManager
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::BACK_GROUND, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Item, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Player, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::BACK_GROUND, true);
		CollisionManager::SetLayer(eLayerType::MiniBoss, eLayerType::BACK_GROUND, true);
		CollisionManager::SetLayer(eLayerType::Bullet, eLayerType::BACK_GROUND, true);
		CollisionManager::SetLayer(eLayerType::Boss, eLayerType::BACK_GROUND, true);
		CollisionManager::SetLayer(eLayerType::Item, eLayerType::BACK_GROUND, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Boss, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::MiniBoss, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Hitbox, true);
		CollisionManager::SetLayer(eLayerType::Boss, eLayerType::Hitbox, true);
		CollisionManager::SetLayer(eLayerType::MiniBoss, eLayerType::Hitbox, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Hitbox, true);

#pragma endregion 

		_player = object::Instantiate<Player>(Vector3(0.f, -100.f, -250.f), eLayerType::Player);
		_player->SetName(L"player_select");

		_Stage1_Boss = object::Instantiate<Yggdrasil>(Vector3(0.f, -500.f, -250.f), eLayerType::Boss);
		_Stage1_Boss->SetName(L"Stage1_BOSS");
		_Stage1_Boss->SetState(GameObject::eState::Paused);


		#pragma region BG	
		{
			Back_ground* Kingbg = object::Instantiate<Back_ground>(Vector3(40.f, 50.f, 10.f), eLayerType::BACK_GROUND, L"Stage_king1");
			Kingbg->GetComponent<Transform>()->SetScale(Vector3(900.f * 2, 560.0f * 2, 0.0f));			
		}
		#pragma endregion	

		#pragma region tile_map	
		{
			static Vector2 TileSize = Vector2(32.f, 32.f);
			static int Tile_Colum = 120;
			static int Tile_Row = 15;

			static Tile_Ground* Tile_map = object::Instantiate<Tile_Ground>(eLayerType::BACK_GROUND);
			Tile_map->SetName(L"tile_stage1_boss");
			Transform* tr = Tile_map->GetComponent<Transform>();
			tr->AddPositionY(-230.f);
			tr->SetPositionX(-100.f);
			tr->SetPositionZ(-200.f);
			tr->SetScale(Vector3(Tile_Colum * TileSize.x, Tile_Row * TileSize.y, 0.f));

			Collider2D* cd = Tile_map->AddComponent<Collider2D>();
			cd->SetSize(Vector2(1.f, 0.5f));
			cd->SetCenter(Vector2(-955.f, -45.f));

			Collider2D* cd2 = Tile_map->AddComponent<Collider2D>();
			cd2->SetSize(Vector2(0.5f, 0.5f));
			cd2->SetCenter(Vector2(1925.f, 115.f));


			TileMap::TileMap_Setting(Tile_map, L"Stage1_MiniBoss", TileSize, Tile_Colum, Tile_Row, L"\\Resources\\Metadata\\TileMap\\Yggdrasil_bossmap.xml");
		}
		#pragma endregion	
	}
	void Stage1_Boss::Update()
	{
		if (_player->firstGroundcheck == true)
		{
			if (_first_groundturch == false)
			{
				_first_groundturch = true;
				_Stage1_Boss->SetState(GameObject::eState::Active);
			}
		}

		CamareShooting();

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
	void Stage1_Boss::OnEnter()
	{
#pragma region Cam & Mouse& Grid
		//Main Camera			
		Main_Camera* camera = object::Instantiate<Main_Camera>(Vector3(0.f, 0.f, -10.f), eLayerType::Camera);
		cameraComp = camera->AddComponent<Camera>();
		cameraComp->TurnLayerMask(eLayerType::UI, true);
		renderer::cameras.push_back(cameraComp);
		renderer::mainCamera = cameraComp;
		cameraComp->SetTarget(_player);
		cameraComp->SetCamera = true;
		cameraComp->SetYggdrasilCamera = true;
		cameraComp->SetCameraXY = true;
		cameraComp->Set_MaxPlayerX(700.f);
		cameraComp->Set_MinPlayerX(-840.f);
		cameraComp->Set_MaxPlayerY(400.f);
		cameraComp->Set_MinPlayerY(-360.f);

		//UI Camera		
		UI_Camera* UI_camera = object::Instantiate<UI_Camera>(Vector3(0.f, 0.f, -10.f), eLayerType::Camera);
		Camera* cameraComp_ui = UI_camera->AddComponent<Camera>();
		cameraComp_ui->TurnLayerMask(eLayerType::Player, false);
		cameraComp_ui->TurnLayerMask(eLayerType::Monster, false);
		cameraComp_ui->TurnLayerMask(eLayerType::MiniBoss, false);
		cameraComp_ui->TurnLayerMask(eLayerType::Boss, false);
		cameraComp_ui->TurnLayerMask(eLayerType::Bullet, false);
		cameraComp_ui->TurnLayerMask(eLayerType::Effect, false);
		cameraComp_ui->TurnLayerMask(eLayerType::Camera, false);
		cameraComp_ui->TurnLayerMask(eLayerType::Item, false);
		cameraComp_ui->TurnLayerMask(eLayerType::Hitbox, false);
		cameraComp_ui->TurnLayerMask(eLayerType::BACK_GROUND, false);
		cameraComp_ui->TurnLayerMask(eLayerType::Fore_Ground, false);
		cameraComp_ui->TurnLayerMask(eLayerType::Mid_Ground, false);
		cameraComp_ui->TurnLayerMask(eLayerType::Map_Effect, false);
		cameraComp_ui->TurnLayerMask(eLayerType::Camera, false);
		renderer::cameras.push_back(cameraComp_ui);

		//UI_Mouse
		UI_Mouse* cursor = object::Instantiate<UI_Mouse>(Vector3(Vector3::One), eLayerType::Camera);
		cursor->SetName(L"Catle_Cursor_UI");
		cursor->GetComponent<Transform>()->SetScale(Vector3(42.f, 42.f, -250.f));
		cursor->SetName(L"Mouse_UI"); cursor->SetCamera(UI_camera); cursor->SetCamera(camera);

		//Grid
		Grid* grid = object::Instantiate<Grid>(Vector3(Vector3::One), eLayerType::Grid);
		grid->SetName(L"Catle_Grid");
		GridScript* gridSc = grid->AddComponent<GridScript>();
		gridSc->SetCamera(cameraComp);
#pragma endregion	
	}
	void Stage1_Boss::OnExit()
	{
	}


	void Stage1_Boss::CamareShooting()
	{
		Transform* PlayerTR = _player->GetComponent<Transform>();
		Vector3 player_pos = PlayerTR->GetPosition();

		if (_first_groundturch == true)
			cameraComp->SetCameraXY = false;


		//if (player_pos.x <= -610)
		//	cameraComp->SetCameraXY = false;


		//if (_Boss_Create == false)
		//{
		//	if (player_pos.x > -610 && player_pos.x <= -240)
		//		cameraComp->SetCameraXY = true;
		//	if (player_pos.x > -10)
		//	{
		//		cameraComp->SetCameraXY = false;		
		//	}
		//}
	}
}