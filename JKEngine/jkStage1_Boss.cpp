#include "jkStage1_Boss.h"
#include "LoadScenes.h"
#include "Include_Common.h"
#include "Stage1_BossDoor.h"
#include "..\Engine_SOURCE\jkAudioSource.h"
#include "Sound.h"

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


		_BGSound = object::Instantiate<Sound>(Vector3(0.f, -150.f, -250.f), eLayerType::Player);
		as = _BGSound->AddComponent<AudioSource>();
		as->SetClip(Resources::Load<AudioClip>(L"Chapter1Sound", L"..\\Resources\\Sound\\Chapter1\\Chapter1_Boss.wav", "Chapter1_Boss"));
		as->SetLoop(true);

		
		_player = object::Instantiate<Player>(Vector3(0.f, -100.f, -250.f), eLayerType::Player);
		_player->SetName(L"player_select");

		_Stage1_Boss = object::Instantiate<Yggdrasil>(Vector3(0.f, -500.f, -250.f), eLayerType::Boss);
		_Stage1_Boss->SetName(L"Stage1_BOSS");
		_Stage1_Boss->SetState(GameObject::eState::Paused);


		#pragma region BG	
		{
			_Door = object::Instantiate<Stage1_BossDoor>(Vector3(1300.f, 157.f, 5.f), eLayerType::BACK_GROUND);
			

			Kingbg = object::Instantiate<Back_ground>(Vector3(40.f, 50.f, 10.f), eLayerType::BACK_GROUND, L"Stage_king1");
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


			Ground_Map* bossMap = object::Instantiate<Ground_Map>(Vector3(1343, -10.f, -205.f), eLayerType::BACK_GROUND);
			bossMap->GetComponent<Transform>()->SetScale(Vector3(955, 30.f, 0.f));	bossMap->SetName(L"ST1boss_ground00");

			Ground_and_Wall* bossWall = object::Instantiate<Ground_and_Wall>(Vector3(878.f, -90.f, -205.f), eLayerType::BACK_GROUND);
			bossWall->GetComponent<Transform>()->SetScale(Vector3(30, 175.f, 0.f));	bossWall->SetName(L"ST1boss_Wall00");


			Ground_Map* MinibossMapbottom = object::Instantiate<Ground_Map>(Vector3(0, -300.f, -205.f), eLayerType::BACK_GROUND);
			MinibossMapbottom->GetComponent<Transform>()->SetScale(Vector3(3000, 300.f, 0.f));	MinibossMapbottom->SetName(L"ST1boss_groundbottom");

			TileMap::TileMap_Setting(Tile_map, L"Stage1_MiniBoss", TileSize, Tile_Colum, Tile_Row, L"\\Resources\\Metadata\\TileMap\\Yggdrasil_bossmap.xml");
		}
		#pragma endregion	
	}
	void Stage1_Boss::Update()
	{
		Transform* PlayerTR = _player->GetComponent<Transform>();
		Vector3 player_pos = PlayerTR->GetPosition();

		if (_player->firstGroundcheck == true)
		{
			if (_first_groundturch == false)
			{
				_first_groundturch = true;
				_Stage1_Boss->SetState(GameObject::eState::Active);				
			}
		}

		if (_Stage1_Boss->_Intro_song == true)
			as->Play("Chapter1_Boss");
		else
			as->Stop("Chapter1_Boss");


		if (_Stage1_Boss->_BossDie == true)
		{
				if (_Fadein == false)
				{
					Alpha_Blend* _Alpha = object::Instantiate<Alpha_Blend>(Vector3(0.f, 0.f, -251.f), eLayerType::Map_Effect);
					_Alpha->GetComponent<Transform>()->SetScale(Vector3(10000.f, 10000.f, 0.f));
					_Alpha->Set_White_Transparent();
					_Fadein = true;
				}
				else
				{
					if (_Fadeout == false)
						_Fadetime += 2.75f * static_cast<float>(Time::DeltaTime());
					if (_Fadetime > 3)
					{
						_Fadetime = 0.f;
						_Fadeout = true;
						_Boss_Dead = true;
						//_Stage1_Boss->SetState(GameObject::eState::Paused);
					}
				}			
		}

		CamareShooting();

		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(L"Stage2_1");
		}

		if (_changecheck == true)
		{
			_player->SetPlayer_Pos(player_pos);
			_player->SetPlay_List(_player->GetCurrentPlay_List(), _player->GetPlay_List(), true, _player->GetDirection());
			_changecheck = false;
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
		Transform* PlayerTR = _player->GetComponent<Transform>();
		Vector3 player_pos = PlayerTR->GetPosition();
		_player->SetPlayer_Pos(player_pos);
		_player->SetSwitch(true);
		_changecheck = true;
		#pragma region Cam & Mouse& Grid
		//Main Camera			
		Main_Camera* camera = object::Instantiate<Main_Camera>(Vector3(0.f, 0.f, -10.f), eLayerType::Camera);
		cameraComp = camera->AddComponent<Camera>();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		renderer::cameras.push_back(cameraComp);
		renderer::mainCamera = cameraComp;
		cameraComp->SetTarget(_player);
		cameraComp->SetCamera = true;
		cameraComp->SetYggdrasilCamera = true;
		cameraComp->SetCameraXY = true;
		cameraComp->Set_MaxPlayerX(1500.f);
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


		//Grid
		Grid* grid = object::Instantiate<Grid>(Vector3(Vector3::One), eLayerType::Grid);
		grid->SetName(L"Catle_Grid");
		GridScript* gridSc = grid->AddComponent<GridScript>();
		gridSc->SetCamera(cameraComp);
#pragma endregion	
	}
	void Stage1_Boss::OnExit()
	{
		as->Stop("Chapter1_Boss");
		_player->SettingPlay_List(jk::Player_INFO->GetCurrentPlay_List());
	}


	void Stage1_Boss::CamareShooting()
	{
		Transform* PlayerTR = _player->GetComponent<Transform>();
		Vector3 player_pos = PlayerTR->GetPosition();

		if (_first_groundturch == true)
		{
			if (_Boss_Dead == false)
				cameraComp->SetCameraXY = false;
		}

		if (_Boss_Dead == true)
		{
			cameraComp->Set_MaxBGX(700.f);
			cameraComp->Set_MinBGX(0.f);
			cameraComp->SetTarget_BG(Kingbg);
			cameraComp->BgCamera = true;
			//cameraComp->SetCameraX = true;

			if (player_pos.x >= 950 || player_pos.x <= -450)
				cameraComp->SetCameraX = false;
			else
				cameraComp->SetCameraX = true;

			if (player_pos.x >= 750 && player_pos.x <= 930)
				cameraComp->SetCameraXY = true;
			else
				cameraComp->SetCameraXY = false;
		}
	}
}