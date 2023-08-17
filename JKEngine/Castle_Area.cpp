#include "Castle_Area.h"
#include "jkAnimator.h"
#include "jkParticleSystem.h"

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
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::BACK_GROUND, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Item, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::BACK_GROUND, true);
		CollisionManager::SetLayer(eLayerType::MiniBoss, eLayerType::BACK_GROUND, true);
		CollisionManager::SetLayer(eLayerType::Bullet, eLayerType::BACK_GROUND, true);
		CollisionManager::SetLayer(eLayerType::Boss, eLayerType::BACK_GROUND, true);
		CollisionManager::SetLayer(eLayerType::Item, eLayerType::BACK_GROUND, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::MiniBoss, true);
		CollisionManager::SetLayer(eLayerType::MiniBoss, eLayerType::Hitbox, true);
	

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

			#pragma region Player	
					{
						//Skul_Basic* Basic_Skul = object::Instantiate<Skul_Basic>(Vector3(0.f, -100.f, -250.f), eLayerType::Player);
						//Basic_Skul->SetName(L"Basic_Skul");
						////Basic_Skul->GetComponent<Transform>()->SetScale(Vector3(40.f, 30.f, 0.f));
						//Collider2D* cd = Basic_Skul->AddComponent<Collider2D>();
						//Basic_Skul->AddComponent<PlayerScript>();
						//Basic_Skul->AddComponent<CameraScript>();
					}
					{
						//Skul_Nohead* Nohead_Skul = object::Instantiate<Skul_Nohead>(Vector3(0.f, -100.f, -250.f), eLayerType::Player);
						//Nohead_Skul->SetName(L"Nohead_Skul");
						////Basic_Skul->GetComponent<Transform>()->SetScale(Vector3(40.f, 30.f, 0.f));
						//Collider2D* cd = Nohead_Skul->AddComponent<Collider2D>();
						//Nohead_Skul->AddComponent<PlayerScript>();
						//Nohead_Skul->AddComponent<CameraScript>();
					}
					{
						//Skul_Spear* Spear_Skul = object::Instantiate<Skul_Spear>(Vector3(0.f, -100.f, -250.f), eLayerType::Player);
						//Spear_Skul->SetName(L"Spear_Skul");
						////Basic_Skul->GetComponent<Transform>()->SetScale(Vector3(40.f, 30.f, 0.f));
						//Collider2D* cd = Spear_Skul->AddComponent<Collider2D>();
						//Spear_Skul->AddComponent<PlayerScript>();
						//Spear_Skul->AddComponent<CameraScript>();
					}
					//{
					//	Skul_Wolf* Wolf_Skul = object::Instantiate<Skul_Wolf>(Vector3(0.f, -100.f, -250.f), eLayerType::Player);
					//	Wolf_Skul->SetName(L"Wolf_Skul");	
					//}
		
						Player* _player = object::Instantiate<Player>(Vector3(0.f, -100.f, -250.f), eLayerType::Player);
						_player->SetName(L"player_select");
		
			#pragma region Test_monster

						//Layana_Sisters* testboss = object::Instantiate<Layana_Sisters>(Vector3(0.f, 0.f, -250.f), eLayerType::Boss);
						//testboss->SetName(L"test_BOSS");

		
						//Yggdrasil* testboss = object::Instantiate<Yggdrasil>(Vector3(0.f, 0.f, -250.f), eLayerType::Boss);
						//testboss->SetName(L"test_BOSS");


						//Mini_Boss* testmboss = object::Instantiate<Mini_Boss>(Vector3(0.f, 0.f, -250.f), eLayerType::MiniBoss);
						//testmboss->SetName(L"test_mboss");


						//Monster* testmonster = object::Instantiate<Monster>(Vector3(0.f, 0.f, -250.f), eLayerType::Monster);
						//testmonster->SetName(L"test_monster"); 
						//Monster::SetPlayer(_player);	
			#pragma endregion
		



			#pragma endregion

			#pragma region Npc	

			#pragma endregion

			#pragma region CASTLE

					Back_ground* in_Catle_Back = object::Instantiate<Back_ground>(Vector3(0.f, 0.f, 100.f), eLayerType::Fore_Ground, L"In_Fore_GR");
					in_Catle_Back->GetComponent<Transform>()->SetScale(Vector3(1280.f, 720.f, 0.f));	in_Catle_Back->SetName(L"in_Catle_Back");

					Back_ground* out_Catle_Back = object::Instantiate<Back_ground>(Vector3(1200.f, 0.f, 101.f), eLayerType::Fore_Ground, L"Out_Fore_GR");
					out_Catle_Back->GetComponent<Transform>()->SetScale(Vector3(1200.f, 2204.f, 0.f));	out_Catle_Back->SetName(L"out_Catle_Back");

					Back_ground* Castle_wall_Back = object::Instantiate<Back_ground>(Vector3(0.f, 0.f, -100.f), eLayerType::BACK_GROUND, L"Catle_wall_Back");
					Castle_wall_Back->GetComponent<Transform>()->SetScale(Vector3(950, 350.f, 0.f)); Castle_wall_Back->SetName(L"Catle_Back");

					Back_ground* Castle_wall = object::Instantiate<Back_ground>(Vector3(0.0f, -880.f, -150.f), eLayerType::BACK_GROUND, L"Catle_wall_Front_01");
					Castle_wall->GetComponent<Transform>()->SetScale(Vector3(1966.f, 2306.f, 0.f));	Castle_wall->SetName(L"Catle_front");

					Back_ground* _chair = object::Instantiate<Back_ground>(Vector3(-695.f, 0.1f, -200.f), eLayerType::BACK_GROUND, L"Devil_Chair");
					_chair->GetComponent<Transform>()->SetScale(Vector3(447.f, 322.f, 0.f)); _chair->SetName(L"Devil_chair");

					Back_ground* front_obj = object::Instantiate<Back_ground>(Vector3(-300.f, 0.f, -220.f), eLayerType::BACK_GROUND, L"Front_obj");
					front_obj->GetComponent<Transform>()->SetScale(Vector3(1266.f, 548.f, 0.f)); front_obj->SetName(L"front_obj");

					Cloud* cloud = object::Instantiate<Cloud>(Vector3(500.f, -750.f, 90.f), eLayerType::Map_Effect, L"Cloud_Devil");
					cloud->GetComponent<Transform>()->SetScale(Vector3(1120.f * 5, 2204.f, 0.f)); cloud->SetName(L"Castle_cloud");


					//GameObject* front_obj = object::Instantiate<GameObject>(Vector3(-300.f, 0.f, -220.f), eLayerType::Monster);
					//front_obj->SetName(L"front_obj"); MeshRenderer* mr = front_obj->AddComponent<MeshRenderer>();
					//mr->SetMesh(Resources::Find<Mesh>(L"RectMesh")); mr->SetMaterial(Resources::Find<Material>(L"Front_obj"));		
					//front_obj->GetComponent<Transform>()->SetScale(Vector3(1266.f, 548.f, 0.f));

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
					cameraComp_ui->TurnLayerMask(eLayerType::MiniBoss, false);
					cameraComp_ui->TurnLayerMask(eLayerType::Boss, false);
					cameraComp_ui->TurnLayerMask(eLayerType::Bullet, false);
					cameraComp_ui->TurnLayerMask(eLayerType::Effect, false);
					cameraComp_ui->TurnLayerMask(eLayerType::Camera, false);
					cameraComp_ui->TurnLayerMask(eLayerType::Item, false);
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
						tr->SetScale(Vector3(Tile_Colum* TileSize.x, Tile_Row* TileSize.y, 0.f));

						TileMap::TileMap_Setting(Tile_map, L"Devil_castle_tile", TileSize, Tile_Colum, Tile_Row, L"\\Resources\\Metadata\\TileMap\\Devil_castle_Tile.xml");			
					}
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
