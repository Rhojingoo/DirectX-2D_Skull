#include "Monster_GreenTree.h"
#include "Particle_DamageEffect.h"
#include "Include_Common.h"
#include "Monster_GroundAttack_Sign.h"
#include "Monster_Ent_GroundAttack.h"
#include "Monster_Hit_Effect.h"
#include "Monster_Death_Effect.h"
#include "Monster_Hp_Bar.h"
#include "HP_Frame.h"
#include "..\Engine_SOURCE\jkAudioSource.h"
namespace jk
{
	Monster_GreenTree::Monster_GreenTree()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}
	Monster_GreenTree::~Monster_GreenTree()
	{
	}


	void Monster_GreenTree::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		tr = GetComponent<Transform>();
		_pos = tr->GetPosition();
		_first_place = _pos;


		as = AddComponent<AudioSource>();
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\Stage1\\GreenTree\\OldTreeEnt_Atk_Ready.wav", "OldTreeEnt_Atk_Ready");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\Stage1\\GreenTree\\OldTreeEnt_Attack.wav", "OldTreeEnt_Attack");

		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\Common_Dead\\Enemy_Dead.wav", "Enemy_Dead");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\Common_Hit\\Hit_Blunt_Small.wav", "Hit_Blunt_Small");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\Common_Hit\\Hit_Sword_Small.wav", "Hit_Sword_Small");


		
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GreenTree\\Attack_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GreenTree\\Attack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GreenTree\\Hit", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GreenTree\\Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GreenTree\\Walk", this);

		
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GreenTree\\Attack_Ready", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GreenTree\\Attack", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GreenTree\\Hit", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GreenTree\\Idle", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GreenTree\\Walk", this, 1);

		at->CompleteEvent(L"GreenTreeAttack") = std::bind(&Monster_GreenTree::Complete_Attack, this);
		at->CompleteEvent(L"GreenTreeAttackR") = std::bind(&Monster_GreenTree::Complete_Attack, this);
				

		at->PlayAnimation(L"GreenTreeIdle", true);

			Scene* scene = SceneManager::GetInitializeScene();
		//체력관련
		{
			Hpbar_Frame = new HP_Frame(L"EnemyHealthBar_Frame");
			scene->AddGameObject(eLayerType::Monster, Hpbar_Frame);
			Hpbar_Frame->SetName(L"hp_bar_frame");
			Transform* hp_tr = Hpbar_Frame->GetComponent<Transform>();
			hp_tr->SetPosition(Vector3(_pos.x, _pos.y + 50.f, _pos.z - 1.f));
			hp_tr->SetScale(50.f, 5.f, 0.f);
			Hpbar_Frame->SetState(eState::Paused);
		}

		{
			Monster_DamegeHp = new Monster_Hp_Bar(L"EnemyHealthBar_Damage");
			scene->AddGameObject(eLayerType::Monster, Monster_DamegeHp);
			Monster_DamegeHp->SetName(L"warrior_hp_bar");
			Transform* hp_tr = Monster_DamegeHp->GetComponent<Transform>();
			hp_tr->SetPosition(Vector3(_pos.x, _pos.y + 50.f, _pos.z - 1.5f));
			hp_tr->SetScale(48.f, 3.f, 0.f);
			Monster_DamegeHp->Set_Max_Hp(_MaxHp);
			Monster_DamegeHp->Set_Current_Hp(_MaxHp);
			Monster_DamegeHp->Set_Type(1);
			Monster_DamegeHp->SetState(eState::Paused);
		}

		{
			Monster_Hp = new Monster_Hp_Bar(L"EnemyHealthBar");
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
			GroundAttack_Sign = new Monster_GroundAttack_Sign;
			GroundAttack_Sign->Initialize();
			scene->AddGameObject(eLayerType::Effect, GroundAttack_Sign);
			Transform* bullet_tr = GroundAttack_Sign->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(_pos.x, _pos.y, -205));
			GroundAttack_Sign->SetState(eState::Paused);
		}

		{
			GroundAttack = new Monster_Ent_GroundAttack;
			GroundAttack->Initialize();
			scene->AddGameObject(eLayerType::Bullet, GroundAttack);
			Transform* bullet_tr = GroundAttack->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(_pos.x, _pos.y, -205));
			GroundAttack->SetState(eState::Paused);
		}		
		

		{
			_Hit_Effect = new Monster_Hit_Effect;
			_Hit_Effect->Initialize();
			scene->AddGameObject(eLayerType::Effect, _Hit_Effect);
			_Hit_Effect->SetState(eState::Paused);
		}


		{
			_Death_Effect = new Monster_Death_Effect;
			_Death_Effect->Initialize();
			scene->AddGameObject(eLayerType::Effect, _Death_Effect);
			_Death_Effect->SetState(eState::Paused);
		}


		{
			Hit_Particle = new GameObject();
			Particle_DamageEffect* mr = Hit_Particle->AddComponent<Particle_DamageEffect>(Vector3());
			scene->AddGameObject(eLayerType::Effect, Hit_Particle);
			Hit_Particle->SetState(eState::Paused);
		}
		
		GameObject::Initialize();
	}	
	void Monster_GreenTree::Update()
	{
		SetDirection();
		Particle_Control();
		Hpcontrol();
		Effect_Control();

		if (_player_groundcheck == true)
			_AttackSign_place = Vector3(_playerGRpos.x, _playerGRpos.y - 20, _playerGRpos.z - 1);


		switch (_state)
		{
		case jk::Monster_GreenTree::Monster_GreenTree_State::Idle:
			idle();
			break;

		case jk::Monster_GreenTree::Monster_GreenTree_State::Attack_Ready:
			attack_ready();
			break;

		case jk::Monster_GreenTree::Monster_GreenTree_State::Attack:
			attack();
			break;

		case jk::Monster_GreenTree::Monster_GreenTree_State::Attack_End:
			attack_end();
			break;

		case jk::Monster_GreenTree::Monster_GreenTree_State::Dead:
			dead();
			break;

		case jk::Monster_GreenTree::Monster_GreenTree_State::Hit:
			hit();
			break;

		case jk::Monster_GreenTree::Monster_GreenTree_State::WalkR:
			walk_R();
			break;

		case jk::Monster_GreenTree::Monster_GreenTree_State::WalkL:
			walk_L();
			break;

		default:
			break;
		}
		tr->SetPosition(_pos);
		GameObject::Update();
	}
	void Monster_GreenTree::LateUpdate()
	{
		_collider->SetSize(Vector2(0.5f, 0.8f));
		_collider->SetCenter(Vector2(1.f, -5.5f));
		GameObject::LateUpdate();
	}
	void Monster_GreenTree::Render()
	{
		GameObject::Render();
	}


	void Monster_GreenTree::OnCollisionEnter(Collider2D* other)
	{
		if (HitBox_Player* player = dynamic_cast<HitBox_Player*>(other->GetOwner()))
		{
			if (_state == Monster_GreenTree_State::Dead)
				return;

			_Damage = player->GetDamage();

			Particle_DamageEffect* mr = Hit_Particle->GetComponent<Particle_DamageEffect>();

			if (!(_state == Monster_GreenTree_State::Attack || _state == Monster_GreenTree_State::Attack_Ready))
			{
				_state = Monster_GreenTree_State::Hit;
				if (mDir == 1)
				{
					at->PlayAnimation(L"GreenTreeHit", false);
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
					at->PlayAnimation(L"GreenTreeHitR", false);
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
					_state = Monster_GreenTree_State::Dead;
					as->Stop("Enemy_Dead");
					_Death_Effect->_effect_animation = true;
					_Death_Effect->SetState(eState::Active);
				}
			}

			if ((_state == Monster_GreenTree_State::Attack || _state == Monster_GreenTree_State::Attack_Ready))
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
					_state = Monster_GreenTree_State::Dead;
					as->Stop("Enemy_Dead");
					_Death_Effect->_effect_animation = true;
					_Death_Effect->SetState(eState::Active);
				}
			}
		}

		if (Skul_head* player = dynamic_cast<Skul_head*>(other->GetOwner()))
		{
			if (_state == Monster_GreenTree_State::Dead)
				return;

			_Damage = player->GetDamage();

			Particle_DamageEffect* mr = Hit_Particle->GetComponent<Particle_DamageEffect>();
			if (!(_state == Monster_GreenTree_State::Attack || _state == Monster_GreenTree_State::Attack_Ready))
			{
				if (player->_Head_Attack == false && _bulletcheck == 0)
				{
					if (player->_Ground_check == true)
						return;

					as->Play("Hit_Blunt_Small");
					_state = Monster_GreenTree_State::Hit;
					if (mDir == 1)
					{
						at->PlayAnimation(L"GreenTreeHit", false);
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
						at->PlayAnimation(L"GreenTreeHitR", false);
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
						_state = Monster_GreenTree_State::Dead;
						as->Stop("Enemy_Dead");
						_Death_Effect->_effect_animation = true;
						_Death_Effect->SetState(eState::Active);
					}
					_bulletcheck++;
				}
			}

			if ((_state == Monster_GreenTree_State::Attack || _state == Monster_GreenTree_State::Attack_Ready))
			{
				if (player->_Head_Attack == false && _bulletcheck == 0)
				{
					if (player->_Ground_check == true)
						return;
									

					as->Play("Hit_Blunt_Small");
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
						_state = Monster_GreenTree_State::Dead;
						as->Stop("Enemy_Dead");
						_Death_Effect->_effect_animation = true;
						_Death_Effect->SetState(eState::Active);
					}
					_bulletcheck++;
				}
			}
		}
	}
	void Monster_GreenTree::OnCollisionStay(Collider2D* other)
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
			else
			{
				Transform* GRTR = mGround->GetComponent<Transform>();
				Vector3 GRpos = GRTR->GetPosition();
				{
					Collider2D* GRCol = mGround->GetComponent<Collider2D>();
					float GrColsize = GRCol->GetScale().y / 2;
					float playercolsize = _collider->GetScale().y / 2;
					float Sizecheck = playercolsize + GrColsize + 5;


					float CheckPos = fabs(_pos.y - GRpos.y);
					if (Sizecheck > CheckPos)
					{
						_pos.y = GRpos.y + Sizecheck;
						tr->SetPosition(_pos);
					}
				}
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
				Transform* GRTR = mGround->GetComponent<Transform>();
				Vector3 GRpos = GRTR->GetPosition();
				{
					Collider2D* GRCol = mGround->GetComponent<Collider2D>();
					float GrColsize = GRCol->GetScale().y / 2;
					float playercolsize = _collider->GetScale().y / 2;
					float Sizecheck = playercolsize + GrColsize + 5;


					float CheckPos = fabs(_pos.y - GRpos.y);
					if (Sizecheck > CheckPos)
					{
						_pos.y = GRpos.y + Sizecheck;
						tr->SetPosition(_pos);
					}
				}
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
				Transform* GRTR = mGround->GetComponent<Transform>();
				Vector3 GRpos = GRTR->GetPosition();
				{
					Collider2D* GRCol = mGround->GetComponent<Collider2D>();
					float GrColsize = GRCol->GetScale().y / 2;
					float playercolsize = _collider->GetScale().y / 2;
					float Sizecheck = playercolsize + GrColsize + 5;


					float CheckPos = fabs(_pos.y - GRpos.y);
					if (Sizecheck > CheckPos)
					{
						_pos.y = GRpos.y + Sizecheck;
						tr->SetPosition(_pos);
					}
				}
			}
		}
	}
	void Monster_GreenTree::OnCollisionExit(Collider2D* other)
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


	void Monster_GreenTree::idle()
	{
		_time += static_cast<float>(Time::DeltaTime());

		if ((_distance <= 250) && (_distance >= -250))		
			_choiceattack = 0;				
		else
			_choiceattack = 1;


		if (_choiceattack == 0)
		{
			if (_time >= 3.f)
				_attackcheck = true;
		}

		if ((_choiceattack == 0)&& (_attackcheck ==true))
		{
			_state = Monster_GreenTree_State::Attack_Ready;
			if (mDir == 1)
			{
				at->PlayAnimation(L"GreenTreeAttack_Ready", false);
				_attackdir = 1;
			}
			else
			{
				at->PlayAnimation(L"GreenTreeAttack_ReadyR", false);
				_attackdir = -1;
			}
			_Attack_place = _AttackSign_place;
			Transform* bullet_tr = GroundAttack_Sign->GetComponent<Transform>();
			bullet_tr->SetPosition(_Attack_place);
			GroundAttack_Sign->_effect_end = true;
			GroundAttack_Sign->SetState(eState::Active);
		}

		if (_time > 5.f)
		{
			if (_walkdir == 1)
			{
				_state = Monster_GreenTree_State::WalkR;
				at->PlayAnimation(L"GreenTreeWalk", true);
			}
			else if (_walkdir == -1)
			{
				_state = Monster_GreenTree_State::WalkL;
				at->PlayAnimation(L"GreenTreeWalkR", true);
			}
		}
	}
	void Monster_GreenTree::attack_ready()
	{
	
		if (GroundAttack_Sign->_effect_end == false)
		{
			_attacktime += static_cast<float>(Time::DeltaTime());
			if (_attacktime > 0.2f)
			{
				Transform* bullet_tr = GroundAttack->GetComponent<Transform>();
				bullet_tr->SetPosition(Vector3(_Attack_place));
				GroundAttack->SetState(eState::Active);
				as->Play("OldTreeEnt_Atk_Ready");
				as->Play("OldTreeEnt_Attack");

				_state = Monster_GreenTree_State::Attack;
				if (_attackdir == 1)
					at->PlayAnimation(L"GreenTreeAttack", true);
				else
					at->PlayAnimation(L"GreenTreeAttackR", true);
				_attacktime = 0;
			}
		}
	}
	void Monster_GreenTree::attack()
	{
	}
	void Monster_GreenTree::attack_end()
	{
	}


	void Monster_GreenTree::dead()
	{
		if(_Die==true)
			this->SetState(eState::Paused);
	}
	void Monster_GreenTree::hit()
	{
		_attacktime += static_cast<float>(Time::DeltaTime());
		if (_attacktime >= 0.5f)
		{
			_state = Monster_GreenTree_State::Idle;
			if (mDir == 1)
				at->PlayAnimation(L"GreenTreeIdle", true);
			else
				at->PlayAnimation(L"GreenTreeIdleR", true);
			_attacktime = 0;
		}
	}
	void Monster_GreenTree::walk_R()
	{
		if (_walkdistance > -50)
			_pos.x += 80.f * static_cast<float>(Time::DeltaTime());
		else
		{
			_state = Monster_GreenTree_State::Idle;
			at->PlayAnimation(L"GreenTreeIdle", true);
			_time = 0; _walkdir *= -1;
		}
	}
	void Monster_GreenTree::walk_L()
	{
		if (_walkdistance < 50)
			_pos.x -= 80.f * static_cast<float>(Time::DeltaTime());
		else
		{
			_state = Monster_GreenTree_State::Idle;
			at->PlayAnimation(L"GreenTreeIdleR", true);
			_time = 0; _walkdir *= -1;
		}
	}


	void Monster_GreenTree::SetDirection()
	{
		_playerpos = Player::GetPlayer_Pos();
		_player_groundcheck = Player::Get_Ground_On();
		_playerGRpos = Player::GetPlayer_GRPos();

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
	void Monster_GreenTree::Particle_Control()
	{
		if (_hit_particle == true)
		{
			_particletime += static_cast<float>(Time::DeltaTime());
			if (_particletime > 0.5f)
			{
				Hit_Particle->SetState(eState::Paused);
				_particletime = 0.f;
				_hit_particle = false;
			}
		}
	}
	void Monster_GreenTree::Hpcontrol()
	{
		Transform* hp_tr = Monster_Hp->GetComponent<Transform>();
		hp_tr->SetPosition(Vector3(_pos.x, _pos.y - 40.f, _pos.z - 2.f));

		Transform* hpdamege_tr = Monster_DamegeHp->GetComponent<Transform>();
		hpdamege_tr->SetPosition(Vector3(_pos.x, _pos.y - 40.f, _pos.z - 1.5f));

		Transform* hpfr_tr = Hpbar_Frame->GetComponent<Transform>();
		hpfr_tr->SetPosition(Vector3(_pos.x, _pos.y - 40.f, _pos.z - 1.f));

		if (_Hp_control == true)
		{
			if (_Hp_control == true)
			{
				if (Monster_DamegeHp->Get_Switch() == true)
				{
					_Hp_time += static_cast<float>(Time::DeltaTime());
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

	}
	void Monster_GreenTree::Effect_Control()
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


	void Monster_GreenTree::Complete_Attack()
	{
		_state = Monster_GreenTree_State::Idle;
		if (mDir == 1)
		at->PlayAnimation(L"GreenTreeIdle", true);
		else
		at->PlayAnimation(L"GreenTreeIdleR", true);
		_time = 0; _attackcheck = false;
	}
	
}