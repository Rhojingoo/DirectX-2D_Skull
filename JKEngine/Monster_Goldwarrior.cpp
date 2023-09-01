#include "Monster_Goldwarrior.h"


namespace jk
{
	Monster_Goldwarrior::Monster_Goldwarrior()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}
	Monster_Goldwarrior::~Monster_Goldwarrior()
	{
	}


	void Monster_Goldwarrior::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_tr = GetComponent<Transform>();
		_pos = _tr->GetPosition();
		_first_place = _pos;


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Gold_Warrior\\Attack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Gold_Warrior\\Attack_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Gold_Warrior\\Dead", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Gold_Warrior\\Hit", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Gold_Warrior\\Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Gold_Warrior\\Walk", this);


		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Gold_Warrior\\Attack", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Gold_Warrior\\Attack_Ready", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Gold_Warrior\\Dead", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Gold_Warrior\\Hit", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Gold_Warrior\\Idle", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Gold_Warrior\\Walk", this, 1);

		//bind ºÎºÐ
		at->CompleteEvent(L"Gold_WarriorAttack") = std::bind(&Monster_Goldwarrior::complete_attack, this);
		at->CompleteEvent(L"Gold_WarriorAttackR") = std::bind(&Monster_Goldwarrior::complete_attack, this);
		at->CompleteEvent(L"Gold_WarriorHit") = std::bind(&Monster_Goldwarrior::complete_attack, this);
		at->CompleteEvent(L"Gold_WarriorHitR") = std::bind(&Monster_Goldwarrior::complete_attack, this);

		at->PlayAnimation(L"Gold_WarriorIdle", true);

		{
			Player_Hp = new Player_Hp_Bar;
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::UI, Player_Hp);
			Player_Hp->SetName(L"player_hp_bar");
			Transform* hp_tr = Player_Hp->GetComponent<Transform>();
			hp_tr->SetPosition(Vector3(_pos.x, _pos.y +50, _pos.z - 1));
			hp_tr->SetScale(_Hp, 10, 0);
			Player_Hp->Set_Max_Hp(_Hp);
			Player_Hp->SetState(eState::Active);
		}


		{
			Hit_Box = new HitBox_Monster();
			Hit_Box->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Hitbox, Hit_Box);
			Hit_Box->SetState(eState::Active);
		}

		GameObject::Initialize();
	}
	void Monster_Goldwarrior::Update()
	{
		Transform* hp_tr = Player_Hp->GetComponent<Transform>();
		hp_tr->SetPosition(Vector3(_pos.x, _pos.y + 50, _pos.z - 1));
		hp_tr->SetScale(_Hp, 10, 0);


		_tr = GetComponent<Transform>();
		_pos = _tr->GetPosition();
		_velocity = _rigidbody->GetVelocity();
		_distance = _playerpos.x - _pos.x;
		if (_distance >= 0.f)
			mDir = 1;
		else
			mDir = -1;

		_walkdistance = _first_place.x - _pos.x;
		if (_walkdistance >= 0.f)
			_walkdir = 1;
		else
			_walkdir = -1;


		switch (_state)
		{
		case jk::Monster_Goldwarrior::Monster_Goldwarrior_State::Idle:
			idle();
			break;

		case jk::Monster_Goldwarrior::Monster_Goldwarrior_State::Attack:
			attack();
			break;

		case jk::Monster_Goldwarrior::Monster_Goldwarrior_State::Attack_Ready:
			attack_ready();
			break;

		case jk::Monster_Goldwarrior::Monster_Goldwarrior_State::Dead:
			dead();
			break;

		case jk::Monster_Goldwarrior::Monster_Goldwarrior_State::Hit:
			hit();
			break;

		case jk::Monster_Goldwarrior::Monster_Goldwarrior_State::Walk:
			walk();
			break;

		case jk::Monster_Goldwarrior::Monster_Goldwarrior_State::WalkR:
			walk_R();
			break;

		case jk::Monster_Goldwarrior::Monster_Goldwarrior_State::WalkL:
			walk_L();
			break;

		default:
			break;
		}

		_tr->SetPosition(_pos);
		GameObject::Update();
	}
	void Monster_Goldwarrior::LateUpdate()
	{
		Transform* HitBox_TR = Hit_Box->GetComponent<Transform>();
		if (_attack_Col == true)
		{
			Hit_Box->SetSize(Vector2(30.f, 60.f));
			Hit_Box->SetCenter(Vector3(100.f, 100.f, -250.f));

			Hit_Box->SetState(eState::Active);
			if (_attackdir == 1)
				HitBox_TR->SetPosition(Vector3(_pos.x + 30, _pos.y - 5, _pos.z));
			else
				HitBox_TR->SetPosition(Vector3(_pos.x - 30, _pos.y - 5, _pos.z));
		}
		else
		{
			Hit_Box->SetState(eState::Paused);
		}

		_collider->SetSize(Vector2(0.35f, 0.75f));
		_collider->SetCenter(Vector2(1.f, -6.5f));


		GameObject::LateUpdate();
	}
	void Monster_Goldwarrior::Render()
	{
		GameObject::Render();
	}


	void Monster_Goldwarrior::OnCollisionEnter(Collider2D* other)
	{
		if (HitBox_Player* player = dynamic_cast<HitBox_Player*>(other->GetOwner()))
		{
			if (!(_state == Monster_Goldwarrior_State::Idle))
				return;

			if (!(_state == Monster_Goldwarrior_State::Attack || _state == Monster_Goldwarrior_State::Attack_Ready))
			{
				_state = Monster_Goldwarrior_State::Hit;
				if (mDir == 1)
				{
					at->PlayAnimation(L"Gold_WarriorHit", false);
					_rigidbody->SetVelocity(Vector2(-70.f, 0.f));
					_tr->SetPosition(_pos);
					_Hp = _Hp  - 10;
				}
				if (mDir == -1)
				{
					at->PlayAnimation(L"Gold_WarriorHitR", false);
					_rigidbody->SetVelocity(Vector2(70.f, 0.f));
					_tr->SetPosition(_pos);
					_Hp = _Hp - 10;
				}					
			}
		}
	}
	void Monster_Goldwarrior::OnCollisionStay(Collider2D* other)
	{
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{
			if (_Ground_check == false)
			{
				_rigidbody->SetGround(true);
				_Ground_check = true;
				_Ground_check = _rigidbody->GetGround();
				_rigidbody->ClearVelocity();
			}	
		}

		if (Ground_Map* mGround = dynamic_cast<Ground_Map*>(other->GetOwner()))
		{
			if (mGround->_SkullOn == true)
				_followskul = true;
			if (mGround->_SkullOn == false)
				_followskul = false;

			if (_Ground_check == false)
			{
				_rigidbody->SetGround(true);
				_Ground_check = true;
				_Ground_check = _rigidbody->GetGround();
				_rigidbody->ClearVelocity();
			}	
		}
	}
	void Monster_Goldwarrior::OnCollisionExit(Collider2D* other)
	{
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{
			_rigidbody->SetGround(false);
			_Ground_check = false;
		}
		if (Ground_Map* mGround = dynamic_cast<Ground_Map*>(other->GetOwner()))
		{
			_rigidbody->SetGround(false);
			_Ground_check = false;
		}
		if (Sky_Ground* mGround = dynamic_cast<Sky_Ground*>(other->GetOwner()))
		{
			_rigidbody->SetGround(false);
			_Ground_check = false;
		}
	}


	void Monster_Goldwarrior::idle()
	{

		if (_followskul == true)
		{
			_time += Time::DeltaTime();

			if (_time > 2.f)
			{
				if ((_distance >= 75 || _distance <= -75))
				{
					_state = Monster_Goldwarrior_State::Walk;
					if (mDir == 1)
					{
						at->PlayAnimation(L"Gold_WarriorWalk", true);
					}
					else
					{
						at->PlayAnimation(L"Gold_WarriorWalkR", true);
					}
				}
				if (_distance > -60 && _distance < 60)
				{
					_state = Monster_Goldwarrior_State::Attack_Ready;
					if (mDir == 1)
					{
						at->PlayAnimation(L"Gold_WarriorAttack_Ready", false);
						_attackdir = 1;
					}
					else
					{
						at->PlayAnimation(L"Gold_WarriorAttack_ReadyR", false);
						_attackdir = -1;
					}
				}
			}
		}
		else
		{
			_time += Time::DeltaTime();
			if (_time > 3.f)
			{
				if (_walkdir == 1)
				{
					_state = Monster_Goldwarrior_State::WalkR;
					at->PlayAnimation(L"Gold_WarriorWalk", true);
				}
				else if (_walkdir == -1)
				{
					_state = Monster_Goldwarrior_State::WalkL;
					at->PlayAnimation(L"Gold_WarriorWalkR", true);
				}
			}
		}
	}

	void Monster_Goldwarrior::attack()
	{
		_attack_Col = true;
	}

	void Monster_Goldwarrior::attack_ready()
	{
		_attacktime += Time::DeltaTime();
		if (_attacktime >= 1)
		{
			_state = Monster_Goldwarrior_State::Attack;
			if (_attackdir == 1)
			{
				at->PlayAnimation(L"Gold_WarriorAttack", true);
				_rigidbody->SetVelocity(Vector2(100.f, 0.f));
			}
			else
			{
				at->PlayAnimation(L"Gold_WarriorAttackR", true);
				_rigidbody->SetVelocity(Vector2(-100.f, 0.f));
			}
			_attacktime = 0;
		}
	}

	void Monster_Goldwarrior::dead()
	{
	}


	void Monster_Goldwarrior::hit()
	{
		_attacktime += Time::DeltaTime();
		if (_attacktime >= 0.5)
		{
			_state = Monster_Goldwarrior_State::Idle;
			if (mDir == 1)
				at->PlayAnimation(L"Gold_WarriorIdle", true);
			else
				at->PlayAnimation(L"Gold_WarriorIdleR", true);
			_attacktime = 0;
		}
	}

	void Monster_Goldwarrior::walk()
	{
		if (_distance > -50 && _distance < 50)
		{
			_state = Monster_Goldwarrior_State::Attack_Ready;
			if (mDir == 1)
			{
				at->PlayAnimation(L"Gold_WarriorAttack_Ready", false);
				_attackdir = 1;
			}
			else
			{
				at->PlayAnimation(L"Gold_WarriorAttack_ReadyR", false);
				_attackdir = -1;
			}
		}
		else
		{
			if (_distance >= 0.f)
				_pos.x += 150.f * Time::DeltaTime();
			else
				_pos.x -= 150.f * Time::DeltaTime();
			_tr->SetPosition(_pos);
		}
	}

	void Monster_Goldwarrior::walk_R()
	{
		if (_walkdistance > -100)
			_pos.x += 80.f * Time::DeltaTime();
		else
		{
			_state = Monster_Goldwarrior_State::Idle;
			at->PlayAnimation(L"Gold_WarriorIdle", true);
			_time = 0; _walkdir *= -1;
		}
	}

	void Monster_Goldwarrior::walk_L()
	{
		if (_walkdistance < 100)
			_pos.x -= 80.f * Time::DeltaTime();
		else
		{
			_state = Monster_Goldwarrior_State::Idle;
			at->PlayAnimation(L"Gold_WarriorIdleR", true);
			_time = 0; _walkdir *= -1;
		}
	}

	void Monster_Goldwarrior::complete_attack()
	{
		_attack_Col = false;
		_rigidbody->ClearVelocity();
		_state = Monster_Goldwarrior_State::Idle;
		if (mDir == 1)
			at->PlayAnimation(L"Gold_WarriorIdle", true);
		else
			at->PlayAnimation(L"Gold_WarriorIdleR", true);

		_time = 0;
	}
	void Monster_Goldwarrior::complete_hit()
	{
		_state = Monster_Goldwarrior_State::Idle;
		if (mDir == 1)
			at->PlayAnimation(L"Gold_WarriorIdle", true);
		else
			at->PlayAnimation(L"Gold_WarriorIdleR", true);

		_time = 0;
	}
}