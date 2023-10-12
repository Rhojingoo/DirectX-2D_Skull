#include "Castle_Area.h"
#include "jkAnimator.h"
#include "jkParticleSystem.h"
#include "jkPaintShader.h"
#include "Blosome.h"
#include "LoadScenes.h"
#include "jkAudioListener.h"
#include "jkAudioClip.h"
#include "jkAudioSource.h"

#include "Monster_LionWarrior.h"
#include "Monster_LionSpear.h"
#include "Monster_LionWizard.h"
#include "Mushroom_Spring.h"

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
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::BACK_GROUND, true);
		CollisionManager::SetLayer(eLayerType::MiniBoss, eLayerType::BACK_GROUND, true);
		CollisionManager::SetLayer(eLayerType::Bullet, eLayerType::BACK_GROUND, true);
		CollisionManager::SetLayer(eLayerType::Boss, eLayerType::BACK_GROUND, true);
		CollisionManager::SetLayer(eLayerType::Item, eLayerType::BACK_GROUND, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Boss, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::MiniBoss, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Hitbox, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Bullet, true);
		CollisionManager::SetLayer(eLayerType::Boss, eLayerType::Hitbox, true);
		CollisionManager::SetLayer(eLayerType::MiniBoss, eLayerType::Hitbox, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Hitbox, true);
	

		std::shared_ptr<PaintShader> paintShader = Resources::Find<PaintShader>(L"PaintShader");
		std::shared_ptr<Texture> paintTexture = Resources::Find<Texture>(L"PaintTexuture");
		paintShader->SetTarget(paintTexture);
		paintShader->OnExcute();		

		_BGSound = object::Instantiate<Sound>(Vector3(0.f, -150.f, -250.f), eLayerType::Player);
		as = _BGSound->AddComponent<AudioSource>();
		as->SetClip(Resources::Load<AudioClip>(L"DemonCastleSound", L"..\\Resources\\Sound\\DemonCastle\\DemonCastle.wav"));
		as->SetLoop(true);

		#pragma region Player				
				_player = object::Instantiate<Player>(Vector3(0.f, -50.f, -250.f), eLayerType::Player);
				_player->SetName(L"player_select");
		#pragma endregion



	//	Monster_warrior* test = object::Instantiate<Monster_warrior>(Vector3(0.f, -50.f, -249.f), eLayerType::Monster);
	//	Stone_wizard* test1 = object::Instantiate<Stone_wizard>(Vector3(0.f, -50.f, -249.f), eLayerType::Monster);
	//	Monster_GreenTree* test2 = object::Instantiate<Monster_GreenTree>(Vector3(0.f, -50.f, -249.f), eLayerType::Monster);
	//	Monster_BlossomEnt* test3 = object::Instantiate<Monster_BlossomEnt>(Vector3(0.f, -50.f, -249.f), eLayerType::Monster);
	//	Monster_Hammer* test4 = object::Instantiate<Monster_Hammer>(Vector3(0.f, -50.f, -249.f), eLayerType::Monster);
		//Monster_BigEnt* test5 = object::Instantiate<Monster_BigEnt>(Vector3(0.f, -50.f, -249.f), eLayerType::Monster);


		//Monster_Goldwarrior* test11 = object::Instantiate<Monster_Goldwarrior>(Vector3(0.f, -50.f, -249.f), eLayerType::Monster);
		//Monster_GoldHammer* test12 = object::Instantiate<Monster_GoldHammer>(Vector3(0.f, -50.f, -249.f), eLayerType::Monster);
		//Monster_LionWarrior* test13 = object::Instantiate<Monster_LionWarrior>(Vector3(0.f, -50.f, -249.f), eLayerType::Monster);
		//Monster_LionSpear* test14 = object::Instantiate<Monster_LionSpear>(Vector3(0.f, -50.f, -249.f), eLayerType::Monster);
		//Monster_LionWizard* test15 = object::Instantiate<Monster_LionWizard>(Vector3(0.f, -50.f, -249.f), eLayerType::Monster);

		//Mushroom_Spring* test16 = object::Instantiate<Mushroom_Spring>(Vector3(150.f, -80.f, -249.f), eLayerType::Monster);

		//Archer* test5 = object::Instantiate<Archer>(Vector3(0.f, -50.f, -249.f), eLayerType::MiniBoss);
		//Cleric* test5 = object::Instantiate<Cleric>(Vector3(0.f, -50.f, -249.f), eLayerType::MiniBoss);
		//Knight_male* test5 = object::Instantiate<Knight_male>(Vector3(0.f, -50.f, -249.f), eLayerType::MiniBoss);
		//Mage* test5 = object::Instantiate<Mage>(Vector3(0.f, -50.f, -249.f), eLayerType::MiniBoss);

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

			if (_player->firstGroundcheck == true)
			{
				if (first_groundturch = false)
				{
					cameraComp->SetCameraXY = false;
					first_groundturch = true;
				}
			}


			if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
			{
				_Alpha = object::Instantiate<Alpha_Blend>(Vector3(0.f, 0.f, -251.f), eLayerType::Map_Effect);
				_Alpha->GetComponent<Transform>()->SetScale(Vector3(10000.f, 10000.f, 0.f));
				_Alpha->Set_Black_Transparent();
				_Fadecheck = true;
				_player->SettingPlay_List(jk::Player_INFO->GetCurrentPlay_List());
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
		//as->Play();
		#pragma region Cam & Mouse& Grid
		//Main Camera			
		Main_Camera* camera = object::Instantiate<Main_Camera>(Vector3(0.f, 0.f, -10.f), eLayerType::Camera);
		cameraComp = camera->AddComponent<Camera>();
		camera->AddComponent<AudioListener>();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		renderer::cameras.push_back(cameraComp);
		renderer::mainCamera = cameraComp;
		cameraComp->SetTarget(_player);
		cameraComp->SetCamera = true;
		cameraComp->SetCameraXY = true;
		cameraComp->SetCameraX = true;
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
		_player->SettingPlay_List(jk::Player_INFO->GetCurrentPlay_List());
		//jk::Player_INFO->Set_HP_Bar(_player->Get_HP_Bar());
		//jk::Player_INFO->Set_DamageHP_Bar(_player->Get_DamageHP_Bar());
		as->Stop();
	}
}
