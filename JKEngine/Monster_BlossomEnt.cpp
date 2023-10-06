#include "Monster_BlossomEnt.h"
#include "Particle_DamageEffect.h"

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
			Blossomeenct_Attack = new Monster_Blossomeenct_Attack;
			Blossomeenct_Attack->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Bullet, Blossomeenct_Attack);
			Transform* bullet_tr = Blossomeenct_Attack->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(_pos.x, _pos.y, -205));
			Blossomeenct_Attack->SetState(eState::Paused);
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
			Hit_Particle = new GameObject();
			Particle_DamageEffect* mr = Hit_Particle->AddComponent<Particle_DamageEffect>(Vector3());
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, Hit_Particle);
			Hit_Particle->SetState(eState::Paused);
		}

		GameObject::Initialize();
	}

	void Monster_BlossomEnt::Update()
	{

		 SetDirection();
		 Particle_Control();
		 Hpcontrol();
		 Effect_Control();
		

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
			_Damage = player->GetDamage();

			Particle_DamageEffect* mr = Hit_Particle->GetComponent<Particle_DamageEffect>();

			if (!(_state == Monster_BlossomEnt_State::Attack || _state == Monster_BlossomEnt_State::Attack_Ready))
			{
				_state = Monster_BlossomEnt_State::Hit;
				if (mDir == 1)
				{
					at->PlayAnimation(L"BlossomEntHit", false);
					_rigidbody->SetVelocity(Vector2(-70.f, 0.f));
					tr->SetPosition(_pos);
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
					at->PlayAnimation(L"BlossomEntHitR", false);
					_rigidbody->SetVelocity(Vector2(70.f, 0.f));
					tr->SetPosition(_pos);
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
					_Death_Effect->SetState(eState::Active);
					Hit_Particle->SetState(eState::Paused);
					_state = Monster_BlossomEnt_State::Dead;
				}
			}

			if ((_state == Monster_BlossomEnt_State::Attack || _state == Monster_BlossomEnt_State::Attack_Ready))
			{				
				if (mDir == 1)
				{					
					_rigidbody->SetVelocity(Vector2(-70.f, 0.f));
					tr->SetPosition(_pos);
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
					tr->SetPosition(_pos);
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
					_Hit_Effect->_effect_animation = true;
					_Death_Effect->SetState(eState::Active);
					_Hit_Effect->SetState(eState::Paused);
					Hit_Particle->SetState(eState::Paused);
					_particletime = 0.f;
					_hit_particle = false;;
					_state = Monster_BlossomEnt_State::Dead;
				}
			}
		}

		if (Skul_head* player = dynamic_cast<Skul_head*>(other->GetOwner()))
		{
			_Damage = player->GetDamage();

			Particle_DamageEffect* mr = Hit_Particle->GetComponent<Particle_DamageEffect>();
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
						at->PlayAnimation(L"BlossomEntHitR", false);
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
						_state = Monster_BlossomEnt_State::Dead;
						_Hit_Effect->_effect_animation = true;
					}
					_bulletcheck++;
				}
			}

			if ((_state == Monster_BlossomEnt_State::Attack || _state == Monster_BlossomEnt_State::Attack_Ready))
			{
				if (player->_Head_Attack == false && _bulletcheck == 0)
				{
					if (player->_Ground_check == true)
						return;
					
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


	void Monster_BlossomEnt::SetDirection()
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
	}
	void Monster_BlossomEnt::Particle_Control()
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
	void Monster_BlossomEnt::Hpcontrol()
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
			_Die = true;
			this->SetState(eState::Paused);
		}
	}
	void Monster_BlossomEnt::Effect_Control()
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