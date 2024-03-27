#include "OutSide_CastleArea.h"
#include "LoadScenes.h"
#include "Include_Common.h"
#include "jkPlayScene.h"
#include "Alpha_Blend.h"
#include "..\Engine_SOURCE\jkAudioSource.h"
#include "Sound.h"


namespace jk
{


	OutSide_CastleArea::OutSide_CastleArea()
	{
	}
	OutSide_CastleArea::~OutSide_CastleArea()
	{
	}
	void OutSide_CastleArea::Initialize()
	{		

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

			_BGSound = object::Instantiate<Sound>(Vector3(0.f, -150.f, -250.f), eLayerType::Player);
			as = _BGSound->AddComponent<AudioSource>();
			as->SetClip(Resources::Load<AudioClip>(L"Chapter1", L"..\\Resources\\Sound\\Chapter1\\Chapter1.wav", "Chapter1"));
			as->SetLoop(true);
			//as->SetClip(Resources::Load<AudioClip>(L"Chapter2", L"..\\Resources\\Sound\\Chapter2\\Chapter2.wav", "Chapter2"));


			#pragma region Player		
			_player = object::Instantiate<Player>(Vector3(0.f, 750.f, -250.f), eLayerType::Player);
			_player->SetName(L"player_select");
			#pragma endregion	



			#pragma region Door
							Door1 = object::Instantiate<Stage1_Door>(Vector3(170.f, -80.f, -249.f), eLayerType::BACK_GROUND);
							Door1->Set_Door_Allow(true); Door1->Set_Stage1_Door(0);	Door1->Set_NextStage(L"Stage1_1");


							Stage1_Door* Door2 = object::Instantiate<Stage1_Door>(Vector3(440.f, -80.f, -249.f), eLayerType::BACK_GROUND);
							Door2->Set_Door_Allow(true); Door2->Set_Stage1_Door(8); Door2->Set_NextStage(L"Stage1_1");


							Stage_end_wall* Door_Wall = object::Instantiate<Stage_end_wall>(Vector3(303.f, -80.f, -248.f), eLayerType::BACK_GROUND);
							Door_Wall->Set_Wall_Allow(true);  Door_Wall->Set_Wall_Stage(0);

							
							Back_ground* Ch1_Gate_Table = object::Instantiate<Back_ground>(Vector3(303.f, -110.f, -249.f), eLayerType::BACK_GROUND, L"Ch1_Gate_Table");
							Ch1_Gate_Table->GetComponent<Transform>()->SetScale(Vector3(90.f, 19.f, 0.f));	Ch1_Gate_Table->SetName(L"Ch1_Gate_Table1");

							NPC_by_stage* _npc_by_stage = object::Instantiate<NPC_by_stage>(Vector3(-90.f, -50.f, -249.f), eLayerType::Item);
							_npc_by_stage->Set_Table_Allow(true);  _npc_by_stage->Set_End_Table(1);
				#pragma endregion	

			#pragma region CASTLE
							Back_ground* out_Catle_Back = object::Instantiate<Back_ground>(Vector3(0.f, 0.f, 101.f), eLayerType::Fore_Ground, L"Out_Fore_GR");
							out_Catle_Back->GetComponent<Transform>()->SetScale(Vector3(1200.f, 5500.f, 0.f));	out_Catle_Back->SetName(L"out_Catle_Back");

							Back_ground* _Out_Catle = object::Instantiate<Back_ground>(Vector3(150.f, 300.f, -80.f), eLayerType::BACK_GROUND, L"Out_Catle");
							_Out_Catle->GetComponent<Transform>()->SetScale(Vector3(1056.f, 1269.f, 0.f));	_Out_Catle->SetName(L"Out_catle");

							Back_ground* _Rampart = object::Instantiate<Back_ground>(Vector3(-200.f, 50.f, -99.f), eLayerType::BACK_GROUND, L"Rampart_Base");
							_Rampart->GetComponent<Transform>()->SetScale(Vector3(256.f, 415.f, 0.f));	_Out_Catle->SetName(L"Rampart_base");


							Back_ground* _Pillar01 = object::Instantiate<Back_ground>(Vector3(-30.f, -10.f, -99.f), eLayerType::BACK_GROUND, L"Pillar03");
							_Pillar01->GetComponent<Transform>()->SetScale(Vector3(58.f, 222.f, 0.f));	_Pillar01->SetName(L"pillar01");


							Back_ground* _Pillar02 = object::Instantiate<Back_ground>(Vector3(70.f, -10.f, -99.f), eLayerType::BACK_GROUND, L"Pillar03");
							_Pillar02->GetComponent<Transform>()->SetScale(Vector3(58.f, 222.f, 0.f));	_Pillar02->SetName(L"pillar02");


							Back_ground* _Pillar03 = object::Instantiate<Back_ground>(Vector3(170.f, -10.f, -99.f), eLayerType::BACK_GROUND, L"Pillar03");
							_Pillar03->GetComponent<Transform>()->SetScale(Vector3(58.f, 222.f, 0.f));	_Pillar03->SetName(L"pillar03");


							Back_ground* _Pillar04 = object::Instantiate<Back_ground>(Vector3(270.f, -10.f, -99.f), eLayerType::BACK_GROUND, L"Pillar03");
							_Pillar04->GetComponent<Transform>()->SetScale(Vector3(58.f, 222.f, 0.f));	_Pillar04->SetName(L"pillar04");


							Back_ground* _Pillar05 = object::Instantiate<Back_ground>(Vector3(470.f, -10.f, -99.f), eLayerType::BACK_GROUND, L"Pillar03");
							_Pillar05->GetComponent<Transform>()->SetScale(Vector3(58.f, 222.f, 0.f));	_Pillar05->SetName(L"pillar05");


							Back_ground* _Trees = object::Instantiate<Back_ground>(Vector3(250.f, -25.f, -90.f), eLayerType::BACK_GROUND, L"Stage1_Back_GR14");
							_Trees->GetComponent<Transform>()->SetScale(Vector3(780.f, 189.f, 0.f));	_Trees->SetName(L"S1_Back_GR14");


							Back_ground* _Bush00 = object::Instantiate<Back_ground>(Vector3(100.f, -150.f, -201.f), eLayerType::BACK_GROUND, L"Fore_Bush00");
							_Bush00->GetComponent<Transform>()->SetScale(Vector3(543.f, 74.f, 0.f));	_Trees->SetName(L"Fore_bush00");


							Back_ground* _Bush01 = object::Instantiate<Back_ground>(Vector3(-185.f, -135.f, -251.f), eLayerType::BACK_GROUND, L"Fore_Bush02");
							_Bush01->GetComponent<Transform>()->SetScale(Vector3(219.f, 137.f, 0.f));	_Bush01->SetName(L"Fore_bush02");


							Back_ground* _Bush02 = object::Instantiate<Back_ground>(Vector3(550.f, -135.f, -252.f), eLayerType::BACK_GROUND, L"Fore_Bush03");
							_Bush02->GetComponent<Transform>()->SetScale(Vector3(280.f, 204.f, 0.f));	_Bush02->SetName(L"Fore_bush03");


							Back_ground* _Bush03 = object::Instantiate<Back_ground>(Vector3(500.f, -150.f, -251.f), eLayerType::BACK_GROUND, L"Fore_Bush04");
							_Bush03->GetComponent<Transform>()->SetScale(Vector3(339.f, 112.f, 0.f));	_Bush03->SetName(L"Fore_bush04");


							Back_ground* _Bush04 = object::Instantiate<Back_ground>(Vector3(700.f, -150.f, -251.f), eLayerType::BACK_GROUND, L"Fore_Tree01");
							_Bush04->GetComponent<Transform>()->SetScale(Vector3(422.f, 501.f, 0.f));	_Bush04->SetName(L"Fore_tree01");

				#pragma endregion				

			#pragma region tile_map		
							{
								static Vector2 TileSize = Vector2(32.f, 32.f);
								static int Tile_Colum = 60;
								static int Tile_Row = 5;

								static Tile_Ground* Tile_map = object::Instantiate<Tile_Ground>(eLayerType::BACK_GROUND);
								Tile_map->SetName(L"Tile_Map");
								Transform* tr = Tile_map->GetComponent<Transform>();
								Collider2D* cd = Tile_map->AddComponent<Collider2D>();
								//tr->SetPositionZ(-200.f);
								tr->SetPositionZ(-200.f);
								tr->AddPositionY(-200.f);
								tr->SetPositionX(0.f);
								tr->SetScale(Vector3(Tile_Colum * TileSize.x, Tile_Row * TileSize.y, 0.f));

								TileMap::TileMap_Setting(Tile_map, L"Out_castle_tiles", TileSize, Tile_Colum, Tile_Row, L"\\Resources\\Metadata\\TileMap\\Castle_Out.xml");
							}
				#pragma endregion	


	}
	void OutSide_CastleArea::Update()
	{
		Transform* PlayerTR = _player->GetComponent<Transform>();
		Vector3 player_pos = PlayerTR->GetPosition();

		if (player_pos.y < 50)		
			cameraComp->SetTarget(_player);				
		

		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			_Alpha = object::Instantiate<Alpha_Blend>(Vector3(0.f, 0.f, -251.f), eLayerType::Map_Effect);
			_Alpha->GetComponent<Transform>()->SetScale(Vector3(10000.f, 10000.f, 0.f));
			_Alpha->Set_Black_Transparent();
			_Fadecheck = true;
		}

		if (_Fadecheck == true)
		{
			_time += 2.75f * static_cast<float>(Time::DeltaTime());
			if (_time > 3)
			{
				SceneManager::LoadScene(L"Stage1_1");
				_time = 0;
				_Fadecheck = false;
			}
		}

		if (_changecheck == true)
		{
			_player->SetSwitch(true);
			_player->SetPlayer_Pos(player_pos);
			_player->SetPlay_List(_player->GetCurrentPlay_List(), _player->GetPlay_List(), true, _player->GetDirection());
			_changecheck = false;		
		}

		Scene::Update();
	}
	void OutSide_CastleArea::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void OutSide_CastleArea::Render()
	{
		Scene::Render();
	}


	void OutSide_CastleArea::OnEnter()
	{
		as->Play("Chapter1");
		Transform* PlayerTR = _player->GetComponent<Transform>();
		Vector3 player_pos = PlayerTR->GetPosition();
		_player->SetPlayer_Pos(player_pos);	
		_changecheck = true;



#pragma region Cam & Mouse& Grid
		//Main Camera			
		Main_Camera* camera = object::InstantiateActive<Main_Camera>(Vector3(0.f, 0.f, -10.f), eLayerType::Camera);
		cameraComp = camera->AddComponent<Camera>();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		renderer::cameras.push_back(cameraComp);
		renderer::mainCamera = cameraComp;
		cameraComp->SetCamera = true;
		cameraComp->SetCameraX = true;
		cameraComp->Set_MaxPlayerX(280.f);
		cameraComp->Set_MinPlayerX(0.f);


		//UI Camera		
		UI_Camera* UI_camera = object::InstantiateActive<UI_Camera>(Vector3(0.f, 0.f, -10.f), eLayerType::Camera);
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
		UI_Mouse* cursor = object::InstantiateActive<UI_Mouse>(Vector3(Vector3::One), eLayerType::Camera);
		cursor->SetName(L"Catle_Cursor_UI");
		cursor->GetComponent<Transform>()->SetScale(Vector3(42.f, 42.f, -250.f));
		cursor->SetName(L"Mouse_UI"); cursor->SetCamera(UI_camera);

		//Grid
		Grid* grid = object::InstantiateActive<Grid>(Vector3(Vector3::One), eLayerType::Grid);
		grid->SetName(L"Catle_Grid");
		GridScript* gridSc = grid->AddComponent<GridScript>();
		gridSc->SetCamera(cameraComp);
#pragma endregion		
	}
	void OutSide_CastleArea::OnExit()
	{
		jk::Player_INFO->SettingPlay_List(_player->GetPlay_List());
		as->Stop("Chapter1");
	}
}