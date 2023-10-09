#include "Monster_LionWarrior.h"
#include "Particle_DamageEffect.h"

namespace jk
{
	Monster_LionWarrior::Monster_LionWarrior()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}
	Monster_LionWarrior::~Monster_LionWarrior()
	{
	}


	void Monster_LionWarrior::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_tr = GetComponent<Transform>();
		_pos = _tr->GetPosition();
		_first_place = _pos;


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_Warrior\\Attack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_Warrior\\Attack_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_Warrior\\Dead", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_Warrior\\Hit", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_Warrior\\Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_Warrior\\Walk", this);


		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_Warrior\\Attack", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_Warrior\\Attack_Ready", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_Warrior\\Dead", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_Warrior\\Hit", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_Warrior\\Idle", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_Warrior\\Walk", this, 1);
		
		//bind 부분
		at->CompleteEvent(L"Lion_WarriorAttack") = std::bind(&Monster_LionWarrior::complete_attack, this);
		at->CompleteEvent(L"Lion_WarriorAttackR") = std::bind(&Monster_LionWarrior::complete_attack, this);
		at->CompleteEvent(L"Lion_WarriorHit") = std::bind(&Monster_LionWarrior::complete_hit, this);
		at->CompleteEvent(L"Lion_WarriorHitR") = std::bind(&Monster_LionWarrior::complete_hit, this);

		at->PlayAnimation(L"Lion_WarriorIdle", true);

		//체력관련
		{
			Hpbar_Frame = new HP_Frame(L"EnemyHealthBar_Frame");
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Monster, Hpbar_Frame);
			Hpbar_Frame->SetName(L"hp_bar_frame");
			Transform* hp_tr = Hpbar_Frame->GetComponent<Transform>();
			hp_tr->SetPosition(Vector3(_pos.x, _pos.y + 50, _pos.z - 1));
			hp_tr->SetScale(50, 5, 0);
			Hpbar_Frame->SetState(eState::Paused);
		}

		{
			Monster_DamegeHp = new Monster_Hp_Bar(L"EnemyHealthBar_Damage");
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Monster, Monster_DamegeHp);
			Monster_DamegeHp->SetName(L"warrior_hp_bar");
			Transform* hp_tr = Monster_DamegeHp->GetComponent<Transform>();
			hp_tr->SetPosition(Vector3(_pos.x, _pos.y + 50, _pos.z - 1.5));
			hp_tr->SetScale(48, 3, 0);
			Monster_DamegeHp->Set_Max_Hp(_MaxHp);
			Monster_DamegeHp->Set_Current_Hp(_MaxHp);
			Monster_DamegeHp->Set_Type(1);
			Monster_DamegeHp->SetState(eState::Paused);
		}

		{
			Monster_Hp = new Monster_Hp_Bar(L"EnemyHealthBar");
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Monster, Monster_Hp);
			Monster_Hp->SetName(L"warrior_hp_bar");
			Transform* hp_tr = Monster_Hp->GetComponent<Transform>();
			hp_tr->SetPosition(Vector3(_pos.x, _pos.y + 50, _pos.z - 1));
			hp_tr->SetScale(48, 3, 0);
			Monster_Hp->Set_Max_Hp(_MaxHp);
			Monster_Hp->Set_Current_Hp(_MaxHp);
			Monster_Hp->SetState(eState::Paused);
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
			Hit_Box = new HitBox_Monster();
			Hit_Box->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Hitbox, Hit_Box);
			Hit_Box->SetState(eState::Active);
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
	void Monster_LionWarrior::Update()
	{
		SetDirection();
		Particle_Control();
		Hpcontrol();
		Effect_Control();


		switch (_state)
		{
		case jk::Monster_LionWarrior::Monster_LionWarrior_State::Idle:
			idle();
			break;

		case jk::Monster_LionWarrior::Monster_LionWarrior_State::Attack:
			attack();
			break;

		case jk::Monster_LionWarrior::Monster_LionWarrior_State::Attack_Ready:
			attack_ready();
			break;

		case jk::Monster_LionWarrior::Monster_LionWarrior_State::Dead:
			dead();
			break;

		case jk::Monster_LionWarrior::Monster_LionWarrior_State::Hit:
			hit();
			break;

		case jk::Monster_LionWarrior::Monster_LionWarrior_State::Walk:
			walk();
			break;

		case jk::Monster_LionWarrior::Monster_LionWarrior_State::WalkR:
			walk_R();
			break;

		case jk::Monster_LionWarrior::Monster_LionWarrior_State::WalkL:
			walk_L();
			break;

		default:
			break;
		}

		_tr->SetPosition(_pos);
		GameObject::Update();
	}
	void Monster_LionWarrior::LateUpdate()
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
	void Monster_LionWarrior::Render()
	{
		GameObject::Render();
	}


	void Monster_LionWarrior::OnCollisionEnter(Collider2D* other)
	{
		if (HitBox_Player* player = dynamic_cast<HitBox_Player*>(other->GetOwner()))
		{
			if (_state == Monster_LionWarrior_State::Dead)
				return;

			_Damage = player->GetDamage();

			Particle_DamageEffect* mr = Hit_Particle->GetComponent<Particle_DamageEffect>();
			if (!(_state == Monster_LionWarrior_State::Attack || _state == Monster_LionWarrior_State::Attack_Ready))
			{
				_state = Monster_LionWarrior_State::Hit;
				if (mDir == 1)
				{
					at->PlayAnimation(L"Lion_WarriorHit", false);
					_rigidbody->SetVelocity(Vector2(-70.f, 0.f));
					Monster_Hp->_HitOn = true;
					_CurrenHp = _CurrenHp - _Damage;
					Monster_Hp->SetHitDamage(_Damage);
					Monster_DamegeHp->_HitOn = true;
					Monster_DamegeHp->Set_Target(_CurrenHp);
					_Hp_control = true;
					Hpbar_Frame->SetState(eState::Active);
					Monster_DamegeHp->SetState(eState::Active);
					Monster_Hp->SetState(eState::Active);

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
					at->PlayAnimation(L"Lion_WarriorHitR", false);
					_rigidbody->SetVelocity(Vector2(70.f, 0.f));
					Monster_Hp->_HitOn = true;
					_CurrenHp = _CurrenHp - _Damage;
					Monster_Hp->SetHitDamage(_Damage);
					Monster_DamegeHp->_HitOn = true;
					Monster_DamegeHp->Set_Target(_CurrenHp);
					_Hp_control = true;
					Hpbar_Frame->SetState(eState::Active);
					Monster_DamegeHp->SetState(eState::Active);
					Monster_Hp->SetState(eState::Active);

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
					_state = Monster_LionWarrior_State::Dead;
					_Hit_Effect->_effect_animation = true;
					if (mDir == 1)
					{
						at->PlayAnimation(L"Lion_WarriorDead", false);
						_Hit_Effect->SetDirection(1);
					}
					else
					{
						at->PlayAnimation(L"Lion_WarriorDeadR", false);
						_Hit_Effect->SetDirection(-1);
					}
					_Death_Effect->SetState(eState::Active);
				}
			}

			if ((_state == Monster_LionWarrior_State::Attack || _state == Monster_LionWarrior_State::Attack_Ready))
			{
				if (mDir == 1)
				{
					_rigidbody->SetVelocity(Vector2(-70.f, 0.f));
					Monster_Hp->_HitOn = true;
					_CurrenHp = _CurrenHp - _Damage;
					Monster_Hp->SetHitDamage(_Damage);
					Monster_DamegeHp->_HitOn = true;
					Monster_DamegeHp->Set_Target(_CurrenHp);
					_Hp_control = true;
					Hpbar_Frame->SetState(eState::Active);
					Monster_DamegeHp->SetState(eState::Active);
					Monster_Hp->SetState(eState::Active);

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
					Monster_Hp->_HitOn = true;
					_CurrenHp = _CurrenHp - _Damage;
					Monster_Hp->SetHitDamage(_Damage);
					Monster_DamegeHp->_HitOn = true;
					Monster_DamegeHp->Set_Target(_CurrenHp);
					_Hp_control = true;
					Hpbar_Frame->SetState(eState::Active);
					Monster_DamegeHp->SetState(eState::Active);
					Monster_Hp->SetState(eState::Active);

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
					_state = Monster_LionWarrior_State::Dead;
					_Hit_Effect->_effect_animation = true;
					if (mDir == 1)
					{
						at->PlayAnimation(L"Lion_WarriorDead", false);
						_Hit_Effect->SetDirection(1);
					}
					else
					{
						at->PlayAnimation(L"Lion_WarriorDeadR", false);
						_Hit_Effect->SetDirection(-1);
					}
					_Death_Effect->SetState(eState::Active);
				}
			}
		}

		if (Skul_head* player = dynamic_cast<Skul_head*>(other->GetOwner()))
		{
			if (_state == Monster_LionWarrior_State::Dead)
				return;

			_Damage = player->GetDamage();

			Particle_DamageEffect* mr = Hit_Particle->GetComponent<Particle_DamageEffect>();
			if (!(_state == Monster_LionWarrior_State::Attack || _state == Monster_LionWarrior_State::Attack_Ready))
			{
				Particle_DamageEffect* mr = Hit_Particle->GetComponent<Particle_DamageEffect>();
				if (player->_Head_Attack == false && _bulletcheck == 0)
				{
					if (player->_Ground_check == true)
						return;

					_state = Monster_LionWarrior_State::Hit;
					if (mDir == 1)
					{
						at->PlayAnimation(L"Lion_WarriorHit", false);
						_rigidbody->SetVelocity(Vector2(-70.f, 0.f));
						Monster_Hp->_HitOn = true;
						_CurrenHp = _CurrenHp - _Damage;
						Monster_Hp->SetHitDamage(_Damage);
						Monster_DamegeHp->_HitOn = true;
						Monster_DamegeHp->Set_Target(_CurrenHp);
						_Hp_control = true;
						Hpbar_Frame->SetState(eState::Active);
						Monster_DamegeHp->SetState(eState::Active);
						Monster_Hp->SetState(eState::Active);

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
						at->PlayAnimation(L"Lion_WarriorHitR", false);
						_rigidbody->SetVelocity(Vector2(70.f, 0.f));
						Monster_Hp->_HitOn = true;
						_CurrenHp = _CurrenHp - _Damage;
						Monster_Hp->SetHitDamage(_Damage);
						Monster_DamegeHp->_HitOn = true;
						Monster_DamegeHp->Set_Target(_CurrenHp);
						_Hp_control = true;
						Hpbar_Frame->SetState(eState::Active);
						Monster_DamegeHp->SetState(eState::Active);
						Monster_Hp->SetState(eState::Active);


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
						_state = Monster_LionWarrior_State::Dead;
						_Hit_Effect->_effect_animation = true;
						if (mDir == 1)
						{
							at->PlayAnimation(L"Lion_WarriorDead", false);
							_Hit_Effect->SetDirection(1);
						}
						else
						{
							at->PlayAnimation(L"Lion_WarriorDeadR", false);
							_Hit_Effect->SetDirection(-1);
						}
						_Death_Effect->SetState(eState::Active);
					}
					_bulletcheck++;
				}
			}

			if ((_state == Monster_LionWarrior_State::Attack || _state == Monster_LionWarrior_State::Attack_Ready))
			{
				Particle_DamageEffect* mr = Hit_Particle->GetComponent<Particle_DamageEffect>();
				if (player->_Head_Attack == false && _bulletcheck == 0)
				{
					if (player->_Ground_check == true)
						return;

					if (mDir == 1)
					{
						at->PlayAnimation(L"Lion_WarriorHit", false);
						_rigidbody->SetVelocity(Vector2(-70.f, 0.f));
						Monster_Hp->_HitOn = true;
						_CurrenHp = _CurrenHp - _Damage;
						Monster_Hp->SetHitDamage(_Damage);
						Monster_DamegeHp->_HitOn = true;
						Monster_DamegeHp->Set_Target(_CurrenHp);
						_Hp_control = true;
						Hpbar_Frame->SetState(eState::Active);
						Monster_DamegeHp->SetState(eState::Active);
						Monster_Hp->SetState(eState::Active);

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
						Monster_Hp->_HitOn = true;
						_CurrenHp = _CurrenHp - _Damage;
						Monster_Hp->SetHitDamage(_Damage);
						Monster_DamegeHp->_HitOn = true;
						Monster_DamegeHp->Set_Target(_CurrenHp);
						_Hp_control = true;
						Hpbar_Frame->SetState(eState::Active);
						Monster_DamegeHp->SetState(eState::Active);
						Monster_Hp->SetState(eState::Active);

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
						_state = Monster_LionWarrior_State::Dead;
						_Hit_Effect->_effect_animation = true;
						if (mDir == 1)
						{
							at->PlayAnimation(L"Lion_WarriorDead", false);
							_Hit_Effect->SetDirection(1);
						}
						else
						{
							at->PlayAnimation(L"Lion_WarriorDeadR", false);
							_Hit_Effect->SetDirection(-1);
						}
						_Death_Effect->SetState(eState::Active);
					}
					_bulletcheck++;
				}
			}
		}
	}
	void Monster_LionWarrior::OnCollisionStay(Collider2D* other)
	{
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{
			if (mGround->_SkullOn == true)
				_followskul = true;
			if (mGround->_SkullOn == false)
				_followskul = false;

			if (mGround->_SkullOn == true)
				_followWolf = true;
			if (mGround->_SkullOn == false)
				_followWolf = false;

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
	void Monster_LionWarrior::OnCollisionExit(Collider2D* other)
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


	void Monster_LionWarrior::idle()
	{

		if (_followskul == true)
		{
			_time += Time::DeltaTime();

			if (_time > 2.f)
			{
				if ((_distance >= 75 || _distance <= -75))
				{
					_state = Monster_LionWarrior_State::Walk;
					if (mDir == 1)
					{
						at->PlayAnimation(L"Lion_WarriorWalk", true);
					}
					else
					{
						at->PlayAnimation(L"Lion_WarriorWalkR", true);
					}
				}
				if (_distance > -75 && _distance < 75)
				{
					_state = Monster_LionWarrior_State::Attack_Ready;
					if (mDir == 1)
					{
						at->PlayAnimation(L"Lion_WarriorAttack_Ready", false);
						_attackdir = 1;
					}
					else
					{
						at->PlayAnimation(L"Lion_WarriorAttack_ReadyR", false);
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
					_state = Monster_LionWarrior_State::WalkR;
					at->PlayAnimation(L"Lion_WarriorWalk", true);
				}
				else if (_walkdir == -1)
				{
					_state = Monster_LionWarrior_State::WalkL;
					at->PlayAnimation(L"Lion_WarriorWalkR", true);
				}
			}
		}
	}
	void Monster_LionWarrior::attack()
	{
		_attack_Col = true;
	}
	void Monster_LionWarrior::attack_ready()
	{
		_attacktime += Time::DeltaTime();
		if (_attacktime >= 1)
		{
			_state = Monster_LionWarrior_State::Attack;
			if (_attackdir == 1)
			{
				at->PlayAnimation(L"Lion_WarriorAttack", true);
				_rigidbody->SetVelocity(Vector2(200.f, 0.f));
			}
			else
			{
				at->PlayAnimation(L"Lion_WarriorAttackR", true);
				_rigidbody->SetVelocity(Vector2(-200.f, 0.f));
			}
			_attacktime = 0;
		}
	}
	void Monster_LionWarrior::dead()
	{
	}
	void Monster_LionWarrior::hit()
	{
		_attacktime += Time::DeltaTime();
		if (_attacktime >= 0.5)
		{
			_state = Monster_LionWarrior_State::Idle;
			if (mDir == 1)
				at->PlayAnimation(L"Lion_WarriorIdle", true);
			else
				at->PlayAnimation(L"Lion_WarriorIdleR", true);
			_attacktime = 0;
		}
	}
	void Monster_LionWarrior::walk()
	{
		if (_distance > -75 && _distance < 75)
		{
			_state = Monster_LionWarrior_State::Attack_Ready;
			if (mDir == 1)
			{
				at->PlayAnimation(L"Lion_WarriorAttack_Ready", false);
				_attackdir = 1;
			}
			else
			{
				at->PlayAnimation(L"Lion_WarriorAttack_ReadyR", false);
				_attackdir = -1;
			}
		}
		else
		{
			if (_distance >= 0.f)
				_pos.x += 200.f * Time::DeltaTime();
			else
				_pos.x -= 200.f * Time::DeltaTime();
			_tr->SetPosition(_pos);
		}
	}
	void Monster_LionWarrior::walk_R()
	{
		if (_walkdistance > -100)
			_pos.x += 80.f * Time::DeltaTime();
		else
		{
			_state = Monster_LionWarrior_State::Idle;
			at->PlayAnimation(L"Lion_WarriorIdle", true);
			_time = 0; _walkdir *= -1;
		}
	}
	void Monster_LionWarrior::walk_L()
	{
		if (_walkdistance < 100)
			_pos.x -= 80.f * Time::DeltaTime();
		else
		{
			_state = Monster_LionWarrior_State::Idle;
			at->PlayAnimation(L"Lion_WarriorIdleR", true);
			_time = 0; _walkdir *= -1;
		}
	}




	void Monster_LionWarrior::SetDirection()
	{
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
	}
	void Monster_LionWarrior::Particle_Control()
	{
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
	}
	void Monster_LionWarrior::Hpcontrol()
	{
		Transform* hp_tr = Monster_Hp->GetComponent<Transform>();
		hp_tr->SetPosition(Vector3(_pos.x, _pos.y - 40, _pos.z - 2));

		Transform* hpdamege_tr = Monster_DamegeHp->GetComponent<Transform>();
		hpdamege_tr->SetPosition(Vector3(_pos.x, _pos.y - 40, _pos.z - 1.5));

		Transform* hpfr_tr = Hpbar_Frame->GetComponent<Transform>();
		hpfr_tr->SetPosition(Vector3(_pos.x, _pos.y - 40, _pos.z - 1));


		if (_Hp_control == true)
		{
			if (Monster_DamegeHp->Get_Switch() == true)
			{
				_Hp_time += Time::DeltaTime();
				if (_Hp_time > 2)
				{
					Hpbar_Frame->SetState(eState::Paused);
					Monster_DamegeHp->SetState(eState::Paused);
					Monster_Hp->SetState(eState::Paused);
					Monster_DamegeHp->Set_Switch(false);

					_Hp_control = false;
					_Hp_time = 0.f;
				}
			}
		}
		if (_CurrenHp <= 0)
		{
			_hit_particle = false;
			Hit_Particle->SetState(eState::Paused);
			Hpbar_Frame->SetState(eState::Paused);
			Monster_DamegeHp->SetState(eState::Paused);
			Monster_Hp->SetState(eState::Paused);
			Hit_Box->SetState(eState::Paused);
			_Die = true;
			this->SetState(eState::Paused);
		}
	}
	void Monster_LionWarrior::Effect_Control()
	{
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
	}



	void Monster_LionWarrior::complete_attack()
	{
		_attack_Col = false;
		_rigidbody->ClearVelocity();
		_state = Monster_LionWarrior_State::Idle;
		if (mDir == 1)
			at->PlayAnimation(L"Lion_WarriorIdle", true);
		else
			at->PlayAnimation(L"Lion_WarriorIdleR", true);

		_time = 0;
	}
	void Monster_LionWarrior::complete_hit()
	{
		_state = Monster_LionWarrior_State::Idle;
		if (mDir == 1)
			at->PlayAnimation(L"Lion_WarriorIdle", true);
		else
			at->PlayAnimation(L"Lion_WarriorIdleR", true);

		_time = 0;
	}
}