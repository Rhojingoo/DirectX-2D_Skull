#include "Monster_BlossomEnt.h"


namespace jk
{
	int Monster_BlossomEnt::mDir = 1;
	bool Monster_BlossomEnt::_switch = false;

	Monster_BlossomEnt::Monster_BlossomEnt()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}

	Monster_BlossomEnt::~Monster_BlossomEnt()
	{
	}

	void Monster_BlossomEnt::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\BlossomEnt\\Attack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\BlossomEnt\\Attack_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\BlossomEnt\\Effect", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\BlossomEnt\\Hit", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\BlossomEnt\\Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\BlossomEnt\\Walk", this);

		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\BlossomEnt\\Attack", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\BlossomEnt\\Attack_Ready", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\BlossomEnt\\Effect", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\BlossomEnt\\Hit", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\BlossomEnt\\Idle", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\BlossomEnt\\Walk", this, 1);


		at->CompleteEvent(L"BlossomEntAttack_Ready") = std::bind(&Monster_BlossomEnt::attack_setting, this);
		at->CompleteEvent(L"BlossomEntAttack_ReadyR") = std::bind(&Monster_BlossomEnt::attack_setting, this);
		at->CompleteEvent(L"BlossomEntAttack") = std::bind(&Monster_BlossomEnt::attack_idle, this);
		at->CompleteEvent(L"BlossomEntAttackR") = std::bind(&Monster_BlossomEnt::attack_idle, this);

		_first_place = _pos;
		at->PlayAnimation(L"BlossomEntIdle", true);

		{
			Blossomeenct_Attack = new Monster_Blossomeenct_Attack;
			Blossomeenct_Attack->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Bullet, Blossomeenct_Attack);
			Transform* bullet_tr = Blossomeenct_Attack->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(_pos.x, _pos.y, -205));
			Blossomeenct_Attack->SetState(eState::Paused);
		}

		{
			Player_Hp = new Player_Hp_Bar;
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Monster, Player_Hp);
			Player_Hp->SetName(L"player_hp_bar");
			Transform* hp_tr = Player_Hp->GetComponent<Transform>();
			hp_tr->SetPosition(Vector3(_pos.x, _pos.y + 50, _pos.z - 1));
			hp_tr->SetScale(_MaxHp, 10, 0);
			Player_Hp->Set_Max_Hp(_MaxHp);
			Player_Hp->Set_Current_Hp(_MaxHp);
			Player_Hp->SetState(eState::Active);
		}
		;
		{
			_Hit_Effect = new Monster_Hit_Effect;
			_Hit_Effect->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, _Hit_Effect);
			_Hit_Effect->SetState(eState::Paused);
		}

		{
			_Death_Effect = new Monster_Death_Effect;
			_Death_Effect->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, _Death_Effect);
			_Death_Effect->SetState(eState::Paused);
		}

		GameObject::Initialize();
	}

	void Monster_BlossomEnt::Update()
	{
		tr = GetComponent<Transform>();
		_pos = tr->GetPosition();
		_velocity = _rigidbody->GetVelocity();
		_walkdistance = _first_place.x - _pos.x;
		if (_walkdistance >= 0.f)
			_walkdir = 1;
		else
			_walkdir = -1;

		_distance = _playerpos.x - _pos.x;
		if (_distance >= 0.f)
			mDir = 1;
		else
			mDir = -1;

		Transform* hp_tr = Player_Hp->GetComponent<Transform>();
		hp_tr->SetPosition(Vector3(_pos.x - (_MaxHp - _CurrenHp), _pos.y + 50, _pos.z - 1));
		hp_tr->SetScale(_CurrenHp, 10, 0);

		if (_CurrenHp <= 0)
			this->SetState(eState::Paused);

		{
			Transform* _Hit_Effect_TR = _Hit_Effect->GetComponent<Transform>();
			if (mDir == 1)
				_Hit_Effect_TR->SetPosition(Vector3(_pos.x + 15, _pos.y, _pos.z - 1));
			else
				_Hit_Effect_TR->SetPosition(Vector3(_pos.x - 15, _pos.y, _pos.z - 1));
		}
		{
			Transform* _Effect_TR = _Death_Effect->GetComponent<Transform>();
			_Effect_TR->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 1));
		}



		switch (_state)
		{
		case Monster_BlossomEnt::Monster_BlossomEnt_State::Idle:
			idle();
			break;

		case Monster_BlossomEnt::Monster_BlossomEnt_State::Attack_Ready:
			attack_ready();
			break;

		case Monster_BlossomEnt::Monster_BlossomEnt_State::Attack:
			attack();
			break;

		case Monster_BlossomEnt::Monster_BlossomEnt_State::Dead:
			dead();
			break;

		case Monster_BlossomEnt::Monster_BlossomEnt_State::Hit:
			hit();
			break;

		case Monster_BlossomEnt::Monster_BlossomEnt_State::WalkR:
			walk_R();
			break;

		case Monster_BlossomEnt::Monster_BlossomEnt_State::WalkL:
			walk_L();
			break;

		default:
			break;
		}
		tr->SetPosition(_pos);
		GameObject::Update();
	}

	void Monster_BlossomEnt::LateUpdate()
	{
		_collider->SetSize(Vector2(0.35f, 0.8f));
		_collider->SetCenter(Vector2(1.f, -5.5f));
		GameObject::LateUpdate();
	}

	void Monster_BlossomEnt::Render()
	{
		GameObject::Render();
	}

	void Monster_BlossomEnt::OnCollisionEnter(Collider2D* other)
	{
		if (HitBox_Player* player = dynamic_cast<HitBox_Player*>(other->GetOwner()))
		{
			if (!(_state == Monster_BlossomEnt_State::Idle))
				return;

			if (!(_state == Monster_BlossomEnt_State::Attack || _state == Monster_BlossomEnt_State::Attack_Ready))
			{
				_state = Monster_BlossomEnt_State::Hit;
				if (mDir == 1)
				{
					at->PlayAnimation(L"BlossomEntHit", false);
					_rigidbody->SetVelocity(Vector2(-70.f, 0.f));
					tr->SetPosition(_pos);
					Player_Hp->_HitOn = true;
					Player_Hp->SetHitDamage(10);
					_CurrenHp = _CurrenHp - 10;

					_Hit_Effect->_effect_animation = true;
					_Hit_Effect->SetDirection(1);
					_Hit_Effect->SetState(eState::Active);
				}
				if (mDir == -1)
				{
					at->PlayAnimation(L"BlossomEntHitR", false);
					_rigidbody->SetVelocity(Vector2(70.f, 0.f));
					tr->SetPosition(_pos);
					Player_Hp->_HitOn = true;
					Player_Hp->SetHitDamage(10);
					_CurrenHp = _CurrenHp - 10;

					_Hit_Effect->_effect_animation = true;
					_Hit_Effect->SetDirection(1);
					_Hit_Effect->SetState(eState::Active);
				}
				if (_CurrenHp <= 0)
				{
					_state = Monster_BlossomEnt_State::Dead;
					_Hit_Effect->_effect_animation = true;
				}
			}
		}

		if (Skul_head* player = dynamic_cast<Skul_head*>(other->GetOwner()))
		{
			if (!(_state == Monster_BlossomEnt_State::Attack || _state == Monster_BlossomEnt_State::Attack_Ready))
			{
				if (player->_Head_Attack == false && _bulletcheck == 0)
				{
					if (player->_Ground_check == true)
						return;

					_state = Monster_BlossomEnt_State::Hit;
					if (mDir == 1)
					{
						at->PlayAnimation(L"BlossomEntHit", false);
						_rigidbody->SetVelocity(Vector2(-70.f, 0.f));
						tr->SetPosition(_pos);
						Player_Hp->_HitOn = true;
						Player_Hp->SetHitDamage(25);
						_CurrenHp = _CurrenHp - 25;

						_Hit_Effect->_effect_animation = true;
						_Hit_Effect->SetDirection(1);
						_Hit_Effect->SetState(eState::Active);
					}
					if (mDir == -1)
					{
						at->PlayAnimation(L"BlossomEntHitR", false);
						_rigidbody->SetVelocity(Vector2(70.f, 0.f));
						tr->SetPosition(_pos);
						_CurrenHp = _CurrenHp - 25;
						Player_Hp->_HitOn = true;
						Player_Hp->SetHitDamage(25);

						_Hit_Effect->_effect_animation = true;
						_Hit_Effect->SetDirection(-1);
						_Hit_Effect->SetState(eState::Active);
					}
					if (_CurrenHp <= 0)
					{
						_state = Monster_BlossomEnt_State::Dead;
						_Hit_Effect->_effect_animation = true;
					}
					_bulletcheck++;
				}
			}
		}
	}
	void Monster_BlossomEnt::OnCollisionStay(Collider2D* other)
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
			if (_Ground_check == false)
			{
				_rigidbody->SetGround(true);
				_Ground_check = true;
				_Ground_check = _rigidbody->GetGround();
				_rigidbody->ClearVelocity();
			}
		}

		if (Sky_Ground* mGround = dynamic_cast<Sky_Ground*>(other->GetOwner()))
		{
			if (_Ground_check == false)
			{
				_rigidbody->SetGround(true);
				_Ground_check = true;
				_Ground_check = _rigidbody->GetGround();
				_rigidbody->ClearVelocity();
			}
		}
	}
	void Monster_BlossomEnt::OnCollisionExit(Collider2D* other)
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
		if (Skul_head* player = dynamic_cast<Skul_head*>(other->GetOwner()))
		{
			_bulletcheck = 0;
		}
	}


	void Monster_BlossomEnt::idle()
	{

		_time += Time::DeltaTime();
		if (_time >2.f)
		{
			if (((_distance <= 100) && (_distance >= -100)))
			{
				_state = Monster_BlossomEnt_State::Attack_Ready;
				if (mDir == 1)
					at->PlayAnimation(L"BlossomEntAttack_Ready", true);
				else
					at->PlayAnimation(L"BlossomEntAttack_ReadyR", true);				
			}
			else
			{				
				if (_walkdir == 1)
				{
					_state = Monster_BlossomEnt_State::WalkR;
					at->PlayAnimation(L"BlossomEntWalk", true);
				}
				else if (_walkdir == -1)
				{
					_state = Monster_BlossomEnt_State::WalkL;
					at->PlayAnimation(L"BlossomEntWalkR", true);
				}				
			}
		}
	}

	void Monster_BlossomEnt::attack_ready()
	{
		_Attackset = 0;
	}

	void Monster_BlossomEnt::attack()
	{
		if (Blossomeenct_Attack->_bullet_Life == false)
		{
			_Attackset += Time::DeltaTime();
			if (_Attackset > 1)
			{
				_state = Monster_BlossomEnt_State::Idle;
				if (mDir == 1)
					at->PlayAnimation(L"BlossomEntIdle", true);
				else
					at->PlayAnimation(L"BlossomEntIdleR", true);
				_Attackset = 0;
				_time = 0;
			}
		}
	}

	void Monster_BlossomEnt::dead()
	{
	}
	void Monster_BlossomEnt::hit()
	{
		_Attackset += Time::DeltaTime();
		if (_Attackset >= 0.5)
		{
			_state = Monster_BlossomEnt_State::Idle;
			if (mDir == 1)
				at->PlayAnimation(L"BlossomEntIdle", true);
			else
				at->PlayAnimation(L"BlossomEntIdleR", true);
			_Attackset = 0;
			_time = 0;
		}
	}
	void Monster_BlossomEnt::walk_R()
	{
		if (_walkdistance > -100)
			_pos.x += 80.f * Time::DeltaTime();
		else
		{
			_state = Monster_BlossomEnt_State::Idle;
			at->PlayAnimation(L"BlossomEntIdle", true);
			_time = 0; _walkdir *= -1;
		}
	}

	void Monster_BlossomEnt::walk_L()
	{
		if (_walkdistance < 100)
			_pos.x -= 80.f * Time::DeltaTime();
		else
		{
			_state = Monster_BlossomEnt_State::Idle;
			at->PlayAnimation(L"BlossomEntIdleR", true);
			_time = 0; _walkdir *= -1;
		}
	}

	void Monster_BlossomEnt::attack_setting()
	{
		Blossomeenct_Attack->_bullet_animation = true;
		if (mDir == 1)
		{
			at->PlayAnimation(L"BlossomEntAttack", false);
			Blossomeenct_Attack->SetDirection(1);
		}
		else if (mDir == -1)
		{
			at->PlayAnimation(L"BlossomEntAttackR", false);
			Blossomeenct_Attack->SetDirection(-1);
		}
		Transform* bullet_tr = Blossomeenct_Attack->GetComponent<Transform>();
		bullet_tr->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 1));
		Blossomeenct_Attack->_bullet_Life = true;
		Blossomeenct_Attack->SetState(eState::Active);
		_state = Monster_BlossomEnt_State::Attack;		
	}

	void Monster_BlossomEnt::attack_idle()
	{

	}
}