#include "Monster_warrior.h"
#include "Particle_DamageEffect.h"

namespace jk
{
	Monster_warrior::Monster_warrior()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}
	Monster_warrior::~Monster_warrior()
	{
	}


	void Monster_warrior::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_tr = GetComponent<Transform>();
		_pos = _tr->GetPosition();
		_first_place = _pos;


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Warrior\\Attack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Warrior\\Attack_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Warrior\\Dead", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Warrior\\Hit", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Warrior\\Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Warrior\\Walk", this);
		
		
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Warrior\\Attack", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Warrior\\Attack_Ready", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Warrior\\Dead", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Warrior\\Hit", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Warrior\\Idle", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Warrior\\Walk", this, 1);

		//bind ºÎºÐ
		at->CompleteEvent(L"WarriorAttack") = std::bind(&Monster_warrior::complete_attack, this);
		at->CompleteEvent(L"WarriorAttackR") = std::bind(&Monster_warrior::complete_attack, this);
		at->CompleteEvent(L"WarriorHit") = std::bind(&Monster_warrior::complete_attack, this);
		at->CompleteEvent(L"WarriorHitR") = std::bind(&Monster_warrior::complete_attack, this);

		at->PlayAnimation(L"WarriorIdle", true);


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

		{
			Hit_Box = new HitBox_Monster();
			Hit_Box->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Hitbox, Hit_Box);
			Hit_Box->SetState(eState::Paused);
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
			Hit_Particle = new GameObject();
			Particle_DamageEffect* mr = Hit_Particle->AddComponent<Particle_DamageEffect>(Vector3());
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, Hit_Particle);
			Hit_Particle->SetState(eState::Paused);
		}

		GameObject::Initialize();
	}
	void Monster_warrior::Update()
	{
		Transform* hp_tr = Player_Hp->GetComponent<Transform>();
		hp_tr->SetPosition(Vector3(_pos.x-(_MaxHp - _CurrenHp), _pos.y + 50, _pos.z - 1));
		hp_tr->SetScale(_CurrenHp, 10, 0);
		
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

		if (_hit_particle == true)
		{
			_particletime += Time::DeltaTime();
			if (_particletime > 0.5)
			{
				Hit_Particle->SetState(eState::Paused);
				_particletime = 0.f;
				_hit_particle = false;
			}
		}


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
		case jk::Monster_warrior::Monster_warrior_State::Idle:
			idle();
			break;

		case jk::Monster_warrior::Monster_warrior_State::Attack:
			attack();
			break;

		case jk::Monster_warrior::Monster_warrior_State::Attack_Ready:
			attack_ready();
			break;

		case jk::Monster_warrior::Monster_warrior_State::Dead:
			dead();
			break;

		case jk::Monster_warrior::Monster_warrior_State::Hit:
			hit();
			break;

		case jk::Monster_warrior::Monster_warrior_State::Walk:
			walk();
			break;

		case jk::Monster_warrior::Monster_warrior_State::WalkR:
			walk_R();
			break;
			
		case jk::Monster_warrior::Monster_warrior_State::WalkL:
			walk_L();
			break;		

		default:
			break;
		}

		_tr->SetPosition(_pos);
		GameObject::Update();
	}
	void Monster_warrior::LateUpdate()
	{
		Transform* HitBox_TR = Hit_Box->GetComponent<Transform>();
		if (_attack_Col == true)
		{
			Hit_Box->SetSize(Vector2(30.f, 60.f));
			Hit_Box->SetCenter(Vector3(100.f, 100.f, -250.f));
			Hit_Box->SetState(eState::Active);


			if (_attackdir == 1)
				HitBox_TR->SetPosition(Vector3(_pos.x + 30, _pos.y-5, _pos.z));
			else
				HitBox_TR->SetPosition(Vector3(_pos.x - 30, _pos.y-5, _pos.z));
		}
		else		
			Hit_Box->SetState(eState::Paused);
		
		if(_state== Monster_warrior_State::Dead)
			Hit_Box->SetState(eState::Paused);

		_collider->SetSize(Vector2(0.35f, 0.75f));
		_collider->SetCenter(Vector2(1.f, -6.5f));


		GameObject::LateUpdate();
	}
	void Monster_warrior::Render()
	{
		GameObject::Render();
	}


	void Monster_warrior::OnCollisionEnter(Collider2D* other)
	{	
		if (HitBox_Player* player = dynamic_cast<HitBox_Player*>(other->GetOwner()))
		{
			if (_state == Monster_warrior_State::Dead)
				return;

			Particle_DamageEffect* mr = Hit_Particle->GetComponent<Particle_DamageEffect>();
			if (!(_state == Monster_warrior_State::Attack || _state == Monster_warrior_State::Attack_Ready))
			{
				_state = Monster_warrior_State::Hit;
				if (mDir == 1)
				{
					at->PlayAnimation(L"WarriorHit", false);					
					_rigidbody->SetVelocity(Vector2(-70.f, 0.f));
					_tr->SetPosition(_pos);					
					Player_Hp->_HitOn = true;
					Player_Hp->SetHitDamage(10);
					_CurrenHp = _CurrenHp - 10;

					_Hit_Effect->_effect_animation = true;
					_Hit_Effect->SetDirection(1);
					_Hit_Effect->SetState(eState::Active);

					Hit_Particle->SetState(eState::Active);
					mr->SetPosition(_pos);
					mr->Setpos_siwtch(true);
					mr->SetDirection(1);
					_hit_particle = true;
				}
				if (mDir == -1)
				{
					at->PlayAnimation(L"WarriorHitR", false);				
					_rigidbody->SetVelocity(Vector2(70.f, 0.f));
					_tr->SetPosition(_pos);
					Player_Hp->_HitOn = true;
					Player_Hp->SetHitDamage(10);
					_CurrenHp = _CurrenHp - 10;

					_Hit_Effect->_effect_animation = true;
					_Hit_Effect->SetDirection(-1);
					_Hit_Effect->SetState(eState::Active);

					Hit_Particle->SetState(eState::Active);
					mr->SetPosition(_pos);
					mr->Setpos_siwtch(true);
					mr->SetDirection(-1);
					_hit_particle = true;
				}		
				if (_CurrenHp <= 0)
				{
					_state = Monster_warrior_State::Dead;
					_Hit_Effect->_effect_animation = true;
					if (mDir == 1)
					{
						at->PlayAnimation(L"WarriorDead", false);
						_Hit_Effect->SetDirection(1);
					}
					else
					{
						at->PlayAnimation(L"WarriorDeadR", false);
						_Hit_Effect->SetDirection(-1);
					}	
					_Death_Effect->SetState(eState::Active);
				}
			}

			if ((_state == Monster_warrior_State::Attack || _state == Monster_warrior_State::Attack_Ready))
			{		
				if (mDir == 1)
				{				
					_rigidbody->SetVelocity(Vector2(-70.f, 0.f));
					_tr->SetPosition(_pos);
					Player_Hp->_HitOn = true;
					Player_Hp->SetHitDamage(10);
					_CurrenHp = _CurrenHp - 10;

					_Hit_Effect->_effect_animation = true;
					_Hit_Effect->SetDirection(1);
					_Hit_Effect->SetState(eState::Active);

					Hit_Particle->SetState(eState::Active);
					mr->SetPosition(_pos);
					mr->Setpos_siwtch(true);
					mr->SetDirection(1);
					_hit_particle = true;
				}
				if (mDir == -1)
				{					
					_rigidbody->SetVelocity(Vector2(70.f, 0.f));
					_tr->SetPosition(_pos);
					Player_Hp->_HitOn = true;
					Player_Hp->SetHitDamage(10);
					_CurrenHp = _CurrenHp - 10;

					_Hit_Effect->_effect_animation = true;
					_Hit_Effect->SetDirection(-1);
					_Hit_Effect->SetState(eState::Active);

					Hit_Particle->SetState(eState::Active);
					mr->SetPosition(_pos);
					mr->Setpos_siwtch(true);
					mr->SetDirection(-1);
					_hit_particle = true;
				}
				if (_CurrenHp <= 0)
				{
					_state = Monster_warrior_State::Dead;
					_Hit_Effect->_effect_animation = true;
					if (mDir == 1)
					{
						at->PlayAnimation(L"WarriorDead", false);
						_Hit_Effect->SetDirection(1);
					}
					else
					{
						at->PlayAnimation(L"WarriorDeadR", false);
						_Hit_Effect->SetDirection(-1);
					}
					_Death_Effect->SetState(eState::Active);
				}
			}
		}

		if (Skul_head* player = dynamic_cast<Skul_head*>(other->GetOwner()))
		{
			if (_state == Monster_warrior_State::Dead)
				return;

			Particle_DamageEffect* mr = Hit_Particle->GetComponent<Particle_DamageEffect>();
			if (!(_state == Monster_warrior_State::Attack || _state == Monster_warrior_State::Attack_Ready))
			{
				if (player->_Head_Attack == false && _bulletcheck == 0)
				{
					if (player->_Ground_check == true)
						return;

					_state = Monster_warrior_State::Hit;
					if (mDir == 1)
					{
						at->PlayAnimation(L"WarriorHit", false);
						_rigidbody->SetVelocity(Vector2(-70.f, 0.f));
						_tr->SetPosition(_pos);
						Player_Hp->_HitOn = true;
						Player_Hp->SetHitDamage(25);
						_CurrenHp = _CurrenHp - 25;

						_Hit_Effect->_effect_animation = true;
						_Hit_Effect->SetDirection(1);
						_Hit_Effect->SetState(eState::Active);

						Hit_Particle->SetState(eState::Active);
						mr->SetPosition(_pos);
						mr->Setpos_siwtch(true);
						mr->SetDirection(1);
						_hit_particle = true;
					}
					if (mDir == -1)
					{
						at->PlayAnimation(L"WarriorHitR", false);
						_rigidbody->SetVelocity(Vector2(70.f, 0.f));
						_tr->SetPosition(_pos);
						_CurrenHp = _CurrenHp - 25;
						Player_Hp->_HitOn = true;
						Player_Hp->SetHitDamage(25);

						_Hit_Effect->_effect_animation = true;
						_Hit_Effect->SetDirection(-1);
						_Hit_Effect->SetState(eState::Active);

						Hit_Particle->SetState(eState::Active);
						mr->SetPosition(_pos);
						mr->Setpos_siwtch(true);
						mr->SetDirection(-1);
						_hit_particle = true;
					}
					if (_CurrenHp <= 0)
					{
						_state = Monster_warrior_State::Dead;
						_Hit_Effect->_effect_animation = true;
						if (mDir == 1)
						{
							at->PlayAnimation(L"WarriorDead", false);
							_Hit_Effect->SetDirection(1);
						}
						else
						{
							at->PlayAnimation(L"WarriorDeadR", false);
							_Hit_Effect->SetDirection(-1);
						}
					}
					_bulletcheck++;
				}
			}

			if ((_state == Monster_warrior_State::Attack || _state == Monster_warrior_State::Attack_Ready))
			{
				if (player->_Head_Attack == false && _bulletcheck == 0)
				{
					if (player->_Ground_check == true)
						return;

					_state = Monster_warrior_State::Hit;
					if (mDir == 1)
					{					
						_rigidbody->SetVelocity(Vector2(-70.f, 0.f));
						_tr->SetPosition(_pos);
						Player_Hp->_HitOn = true;
						Player_Hp->SetHitDamage(25);
						_CurrenHp = _CurrenHp - 25;

						_Hit_Effect->_effect_animation = true;
						_Hit_Effect->SetDirection(1);
						_Hit_Effect->SetState(eState::Active);

						Hit_Particle->SetState(eState::Active);
						mr->SetPosition(_pos);
						mr->Setpos_siwtch(true);
						mr->SetDirection(1);
						_hit_particle = true;
					}
					if (mDir == -1)
					{					
						_rigidbody->SetVelocity(Vector2(70.f, 0.f));
						_tr->SetPosition(_pos);
						_CurrenHp = _CurrenHp - 25;
						Player_Hp->_HitOn = true;
						Player_Hp->SetHitDamage(25);

						_Hit_Effect->_effect_animation = true;
						_Hit_Effect->SetDirection(-1);
						_Hit_Effect->SetState(eState::Active);

						Hit_Particle->SetState(eState::Active);
						mr->SetPosition(_pos);
						mr->Setpos_siwtch(true);
						mr->SetDirection(-1);
						_hit_particle = true;
					}
					if (_CurrenHp <= 0)
					{
						_state = Monster_warrior_State::Dead;
						_Hit_Effect->_effect_animation = true;
						if (mDir == 1)
						{
							at->PlayAnimation(L"WarriorDead", false);
							_Hit_Effect->SetDirection(1);
						}
						else
						{
							at->PlayAnimation(L"WarriorDeadR", false);
							_Hit_Effect->SetDirection(-1);
						}
					}
					_bulletcheck++;
				}
			}
		}
	}
	void Monster_warrior::OnCollisionStay(Collider2D* other)
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
	void Monster_warrior::OnCollisionExit(Collider2D* other)
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


	void Monster_warrior::idle()
	{
		if (_followskul == true)
		{
			_time += Time::DeltaTime();

			if (_time > 2.f)
			{
				if ((_distance >= 75 || _distance <= -75))
				{					
					_state = Monster_warrior_State::Walk;
					if (mDir == 1)
					{
						at->PlayAnimation(L"WarriorWalk", true);
					}
					else
					{
						at->PlayAnimation(L"WarriorWalkR", true);
					}					
				}
				if (_distance > -60 && _distance < 60)
				{
					_state = Monster_warrior_State::Attack_Ready;
					if (mDir == 1)
					{
						at->PlayAnimation(L"WarriorAttack_Ready", false);
						_attackdir = 1;
					}
					else
					{
						at->PlayAnimation(L"WarriorAttack_ReadyR", false);
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
					_state = Monster_warrior_State::WalkR;
					at->PlayAnimation(L"WarriorWalk", true);			
				}
				else if (_walkdir == -1)
				{
					_state = Monster_warrior_State::WalkL;
					at->PlayAnimation(L"WarriorWalkR", true);
				}
			}
		}
		if (_CurrenHp <= 0)
		{
			_state = Monster_warrior_State::Dead;
			if (mDir == 1)
				at->PlayAnimation(L"WarriorDead", false);
			else
				at->PlayAnimation(L"WarriorDeadR", false);
		}
	}

	void Monster_warrior::attack()
	{
		_attack_Col = true;
		if (_CurrenHp <= 0)
		{
			_state = Monster_warrior_State::Dead;
			if (mDir == 1)
				at->PlayAnimation(L"WarriorDead", false);
			else
				at->PlayAnimation(L"WarriorDeadR", false);
		}
	}

	void Monster_warrior::attack_ready()
	{
		_attacktime += Time::DeltaTime();
		if (_attacktime >= 1)
		{
			_state = Monster_warrior_State::Attack;
			if (_attackdir == 1)
			{
				at->PlayAnimation(L"WarriorAttack", true);	
				_rigidbody->SetVelocity(Vector2(100.f, 0.f));
			}
			else
			{
				at->PlayAnimation(L"WarriorAttackR", true);		
				_rigidbody->SetVelocity(Vector2(-100.f, 0.f));
			}
			_attacktime = 0;
		}
		if (_CurrenHp <= 0)
		{
			_state = Monster_warrior_State::Dead;
			if (mDir == 1)
				at->PlayAnimation(L"WarriorDead", false);
			else
				at->PlayAnimation(L"WarriorDeadR", false);
		}
	}

	void Monster_warrior::dead()
	{
		Hit_Particle->SetState(eState::Paused);
		_hit_particle = false;
		_particletime = 0.f;
	

		_Die = true;
	}

	void Monster_warrior::hit()
	{
		_attacktime += Time::DeltaTime();
		if (_attacktime >= 0.5)
		{
			_state = Monster_warrior_State::Idle;
			if (mDir == 1)
				at->PlayAnimation(L"WarriorIdle", true);
			else
				at->PlayAnimation(L"WarriorIdleR", true);
			_attacktime = 0;
		}
		if (_CurrenHp <= 0)
		{
			_state = Monster_warrior_State::Dead;
			if (mDir == 1)
				at->PlayAnimation(L"WarriorDead", false);
			else
				at->PlayAnimation(L"WarriorDeadR", false);
		}
	}

	void Monster_warrior::walk()
	{
		if (_distance > -50 && _distance <50)
		{
			_state = Monster_warrior_State::Attack_Ready;
			if (mDir == 1)
			{
				at->PlayAnimation(L"WarriorAttack_Ready", false);
				_attackdir = 1;
			}
			else
			{
				at->PlayAnimation(L"WarriorAttack_ReadyR", false);
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

	void Monster_warrior::walk_R()
	{
		if (_walkdistance > -100)
			_pos.x += 80.f * Time::DeltaTime();
		else
		{
			_state = Monster_warrior_State::Idle;
			at->PlayAnimation(L"WarriorIdle", true);
			_time = 0; _walkdir *= -1;
		}
	}

	void Monster_warrior::walk_L()
	{
		if (_walkdistance < 100)
			_pos.x -= 80.f * Time::DeltaTime();
		else
		{
			_state = Monster_warrior_State::Idle;
			at->PlayAnimation(L"WarriorIdleR", true);
			_time = 0; _walkdir *= -1;
		}
	}
	
	void Monster_warrior::complete_attack()
	{
		_attack_Col = false;
		_rigidbody->ClearVelocity();
		_state = Monster_warrior_State::Idle;
		if (mDir == 1)
			at->PlayAnimation(L"WarriorIdle", true);
		else
			at->PlayAnimation(L"WarriorIdleR", true);

		_time = 0;
	}
	void Monster_warrior::complete_hit()
	{
		_state = Monster_warrior_State::Idle;
		if (mDir == 1)
			at->PlayAnimation(L"WarriorIdle", true);
		else
			at->PlayAnimation(L"WarriorIdleR", true);

		_time = 0;
	}
}