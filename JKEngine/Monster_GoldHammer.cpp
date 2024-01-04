#include "Monster_GoldHammer.h"
#include "Particle_DamageEffect.h"
#include "Include_Common.h"
#include "Monster_Hit_Effect.h"
#include "Monster_Death_Effect.h"
#include "Monster_Tackle_Flash_Effect.h"
#include "Monster_Hammer_Effect.h"
#include "Player_Hp_Bar.h"
#include "Monster_Hp_Bar.h"
#include "HP_Frame.h"
#include "..\Engine_SOURCE\jkAudioSource.h"

namespace jk
{
	Monster_GoldHammer::Monster_GoldHammer()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}
	Monster_GoldHammer::~Monster_GoldHammer()
	{
	}


	void Monster_GoldHammer::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(false);
		tr = GetComponent<Transform>();
		_pos = tr->GetPosition();
		_first_place = _pos;

		as = AddComponent<AudioSource>();
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\HeavyInfanity\\charge\\Atk_Flame_Large.wav", "Atk_Flame_Large");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\HeavyInfanity\\charge\\MAA_Tackle_Ready.wav", "MAA_Tackle_Ready");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\HeavyInfanity\\hmmer_atk\\Atk_Stomp_Medium.wav", "Atk_Stomp_Medium");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\HeavyInfanity\\hmmer_atk\\MAA_Atk_Ready.wav", "MAA_Atk_Ready");

		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\Common_Dead\\Enemy_Dead.wav", "Enemy_Dead");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\Common_Hit\\Hit_Blunt_Small.wav", "Hit_Blunt_Small");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\Common_Hit\\Hit_Sword_Small.wav", "Hit_Sword_Small");

		//as->Play("Atk_Flame_Large");
		//as->Play("MAA_Tackle_Ready");
		//as->Play("Atk_Stomp_Medium");
		//as->Play("MAA_Atk_Ready");
		//as->Play("Atk_Sword_wariior");



		as = AddComponent<AudioSource>();
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\HeavyInfanity\\charge\\Atk_Flame_Large.wav", "Atk_Flame_Large");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\HeavyInfanity\\charge\\MAA_Tackle_Ready.wav", "MAA_Tackle_Ready");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\HeavyInfanity\\hmmer_atk\\Atk_Stomp_Medium.wav", "Atk_Stomp_Medium");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\HeavyInfanity\\hmmer_atk\\MAA_Atk_Ready.wav", "MAA_Atk_Ready");

		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\Common_Dead\\Enemy_Dead.wav", "Enemy_Dead");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\Common_Hit\\Hit_Blunt_Small.wav", "Hit_Blunt_Small");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\Common_Hit\\Hit_Sword_Small.wav", "Hit_Sword_Small");




		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GoldHammer\\Attack", this,0,0.05f);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GoldHammer\\Attack_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GoldHammer\\Dead", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GoldHammer\\Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GoldHammer\\Tackle_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GoldHammer\\Tackle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GoldHammer\\Tackle_End", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GoldHammer\\Walk", this);


		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GoldHammer\\Attack", this, 1,0.05f);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GoldHammer\\Attack_Ready", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GoldHammer\\Dead", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GoldHammer\\Idle", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GoldHammer\\Tackle_Ready", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GoldHammer\\Tackle", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GoldHammer\\Tackle_End", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GoldHammer\\Walk", this, 1);

		//bind 부분
		at->CompleteEvent(L"GoldHammerAttack") = std::bind(&Monster_GoldHammer::Complete_attack, this);
		at->CompleteEvent(L"GoldHammerAttackR") = std::bind(&Monster_GoldHammer::Complete_attack, this);

		at->PlayAnimation(L"GoldHammerIdle", true);

		//체력관련
		{
			Hpbar_Frame = new HP_Frame(L"EnemyHealthBar_BigFrame");
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Monster, Hpbar_Frame);
			Hpbar_Frame->SetName(L"hp_bar_frame");
			Transform* hp_tr = Hpbar_Frame->GetComponent<Transform>();
			hp_tr->SetPosition(Vector3(_pos.x, _pos.y + 50, _pos.z - 1));
			hp_tr->SetScale(85, 5, 0);
			Hpbar_Frame->SetState(eState::Paused);
		}

		{
			Monster_DamegeHp = new Monster_Hp_Bar(L"EnemyHealthBar_Damage");
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Monster, Monster_DamegeHp);
			Monster_DamegeHp->SetName(L"warrior_hp_bar");
			Transform* hp_tr = Monster_DamegeHp->GetComponent<Transform>();
			hp_tr->SetPosition(Vector3(_pos.x, _pos.y + 50.f, _pos.z - 1.5f));
			hp_tr->SetScale(80.f, 3.f, 0.f);
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
			hp_tr->SetScale(80, 3, 0);
			Monster_Hp->Set_Max_Hp(_MaxHp);
			Monster_Hp->Set_Current_Hp(_MaxHp);
			Monster_Hp->SetState(eState::Paused);
		}





		{
			Hit_Box = new HitBox_Monster();
			Hit_Box->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Hitbox, Hit_Box);
			Hit_Box->SetSound(1);
			Hit_Box->SetState(eState::Paused);
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

		{
			Hit_Particle = new GameObject();
			Particle_DamageEffect* mr = Hit_Particle->AddComponent<Particle_DamageEffect>(Vector3());
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, Hit_Particle);
			Hit_Particle->SetState(eState::Paused);
		}

		GameObject::Initialize();
	}
	void Monster_GoldHammer::Update()
	{
		SetDirection();
		Particle_Control();
		Hpcontrol();
		Effect_Control();


		switch (_state)
		{
		case jk::Monster_GoldHammer::Monster_GoldHammer_State::Idle:
			idle();
			break;

		case jk::Monster_GoldHammer::Monster_GoldHammer_State::Attack_Ready:
			attack_ready();
			break;

		case jk::Monster_GoldHammer::Monster_GoldHammer_State::Attack:
			attack();
			break;

		case jk::Monster_GoldHammer::Monster_GoldHammer_State::Dead:
			dead();
			break;

		case jk::Monster_GoldHammer::Monster_GoldHammer_State::Tackle_Ready:
			tackle_ready();
			break;

		case jk::Monster_GoldHammer::Monster_GoldHammer_State::Tackle:
			tackle();
			break;

		case jk::Monster_GoldHammer::Monster_GoldHammer_State::Tackle_End:
			tackle_end();
			break;

		case jk::Monster_GoldHammer::Monster_GoldHammer_State::Walk:
			walk();
			break;

		case jk::Monster_GoldHammer::Monster_GoldHammer_State::WalkR:
			walk_R();
			break;

		case jk::Monster_GoldHammer::Monster_GoldHammer_State::WalkL:
			walk_L();
			break;

		default:
			break;
		}

		tr->SetPosition(_pos);
		Effect_tr->SetPosition(_Effect_pos);
		GameObject::Update();
	}
	void Monster_GoldHammer::LateUpdate()
	{
		Transform* HitBox_TR = Hit_Box->GetComponent<Transform>();
		if (_attack_Col == true)
		{
			Hit_Box->SetSize(Vector2(100.f, 100.f));
			Hit_Box->SetCenter(Vector3(100.f, 100.f, -250.f));

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
		_collider->SetCenter(Vector2(1.f, -6.f));
		GameObject::LateUpdate();
	}
	void Monster_GoldHammer::Render()
	{
		GameObject::Render();
	}


	void Monster_GoldHammer::OnCollisionEnter(Collider2D* other)
	{
		if (Ground_and_Wall* mGround = dynamic_cast<Ground_and_Wall*>(other->GetOwner()))
		{
			_rigidbody->ClearVelocity();
			Transform* Ground_TR = other->GetOwner()->GetComponent<Transform>();
			Vector3 wall_pos = Ground_TR->GetPosition();

			_attacktime += static_cast<float>(Time::DeltaTime());
			if (_attacktime > 0.7f)
			{
				_state = Monster_GoldHammer_State::Idle;
				if (_Dir == 1)
					at->PlayAnimation(L"GoldHammerIdle", true);
				else
					at->PlayAnimation(L"GoldHammerIdleR", true);

				_time = 0;
				_AttackCheck = 0;
				_attacktime = 0;
			}
		}

		if (HitBox_Player* player = dynamic_cast<HitBox_Player*>(other->GetOwner()))
		{
			if (_state == Monster_GoldHammer_State::Dead)
				return;

			_Damage = player->GetDamage();

			Particle_DamageEffect* mr = Hit_Particle->GetComponent<Particle_DamageEffect>();
			if (!(_state == Monster_GoldHammer_State::Attack || _state == Monster_GoldHammer_State::Tackle))
			{
				if (_Dir == 1)
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
				if (_Dir == -1)
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
					_state = Monster_GoldHammer_State::Dead;
					as->Stop("Enemy_Dead");
					_Hit_Effect->_effect_animation = true;
					if (_attackdir == 1)
					{
						at->PlayAnimation(L"GoldHammerDead", false);
						_Hit_Effect->SetDirection(1);
					}
					else
					{
						at->PlayAnimation(L"GoldHammerDeadR", false);
						_Hit_Effect->SetDirection(-1);
					}
					_Death_Effect->SetState(eState::Active);
				}
			}

			if ((_state == Monster_GoldHammer_State::Attack || _state == Monster_GoldHammer_State::Tackle))
			{
				if (_Dir == 1)
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
				if (_Dir == -1)
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
					_state = Monster_GoldHammer_State::Dead;
					as->Stop("Enemy_Dead");
					_Hit_Effect->_effect_animation = true;
					if (_attackdir == 1)
					{
						at->PlayAnimation(L"GoldHammerDead", false);
						_Hit_Effect->SetDirection(1);
					}
					else
					{
						at->PlayAnimation(L"GoldHammerDeadR", false);
						_Hit_Effect->SetDirection(-1);
					}
					_Death_Effect->SetState(eState::Active);
				}
			}

		}

		if (Skul_head* player = dynamic_cast<Skul_head*>(other->GetOwner()))
		{
			if (_state == Monster_GoldHammer_State::Dead)
				return;

			_Damage = player->GetDamage();

			Particle_DamageEffect* mr = Hit_Particle->GetComponent<Particle_DamageEffect>();
			if (!(_state == Monster_GoldHammer_State::Attack || _state == Monster_GoldHammer_State::Tackle))
			{
				if (player->_Head_Attack == false && _bulletcheck == 0)
				{

					if (player->_Ground_check == true)
						return;

					as->Play("Hit_Blunt_Small");
					if (_Dir == 1)
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
					if (_Dir == -1)
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
						_state = Monster_GoldHammer_State::Dead;
						as->Stop("Enemy_Dead");
						_Hit_Effect->_effect_animation = true;
						if (_attackdir == 1)
						{
							at->PlayAnimation(L"GoldHammerDead", false);
							_Hit_Effect->SetDirection(1);
						}
						else
						{
							at->PlayAnimation(L"GoldHammerDeadR", false);
							_Hit_Effect->SetDirection(-1);
						}
						_Death_Effect->SetState(eState::Active);
					}
					_bulletcheck++;

				}
			}

			if ((_state == Monster_GoldHammer_State::Attack || _state == Monster_GoldHammer_State::Tackle))
			{
				if (player->_Head_Attack == false && _bulletcheck == 0)
				{
					if (player->_Ground_check == true)
						return;

					as->Play("Hit_Blunt_Small");
					if (_Dir == 1)
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
					if (_Dir == -1)
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
						_state = Monster_GoldHammer_State::Dead;
						as->Stop("Enemy_Dead");
						_Hit_Effect->_effect_animation = true;
						if (_attackdir == 1)
						{
							at->PlayAnimation(L"GoldHammerDead", false);
							_Hit_Effect->SetDirection(1);
						}
						else
						{
							at->PlayAnimation(L"GoldHammerDeadR", false);
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
	void Monster_GoldHammer::OnCollisionStay(Collider2D* other)
	{
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
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

		if (Ground_and_Wall* mGround = dynamic_cast<Ground_and_Wall*>(other->GetOwner()))
		{
			Transform* GRTR = mGround->GetComponent<Transform>();
			Vector3 GRpos = GRTR->GetPosition();

			if (GRpos.x > _pos.x)
			{
				_rigidbody->ClearVelocity();
				if (_state == Monster_GoldHammer_State::WalkR)
				{
					_state = Monster_GoldHammer_State::WalkL;
					at->PlayAnimation(L"GoldHammerWalkR", true);
				}
			}
			else if (GRpos.x < _pos.x)
			{
				_rigidbody->ClearVelocity();
				if (_state == Monster_GoldHammer_State::WalkL)
				{
					_state = Monster_GoldHammer_State::WalkR;
					at->PlayAnimation(L"GoldHammerWalk", true);
				}
			}
		}
	}
	void Monster_GoldHammer::OnCollisionExit(Collider2D* other)
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


	void Monster_GoldHammer::idle()
	{
		if (_followskul == true)
		{
			_time += static_cast<float>(Time::DeltaTime());
			if (_time > 1.5f)
			{
				if (_AttackCheck == 0)
				{
					if ((_distance >= 90 || _distance <= -90))
					{
						_state = Monster_GoldHammer_State::Walk;
						if (_Dir == 1)
							at->PlayAnimation(L"GoldHammerWalk", true);
						else
							at->PlayAnimation(L"GoldHammerWalkR", true);
					}
					if (_distance > -80 && _distance < 80)
					{
						_state = Monster_GoldHammer_State::Attack_Ready;
						if (_Dir == 1)
						{
							at->PlayAnimation(L"GoldHammerAttack_Ready", false);
							_attackdir = 1;
						}
						else
						{
							at->PlayAnimation(L"GoldHammerAttack_ReadyR", false);
							_attackdir = -1;
						}
					}
				}

				if (_AttackCheck == 1)
				{
					if ((_distance >= 125 || _distance <= -125))
					{
						_state = Monster_GoldHammer_State::Walk;
						if (_Dir == 1)
							at->PlayAnimation(L"GoldHammerWalk", true);
						else
							at->PlayAnimation(L"GoldHammerWalkR", true);
					}
					else
					{
						_state = Monster_GoldHammer_State::Tackle_Ready;
						if (_Dir == 1)
						{
							at->PlayAnimation(L"GoldHammerTackle_Ready", true);
							_attackdir = 1;
						}
						else
						{
							at->PlayAnimation(L"GoldHammerTackle_ReadyR", true);
							_attackdir = -1;
						}

					}
				}
			}
		}
		else
		{
			_time += static_cast<float>(Time::DeltaTime());
			if (_time > 3.f)
			{
				if (_walkdir == 1)
				{
					_state = Monster_GoldHammer_State::WalkR;
					at->PlayAnimation(L"GoldHammerWalk", true);
				}
				else if (_walkdir == -1)
				{
					_state = Monster_GoldHammer_State::WalkL;
					at->PlayAnimation(L"GoldHammerWalkR", true);
				}
			}
		}
	}

	void Monster_GoldHammer::attack_ready()
	{
		_attacktime += static_cast<float>(Time::DeltaTime());
		if (_attacktime > 1)
		{
			_state = Monster_GoldHammer_State::Attack;
			as->Play("MAA_Atk_Ready");
			if (_attackdir == 1)
				at->PlayAnimation(L"GoldHammerAttack", true);
			else
				at->PlayAnimation(L"GoldHammerAttackR", true);
			_attacktime = 0;
		}
	}

	void Monster_GoldHammer::attack()
	{
		_attack_Col = true;

		Transform* Attack_Effect_Tr = _Hammer_Effect->GetComponent<Transform>();
		if (_attackdir == 1)
			Attack_Effect_Tr->SetPosition(_pos.x + 30, _pos.y - 50, _pos.z - 1);
		else
			Attack_Effect_Tr->SetPosition(_pos.x - 30, _pos.y - 50, _pos.z - 1);
		_Hammer_Effect->SetState(eState::Active);
	}

	void Monster_GoldHammer::tackle_ready()
	{
		_attacktime += static_cast<float>(Time::DeltaTime());
		if (_attacktime > 2.f)
		{
			_state = Monster_GoldHammer_State::Tackle;
			as->Play("MAA_Tackle_Ready");
			as->Play("Atk_Flame_Large");
			if (_attackdir == 1)
			{
				at->PlayAnimation(L"GoldHammerTackle", true);
				_rigidbody->SetVelocity(Vector2(350.f, 0.f));
				Tackle_Flash->_effect_animation = true;
				Tackle_Flash->SetDirection(1);
			}
			else
			{
				at->PlayAnimation(L"GoldHammerTackleR", true);
				_rigidbody->SetVelocity(Vector2(-350.f, 0.f));
				Tackle_Flash->_effect_animation = true;
				Tackle_Flash->SetDirection(-1);
			}
			_attacktime = 0;
			Tackle_Flash->SetState(eState::Active);
		}
	}

	void Monster_GoldHammer::tackle()
	{
		_rigidbody->ClearVelocityY();
		if (_attackdir == 1 && _velocity.x <= 285.0)
		{
			_state = Monster_GoldHammer_State::Tackle_End;
			at->PlayAnimation(L"GoldHammerTackle_End", false);
			_rigidbody->ClearVelocityX();
			Tackle_Flash->SetState(eState::Paused);
		}
		else if (_attackdir == -1 && _velocity.x >= -285.0)
		{
			_state = Monster_GoldHammer_State::Tackle_End;
			at->PlayAnimation(L"GoldHammerTackle_EndR", false);
			_rigidbody->ClearVelocityX();
			Tackle_Flash->SetState(eState::Paused);
		}
	}

	void Monster_GoldHammer::tackle_end()
	{
		_attacktime += static_cast<float>(Time::DeltaTime());
		if (_attacktime > 0.7f)
		{
			_state = Monster_GoldHammer_State::Idle;
			if (_Dir == 1)
				at->PlayAnimation(L"GoldHammerIdle", true);
			else
				at->PlayAnimation(L"GoldHammerIdleR", true);

			_time = 0;
			_AttackCheck = 0;
			_attacktime = 0;
		}
	}

	void Monster_GoldHammer::walk()
	{
		if (_distance >= 0.f)
			_pos.x += 150.f * static_cast<float>(Time::DeltaTime());
		else
			_pos.x -= 150.f * static_cast<float>(Time::DeltaTime());

		if (_AttackCheck == 0)
		{
			if (_distance > -80 && _distance < 80)
			{
				_state = Monster_GoldHammer_State::Attack_Ready;
				if (_Dir == 1)
				{
					at->PlayAnimation(L"GoldHammerAttack_Ready", false);
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
				_state = Monster_GoldHammer_State::Tackle_Ready;
				if (_Dir == 1)
				{
					at->PlayAnimation(L"GoldHammerTackle_Ready", true);
					_attackdir = 1;
				}
				else
				{
					at->PlayAnimation(L"GoldHammerTackle_ReadyR", true);
					_attackdir = -1;
				}
			}
		}
		tr->SetPosition(_pos);
	}

	void Monster_GoldHammer::walk_R()
	{
		if (_walkdistance > -100)
			_pos.x += 100.f * static_cast<float>(Time::DeltaTime());
		else
		{
			_state = Monster_GoldHammer_State::Idle;
			at->PlayAnimation(L"GoldHammerIdle", true);
			_time = 0; _walkdir *= -1;
		}
	}

	void Monster_GoldHammer::walk_L()
	{
		if (_walkdistance < 100)
			_pos.x -= 100.f * static_cast<float>(Time::DeltaTime());
		else
		{
			_state = Monster_GoldHammer_State::Idle;
			at->PlayAnimation(L"GoldHammerIdleR", true);
			_time = 0; _walkdir *= -1;
		}
	}

	void Monster_GoldHammer::dead()
	{
		Tackle_Flash->SetState(eState::Paused);
	}

	void Monster_GoldHammer::Complete_attack()
	{
		_attack_Col = false;
		as->Play("Atk_Stomp_Medium");

		if (_attack_Col == false)
			_state = Monster_GoldHammer_State::Idle;
		if (_Dir == 1)
			at->PlayAnimation(L"GoldHammerIdle", true);
		else
			at->PlayAnimation(L"GoldHammerIdleR", true);
		_time = 0;

		_AttackCheck++;
	}

	void Monster_GoldHammer::SetDirection()
	{
		tr = GetComponent<Transform>();
		_pos = tr->GetPosition();
		_velocity = _rigidbody->GetVelocity();

		_distance = _playerpos.x - _pos.x;
		if (_distance >= 0.f)
			_Dir = 1;
		else
			_Dir = -1;

		_walkdistance = _first_place.x - _pos.x;
		if (_walkdistance >= 0.f)
			_walkdir = 1;
		else
			_walkdir = -1;
	}
	void Monster_GoldHammer::Particle_Control()
	{
		if (_hit_particle == true)
		{
			_particletime += static_cast<float>(Time::DeltaTime());
			if (_particletime > 0.5)
			{
				Hit_Particle->SetState(eState::Paused);
				_particletime = 0.f;
				_hit_particle = false;
			}
		}
	}
	void Monster_GoldHammer::Hpcontrol()
	{
		Transform* hp_tr = Monster_Hp->GetComponent<Transform>();
		hp_tr->SetPosition(Vector3(_pos.x, _pos.y - 65.f, _pos.z - 2.f));

		Transform* hpdamege_tr = Monster_DamegeHp->GetComponent<Transform>();
		hpdamege_tr->SetPosition(Vector3(_pos.x, _pos.y - 65.f, _pos.z - 1.5f));

		Transform* hpfr_tr = Hpbar_Frame->GetComponent<Transform>();
		hpfr_tr->SetPosition(Vector3(_pos.x, _pos.y - 65.f, _pos.z - 1.f));


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
					Tackle_Flash->SetState(eState::Paused);
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
	void Monster_GoldHammer::Effect_Control()
	{
		{
			Transform* _Hit_Effect_TR = _Hit_Effect->GetComponent<Transform>();
			if (_Dir == 1)
				_Hit_Effect_TR->SetPosition(Vector3(_pos.x + 25, _pos.y, _pos.z - 1));
			else
				_Hit_Effect_TR->SetPosition(Vector3(_pos.x - 25, _pos.y, _pos.z - 1));
		}
		{
			Transform* _Effect_TR = _Death_Effect->GetComponent<Transform>();
			_Effect_TR->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 1));
		}

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