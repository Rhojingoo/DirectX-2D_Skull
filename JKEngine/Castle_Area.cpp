#include "Castle_Area.h"
#include "jkAnimator.h"
#include "jkParticleSystem.h"
#include "jkPaintShader.h"
#include "Blosome.h"

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
		//PlayScene::Initialize();
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
	

			#pragma region UI	
					//Player_State_UI* Player_State = object::Instantiate<Player_State_UI>(Vector3(-700.f, -300.f, 1.f), eLayerType::UI);
					//Player_State->GetComponent<Transform>()->SetScale(Vector3(168.f, 66.f, 0.f));
					//Player_State->SetName(L"playyer_state_inventory");

					//Player_Hp_Bar* Player_Hp = object::Instantiate<Player_Hp_Bar>(Vector3(0.085f, -0.25f, -2.f), eLayerType::UI);
					//Player_Hp->GetComponent<Transform>()->SetScale(Vector3(0.68f, 0.185f, 0.f));
					//Player_Hp->SetName(L"player_hp_bar");
					//Player_Hp->GetComponent<Transform>()->SetParent(Player_State->GetComponent<Transform>());

					//Face_UI* Player_Face = object::Instantiate<Face_UI>(Vector3(-0.33f, 0.23f, -2.1f), eLayerType::UI);
					//Player_Face->GetComponent<Transform>()->SetScale(Vector3(0.324f, 0.824f, 0.f));
					//Player_Face->SetName(L"player_head");
					//Player_Face->GetComponent<Transform>()->SetParent(Player_State->GetComponent<Transform>());

			#pragma endregion	

			std::shared_ptr<PaintShader> paintShader = Resources::Find<PaintShader>(L"PaintShader");
			std::shared_ptr<Texture> paintTexture = Resources::Find<Texture>(L"PaintTexuture");
			paintShader->SetTarget(paintTexture);
			paintShader->OnExcute();


		//{//파티클 성공
		//	GameObject* player = new GameObject();
		//	player->SetName(L"Particle");
		//	AddGameObject(eLayerType::Monster, player);
		//	ParticleSystem* mr = player->AddComponent<ParticleSystem>();
		//	player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -249.0f));
		//}

			#pragma region Player				
					_player = object::Instantiate<Player>(Vector3(0.f, 0.f, -250.f), eLayerType::Player);
					_player->SetName(L"player_select");
			#pragma endregion

			#pragma region Npc	

			#pragma endregion

			#pragma region CASTLE
					Back_ground* in_Catle_Back = object::Instantiate<Back_ground>(Vector3(0.f, 0.f, 100.f), eLayerType::Fore_Ground, L"In_Fore_GR");
					in_Catle_Back->GetComponent<Transform>()->SetScale(Vector3(1280.f, 720.f, 0.f));	in_Catle_Back->SetName(L"in_Catle_Back");

					Castle_wall_Back = object::Instantiate<Back_ground>(Vector3(0.f, -30.f, -149.f), eLayerType::BACK_GROUND, L"Catle_wall_Back");
					Castle_wall_Back->GetComponent<Transform>()->SetScale(Vector3(960, 350.f, 0.f)); Castle_wall_Back->SetName(L"Catle_Back");

					Back_ground* Castle_wall = object::Instantiate<Back_ground>(Vector3(0.0f, -880.f, -150.f), eLayerType::BACK_GROUND, L"Catle_wall_Front_01");
					Castle_wall->GetComponent<Transform>()->SetScale(Vector3(1966.f, 2306.f, 0.f));	Castle_wall->SetName(L"Catle_front");

					Back_ground* _chair = object::Instantiate<Back_ground>(Vector3(-695.f, 0.1f, -200.f), eLayerType::BACK_GROUND, L"Devil_Chair");
					_chair->GetComponent<Transform>()->SetScale(Vector3(447.f, 322.f, 0.f)); _chair->SetName(L"Devil_chair");

					Back_ground* front_obj = object::Instantiate<Back_ground>(Vector3(-300.f, 0.f, -220.f), eLayerType::BACK_GROUND, L"Front_obj");
					front_obj->GetComponent<Transform>()->SetScale(Vector3(1266.f, 548.f, 0.f)); front_obj->SetName(L"front_obj");

					Back_ground* out_Catle_Back = object::Instantiate<Back_ground>(Vector3(1200.f, 0.f, 101.f), eLayerType::Fore_Ground, L"Out_Fore_GR");
					out_Catle_Back->GetComponent<Transform>()->SetScale(Vector3(1200.f, 5500.f, 0.f));	out_Catle_Back->SetName(L"out_Catle_Back");

					Back_ground* _Out_Catle = object::Instantiate<Back_ground>(Vector3(1200.f, -1500.f, -99.f), eLayerType::BACK_GROUND, L"Out_Catle");
					_Out_Catle->GetComponent<Transform>()->SetScale(Vector3(1056.f, 1269.f, 0.f));	_Out_Catle->SetName(L"Out_catle");

					Cloud* cloud = object::Instantiate<Cloud>(Vector3(500.f, -750.f, 90.f), eLayerType::Map_Effect, L"Cloud_Devil");
					cloud->GetComponent<Transform>()->SetScale(Vector3(1120.f * 5, 2204.f, 0.f)); cloud->SetName(L"Castle_cloud");

			#pragma endregion				

			#pragma region tile_map		
					{
						Ground_Map* MinibossMap = object::Instantiate<Ground_Map>(Vector3(780.f, -252.f, -201.f), eLayerType::BACK_GROUND);
						MinibossMap->GetComponent<Transform>()->SetScale(Vector3(400, 200.f, 0.f));	MinibossMap->SetName(L"CatleArea_GR");
					}
					{
						out_GroundMap = object::Instantiate<Ground_Map>(Vector3(1060.f, /*-1995.f*/-2200.f, -202.f), eLayerType::BACK_GROUND);
						out_GroundMap->GetComponent<Transform>()->SetScale(Vector3(1000, 200.f, 0.f));	out_GroundMap->SetName(L"CatleArea_OUTGR");
						out_GroundMap->Set_StageTurn(true);
					}
					{
						static Vector2 TileSize = Vector2(32.f, 32.f);
						static int Tile_Colum = 60;
						static int Tile_Row = 8;

						static Tile_Ground* Tile_map = object::Instantiate<Tile_Ground>(eLayerType::BACK_GROUND);
						Tile_map->SetName(L"Tile_Map");
						Transform* tr = Tile_map->GetComponent<Transform>();
						Collider2D* cd = Tile_map->AddComponent<Collider2D>();							
						//tr->SetPositionZ(-200.f);
						tr->SetPositionZ(-200.f);
						tr->AddPositionY(-280.f);
						tr->SetPositionX(-300.f);
						tr->SetScale(Vector3(Tile_Colum * TileSize.x, Tile_Row * TileSize.y, 0.f));

						TileMap::TileMap_Setting(Tile_map, L"Devil_castle_tile", TileSize, Tile_Colum, Tile_Row, L"\\Resources\\Metadata\\TileMap\\Devil_castle_Tile.xml");
					}
			#pragma endregion						
	}
	void Castle_Area::Update()
	{
		if (_player)
		{
			Transform* PlayerTR = _player->GetComponent<Transform>();
			Vector3 player_pos = PlayerTR->GetPosition();

			if (player_pos.x < 975 && player_pos.y < -122)
				cameraComp->SetCameraXY = false;


			if (player_pos.x >= 975)
			{
				cameraComp->SetCameraX = false;
				if (player_pos.y < -122)
					cameraComp->SetCameraY = true;
				else
					cameraComp->SetCameraY = false;
			}


			if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
			{
				_Alpha = object::Instantiate<Alpha_Blend>(Vector3(0.f, 0.f, -251.f), eLayerType::Map_Effect);
				_Alpha->GetComponent<Transform>()->SetScale(Vector3(10000.f, 10000.f, 0.f));
				_Alpha->Set_Black_Transparent();
				_Fadecheck = true;
			}
			if (out_GroundMap->Get_Turnon() == true)
			{
				if (_Fadecheck == false)
				{
					_Alpha = object::Instantiate<Alpha_Blend>(Vector3(0.f, 0.f, -251.f), eLayerType::Map_Effect);
					_Alpha->GetComponent<Transform>()->SetScale(Vector3(10000.f, 10000.f, 0.f));
					_Alpha->Set_Black_Transparent();
					_Fadecheck = true;
				}
			}
			if (_Fadecheck == true)
			{
				_time += 2.75 * Time::DeltaTime();
				if (_time > 3)
				{
					SceneManager::LoadScene(L"OutSide_Castle");
					_time = 0;
					_Fadecheck = false;	
					//Transform* _playerTR = _player->GetComponent<Transform>();
					//_playerTR->SetPosition(Vector3(0.f, 750.f, -250.f));
				}
			}
		}
		Scene::Update();
	}
	void Castle_Area::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void Castle_Area::Render()
	{
		Scene::Render();
	}
	void Castle_Area::OnEnter()
	{
		//_player = GetPlayer();
		//Transform* _playerTR = _player->GetComponent<Transform>();
		//_playerTR->SetPosition(Vector3(0.f, -120.f, -250.f));

	#pragma region Cam & Mouse& Grid
		//Main Camera			
		Main_Camera* camera = object::Instantiate<Main_Camera>(Vector3(0.f, 0.f, -10.f), eLayerType::Camera);
		cameraComp = camera->AddComponent<Camera>();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		renderer::cameras.push_back(cameraComp);
		renderer::mainCamera = cameraComp;
		cameraComp->SetTarget(_player);
		cameraComp->SetCamera = true;
		cameraComp->SetCameraXY = true;
		cameraComp->SetCameraX = true;
		cameraComp->SetCameraXY = false;
		cameraComp->Set_MaxPlayerX(1200.f);
		cameraComp->Set_MinPlayerX(-600.f);
		cameraComp->Set_MinPlayerY(-1800.f);
		cameraComp->Set_MaxBGX(400.f);
		cameraComp->Set_MinBGX(-600.f);
		cameraComp->SetTarget_BG(Castle_wall_Back);
		cameraComp->BgCamera = true;

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
		cursor->SetName(L"Mouse_UI"); cursor->SetCamera(UI_camera);

		//Grid
		Grid* grid = object::Instantiate<Grid>(Vector3(Vector3::One), eLayerType::Grid);
		grid->SetName(L"Catle_Grid");
		GridScript* gridSc = grid->AddComponent<GridScript>();
		gridSc->SetCamera(cameraComp);
	#pragma endregion		
	}
	void Castle_Area::OnExit()
	{
	}
}
