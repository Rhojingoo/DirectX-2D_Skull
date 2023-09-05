#include "Monster_Hammer.h"

namespace jk
{
	Monster_Hammer::Monster_Hammer()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}
	Monster_Hammer::~Monster_Hammer()
	{
	}


	void Monster_Hammer::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(false);
		tr = GetComponent<Transform>();		
		_pos = tr->GetPosition();
		_first_place = _pos;		
		

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Hammer\\Attack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Hammer\\Attack_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Hammer\\Dead", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Hammer\\Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Hammer\\Tackle_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Hammer\\Tackle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Hammer\\Tackle_End", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Hammer\\Walk", this);

		
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Hammer\\Attack", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Hammer\\Attack_Ready", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Hammer\\Dead", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Hammer\\Idle", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Hammer\\Tackle_Ready", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Hammer\\Tackle", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Hammer\\Tackle_End", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Hammer\\Walk", this, 1);
		
		//bind ºÎºÐ
		at->CompleteEvent(L"HammerAttack") = std::bind(&Monster_Hammer::Complete_attack, this);
		at->CompleteEvent(L"HammerAttackR") = std::bind(&Monster_Hammer::Complete_attack, this);

		at->PlayAnimation(L"HammerIdle", true);

		{
			Hit_Box = new HitBox_Monster();
			Hit_Box->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Hitbox, Hit_Box);
			Hit_Box->SetState(eState::Active); 
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

		{
			Tackle_Flash = new Monster_Tackle_Flash_Effect();
			Tackle_Flash->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, Tackle_Flash);
			Effect_tr = Tackle_Flash->GetComponent<Transform>();
			Effect_tr->SetPosition(tr->GetPosition());
			Tackle_Flash->SetState(eState::Paused);			
		}

		{
			_Hammer_Effect = new Monster_Hammer_Effect();
			_Hammer_Effect->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, _Hammer_Effect);
			Transform* Attack_Effect_Tr = _Hammer_Effect->GetComponent<Transform>();
			Attack_Effect_Tr->SetPosition(tr->GetPosition());
			_Hammer_Effect->SetState(eState::Paused);
		}

		GameObject::Initialize();
	}
	void Monster_Hammer::Update()
	{
		Transform* hp_tr = Player_Hp->GetComponent<Transform>();
		hp_tr->SetPosition(Vector3(_pos.x - (_MaxHp - _CurrenHp), _pos.y + 50, _pos.z - 1));
		hp_tr->SetScale(_CurrenHp, 10, 0);
		{
			Transform* _Hit_Effect_TR = _Hit_Effect->GetComponent<Transform>();
			if (mDir == 1)
				_Hit_Effect_TR->SetPosition(Vector3(_pos.x + 25, _pos.y, _pos.z - 1));
			else
				_Hit_Effect_TR->SetPosition(Vector3(_pos.x - 25, _pos.y, _pos.z - 1));
		}
		{
			Transform* _Effect_TR = _Death_Effect->GetComponent<Transform>();
			_Effect_TR->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 1));
		}

		tr = GetComponent<Transform>();
		_pos = tr->GetPosition();
		_velocity = _rigidbody->GetVelocity();
		SetDirection();
		SetEffect_pos();

		switch (_state)
		{
		case jk::Monster_Hammer::Monster_Hammer_State::Idle:
			idle();
			break;

		case jk::Monster_Hammer::Monster_Hammer_State::Attack_Ready:
			attack_ready();
			break;

		case jk::Monster_Hammer::Monster_Hammer_State::Attack:
			attack();
			break;

		case jk::Monster_Hammer::Monster_Hammer_State::Dead:
			dead();
			break;

		case jk::Monster_Hammer::Monster_Hammer_State::Tackle_Ready:
			tackle_ready();
			break;

		case jk::Monster_Hammer::Monster_Hammer_State::Tackle:
			tackle();
			break;

		case jk::Monster_Hammer::Monster_Hammer_State::Tackle_End:
			tackle_end();
			break;

		case jk::Monster_Hammer::Monster_Hammer_State::Walk:
			walk();
			break;

		case jk::Monster_Hammer::Monster_Hammer_State::WalkR:
			walk_R();
			break;

		case jk::Monster_Hammer::Monster_Hammer_State::WalkL:
			walk_L();
			break;

		default:
			break;
		}

		tr->SetPosition(_pos);
		Effect_tr->SetPosition(_Effect_pos);
		GameObject::Update();
	}
	void Monster_Hammer::LateUpdate()
	{
		Transform* HitBox_TR = Hit_Box->GetComponent<Transform>();
		if (_attack_Col == true)
		{
			Hit_Box->SetSize(Vector2(100.f, 100.f));
			Hit_Box->SetCenter(Vector3(100.f, 100.f,-250.f));

			Hit_Box->SetState(eState::Active);
			if (_attackdir == 1)
				HitBox_TR->SetPosition(Vector3(_pos.x + 50, _pos.y, _pos.z));
			else
				HitBox_TR->SetPosition(Vector3(_pos.x - 50, _pos.y, _pos.z));
		}
		else
		{
			Hit_Box->SetState(eState::Paused);
		}


		_collider->SetSize(Vector2(0.65f, 0.75f));
		_collider->SetCenter(Vector2(1.f, -8.5f));
		GameObject::LateUpdate();
	}
	void Monster_Hammer::Render()
	{
		GameObject::Render();
	}


	void Monster_Hammer::OnCollisionEnter(Collider2D* other)
	{		
		if (Ground_and_Wall* mGround = dynamic_cast<Ground_and_Wall*>(other->GetOwner()))
		{			
			_rigidbody->ClearVelocity();
			Transform* Ground_TR = other->GetOwner()->GetComponent<Transform>();
			Vector3 wall_pos = Ground_TR->GetPosition();			

			_attacktime += Time::DeltaTime();
			if (_attacktime > 0.7f)
			{
				_state = Monster_Hammer_State::Idle;
				if (mDir == 1)
					at->PlayAnimation(L"HammerIdle", true);
				else
					at->PlayAnimation(L"HammerIdleR", true);

				_time = 0;
				_AttackCheck = 0;
				_attacktime = 0;
			}
		}
	
		
		if (HitBox_Player* player = dynamic_cast<HitBox_Player*>(other->GetOwner()))
		{
			if (!(_state == Monster_Hammer_State::Attack || _state == Monster_Hammer_State::Tackle))
			{
				if (mDir == 1)
				{		
					_rigidbody->SetVelocity(Vector2(-70.f, 0.f));

					_CurrenHp = _CurrenHp - 10;
					Player_Hp->_HitOn = true;
					Player_Hp->SetHitDamage(10);

					_Hit_Effect->_effect_animation = true;
					_Hit_Effect->SetDirection(1);
					_Hit_Effect->SetState(eState::Active);
				}
				if (mDir == -1)
				{
					_rigidbody->SetVelocity(Vector2(70.f, 0.f));

					_CurrenHp = _CurrenHp - 10;
					Player_Hp->_HitOn = true;
					Player_Hp->SetHitDamage(10);

					_Hit_Effect->_effect_animation = true;
					_Hit_Effect->SetDirection(-1);
					_Hit_Effect->SetState(eState::Active);
				}
				if (_CurrenHp <= 0)
				{
					_state = Monster_Hammer_State::Dead;
					_Hit_Effect->_effect_animation = true;
					if (_attackdir == 1)
					{
						at->PlayAnimation(L"HammerDead", false);
						_Hit_Effect->SetDirection(1);
					}
					else
					{
						at->PlayAnimation(L"HammerDeadR", false);
						_Hit_Effect->SetDirection(-1);
					}
					_Death_Effect->SetState(eState::Active);
				}
			}
		}

		if (Skul_head* player = dynamic_cast<Skul_head*>(other->GetOwner()))
		{
			if (!(_state == Monster_Hammer_State::Attack || _state == Monster_Hammer_State::Tackle))
			{
				if (player->_Head_Attack == false && _bulletcheck ==0)
				{

					if (player->_Ground_check == true)
						return;

					if (mDir == 1)
					{
						_rigidbody->SetVelocity(Vector2(-70.f, 0.f));

						_CurrenHp = _CurrenHp - 25;
						Player_Hp->_HitOn = true;
						Player_Hp->SetHitDamage(25);

						_Hit_Effect->_effect_animation = true;
						_Hit_Effect->SetDirection(1);
						_Hit_Effect->SetState(eState::Active);
					}
					if (mDir == -1)
					{
						_rigidbody->SetVelocity(Vector2(70.f, 0.f));

						_CurrenHp = _CurrenHp - 25;
						Player_Hp->_HitOn = true;
						Player_Hp->SetHitDamage(25);

						_Hit_Effect->_effect_animation = true;
						_Hit_Effect->SetDirection(-1);
						_Hit_Effect->SetState(eState::Active);
					}
					if (_CurrenHp <= 0)
					{
						_state = Monster_Hammer_State::Dead;
						_Hit_Effect->_effect_animation = true;
						if (_attackdir == 1)
						{
							at->PlayAnimation(L"HammerDead", false);
							_Hit_Effect->SetDirection(1);
						}
						else
						{
							at->PlayAnimation(L"HammerDeadR", false);
							_Hit_Effect->SetDirection(-1);
						}
						_Death_Effect->SetState(eState::Active);
					}
					_bulletcheck++;

				}
			}
		}

		//HammerDead
	}
	void Monster_Hammer::OnCollisionStay(Collider2D* other)
	{
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{
			//if (mGround->_SkullOn == true)
			//	_followskul = true;
			//if (mGround->_SkullOn == false)
			//	_followskul = false;

			if (_Ground_check == false)
			{
				_rigidbody->SetGround(true);
				_Ground_check = true;
				_Ground_check = _rigidbody->GetGround();
				_rigidbody->ClearVelocity();
			}
			else
			{
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

		if (Sky_Ground* mGround = dynamic_cast<Sky_Ground*>(other->GetOwner()))
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
	void Monster_Hammer::OnCollisionExit(Collider2D* other)
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


	void Monster_Hammer::idle()
	{
		if (_followskul == true)
		{
			_time += Time::DeltaTime();
			if (_time > 1.5f)
			{
				if (_AttackCheck == 0)
				{
					if ((_distance >= 90 || _distance <= -90))
					{
						_state = Monster_Hammer_State::Walk;
						if (mDir == 1)
							at->PlayAnimation(L"HammerWalk", true);
						else
							at->PlayAnimation(L"HammerWalkR", true);
					}
					if (_distance > -80 && _distance < 80)
					{
						_state = Monster_Hammer_State::Attack_Ready;
						if (mDir == 1)
						{
							at->PlayAnimation(L"HammerAttack_Ready", false);
							_attackdir = 1;
						}
						else
						{
							at->PlayAnimation(L"HammerAttack_ReadyR", false);
							_attackdir = -1;
						}
					}
				}

				if (_AttackCheck == 1)
				{
					if ((_distance >= 125 || _distance <= -125))
					{
						_state = Monster_Hammer_State::Walk;
						if (mDir == 1)
							at->PlayAnimation(L"HammerWalk", true);
						else
							at->PlayAnimation(L"HammerWalkR", true);
					}
					else
					{
						_state = Monster_Hammer_State::Tackle_Ready;
						if (mDir == 1)
						{
							at->PlayAnimation(L"HammerTackle_Ready", true);
							_attackdir = 1;
						}
						else
						{
							at->PlayAnimation(L"HammerTackle_ReadyR", true);
							_attackdir = -1;
						}

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
					_state = Monster_Hammer_State::WalkR;
					at->PlayAnimation(L"HammerWalk", true);
				}
				else if (_walkdir == -1)
				{
					_state = Monster_Hammer_State::WalkL;
					at->PlayAnimation(L"HammerWalkR", true);
				}
			}
		}
	}

	void Monster_Hammer::attack_ready()
	{
		_attacktime += Time::DeltaTime();
		if (_attacktime > 1)
		{
			_state = Monster_Hammer_State::Attack;
			if (_attackdir == 1)			
				at->PlayAnimation(L"HammerAttack", true);				
			else			
				at->PlayAnimation(L"HammerAttackR", true);				
			_attacktime = 0;
		}
	}

	void Monster_Hammer::attack()
	{	
		_attack_Col = true;

		Transform* Attack_Effect_Tr = _Hammer_Effect->GetComponent<Transform>();
		if (_attackdir == 1)
			Attack_Effect_Tr->SetPosition(_pos.x + 30, _pos.y - 50, _pos.z - 1);
		else
			Attack_Effect_Tr->SetPosition(_pos.x - 30, _pos.y - 50, _pos.z - 1);
		_Hammer_Effect->SetState(eState::Active);
	}

	void Monster_Hammer::tackle_ready()
	{
		_attacktime += Time::DeltaTime();
		if (_attacktime > 2.f)
		{
			_state = Monster_Hammer_State::Tackle;
			if (_attackdir == 1)
			{
				at->PlayAnimation(L"HammerTackle", true);
				_rigidbody->SetVelocity(Vector2(350.f, 0.f));
				Tackle_Flash->_effect_animation = true;
				Tackle_Flash->SetDirection(1);				
			}
			else
			{
				at->PlayAnimation(L"HammerTackleR", true);
				_rigidbody->SetVelocity(Vector2(-350.f, 0.f));
				Tackle_Flash->_effect_animation = true;
				Tackle_Flash->SetDirection(-1);				
			}
			_attacktime = 0;	
			Tackle_Flash->SetState(eState::Active);
		}
	}

	void Monster_Hammer::tackle()
	{
		_rigidbody->ClearVelocityY();
		if (_attackdir == 1 && _velocity.x <= 285.0)
		{
			_state = Monster_Hammer_State::Tackle_End;
			at->PlayAnimation(L"HammerTackle_End", false);
			_rigidbody->ClearVelocityX();
			Tackle_Flash->SetState(eState::Paused);
		}
		else if (_attackdir == -1 && _velocity.x >= -285.0)
		{
			_state = Monster_Hammer_State::Tackle_End;
			at->PlayAnimation(L"HammerTackle_EndR", false);
			_rigidbody->ClearVelocityX();
			Tackle_Flash->SetState(eState::Paused);
		}		
	}

	void Monster_Hammer::tackle_end()
	{
		_attacktime += Time::DeltaTime();
		if (_attacktime > 0.7f)
		{
			_state = Monster_Hammer_State::Idle;
			if (mDir == 1)
				at->PlayAnimation(L"HammerIdle", true);
			else
				at->PlayAnimation(L"HammerIdleR", true);

			_time = 0;
			_AttackCheck = 0;
			_attacktime = 0;
		}
	}

	void Monster_Hammer::walk()
	{
		if (_distance >= 0.f)
			_pos.x += 150.f * Time::DeltaTime();
		else
			_pos.x -= 150.f * Time::DeltaTime();

		if (_AttackCheck == 0)
		{
			if (_distance > -80 && _distance < 80)
			{
				_state = Monster_Hammer_State::Attack_Ready;
				if (mDir == 1)
				{
					at->PlayAnimation(L"HammerAttack_Ready", false);
					_attackdir = 1;
				}
				else
				{
					at->PlayAnimation(L"HammerAttack_ReadyR", false);
					_attackdir = -1;
				}
			}
		}
		if (_AttackCheck == 1)
		{
			if ((_distance >= 125 || _distance <= -125))
			{
				_state = Monster_Hammer_State::Tackle_Ready;
				if (mDir == 1)
				{
					at->PlayAnimation(L"HammerTackle_Ready", true);
					_attackdir = 1;
				}
				else
				{
					at->PlayAnimation(L"HammerTackle_ReadyR", true);
					_attackdir = -1;
				}
			}
		}			
		tr->SetPosition(_pos);
	}

	void Monster_Hammer::walk_R()
	{
		if (_walkdistance > -100)
			_pos.x += 100.f * Time::DeltaTime();
		else
		{
			_state = Monster_Hammer_State::Idle;
			at->PlayAnimation(L"HammerIdle", true);
			_time = 0; _walkdir *= -1;
		}
	}

	void Monster_Hammer::walk_L()
	{
		if (_walkdistance < 100)
			_pos.x -= 100.f * Time::DeltaTime();
		else
		{
			_state = Monster_Hammer_State::Idle;
			at->PlayAnimation(L"HammerIdleR", true);
			_time = 0; _walkdir *= -1;
		}
	}

	void Monster_Hammer::dead()
	{
	}

	void Monster_Hammer::Complete_attack()
	{
		_attack_Col = false;

		if (_attack_Col == false)
			_state = Monster_Hammer_State::Idle;
		if (mDir == 1)
			at->PlayAnimation(L"HammerIdle", true);
		else
			at->PlayAnimation(L"HammerIdleR", true);
		_time = 0;

		_AttackCheck++;
	}

	void Monster_Hammer::SetDirection()
	{
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
	}

	void Monster_Hammer::SetEffect_pos()
	{
		if (_attackdir == 1)
		{
			_Effect_pos.x = _pos.x - 50;
			_Effect_pos.y = _pos.y;
			_Effect_pos.z = _pos.z - 1;
		}
		else
		{
			_Effect_pos.x = _pos.x + 50;
			_Effect_pos.y = _pos.y;
			_Effect_pos.z = _pos.z - 1;
		}
	}
}