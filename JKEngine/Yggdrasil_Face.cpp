#include "Yggdrasil_Face.h"

namespace jk
{
	bool Yggdrasil_Face::_BulletReady =  false;
	bool Yggdrasil_Face::_Firstbullet = false;

	Vector3 Yggdrasil_Face::_pos = Vector3(0.f, 0.f, 0.f);;
	Yggdrasil_Face::Yggdrasil_Face()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}
	Yggdrasil_Face::~Yggdrasil_Face()
	{
	}


	void Yggdrasil_Face::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
	
		Yggdrasil_pos = Yggdrasil::GetPos();
		_pos = Vector3(Yggdrasil_pos.x, Yggdrasil_pos.y + 50.f, -197.f);
		tr = GetComponent<Transform>();		
		tr->SetPosition(_pos);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Face\\YggdrasilFace_Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Face\\YggdrasilFace_groggy", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Face\\YggdrasilFace_Change", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Face\\YggdrasilFace_Die", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Face\\YggdrasilFace_Dies", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Face\\YggdrasilFace_Die_Set", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Face\\YggdrasilFace_Die_Effect", this);
		
		//bind 부분
		//at->CompleteEvent(L"ArcherAttack_A") = std::bind(&Archer::choicecombo, this);
		//at->CompleteEvent(L"ArcherAttack_B") = std::bind(&Archer::choicecombo, this);
		//at->CompleteEvent(L"ArcherAttack_C") = std::bind(&Archer::choicecombo, this);
		{
			Energy_Bomb = new Yggdrasil_Energy_Bomb;
			Energy_Bomb->Initialize();			
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Bullet, Energy_Bomb);
			Transform* bullet_tr = Energy_Bomb->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(_pos.x, _pos.y, -205));
			basic_save_pos = Vector3(_pos.x + 10, _pos.y, -205);
			Energy_Bomb->SetState(eState::Paused);
		}

		for (int i = 0; i < 8; i++)
		{
			Bullet[i] = new Yggdrasil_BasicBullet;
			Bullet[i]->Initialize();		
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Bullet, Bullet[i]);
			Transform* bullet_tr = Bullet[i]->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(_pos.x, _pos.y, -205));
			bullet_tr->SetScale(Vector3(35.f, 36.f, 0.f));
			Bullet[i]->SetState(eState::Paused);
		}
		
		for (int i = 0; i < 15; i++)
		{
			Energy_Corps[i] = new Yggdrsil_Energy_Corps;
			Energy_Corps[i]->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Bullet, Energy_Corps[i]);
			Transform* bullet_tr = Energy_Corps[i]->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(random(-250, 250), random(_pos.y, _pos.y + 100), -206.f));
			Energy_Corps[i]->SetState(eState::Paused);
		}
	
		{
			Yggdrasil_effect = new Yggdrasil_Effect;
			Yggdrasil_effect->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, Yggdrasil_effect);
			Transform* bullet_tr = Yggdrasil_effect->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(_pos.x, _pos.y + 30, _pos.z - 1));
			Yggdrasil_effect->SetState(eState::Paused); 
		}
		{
			
			EnergyCorps_Spark = new Yggdrasil_EnergyCorps_Spark;
			EnergyCorps_Spark->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, EnergyCorps_Spark);
			Transform* bullet_tr = EnergyCorps_Spark->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(_pos.x, _pos.y + 30, _pos.z - 1));
			EnergyCorps_Spark->SetState(eState::Paused);
		}
		{
			Groggy_impact = new Yggdrasil_Groggy_GroundEffect;
			Groggy_impact->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, Groggy_impact);
			Transform* bullet_tr = Groggy_impact->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(_pos.x, _pos.y + 30, _pos.z - 1));
			Groggy_impact->SetState(eState::Paused);
		}
		{
			EnergyCorps_Charging = new Yggdrasil_EnergyCorps_Charging;
			EnergyCorps_Charging->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, EnergyCorps_Charging);
			Transform* bullet_tr = EnergyCorps_Charging->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(_pos.x, _pos.y + 30, _pos.z - 1));
			EnergyCorps_Charging->SetState(eState::Paused);
		}
		for (int i = 0; i < 15; i++)
		{
			Groggy_Begin_Efeect[i] = new Yggdrasil_EnergeBall_CreateEffect;
			Groggy_Begin_Efeect[i]->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Bullet, Groggy_Begin_Efeect[i]);
			Transform* bullet_tr = Groggy_Begin_Efeect[i]->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(random(-250, 250), random(_pos.y, _pos.y + 100), -206.f));
			Groggy_Begin_Efeect[i]->SetState(eState::Paused);
		}
		{
			Groggy_Start = new Yggdraisl_Groggy_StartImpact;
			Groggy_Start->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, Groggy_Start);
			Transform* bullet_tr = Groggy_Start->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(_pos.x, _pos.y + 30, _pos.z - 1));
			Groggy_Start->SetState(eState::Paused);
		}
		{
			_Dead_Effect = new Yggdrasil_FaceDead_Effect;
			_Dead_Effect->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, _Dead_Effect);
			Transform* bullet_tr = _Dead_Effect->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 1));
			_Dead_Effect->SetState(eState::Paused);
		}




		at->PlayAnimation(L"FaceYggdrasilFace_Idle", true);
		if (_Changeon == true)
			at->PlayAnimation(L"FaceYggdrasilFace_Change", true);

		GameObject::Initialize();
	}
	void Yggdrasil_Face::Update()
	{
		_playerpos;
		Yggdrasil_rotation = GetRotations();
		Yggdrasil_pos = Yggdrasil::GetPos();
		Facepos_Setting();
					

		_distance = _playerpos.x - _pos.x;
		if (_distance >= 0.f)
			mDir = 1;
		else
			mDir = -1;


		switch (_state)
		{
		case jk::Yggdrasil::Yggdrasil_State::Idle:
			Yggdrasil_Face::idle();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Set:
			Yggdrasil_Face::attack_a_set();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Ready:
			Yggdrasil_Face::attack_a_ready();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Right:
			Yggdrasil_Face::attack_a_right();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Loading:
			Yggdrasil_Face::attack_a_loading();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Finish:
			Yggdrasil_Face::attack_a_finish();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B_Set:
			Yggdrasil_Face::attack_b_set();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B_Ready:
			Yggdrasil_Face::attack_b_ready();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B_Right:
			Yggdrasil_Face::attack_b_right();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B_Left:
			Yggdrasil_Face::attack_b_left();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B_Finish:
			Yggdrasil_Face::attack_b_finish();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C_Set:
			Yggdrasil_Face::attack_c_set();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C_Ready:
			Yggdrasil_Face::attack_c_ready();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C_UP:
			Yggdrasil_Face::attack_c_up();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C:
			Yggdrasil_Face::attack_c();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C_Down:
			Yggdrasil_Face::attack_c_down();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C_Finish:
			Yggdrasil_Face::attack_c_finish();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Groggy_Start:
			Yggdrasil_Face::groggy_start();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Groggy_End:
			Yggdrasil_Face::groggy_end();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Intro_Set_Right:
			Yggdrasil_Face::intro_set_right();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Intro_Set_Left:
			Yggdrasil_Face::intro_set_left();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Intro_Ready:
			Yggdrasil_Face::intro_ready();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Intro:
			Yggdrasil_Face::intro();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Intro_End:
			Yggdrasil_Face::intro_end();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Change_Set:
			Yggdrasil_Face::change_set();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Change_Ready:
			Yggdrasil_Face::change_ready();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Change:
			Yggdrasil_Face::change();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Change_End:
			Yggdrasil_Face::change_end();
			break;

		case jk::Yggdrasil::Yggdrasil_State::DieSet:
			Yggdrasil_Face::die_set();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Die_Waiting:
			Yggdrasil_Face::die_waiting();
			break;

		case jk::Yggdrasil::Yggdrasil_State::DieReady:
			Yggdrasil_Face::die_ready();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Die:
			Yggdrasil_Face::die();
			break;

		default:
			break;
		}


		tr->SetPosition(_pos);
		tr->SetRotation(Yggdrasil_rotation);
		GameObject::Update();
	}


	void Yggdrasil_Face::LateUpdate()
	{
		_collider->SetSize(Vector2(0.4f, 0.75f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Yggdrasil_Face::Render()
	{
		GameObject::Render();
	}


	void Yggdrasil_Face::OnCollisionEnter(Collider2D* other)
	{
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{
			if (_state == Yggdrasil_State::Groggy_Start || _state == Yggdrasil_State::Groggy_End)
			{
				Transform* bullet_tr = Groggy_impact->GetComponent<Transform>();
				bullet_tr->SetPosition(Vector3(_pos.x, _pos.y - 50, _pos.z - 1));
				Groggy_impact->SetState(eState::Active);
			}
		}

		if (HitBox_Player* player = dynamic_cast<HitBox_Player*>(other->GetOwner()))
		{
			bool attack = false;
			bool attack_Cri_Mid = false;
			bool attack_Cri_High = false;

			_HitType = random(1, 6);
			if (_HitType >= 1 && _HitType < 6)
			{
				_Dammege = 3000;
				attack = true;
			}
			//if (_HitType >= 6 && _HitType < 9)
			//{
			//	_Damage = random(15, 25);
			//	attack_Cri_Mid = true;
			//}
			//if (_HitType >= 9 && _HitType <= 10)
			//{
			//	_Damage = random(30, 45);
			//	attack_Cri_High = true;
			//}

			{	
				_Hit_Effect->_effect_animation = true;
				_Critical_Middle->_effect_animation = true;
				_Critical_High->_effect_animation = true;
				if (mDir == 1)
				{
					Player_Hp->_HitOn = true;
					Player_Hp->SetHitDamage(_Dammege);
					_CurrenHp = _CurrenHp - _Dammege;
					_Hit_Effect->SetDirection(-1);
					_Critical_Middle->SetDirection(-1);
					_Critical_High->SetDirection(-1);
				}
				else
				{
					Player_Hp->_HitOn = true;
					Player_Hp->SetHitDamage(_Dammege);
					_CurrenHp = _CurrenHp - _Dammege;
					_Hit_Sword->SetDirection(1);
					_Critical_Middle->SetDirection(1);
					_Critical_High->SetDirection(1);
				}
				if (attack == true)
				{
					_Hit_Effect->_effect_animation = true;
					_Hit_Effect->SetState(eState::Active);
				}
				if (attack_Cri_Mid == true)
				{
					_Critical_Middle->_effect_animation = true;
					_Critical_Middle->SetState(eState::Active);
				}
				if (attack_Cri_High == true)
				{
					_Critical_High->_effect_animation = true;
					_Critical_High->SetState(eState::Active);
				}
			}	
			if (_CurrenHp <= 0)
			{
				if (_Diecheck == 0)
				{
					if (Yggdrasil::_FirstDie == false)
					{				
						Yggdrasil::_FirstDie = true;
						Yggdrasil::_Change = true;
						_Diecheck = 1;
					}
				}
				else if(_Diecheck ==1)
				{
					_DieON = true;
					Yggdrasil::_FirstDie = true;
				}
			}
		}

		if (Skul_head* player = dynamic_cast<Skul_head*>(other->GetOwner()))
		{
			bool attack = false;
			bool attack_Cri_Mid = false;
			bool attack_Cri_High = false;

			_HitType = random(1, 10);
			if (_HitType >= 1 && _HitType < 6)
			{
				_Dammege = 25;
				attack = true;
			}
			if (_HitType >= 6 && _HitType < 9)
			{
				_Dammege = random(35, 40);
				attack_Cri_Mid = true;
			}
			if (_HitType >= 9 && _HitType <= 10)
			{
				_Dammege = random(50, 70);
				attack_Cri_High = true;
			}

			{
				_Hit_Effect->_effect_animation = true;
				_Critical_Middle->_effect_animation = true;
				_Critical_High->_effect_animation = true;
				if (mDir == 1)
				{
					Player_Hp->_HitOn = true;
					Player_Hp->SetHitDamage(_Dammege);
					_CurrenHp = _CurrenHp - _Dammege;
					_Hit_Effect->SetDirection(-1);
					_Critical_Middle->SetDirection(-1);
					_Critical_High->SetDirection(-1);
				}
				else
				{
					Player_Hp->_HitOn = true;
					Player_Hp->SetHitDamage(_Dammege);
					_CurrenHp = _CurrenHp - _Dammege;
					_Hit_Sword->SetDirection(1);
					_Critical_Middle->SetDirection(1);
					_Critical_High->SetDirection(1);
				}
				if (attack == true)
				{
					_Hit_Effect->_effect_animation = true;
					_Hit_Effect->SetState(eState::Active);
				}
				if (attack_Cri_Mid == true)
				{
					_Critical_Middle->_effect_animation = true;
					_Critical_Middle->SetState(eState::Active);
				}
				if (attack_Cri_High == true)
				{
					_Critical_High->_effect_animation = true;
					_Critical_High->SetState(eState::Active);
				}
			}
			if (_CurrenHp <= 0)
			{
				if (_Diecheck == 0)
				{
					if (Yggdrasil::_FirstDie == false)
					{					
						Yggdrasil::_FirstDie = true;
						Yggdrasil::_Change = true;
						_Diecheck = 1;
					}
				}
				else if (_Diecheck == 1)
				{		
					_DieON = true;
					Yggdrasil::_FirstDie = true;
				}
			}
		}
	}
	void Yggdrasil_Face::OnCollisionStay(Collider2D* other)
	{
	}
	void Yggdrasil_Face::OnCollisionExit(Collider2D* other)
	{
	}


	void Yggdrasil_Face::idle()
	{
		at->PlayAnimation(L"FaceYggdrasilFace_Idle", true);
		if (_Changeon == true)
			at->PlayAnimation(L"FaceYggdrasilFace_Change", true);
	}


	void Yggdrasil_Face::attack_a_set()
	{
	}
	void Yggdrasil_Face::attack_a_ready()
	{
	}
	void Yggdrasil_Face::attack_a_right()
	{
	}
	void Yggdrasil_Face::attack_a_left()
	{
	}
	void Yggdrasil_Face::attack_a_loading()
	{
	}
	void Yggdrasil_Face::attack_a_finish()
	{
	}


	void Yggdrasil_Face::attack_b_set()
	{
	}
	void Yggdrasil_Face::attack_b_ready()
	{
	}
	void Yggdrasil_Face::attack_b_left()
	{
	}
	void Yggdrasil_Face::attack_b_right()
	{
	}
	void Yggdrasil_Face::attack_b_finish()
	{
	}


	void Yggdrasil_Face::attack_c_set()
	{
		if (_Firstbullet == false)
		{
			if (_pos.y >= -50.f)
				_pos.y -= 150 * Time::DeltaTime();
			else
			{
				_SetattackC_face = true; 
				_SetattackC_chin = true;
			}
		}
		set_basicbuulet();
	}
	void Yggdrasil_Face::attack_c_ready()
	{		
		if (_Firstbullet == false)
		{
			if (_Changeon == false)
			{
				Transform* bullet_tr = Yggdrasil_effect->GetComponent<Transform>();
				bullet_tr->SetPosition(Vector3(_pos.x + 5, _pos.y + 15, _pos.z - 1));
				Yggdrasil_effect->SetState(eState::Active);

				{
					_introtime += Time::DeltaTime();
					if (_introtime < 1.5)					
						_pos.x = UpdateVibration(_pos.x, 7, 10.f * 3.14, _introtime);					
					else
					{
						_pos.x = Yggdrasil_pos.x;
						Yggdrasil_Chin::_introchin = false;
						Yggdrasil_Chin::_introchinup = true;
						_introtime = 0;
					}
				}				
			}

			if (_Changeon == true)
			{
				Transform* bullet_tr = EnergyCorps_Charging->GetComponent<Transform>();
				bullet_tr->SetPosition(Vector3(_pos.x+5, _pos.y + 15, _pos.z - 1));
				EnergyCorps_Charging->SetState(eState::Active);
			}
		}
	}
	void Yggdrasil_Face::attack_c_up()
	{
		if (_pos.y <= 70.f)
			_pos.y += 250 * Time::DeltaTime();
		else
			_BulletReady = true;		
	}
	void Yggdrasil_Face::attack_c()
	{		
		if (_Changeon == false)
		{
			_time += Time::DeltaTime();
			if (_time <= 3.f)
			{
				for (int i = 0; i < 8; i++)
				{
					Bullet[i]->SetState(eState::Active);
				}
				if(_BulletReady == true)
				Energy_Bomb->SetState(eState::Active);
				if (Energy_Bomb->_effect_switch == false)
					Energy_Bomb->SetState(eState::Paused);
				basicattack();
				Energy_Bombattack();
			}
			else
			{
				if (_CurrenHp <= 0)
				{
					for (int i = 0; i < 8; i++)
					{
						Bullet[i]->SetState(eState::Paused);
						Bullet[i]->GetComponent<Transform>()->SetPosition(basic_save_pos);
					}
					{
						Energy_Bomb->SetState(eState::Paused);
						Energy_Bomb->GetComponent<Transform>()->SetPosition(basic_save_pos);
					}
				}

				_state = Yggdrasil_State::Attack_C_Down;
				Groggy_Start->_groggystartefeect_switch = true;
			}
		}

		// 체인지한뒤 에너지볼변경
		if (_Changeon == true)
		{
			static bool sparkPositionSet[15] = { false };
			_time += Time::DeltaTime();
			if (_time <= 15.f)
			{
				Transform* bullet_tr = EnergyCorps_Spark->GetComponent<Transform>();
				bullet_tr->SetPosition(Vector3(_pos.x, _pos.y + 30, _pos.z - 1));
				EnergyCorps_Spark->SetState(eState::Active);


				if (_time >= 1.f)
				{
					for (int i = 0; i < 5; i++)
					{
						if (_time >= (1.0f + 0.5f * i))
						{						
							Transform* bullet_tr = Energy_Corps[i]->GetComponent<Transform>();
							Transform* effect_tr = Groggy_Begin_Efeect[i]->GetComponent<Transform>();

							if (!sparkPositionSet[i]) // 위치가 설정되지 않았으면 설정
							{
								effect_tr->SetPosition(Vector3(bullet_tr->GetPosition().x, bullet_tr->GetPosition().y, bullet_tr->GetPosition().z - 2));
								sparkPositionSet[i] = true; // 위치 설정 완료								
							}
							Groggy_Begin_Efeect[i]->SetState(eState::Active);
							if (Groggy_Begin_Efeect[i]->_EffectOn == false)
								Groggy_Begin_Efeect[i]->SetState(eState::Paused);

							Energy_Corps[i]->SetState(eState::Active);
							Energy_Corpsattack();
							if(Energy_Corps[i]->_effect_switch == false)
								Energy_Corps[i]->SetState(eState::Paused);
						}
					}
				}
				if (_time >= 3.f)
				{
					for (int i = 5; i < 10; i++)
					{
						if (_time >= (3.0f + 0.5f * i))
						{							
							Transform* bullet_tr = Energy_Corps[i]->GetComponent<Transform>();
							Transform* effect_tr = Groggy_Begin_Efeect[i]->GetComponent<Transform>();

							if (!sparkPositionSet[i])
							{
								effect_tr->SetPosition(Vector3(bullet_tr->GetPosition().x, bullet_tr->GetPosition().y, bullet_tr->GetPosition().z - 2));
								sparkPositionSet[i] = true; 
							}

							Groggy_Begin_Efeect[i]->SetState(eState::Active);
							if (Groggy_Begin_Efeect[i]->_EffectOn == false)
								Groggy_Begin_Efeect[i]->SetState(eState::Paused);

							Energy_Corps[i]->SetState(eState::Active);
							Energy_Corpsattack();
							if (Energy_Corps[i]->_effect_switch == false)
								Energy_Corps[i]->SetState(eState::Paused);
						}
					}
				}
				if (_time >= 10.f)
				{
					for (int i = 10; i < 15; i++)
					{
						if (_time >= (6.0f + 0.5f * i))
						{							
							Transform* bullet_tr = Energy_Corps[i]->GetComponent<Transform>();
							Transform* effect_tr = Groggy_Begin_Efeect[i]->GetComponent<Transform>();

							if (!sparkPositionSet[i]) 
							{
								effect_tr->SetPosition(Vector3(bullet_tr->GetPosition().x, bullet_tr->GetPosition().y, bullet_tr->GetPosition().z - 2));
								sparkPositionSet[i] = true; 
							}

							Groggy_Begin_Efeect[i]->SetState(eState::Active);
							if (Groggy_Begin_Efeect[i]->_EffectOn == false)
								Groggy_Begin_Efeect[i]->SetState(eState::Paused);

							Energy_Corps[i]->SetState(eState::Active);
							Energy_Corpsattack();
							if (Energy_Corps[i]->_effect_switch == false)
								Energy_Corps[i]->SetState(eState::Paused);
						}
					}
				}
			}
			else
			{
				_state = Yggdrasil_State::Attack_C_Down;
				EnergyCorps_Spark->SetState(eState::Paused);
				_EnergyCorps_Spark_off = false;
			}
		}
	}
	void Yggdrasil_Face::attack_c_down()
	{
		if (_Changeon == false)
		{
			if (_NumberofAttack >= 2)
			{
				if (Groggy_Start->_groggystartefeect_switch == true)
				{
					for (int i = 0; i < 8; i++)
					{
						Bullet[i]->SetState(eState::Paused);
						Bullet[i]->GetComponent<Transform>()->SetPosition(basic_save_pos);
					}
					{
						Energy_Bomb->SetState(eState::Paused);
						Energy_Bomb->GetComponent<Transform>()->SetPosition(basic_save_pos);
					}

					Transform* bullet_tr = Groggy_Start->GetComponent<Transform>();
					bullet_tr->SetPosition(Vector3(_pos.x, _pos.y + 30, _pos.z - 1));
					Groggy_Start->SetState(eState::Active);
					at->PlayAnimation(L"FaceYggdrasilFace_groggy", true);
				}
				else
				{
					//_state = Yggdrasil_State::Attack_C_Finish;
					//_NumberofAttack = 0;
					Energy_Bomb->_effect_switch = true;
					_Groggy_Bulletready = true;

				}
			}
			else
			{
				if (_CurrenHp <= 0)
				{
					for (int i = 0; i < 8; i++)
					{
						Bullet[i]->SetState(eState::Paused);
						Bullet[i]->GetComponent<Transform>()->SetPosition(basic_save_pos);
					}
					{
						Energy_Bomb->SetState(eState::Paused);
						Energy_Bomb->GetComponent<Transform>()->SetPosition(basic_save_pos);
					}
				}

				if (_pos.y > 50)
				{
					_pos.y -= 150 * Time::DeltaTime();
					_BulletReady = false;
				}
				else
				{
					for (int i = 0; i < 8; i++)
					{
						Bullet[i]->SetState(eState::Paused);
						Bullet[i]->GetComponent<Transform>()->SetPosition(basic_save_pos);
					}
					{
						Energy_Bomb->SetState(eState::Paused);
						Energy_Bomb->GetComponent<Transform>()->SetPosition(basic_save_pos);
					}
					{
						_time = 0;
						_Firstbullet = true;
						_BulletReady = false;
						Energy_Bomb->_effect_switch = true;
						_AttackC_Face = true;
						//_state = Yggdrasil_State::Attack_C_Ready;					
					}					
				}
			}
		}
		else
		{
			if (_pos.y > 50)
			{
				_pos.y -= 150 * Time::DeltaTime();
				_BulletReady = false;
			}
			else
			{
				for (int i = 0; i < 15; i++)
				{
					Energy_Corps[i]->SetState(eState::Paused);
					Energy_Corps[i]->_effect_switch = true;
					Energy_Corps[i]->GetComponent<Transform>()->SetPosition(Vector3(random(-250, 250), random(_pos.y, _pos.y + 100), -205.f));
					if (Groggy_Begin_Efeect[i]->_EffectOn == false)
						Groggy_Begin_Efeect[i]->_EffectOn=true;
				}
				//if (_EnergyCorps_Spark_off == false)
				//{
				//	_state = Yggdrasil_State::Attack_C_Finish;
				//	_NumberofAttack = 0;
				//	_EnergyCorps_Spark_off = true;
				//}
				if (Groggy_Start->_groggystartefeect_switch == true)
				{
					Transform* bullet_tr = Groggy_Start->GetComponent<Transform>();
					bullet_tr->SetPosition(Vector3(_pos.x, _pos.y + 30, _pos.z - 1));
					Groggy_Start->SetState(eState::Active);
				}
				else
				{
					_state = Yggdrasil_State::Attack_C_Finish;
					_NumberofAttack = 0;
					_EnergyCorps_Spark_off = true;
				}
			}
		}
	}
	void Yggdrasil_Face::attack_c_finish()
	{
		_time = 0;
		_NumberofAttack = 0;
		_Firstbullet = false;
		_AttackC_Finish = true;
		_BulletReady = false;
		_SetattackC_r = false;
		_SetattackC_l = false;
		_SetattackC_face = false;
		_SetattackC_chin = false;


		if (_AttackC_Finish == true)
			_state = Yggdrasil_State::Groggy_Start;
	}

	void Yggdrasil_Face::groggy_start()
	{
		groggy_down();
	}
	void Yggdrasil_Face::groggy_end()
	{
		groggy_up();
	}


	void Yggdrasil_Face::intro_set_right()
	{
	}
	void Yggdrasil_Face::intro_set_left()
	{
	}
	void Yggdrasil_Face::intro_ready()
	{
	}
	void Yggdrasil_Face::intro()
	{
		if (_Intro_Ready == false)
		{			
			_introtime += Time::DeltaTime();
			if (_introtime < 1.5)
			{
				_pos.x = UpdateVibration(_pos.x, 10, 10.f * 3.14, _introtime);
			}
			else
			{
				_pos.x = Yggdrasil_pos.x;
				Yggdrasil_Chin::_introchin = false;
				Yggdrasil_Chin::_introchinup = true;
			}
		}
	}
	void Yggdrasil_Face::intro_end()
	{
		_introtime = 0;
	}


	void Yggdrasil_Face::change_set()
	{
		if (_SetChange_face == false)
		{
			for (int i = 0; i < 8; i++)
			{
				Bullet[i]->SetState(eState::Paused);
				Bullet[i]->GetComponent<Transform>()->SetPosition(basic_save_pos);
			}
			{
				Energy_Bomb->SetState(eState::Paused);
				Energy_Bomb->GetComponent<Transform>()->SetPosition(basic_save_pos);
				Yggdrasil_effect->SetState(eState::Paused);
			}		


			_pos.x = 0;
			_pos.y = 50;
			_SetChange_face = true;
		}

		if (_Change ==true)
			_FaceSet_of_Change = true;
	}
	void Yggdrasil_Face::change_ready()
	{
	}
	void Yggdrasil_Face::change()
	{
		if (_Change_HandL == false && _Change_HandR == false)
		{			
			if (_Change_Face == false)
			{
				_introtime += Time::DeltaTime();
				if (_introtime < 1.5)
				{
					_pos.x = UpdateVibration(_pos.x, 10, 10.f * 3.14, _introtime);
				}
				else
				{					
					_Changeon = true;
					_pos.x = Yggdrasil_pos.x;
				}
			}
		}
		if (_Changeon == true)
		{
			at->PlayAnimation(L"FaceYggdrasilFace_Change", false);
			_Change_Face = true;
		}
	}
	void Yggdrasil_Face::change_end()
	{
		_FaceSet_of_Change = false;
	}


	void Yggdrasil_Face::die_set()
	{
		_pos.x = 0;
		_pos.y = 50;
		for (int i = 0; i < 15; i++)
		{
			Groggy_Begin_Efeect[i]->SetState(eState::Paused);
				Energy_Corps[i]->SetState(eState::Paused);
		}
		Transform* bullet_tr = _Dead_Effect->GetComponent<Transform>();
		bullet_tr->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 1));
		_Dead_Effect->SetState(eState::Active);
		at->PlayAnimation(L"FaceYggdrasilFace_Die_Set", false);		
		_Die_SetFace = true;
	}
	void Yggdrasil_Face::die_waiting()
	{
		at->PlayAnimation(L"FaceYggdrasilFace_Die", false);
		_Dead_Effect->SetState(eState::Paused);
		 _Die_Waiting_Face = true;
	}
	void Yggdrasil_Face::die_ready()
	{

		Die_DOWN();
		
	}
	void Yggdrasil_Face::die()
	{
	}


	void Yggdrasil_Face::basicattack()
	{
		for (int i = 0; i < 8; i++)
		{
			Transform* bullet_tr = Bullet[i]->GetComponent<Transform>();

			Vector3 bulletattack = bullet_tr->GetPosition();
			bulletattack.x += basic_pos[i].x * Time::DeltaTime();
			bulletattack.y += basic_pos[i].y * Time::DeltaTime();
			bullet_tr->SetPosition(Vector3(bulletattack.x, bulletattack.y, -205));
		}
	}
	void Yggdrasil_Face::set_basicbuulet()
	{
		basic_pos[0] = Vector2(0.f, 150.f);
		basic_pos[1] = Vector2(110.f, 110.f);
		basic_pos[2] = Vector2(150.f, 0.f);
		basic_pos[3] = Vector2(110.f, -110.f);
		basic_pos[4] = Vector2(0.f, -150.f);
		basic_pos[5] = Vector2(-110.f, -110.f);
		basic_pos[6] = Vector2(-150.f, 0.f);
		basic_pos[7] = Vector2(-110.f, 110.f);
	}
	void Yggdrasil_Face::Energy_Bombattack()
	{
		Transform* bullet_tr = Energy_Bomb->GetComponent<Transform>();
		RigidBody* bullet_Rb = Energy_Bomb->GetComponent<RigidBody>();
		_playerpos.x;
		_playerpos.y;		
		Vector2 attack_pos = Vector2(_playerpos.x, _playerpos.y);
		attack_pos.Normalize();
		bullet_Rb->SetGround(false);
		bullet_Rb->SetVelocity(Vector2(attack_pos.x * 300.f, attack_pos.y*400));
	}
	void Yggdrasil_Face::Energy_Corpsattack()
	{
		for (int i = 0; i < 15; i++)
		{						
			RigidBody* bullet_Rb = Energy_Corps[i]->GetComponent<RigidBody>();
			_playerpos.x;
			_playerpos.y;
			Vector2 attack_pos = Vector2(_playerpos.x, _playerpos.y);
			attack_pos.Normalize();
			bullet_Rb->SetGround(false);
			bullet_Rb->SetVelocity(Vector2(attack_pos.x * 50.f, attack_pos.y * 250));
		}
	}


	void Yggdrasil_Face::groggy_down()
	{
		if (_Groggy_Face_Down == false)
		{
			if (_pos.y >= -100.f)
				_pos.y -= 50 * Time::DeltaTime();
			if (_pos.x >= -40.f)
				_pos.x -= 35 * Time::DeltaTime();
			if ((_pos.y < -100.f) && (_pos.x < -40.f))
				_Groggy_Face_Down = true;
		}
	}
	void Yggdrasil_Face::groggy_up()
	{
		if (_Groggy_Face_Up == false)
		{
			at->PlayAnimation(L"FaceYggdrasilFace_Idle", true);
			if (_Changeon == true)
				at->PlayAnimation(L"FaceYggdrasilFace_Change", true);
			if (_pos.y <= 0.f)
				_pos.y += 50 * Time::DeltaTime();
			if (_pos.x <= 0.f)
				_pos.x += 35 * Time::DeltaTime();
			if ((_pos.y >= 0.f) && (_pos.x >= 0.f))
			{
				_pos.x = 0;
				_pos.y = 50;
				_Groggy_Face_Up = true;
			}
		}
	}


	void Yggdrasil_Face::Die_DOWN()
	{
		if (_Die_Face_Down == false)
		{
			if (_pos.y >= -100.f)
				_pos.y -= 50 * Time::DeltaTime();
			if (_pos.x >= -40.f)
				_pos.x -= 35 * Time::DeltaTime();
			if ((_pos.y < -100.f) && (_pos.x < -40.f))
				_Die_Face_Down = true;
		}
	}
	float Yggdrasil_Face::UpdateVibration(float originalX, float amplitude, float frequency, float timeElapsed)
	{
		return originalX + amplitude * std::sin(frequency * timeElapsed);
	}
	void Yggdrasil_Face::Facepos_Setting()
	{
		if (_Intro == false)
			_pos = Vector3(Yggdrasil_pos.x, Yggdrasil_pos.y + 50.f, -199.3f);
		if (_state == Yggdrasil_State::Idle)
			_pos = Vector3(Yggdrasil_pos.x, Yggdrasil_pos.y + 50.f, -201.f);
		if (_state == Yggdrasil_State::Change)
			_pos = Vector3(Yggdrasil_pos.x, Yggdrasil_pos.y + 50.f, -201.f);
		if (_state == Yggdrasil_State::Attack_C_Ready)
			_pos = Vector3(Yggdrasil_pos.x, _pos.y, -201.f);		
		if ((_state == Yggdrasil_State::Attack_B_Ready) || (_state == Yggdrasil_State::Attack_B_Right) || (_state == Yggdrasil_State::Attack_B_Left))
			_pos = Vector3(Yggdrasil_pos.x, Yggdrasil_pos.y+50, -201.f);
	}		
}
