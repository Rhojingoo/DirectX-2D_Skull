#include "Stone_wizard.h"
#include <iostream>
#include <random>
#include "Particle_DamageEffect.h"

namespace jk
{
	int Stone_wizard::mDir = 1;
	Stone_wizard::Stone_wizard()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}

	Stone_wizard::~Stone_wizard()
	{
	}

	void Stone_wizard::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(false);
		tr = GetComponent<Transform>();

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Stone_wizard\\Attack_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Stone_wizard\\Attack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Stone_wizard\\Hit", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Stone_wizard\\Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Stone_wizard\\Teleport_In", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Stone_wizard\\Teleport_Out", this);
		
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Stone_wizard\\Attack_Ready", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Stone_wizard\\Attack", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Stone_wizard\\Hit", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Stone_wizard\\Idle", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Stone_wizard\\Teleport_In", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Stone_wizard\\Teleport_Out", this, 1);


		//bind 부분
		at->CompleteEvent(L"Stone_wizardAttack_Ready") = std::bind(&Stone_wizard::complete_attack_ready, this);
		at->CompleteEvent(L"Stone_wizardAttack_ReadyR") = std::bind(&Stone_wizard::complete_attack_ready, this);
		at->CompleteEvent(L"Stone_wizardAttack") = std::bind(&Stone_wizard::complete_attack, this);
		at->CompleteEvent(L"Stone_wizardAttackR") = std::bind(&Stone_wizard::complete_attack, this);
		at->CompleteEvent(L"Stone_wizardTeleport_In") = std::bind(&Stone_wizard::complete_telleport_in, this);
		at->CompleteEvent(L"Stone_wizardTeleport_InR") = std::bind(&Stone_wizard::complete_telleport_in, this);
		at->CompleteEvent(L"Stone_wizardTeleport_Out") = std::bind(&Stone_wizard::complete_telleport_out, this);
		at->CompleteEvent(L"Stone_wizardTeleport_OutR") = std::bind(&Stone_wizard::complete_telleport_out, this);

		at->PlayAnimation(L"Stone_wizardIdle", true);


		//체력관련
		{
			Hpbar_Frame = new HP_Frame(L"EnemyHealthBar_Frame");
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Monster, Hpbar_Frame);
			Hpbar_Frame->SetName(L"hp_bar_frame");
			Transform* hp_tr = Hpbar_Frame->GetComponent<Transform>();
			hp_tr->SetPosition(Vector3(pos.x, pos.y + 50, pos.z - 1));
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
			hp_tr->SetPosition(Vector3(pos.x, pos.y + 50, pos.z - 1.5));
			hp_tr->SetScale(44, 3, 0);
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
			hp_tr->SetPosition(Vector3(pos.x, pos.y + 50, pos.z - 1));
			hp_tr->SetScale(44, 3, 0);
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
			Hit_Box->SetState(eState::Paused);
		}		

		{
			Wizard_Teleport = new Monster_StoneWizard_Teleport();
			Wizard_Teleport->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, Wizard_Teleport);
			Effect_tr = Wizard_Teleport->GetComponent<Transform>();
			Effect_tr->SetPosition(tr->GetPosition());
			Wizard_Teleport->SetState(eState::Paused);
		}

		{
			Icicle_Effect = new Monster_StoneWizard_Icicle_Effect();
			Icicle_Effect->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, Icicle_Effect);
			Transform* effect_tr = Icicle_Effect->GetComponent<Transform>();
			effect_tr->SetPosition(tr->GetPosition());
			Icicle_Effect->SetState(eState::Paused);		
		}

		{
			Icicle_Bullet = new Monster_Stone_wizard_IcicleBullet();
			Icicle_Bullet->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Bullet, Icicle_Bullet);
			Transform* effect_tr = Icicle_Bullet->GetComponent<Transform>();
			effect_tr->SetPosition(tr->GetPosition());
			Icicle_Bullet->SetState(eState::Paused);
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
	void Stone_wizard::Update()
	{
		tr = GetComponent<Transform>();
		pos = tr->GetPosition();
		_velocity = _rigidbody->GetVelocity();
		SetDirection();
		Particle_Control();
		Hpcontrol();		
		Effect_Control();	


		switch (_state)
		{
		case jk::Stone_wizard::Stone_wizard_State::Idle:
			idle();
			break;

		case jk::Stone_wizard::Stone_wizard_State::Attack_Ready:
			attack_ready();
			break;

		case jk::Stone_wizard::Stone_wizard_State::Attack:
			attack();
			break;

		case jk::Stone_wizard::Stone_wizard_State::Hit:
			hit();
			break;

		case jk::Stone_wizard::Stone_wizard_State::Teleport_In:
			teleport_in();
			break;

		case jk::Stone_wizard::Stone_wizard_State::Teleport_Out:
			teleport_out();
			break;

		case jk::Stone_wizard::Stone_wizard_State::Dead:
			dead();
			break;
			
		default:
			break;
		}

		Effect_tr->SetPosition(tr->GetPosition());
		GameObject::Update();
	}
	void Stone_wizard::LateUpdate()
	{
		if (_state == Stone_wizard_State::Dead)		
			_collider->SetSize(Vector2(0.f, 0.f));		
		else
		{
			_collider->SetSize(Vector2(0.45f, 0.7f));
			_collider->SetCenter(Vector2(1.f, -5.8f));
		}

		GameObject::LateUpdate();
	}
	void Stone_wizard::Render()
	{
		GameObject::Render();
	}


	void Stone_wizard::OnCollisionEnter(Collider2D* other)
	{
		if (HitBox_Player* player = dynamic_cast<HitBox_Player*>(other->GetOwner()))
		{	
			_Damage = player->GetDamage();

			Particle_DamageEffect* mr = Hit_Particle->GetComponent<Particle_DamageEffect>();

			if (!(_state == Stone_wizard_State::Attack || _state == Stone_wizard_State::Attack_Ready))
			{			
				_state = Stone_wizard_State::Hit;
				if (mDir == 1)
				{
					at->PlayAnimation(L"Stone_wizardHit", false);
					_rigidbody->SetVelocity(Vector2(-70.f, 0.f));
					tr->SetPosition(pos);
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
					mr->SetPosition(pos);
					mr->Setpos_siwtch(true);
					mr->SetDirection(1);
					_hit_particle = true;
				}
				if (mDir == -1)
				{
					at->PlayAnimation(L"Stone_wizardHitR", false);
					_rigidbody->SetVelocity(Vector2(70.f, 0.f));
					tr->SetPosition(pos);
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
					mr->SetPosition(pos);
					mr->Setpos_siwtch(true);
					mr->SetDirection(-1);
					_hit_particle = true;
				}
				if (_CurrenHp <= 0)
				{
					_state = Stone_wizard_State::Dead;
					_Death_Effect->_effect_animation = true;
					_Death_Effect->SetState(eState::Active);
					_CurrenHp = 0;					
				}
			}			

			if ((_state == Stone_wizard_State::Attack || _state == Stone_wizard_State::Attack_Ready))
			{	
				if (mDir == 1)
				{
					_rigidbody->SetVelocity(Vector2(-70.f, 0.f));
					tr->SetPosition(pos);
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
					mr->SetPosition(pos);
					mr->Setpos_siwtch(true);
					mr->SetDirection(1);
					_hit_particle = true;
				}
				if (mDir == -1)
				{		
					_rigidbody->SetVelocity(Vector2(70.f, 0.f));
					tr->SetPosition(pos);
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
					mr->SetPosition(pos);
					mr->Setpos_siwtch(true);
					mr->SetDirection(-1);
					_hit_particle = true;
				}
				if (_CurrenHp <= 0)
				{
					_state = Stone_wizard_State::Dead;
					_Hit_Effect->_effect_animation = true;
					_Death_Effect->SetState(eState::Active);
					_CurrenHp = 0;
				}
			}
		}	

		if (Skul_head* player = dynamic_cast<Skul_head*>(other->GetOwner()))
		{
			_Damage = player->GetDamage();

			if (!(_state == Stone_wizard_State::Attack || _state == Stone_wizard_State::Attack_Ready))
			{
				if (player->_Head_Attack == false && _bulletcheck == 0)
				{
					if (player->_Ground_check == true)
						return;

					_state = Stone_wizard_State::Hit;
					if (mDir == 1)
					{
						at->PlayAnimation(L"Stone_wizardHit", false);
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
					}
					if (mDir == -1)
					{
						at->PlayAnimation(L"Stone_wizardHitR", false);
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
					}
					if (_CurrenHp <= 0)
					{
						_state = Stone_wizard_State::Dead;
						_Hit_Effect->_effect_animation = true;
						_Death_Effect->SetState(eState::Active);
						_CurrenHp = 0;
					}
					_bulletcheck++;
				}
			}


			if ((_state == Stone_wizard_State::Attack || _state == Stone_wizard_State::Attack_Ready))
			{
				if (player->_Head_Attack == false && _bulletcheck == 0)
				{
					if (player->_Ground_check == true)
						return;

					_state = Stone_wizard_State::Hit;
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
					}
					if (_CurrenHp <= 0)
					{
						_state = Stone_wizard_State::Dead;
						_Hit_Effect->_effect_animation = true;
						_Death_Effect->SetState(eState::Active);
						_CurrenHp = 0;
					}
					_bulletcheck++;
				}
			}

			Hit_Particle->SetState(eState::Active);
			Particle_DamageEffect* mr = Hit_Particle->GetComponent<Particle_DamageEffect>();
			mr->SetPosition(pos);
			mr->Setpos_siwtch(true);
		}
	}
	void Stone_wizard::OnCollisionStay(Collider2D* other)
	{
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{
			if (_Ground_check == false)
			{
				_rigidbody->SetGround(true);
				_Ground_check = true;
				_rigidbody->ClearVelocity();
			}
			else
			{
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
			else
			{
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
			else
			{
			}
		}
	}
	void Stone_wizard::OnCollisionExit(Collider2D* other)
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

	void Stone_wizard::idle()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> distribution(0, 1);
		//_AttackCheck = distribution(gen);

		_time += Time::DeltaTime();

		if (_time > 2.5f)
		{
			if ((_distance < 200 && _distance > -200))
			{
				_state = Stone_wizard_State::Attack_Ready;
				if (mDir == 1)
					at->PlayAnimation(L"Stone_wizardAttack_Ready", true);
				else
					at->PlayAnimation(L"Stone_wizardAttack_ReadyR", true);
			}


			if (_distance <= -250 || _distance >=250)
			{
				if (_teleportCheck == false)
				{
					_state = Stone_wizard_State::Teleport_In;
					if (mDir == 1)
					{
						_teleportCheck = true;
						at->PlayAnimation(L"Stone_wizardTeleport_In", true);
						Effect_tr->SetPosition(tr->GetPosition());
					}
					else
					{
						_teleportCheck = true;
						at->PlayAnimation(L"Stone_wizardTeleport_InR", true);
						Effect_tr->SetPosition(tr->GetPosition());
					}
				}
			}
		}
	}
	void Stone_wizard::attack_ready()
	{
		if (_attack_ready == true)
		{
			if (mDir == 1)
			{
				Transform* effect_tr = Icicle_Effect->GetComponent<Transform>();
				
				Transform* bullet_tr = Icicle_Bullet->GetComponent<Transform>();
				bullet_tr->SetPosition(effect_tr->GetPosition());
				Icicle_Bullet->SetState(eState::Active);
				Icicle_Bullet->_Life = true;

				at->PlayAnimation(L"Stone_wizardAttack", false);
			}
			else
			{
				Transform* effect_tr = Icicle_Effect->GetComponent<Transform>();
		
				Transform* bullet_tr = Icicle_Bullet->GetComponent<Transform>();
				bullet_tr->SetPosition(effect_tr->GetPosition());
				Icicle_Bullet->SetState(eState::Active);
				Icicle_Bullet->_Life = true;

				at->PlayAnimation(L"Stone_wizardAttackR", false);
			}
			_attack_ready = false;
			_state = Stone_wizard_State::Attack;
			_attack = true;
		}
	}
	void Stone_wizard::attack()
	{
		if (_attack == true)
		{
			_attacktime += Time::DeltaTime();
			if (_attacktime > 1.5)
			{
				if (mDir == 1)
				{
					_state = Stone_wizard_State::Idle;
					at->PlayAnimation(L"Stone_wizardIdle", true);		
				}
				else
				{
					_state = Stone_wizard_State::Idle;
					at->PlayAnimation(L"Stone_wizardIdleR", true);		
				}
				_time = 0.f;
				_attacktime = 0.f;
			}
		}
	}
	void Stone_wizard::hit()
	{
		_attacktime += Time::DeltaTime();
		if (_attacktime >= 1)
		{
			_state = Stone_wizard_State::Idle;
			if (mDir == 1)
				at->PlayAnimation(L"Stone_wizardIdle", true);
			else
				at->PlayAnimation(L"Stone_wizardIdleR", true);
			_attacktime = 0;
			_hit_particle = true;
		}
	}

	void Stone_wizard::dead()
	{
		_attacktime += Time::DeltaTime();
		if (_attacktime >= 1)
		{
			_attacktime = 0;
			_hit_particle = true;
		}
	}

	void Stone_wizard::teleport_in()
	{
		if (_teleportCheck == false)
		{
			_attacktime += Time::DeltaTime();
			if (_attacktime > 0.15f)
			{
				if (mDir == 1)
				{
					tr->SetPositionXY(Vector2(_playerpos.x - 100, _playerpos.y + 15));
					_state = Stone_wizard_State::Teleport_Out;
					at->PlayAnimation(L"Stone_wizardTeleport_Out", true);
					_rigidbody->SetGround(false);
					_Ground_check = false;
				}
				else
				{
					tr->SetPositionXY(Vector2(_playerpos.x + 100, _playerpos.y + 15));
					_state = Stone_wizard_State::Teleport_Out;
					at->PlayAnimation(L"Stone_wizardTeleport_OutR", true);
					_rigidbody->SetGround(false);
					_Ground_check = false;
				}
				_attacktime = 0;
			}	
		}
	}
	void Stone_wizard::teleport_out()
	{
		if (_teleportCheck == false)
		{
			if (mDir == 1)
			{
				Wizard_Teleport->_effect_On = true;
				Wizard_Teleport->Telleport_choive = Monster_StoneWizard_Teleport::Stone_wizard_Telleport::Teleport_Out_Right;
				Wizard_Teleport->SetState(eState::Active);
			}
			else
			{
				Wizard_Teleport->_effect_On = true;
				Wizard_Teleport->Telleport_choive = Monster_StoneWizard_Teleport::Stone_wizard_Telleport::Teleport_Out_Left;
				Wizard_Teleport->SetState(eState::Active);
			}			
			_teleportCheck = true;
		}
	}

	void Stone_wizard::Particle_Control()
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
	void Stone_wizard::Hpcontrol()
	{
		Transform* hp_tr = Monster_Hp->GetComponent<Transform>();
		hp_tr->SetPosition(Vector3(pos.x, pos.y - 40, pos.z - 2));

		Transform* hpdamege_tr = Monster_DamegeHp->GetComponent<Transform>();
		hpdamege_tr->SetPosition(Vector3(pos.x, pos.y - 40, pos.z - 1.5));

		Transform* hpfr_tr = Hpbar_Frame->GetComponent<Transform>();
		hpfr_tr->SetPosition(Vector3(pos.x, pos.y - 40, pos.z - 1));

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
	void Stone_wizard::Effect_Control()
	{
		{
			Transform* _Hit_Effect_TR = _Hit_Effect->GetComponent<Transform>();
			if (mDir == 1)
				_Hit_Effect_TR->SetPosition(Vector3(pos.x + 15, pos.y, pos.z - 1));
			else
				_Hit_Effect_TR->SetPosition(Vector3(pos.x - 15, pos.y, pos.z - 1));
		}
		{
			Transform* _Effect_TR = _Death_Effect->GetComponent<Transform>();
			_Effect_TR->SetPosition(Vector3(pos.x, pos.y, pos.z - 1));
		}
	}


	void Stone_wizard::SetDirection()
	{
		_distance = _playerpos.x - pos.x;
		if (_distance >= 0.f)
			mDir = 1;
		else
			mDir = -1;
	}
	void Stone_wizard::complete_telleport_in()
	{
		if (_teleportCheck == true)
		{
			if (mDir == 1)
			{
				Wizard_Teleport->_effect_On = true;
				Wizard_Teleport->Telleport_choive = Monster_StoneWizard_Teleport::Stone_wizard_Telleport::Teleport_In_Right;
				Wizard_Teleport->SetState(eState::Active);
				_teleportCheck = false;
			}
			else
			{
				Wizard_Teleport->_effect_On = true;
				Wizard_Teleport->Telleport_choive = Monster_StoneWizard_Teleport::Stone_wizard_Telleport::Teleport_In_Left;
				Wizard_Teleport->SetState(eState::Active);
				_teleportCheck = false;
			}
		}
	}
	void Stone_wizard::complete_telleport_out()
	{
		if (_teleportCheck == true)
		{
			if (mDir == 1)
			{
				_state = Stone_wizard_State::Idle;
				at->PlayAnimation(L"Stone_wizardIdle", true);
			}
			else
			{
				_state = Stone_wizard_State::Idle;
				at->PlayAnimation(L"Stone_wizardIdleR", true);
			}
			_teleportCheck = false;
			_time = 0.f;
		}
	}

	void Stone_wizard::complete_attack_ready()
	{
		if (_attack_ready == false)
		{		
			if (mDir == 1)
			{
				Icicle_Effect->_effect_On = true;
				Icicle_Effect->SetDirection(1);
				Transform* effect_tr = Icicle_Effect->GetComponent<Transform>();
				effect_tr->SetPosition(Vector3(_playerpos.x, _playerpos.y + 150, _playerpos.z - 1));
				Icicle_Effect->SetState(eState::Active);
			}
			else
			{
				Icicle_Effect->_effect_On = true;
				Icicle_Effect->SetDirection(-1);
				Transform* effect_tr = Icicle_Effect->GetComponent<Transform>();
				effect_tr->SetPosition(Vector3(_playerpos.x, _playerpos.y+150, _playerpos.z-1));
				Icicle_Effect->SetState(eState::Active);
			}
			_attack_ready = true;
		}
	}
	void Stone_wizard::complete_attack()
	{
		//_state = Stone_wizard_State::Idle;
		//if (mDir == 1)
		//	at->PlayAnimation(L"WarriorIdle", true);
		//else
		//	at->PlayAnimation(L"WarriorIdleR", true);

		//_time = 0;
	}
}