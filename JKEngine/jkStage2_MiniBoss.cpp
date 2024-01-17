#include "jkStage2_MiniBoss.h"
#include "Include_Common.h"
#include "Stage2_Door.h"
#include "Monster_Objmanagerl.h"
#include "Knight_male.h"
#include "Archer.h"
#include "Mage.h"
#include "Cleric.h"
#include "..\Engine_SOURCE\jkAudioSource.h"
#include "Sound.h"


jk::Stage2_MiniBoss::Stage2_MiniBoss()
{
}

jk::Stage2_MiniBoss::~Stage2_MiniBoss()
{
	mBossGroup.clear();
}

void jk::Stage2_MiniBoss::Initialize()
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
	CollisionManager::SetLayer(eLayerType::Player, eLayerType::MiniBoss, true);
	CollisionManager::SetLayer(eLayerType::Player, eLayerType::Hitbox, true);
	CollisionManager::SetLayer(eLayerType::MiniBoss, eLayerType::Hitbox, true);
	CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Hitbox, true);
#pragma endregion 


	CreateMiniboss();

	_player = object::Instantiate<Player>(Vector3(-700.f, 10.f, -250.f), eLayerType::Player);
	_player->SetName(L"player_select");


	_BGSound = object::Instantiate<Sound>(Vector3(0.f, -150.f, -250.f), eLayerType::Player);
	as = _BGSound->AddComponent<AudioSource>();
	as->SetClipAndLoad(L"..\\Resources\\Sound\\Adventurer\\Adventurer.wav", "Adventurer");
	as->SetLoop(true);
	as->SetClipAndLoad(L"..\\Resources\\Sound\\Chapter2\\Chapter2.wav", "Chapter2");
	as->SetLoop(true);


#pragma region Door
	Door1 = object::Instantiate<Stage2_Door>(Vector3(587.f, -6.f, -249.f), eLayerType::BACK_GROUND);
	Door1->Set_Door_Allow(true); Door1->Set_Stage2_Door(5);	Door1->Set_NextStage(L"Stage2_2");


	Stage2_Door* Door2 = object::Instantiate<Stage2_Door>(Vector3(857.f, -6.f, -249.f), eLayerType::BACK_GROUND);
	Door2->Set_Door_Allow(true); Door2->Set_Stage2_Door(9); Door2->Set_NextStage(L"Stage2_2");


	Stage_end_wall* Door_Wall = object::Instantiate<Stage_end_wall>(Vector3(720.f, -6.f, -248.f), eLayerType::BACK_GROUND);
	Door_Wall->Set_Wall_Allow(true);  Door_Wall->Set_Wall_Stage(1);
#pragma endregion	

#pragma region BackGround
	{
		Back_ground* Back_Ground = object::Instantiate<Back_ground>(Vector3(0.f, 0.f, 105.f), eLayerType::Fore_Ground, L"ForeGround_Stage2_00");
		Back_Ground->GetComponent<Transform>()->SetScale(Vector3(1920.f, 800.f, 0.0f));
	}
	{
		Back_ground* Back_Ground = object::Instantiate<Back_ground>(Vector3(-500.f, -200.f, 103.f), eLayerType::Fore_Ground, L"Stage1_Back_GR12");
		Back_Ground->GetComponent<Transform>()->SetScale(Vector3(718.f, 380.f, 0.0f));
	}
	{
		Back_ground* Back_Ground = object::Instantiate<Back_ground>(Vector3(0.f, -250.f, 102.f), eLayerType::Fore_Ground, L"Stage1_Back_GR14");
		Back_Ground->GetComponent<Transform>()->SetScale(Vector3(780.f, 189.f, 0.0f));
	}
	{
		Back_ground* Back_Ground = object::Instantiate<Back_ground>(Vector3(500.f, -230.f, 103.f), eLayerType::Fore_Ground, L"Stage1_Back_GR12");
		Back_Ground->GetComponent<Transform>()->SetScale(Vector3(718.f, 380.f, 0.0f));
	}
	{
		Cloud* cloud = object::Instantiate<Cloud>(Vector3(0.f, 0.f, 104.f), eLayerType::Map_Effect, L"Stage2_Cloud");
		cloud->GetComponent<Transform>()->SetScale(Vector3(1860.f, 222.f, 0.f)); cloud->SetName(L"stage2_cloud");
	}
	{
		Cloud* cloud = object::Instantiate<Cloud>(Vector3(0.f, 200.f, 104.f), eLayerType::Map_Effect, L"Stage2_Cloud");
		cloud->GetComponent<Transform>()->SetScale(Vector3(1860.f, 222.f, 0.f)); cloud->SetName(L"stage2_cloud");
	}
	{
		Back_ground* Back_Ground = object::Instantiate<Back_ground>(Vector3(0.f, 0.f, 55.f), eLayerType::Fore_Ground, L"BackGround_Stage2_01");
		Back_Ground->GetComponent<Transform>()->SetScale(Vector3(1920.f, 800.f, 0.0f));
	}

	{
		Back_ground* Back_Ground = object::Instantiate<Back_ground>(Vector3(0.f, 200.f, 40.f), eLayerType::Fore_Ground, L"BackGround_Stage2_02");
		Back_Ground->GetComponent<Transform>()->SetScale(Vector3(1905.f, 402.f, 0.0f));
	}

	{
		Back_ground* Back_Ground = object::Instantiate<Back_ground>(Vector3(0.f, -90.f, 45.f), eLayerType::Fore_Ground, L"Miniboss_01");
		Back_Ground->GetComponent<Transform>()->SetScale(Vector3(183.f, 257.f, 0.0f));
	}

	{
		Back_ground* Back_Ground = object::Instantiate<Back_ground>(Vector3(-650.f, 150.f, 50.f), eLayerType::Fore_Ground, L"Miniboss_03");
		Back_Ground->GetComponent<Transform>()->SetScale(Vector3(267, 357.f * 1.5, 0.f));
	}

	{
		Back_ground* Back_Ground = object::Instantiate<Back_ground>(Vector3(750.f, 150.f, 50.f), eLayerType::Fore_Ground, L"Miniboss_03");
		Back_Ground->GetComponent<Transform>()->SetScale(Vector3(267, 357.f * 1.5, 0.f));
	}



#pragma region Tile		
	{
		Ground_Map* MinibossMap = object::Instantiate<Ground_Map>(Vector3(40.f, -300.f, -205.f), eLayerType::BACK_GROUND);
		MinibossMap->GetComponent<Transform>()->SetScale(Vector3(3000, 170.f, 0.f));	MinibossMap->SetName(L"Stage2_ground00");

		Ground_Map* MinibossMap1 = object::Instantiate<Ground_Map>(Vector3(-720.f, -65.f, -205.f), eLayerType::BACK_GROUND);
		MinibossMap1->GetComponent<Transform>()->SetScale(Vector3(480, 15.f, 0.f));	MinibossMap1->SetName(L"Stage2_ground01");

		Ground_Map* MinibossMap2 = object::Instantiate<Ground_Map>(Vector3(720.f, -65.f, -205.f), eLayerType::BACK_GROUND);
		MinibossMap2->GetComponent<Transform>()->SetScale(Vector3(480, 15.f, 0.f));	MinibossMap2->SetName(L"Stage2_ground02");


		Ground_and_Wall* MinibossWall = object::Instantiate<Ground_and_Wall>(Vector3(-720.f, -145.f, -205.f), eLayerType::BACK_GROUND);
		MinibossWall->GetComponent<Transform>()->SetScale(Vector3(480, 150.f, 0.f));	MinibossWall->SetName(L"Stage2_Wall00");

		Ground_and_Wall* MinibossWall1 = object::Instantiate<Ground_and_Wall>(Vector3(720.f, -145, -205.f), eLayerType::BACK_GROUND);
		MinibossWall1->GetComponent<Transform>()->SetScale(Vector3(480, 150.f, 0.f));	MinibossWall1->SetName(L"Stage2_Wall01");




		static Vector2 TileSize = Vector2(32.f, 32.f);
		static int Tile_Colum = 60;
		static int Tile_Row = 25;

		static Tile_Ground* Tile_map = object::Instantiate<Tile_Ground>(eLayerType::BACK_GROUND);
		Tile_map->SetName(L"Stage2_MiniBoss");
		Transform* tr = Tile_map->GetComponent<Transform>();
		tr->SetPositionZ(-200.f);
		tr->AddPositionY(0.f);
		tr->SetScale(Vector3(Tile_Colum * TileSize.x, Tile_Row * TileSize.y, 0.f));
		TileMap::TileMap_Setting(Tile_map, L"Stage2_Tile", TileSize, Tile_Colum, Tile_Row, L"\\Resources\\Metadata\\TileMap\\Stage2_MiniBoss.xml");
	}
#pragma endregion

#pragma endregion 	
}

void jk::Stage2_MiniBoss::Update()
{
	Transform* PlayerTR = _player->GetComponent<Transform>();
	Vector3 player_pos = PlayerTR->GetPosition();

	if (_player->firstGroundcheck == true)
	{
		if (_first_groundtouch == false)
		{
			_first_groundtouch = true;
		}
	}

	CamareShooting();

	if (_first_groundtouch == true)
	{
		if (_MiniBoss_groundtouch == true)
		{
			if (_MiniBoss_Create == false)
			{
				for (Mini_Boss* mon : mBossGroup)
				{
					as->Play("Adventurer");
					mon->SetState(GameObject::eState::Active);
				}
				_MiniBoss_Create = true;
			}
		}
	}

	AreAllMiniBossDead(mBossGroup);
	if (_MiniBoss_Dead == true)
	{
		if (_Door_Open == false)
		{
			as->Stop("Adventurer");
			as->Play("Chapter2");
			cameraComp->SetCameraXY = true;
			Door1->Set_Door_Allow(true);
			Door1->Set_Stage2_Door(1);
			_Door_Open = true;
			int a = 0;
		}
	}



	if (_changecheck == true)
	{
		_player->SetPlayer_Pos(player_pos);
		_player->SetPlay_List(_player->GetCurrentPlay_List(), _player->GetPlay_List(), true, _player->GetDirection());
		_changecheck = false;
	}


	if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
	{
		SceneManager::LoadScene(L"Stage2_2");
	}
	Scene::Update();
}

void jk::Stage2_MiniBoss::LateUpdate()
{
	Scene::LateUpdate();
}

void jk::Stage2_MiniBoss::Render()
{
	Scene::Render();
}

void jk::Stage2_MiniBoss::OnEnter()
{
	Transform* PlayerTR = _player->GetComponent<Transform>();
	Vector3 player_pos = PlayerTR->GetPosition();
	_player->SetPlayer_Pos(player_pos);
	_player->SetSwitch(true);
	_changecheck = true;
	_player->firstGroundcheck = false;

	Mini_Boss::Left_Ground = (Vector3(-480.f, 0.f, 0.f));
	Mini_Boss::Right_Ground = (Vector3(480.f, 0.f, 0.f));

#pragma region Camera & Grid

	//Main Camera
	Main_Camera* camera = object::Instantiate<Main_Camera>(Vector3(0.f, 0.f, -10.f), eLayerType::Camera);
	cameraComp = camera->AddComponent<Camera>();
	cameraComp->TurnLayerMask(eLayerType::UI, false);
	camera->AddComponent<CameraScript>();
	renderer::cameras.push_back(cameraComp);
	renderer::mainCamera = cameraComp;
	cameraComp->SetCamera = true;
	Transform* camTR = camera->GetComponent<Transform>();
	camTR->SetPosition(Vector3(player_pos.x + 180, player_pos.y, -60.f));
	cameraComp->Set_MaxPlayerX(600.f);
	cameraComp->Set_MinPlayerX(-650.f);
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
	//renderer::cameras.push_back(cameraComp_ui);

	Grid* grid = object::Instantiate<Grid>(Vector3(Vector3::One), eLayerType::Grid);
	grid->SetName(L"Catle_Grid");
	GridScript* gridSc = grid->AddComponent<GridScript>();
	gridSc->SetCamera(cameraComp);
#pragma endregion 
}

void jk::Stage2_MiniBoss::OnExit()
{
	as->Stop("Chapter2");
}

void jk::Stage2_MiniBoss::CamareShooting()
{
	Transform* PlayerTR = _player->GetComponent<Transform>();
	Vector3 player_pos = PlayerTR->GetPosition();

	if (_MiniBoss_Create == false)
	{
		if (player_pos.x <= -490 && player_pos.x > -550)
		{
			cameraComp->SetTarget(_player);
			cameraComp->SetCameraXY = true;
		}

		if (player_pos.x >= -10)
		{
			_MiniBoss_groundtouch = true;
		}
	}
	else
	{
		if (_Door_Open == false)
		{
			cameraComp->SetCameraXY = false;
			cameraComp->SetCameraX = true;
			if (player_pos.x >= 175 || player_pos.x < -170)
				cameraComp->SetCameraX = false;
		}
	}
}

void jk::Stage2_MiniBoss::CreateMiniboss()
{
	
	std::vector<int> selectedMonsters;
	for (int a = 0; a < 3; a++)
	{
		do
		{
			_Randomcheck = Mboss->random(0, 2);
		} while (std::find(selectedMonsters.begin(), selectedMonsters.end(), _Randomcheck) != selectedMonsters.end()); // 이미 선택된 몬스터 번호가 아닐 때까지 반복
		selectedMonsters.push_back(_Randomcheck); // 선택된 몬스터 번호 저장				
	}
	for (int a = 0; a < 3; a++)
	{
		int currentMonster = selectedMonsters[a]; // 백터에서 몬스터 번호 꺼내기

		if (currentMonster == 0)
		{
			Knight_male* _Gobjs = new Knight_male();
			_Gobjs->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::MiniBoss, _Gobjs);
			_Gobjs->SetState(GameObject::eState::Paused);
			Transform* tr = _Gobjs->GetComponent<Transform>();
			mBossGroup.push_back(_Gobjs);


			if (a == 0)
			{
				tr->SetPosition(Vector3(100.f, 0.f, -250.f));
				_Gobjs->SetUIstate(0);
			}
			else if (a == 1)
			{
				tr->SetPosition(Vector3(200.f, 0.f, -250.f));
				_Gobjs->SetUIstate(1);
			}
			else if (a == 2)
			{
				tr->SetPosition(Vector3(300.f, 0.f, -250.f));
				_Gobjs->SetUIstate(2);
			}
		}
		else if (currentMonster == 1)
		{
			Archer* _Gobjs = new Archer();
			_Gobjs->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::MiniBoss, _Gobjs);
			_Gobjs->SetState(GameObject::eState::Paused);
			Transform* tr = _Gobjs->GetComponent<Transform>();
			tr->SetPosition(Vector3(200.f, 0.f, -250.f));
			mBossGroup.push_back(_Gobjs);

			if (a == 0)
			{
				tr->SetPosition(Vector3(100.f, 0.f, -250.f));
				_Gobjs->SetUIstate(0);
			}
			else if (a == 1)
			{
				tr->SetPosition(Vector3(200.f, 0.f, -250.f));
				_Gobjs->SetUIstate(1);
			}
			else if (a == 2)
			{
				tr->SetPosition(Vector3(300.f, 0.f, -250.f));
				_Gobjs->SetUIstate(2);
			}
		}
		else if (currentMonster == 2)
		{
			Mage* _Gobjs = new Mage();
			_Gobjs->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::MiniBoss, _Gobjs);
			_Gobjs->SetState(GameObject::eState::Paused);
			Transform* tr = _Gobjs->GetComponent<Transform>();
			tr->SetPosition(Vector3(200.f, 0.f, -250.f));
			mBossGroup.push_back(_Gobjs);

			if (a == 0)
			{
				tr->SetPosition(Vector3(100.f, 0.f, -250.f));
				_Gobjs->SetUIstate(0);
			}
			else if (a == 1)
			{
				tr->SetPosition(Vector3(200.f, 0.f, -250.f));
				_Gobjs->SetUIstate(1);
			}
			else if (a == 2)
			{
				tr->SetPosition(Vector3(300.f, 0.f, -250.f));
				_Gobjs->SetUIstate(2);
			}
		}
		else if (currentMonster == 3)
		{
			Cleric* _Gobjs = new Cleric();
			_Gobjs->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::MiniBoss, _Gobjs);
			_Gobjs->SetState(GameObject::eState::Paused);
			Transform* tr = _Gobjs->GetComponent<Transform>();
			tr->SetPosition(Vector3(200.f, 0.f, -250.f));
			mBossGroup.push_back(_Gobjs);

			if (a == 0)
			{
				tr->SetPosition(Vector3(100.f, 0.f, -250.f));
				_Gobjs->SetUIstate(0);
			}
			else if (a == 1)
			{
				tr->SetPosition(Vector3(200.f, 0.f, -250.f));
				_Gobjs->SetUIstate(1);
			}
			else if (a == 2)
			{
				tr->SetPosition(Vector3(300.f, 0.f, -250.f));
				_Gobjs->SetUIstate(2);
			}
		}
		
	}
}
int jk::Stage2_MiniBoss::random(int a, int b)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distribution(a, b);
	int answer_random = distribution(gen);
	return answer_random;
}
bool jk::Stage2_MiniBoss::AreAllMiniBossDead(const std::vector<Mini_Boss*>& monsterGroup)
{
	for (const Mini_Boss* monster : monsterGroup)
	{
		if (!monster->_Die)
		{
			_MiniBoss_Dead = false;
			// 하나라도 살아있는 몬스터가 있으면 false 반환
			return _MiniBoss_Dead;
		}
	}
	// 모든 몬스터가 죽었다면 true 반환
	_MiniBoss_Dead = true;
	return _MiniBoss_Dead;
}