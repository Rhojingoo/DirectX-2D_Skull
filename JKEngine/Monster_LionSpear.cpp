#include "Monster_LionSpear.h"
#include "Particle_DamageEffect.h"
#include "Include_Common.h"
#include "Player_Hp_Bar.h"
#include "Monster_Hp_Bar.h"
#include "HP_Frame.h"
#include "Monster_Hit_Effect.h"
#include "Monster_Death_Effect.h"
#include "..\Engine_SOURCE\jkAudioSource.h"


namespace jk
{
	Monster_LionSpear::Monster_LionSpear()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}
	Monster_LionSpear::~Monster_LionSpear()
	{
	}


	void Monster_LionSpear::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_tr = GetComponent<Transform>();
		_pos = _tr->GetPosition();
		_first_place = _pos;


		as = AddComponent<AudioSource>();
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\Recruit\\Recruit_Atk_Ready01.wav", "Recruit_Atk_Ready01");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\Recruit\\Recruit_Atk_Ready02.wav", "Recruit_Atk_Ready02");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\Recruit\\Recruit_Atk_Ready03.wav", "Recruit_Atk_Ready03");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\Recruit\\Recruit_Atk_Ready04.wav", "Recruit_Atk_Ready04");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\Recruit\\Atk_Sword_wariior.wav", "Atk_Sword_wariior");

		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\Common_Dead\\Enemy_Dead.wav", "Enemy_Dead");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\Common_Hit\\Hit_Blunt_Small.wav", "Hit_Blunt_Small");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\Common_Hit\\Hit_Sword_Small.wav", "Hit_Sword_Small");


		//as->Play("Atk_Sword_wariior");


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_Spear\\AttackA", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_Spear\\AttackA_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_Spear\\AttackB", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_Spear\\AttackB_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_Spear\\Dead", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_Spear\\Hit", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_Spear\\Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_Spear\\Walk", this);


		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_Spear\\AttackA", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_Spear\\AttackA_Ready", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_Spear\\AttackB", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_Spear\\AttackB_Ready", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_Spear\\Dead", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_Spear\\Hit", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_Spear\\Idle", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_Spear\\Walk", this, 1);

		//bind 부분
		at->CompleteEvent(L"Lion_SpearAttackA") = std::bind(&Monster_LionSpear::complete_attack, this);
		at->CompleteEvent(L"Lion_SpearAttackAR") = std::bind(&Monster_LionSpear::complete_attack, this);
		at->CompleteEvent(L"Lion_SpearAttackB") = std::bind(&Monster_LionSpear::complete_attack, this);
		at->CompleteEvent(L"Lion_SpearAttackBR") = std::bind(&Monster_LionSpear::complete_attack, this);
		at->CompleteEvent(L"Lion_SpearHit") = std::bind(&Monster_LionSpear::complete_hit, this);
		at->CompleteEvent(L"Lion_SpearHitR") = std::bind(&Monster_LionSpear::complete_hit, this);

		at->PlayAnimation(L"Lion_SpearIdle", true);

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
			hp_tr->SetPosition(Vector3(_pos.x, _pos.y + 50.f, _pos.z - 1.5f));
			hp_tr->SetScale(48.f, 3.f, 0.f);
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
			Hit_Box->SetState(eState::Paused);
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
	void Monster_LionSpear::Update()
	{
		SetDirection();
		Particle_Control();
		Hpcontrol();
		Effect_Control();


		switch (_state)
		{
		case jk::Monster_LionSpear::Monster_Lion_State::Idle:
			idle();
			break;

		case jk::Monster_LionSpear::Monster_Lion_State::AttackA:
			attackA();
			break;

		case jk::Monster_LionSpear::Monster_Lion_State::AttackA_Ready:
			attackA_ready();
			break;


		case jk::Monster_LionSpear::Monster_Lion_State::AttackB:
			attackB();
			break;

		case jk::Monster_LionSpear::Monster_Lion_State::AttackB_Ready:
			attackB_ready();
			break;

		case jk::Monster_LionSpear::Monster_Lion_State::Dead:
			dead();
			break;

		case jk::Monster_LionSpear::Monster_Lion_State::Hit:
			hit();
			break;

		case jk::Monster_LionSpear::Monster_Lion_State::Walk:
			walk();
			break;

		case jk::Monster_LionSpear::Monster_Lion_State::WalkR:
			walk_R();
			break;

		case jk::Monster_LionSpear::Monster_Lion_State::WalkL:
			walk_L();
			break;

		default:
			break;
		}

		_tr->SetPosition(_pos);
		GameObject::Update();
	}
	void Monster_LionSpear::LateUpdate()
	{
		Transform* HitBox_TR = Hit_Box->GetComponent<Transform>();
		if (_attack_ColA == true)
		{
			Hit_Box->SetSize(Vector2(110.f, 20.f));
			Hit_Box->SetCenter(Vector3(100.f, 100.f, -250.f));

			Hit_Box->SetState(eState::Active);
			if (_attackdir == 1)
				HitBox_TR->SetPosition(Vector3(_pos.x + 30, _pos.y - 30, _pos.z));
			else
				HitBox_TR->SetPosition(Vector3(_pos.x - 30, _pos.y - 30, _pos.z));
		}
		else if (_attack_ColB == true)
		{
			Hit_Box->SetSize(Vector2(200.f, 150.f));
			Hit_Box->SetCenter(Vector3(100.f, 100.f, -250.f));

			Hit_Box->SetState(eState::Active);
			if (_attackdir == 1)
				HitBox_TR->SetPosition(Vector3(_pos.x, _pos.y, _pos.z));
			else
				HitBox_TR->SetPosition(Vector3(_pos.x, _pos.y, _pos.z));
		}
		else
		{
			Hit_Box->SetState(eState::Paused);
		}

		_collider->SetSize(Vector2(0.35f, 0.75f));
		_collider->SetCenter(Vector2(1.f, -8.5f));


		GameObject::LateUpdate();
	}
	void Monster_LionSpear::Render()
	{
		GameObject::Render();
	}


	void Monster_LionSpear::OnCollisionEnter(Collider2D* other)
	{
		if (HitBox_Player* player = dynamic_cast<HitBox_Player*>(other->GetOwner()))
		{
			if (_state == Monster_Lion_State::Dead)
				return;

			_Damage = player->GetDamage();

			Particle_DamageEffect* mr = Hit_Particle->GetComponent<Particle_DamageEffect>();
			if (!(_state == Monster_Lion_State::AttackA || _state == Monster_Lion_State::AttackA_Ready || _state == Monster_Lion_State::AttackB || _state == Monster_Lion_State::AttackB_Ready))
			{
				_state = Monster_Lion_State::Hit;
				if (_Dir == 1)
				{
					at->PlayAnimation(L"Lion_SpearHit", false);
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
					at->PlayAnimation(L"Lion_SpearHitR", false);
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
					_state = Monster_Lion_State::Dead;
					as->Stop("Enemy_Dead");
					_Hit_Effect->_effect_animation = true;
					if (_Dir == 1)
					{
						at->PlayAnimation(L"Lion_SpearDead", false);
						_Hit_Effect->SetDirection(1);
					}
					else
					{
						at->PlayAnimation(L"Lion_SpearDeadR", false);
						_Hit_Effect->SetDirection(-1);
					}
					_Death_Effect->SetState(eState::Active);
				}
			}

			if ((_state == Monster_Lion_State::AttackA || _state == Monster_Lion_State::AttackA_Ready || _state == Monster_Lion_State::AttackB || _state == Monster_Lion_State::AttackB_Ready))
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
					_state = Monster_Lion_State::Dead;
					as->Stop("Enemy_Dead");
					_Hit_Effect->_effect_animation = true;
					if (_Dir == 1)
					{
						at->PlayAnimation(L"Lion_SpearDead", false);
						_Hit_Effect->SetDirection(1);
					}
					else
					{
						at->PlayAnimation(L"Lion_SpearDeadR", false);
						_Hit_Effect->SetDirection(-1);
					}
					_Death_Effect->SetState(eState::Active);
				}
			}
		}

		if (Skul_head* player = dynamic_cast<Skul_head*>(other->GetOwner()))
		{
			if (_state == Monster_Lion_State::Dead)
				return;

			_Damage = player->GetDamage();

			Particle_DamageEffect* mr = Hit_Particle->GetComponent<Particle_DamageEffect>();
			if (!(_state == Monster_Lion_State::AttackA || _state == Monster_Lion_State::AttackA_Ready || _state == Monster_Lion_State::AttackB || _state == Monster_Lion_State::AttackB_Ready))
			{
				Particle_DamageEffect* mr = Hit_Particle->GetComponent<Particle_DamageEffect>();
				if (player->_Head_Attack == false && _bulletcheck == 0)
				{
					if (player->_Ground_check == true)
						return;

					_state = Monster_Lion_State::Hit;
					as->Play("Hit_Blunt_Small");
					if (_Dir == 1)
					{
						at->PlayAnimation(L"Lion_SpearHit", false);
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
						at->PlayAnimation(L"Lion_SpearHitR", false);
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
						_state = Monster_Lion_State::Dead;
						as->Stop("Enemy_Dead");
						_Hit_Effect->_effect_animation = true;
						if (_Dir == 1)
						{
							at->PlayAnimation(L"Lion_SpearDead", false);
							_Hit_Effect->SetDirection(1);
						}
						else
						{
							at->PlayAnimation(L"Lion_SpearDeadR", false);
							_Hit_Effect->SetDirection(-1);
						}
						_Death_Effect->SetState(eState::Active);
					}
					_bulletcheck++;
				}
			}

			if ((_state == Monster_Lion_State::AttackA || _state == Monster_Lion_State::AttackA_Ready || _state == Monster_Lion_State::AttackB || _state == Monster_Lion_State::AttackB_Ready))
			{
				Particle_DamageEffect* mr = Hit_Particle->GetComponent<Particle_DamageEffect>();
				if (player->_Head_Attack == false && _bulletcheck == 0)
				{
					if (player->_Ground_check == true)
						return;


					as->Play("Hit_Blunt_Small");
					if (_Dir == 1)
					{
						at->PlayAnimation(L"Lion_SpearHit", false);
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
						_state = Monster_Lion_State::Dead;
						as->Stop("Enemy_Dead");
						_Hit_Effect->_effect_animation = true;
						if (_Dir == 1)
						{
							at->PlayAnimation(L"Lion_SpearDead", false);
							_Hit_Effect->SetDirection(1);
						}
						else
						{
							at->PlayAnimation(L"Lion_SpearDeadR", false);
							_Hit_Effect->SetDirection(-1);
						}
						_Death_Effect->SetState(eState::Active);
					}
					_bulletcheck++;
				}
			}
		}
	}
	void Monster_LionSpear::OnCollisionStay(Collider2D* other)
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

		if (Ground_and_Wall* mGround = dynamic_cast<Ground_and_Wall*>(other->GetOwner()))
		{
			Transform* GRTR = mGround->GetComponent<Transform>();
			Vector3 GRpos = GRTR->GetPosition();

			if (GRpos.x > _pos.x)
			{
				_rigidbody->ClearVelocity();
				if (_state == Monster_Lion_State::WalkR)
				{
					_state = Monster_Lion_State::WalkL;
					at->PlayAnimation(L"Lion_SpearWalkR", true);
				}
			}
			else if (GRpos.x < _pos.x)
			{
				_rigidbody->ClearVelocity();
				if (_state == Monster_Lion_State::WalkL)
				{
					_state = Monster_Lion_State::WalkR;
					at->PlayAnimation(L"Lion_SpearWalk", true);
				}
			}
		}
	}
	void Monster_LionSpear::OnCollisionExit(Collider2D* other)
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


	void Monster_LionSpear::idle()
	{

		if (_followskul == true)
		{
			_time += static_cast<float>(Time::DeltaTime());

			if (_time > 2.f)
			{
				if ((_distance >= 90 || _distance <= -90))
				{
					_state = Monster_Lion_State::Walk;
					if (_Dir == 1)
					{
						at->PlayAnimation(L"Lion_SpearWalk", true);
					}
					else
					{
						at->PlayAnimation(L"Lion_SpearWalkR", true);
					}
				}
				if (_distance > -90 && _distance < 90)
				{
					if (_AttackSellect == 0)
					{
						_state = Monster_Lion_State::AttackA_Ready;
						if (_Dir == 1)
						{
							at->PlayAnimation(L"Lion_SpearAttackA_Ready", false);
							_attackdir = 1;
						}
						else
						{
							at->PlayAnimation(L"Lion_SpearAttackA_ReadyR", false);
							_attackdir = -1;
						}						
					}
					else if(_AttackSellect == 1)
					{
						_state = Monster_Lion_State::AttackB_Ready;
						if (_Dir == 1)
						{
							at->PlayAnimation(L"Lion_SpearAttackB_Ready", false);
							_attackdir = 1;
						}
						else
						{
							at->PlayAnimation(L"Lion_SpearAttackB_ReadyR", false);
							_attackdir = -1;
						}
						_AttackSellect = 0;
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
					_state = Monster_Lion_State::WalkR;
					at->PlayAnimation(L"Lion_SpearWalk", true);
				}
				else if (_walkdir == -1)
				{
					_state = Monster_Lion_State::WalkL;
					at->PlayAnimation(L"Lion_SpearWalkR", true);
				}
			}
		}
	}
	void Monster_LionSpear::attackA()
	{
		_attack_ColA = true;
		_AttackSellect = 1;
	}
	void Monster_LionSpear::attackA_ready()
	{
		_attacktime += static_cast<float>(Time::DeltaTime());
		if (_attacktime >= 1)
		{
			_state = Monster_Lion_State::AttackA;
			as->Play("Recruit_Atk_Ready04");
			as->Play("Atk_Sword_wariior");
			if (_attackdir == 1)
			{
				at->PlayAnimation(L"Lion_SpearAttackA", true);
				_rigidbody->SetVelocity(Vector2(250.f, 0.f));
			}
			else
			{
				at->PlayAnimation(L"Lion_SpearAttackAR", true);
				_rigidbody->SetVelocity(Vector2(-250.f, 0.f));
			}
			_attacktime = 0;
		}
	}
	void Monster_LionSpear::attackB()
	{		
		_attack_ColB = true;
		_AttackSellect = 0;
	}
	void Monster_LionSpear::attackB_ready()
	{
		_attacktime += static_cast<float>(Time::DeltaTime());
		if (_attacktime >= 0.5)
		{
			_state = Monster_Lion_State::AttackB;
			as->Play("Recruit_Atk_Ready04");
			as->Play("Atk_Sword_wariior");
			if (_attackdir == 1)
				at->PlayAnimation(L"Lion_SpearAttackB", true);
			else
				at->PlayAnimation(L"Lion_SpearAttackBR", true);
			_attacktime = 0;
		}
	}

	void Monster_LionSpear::dead()
	{
	}
	void Monster_LionSpear::hit()
	{
		_attacktime += static_cast<float>(Time::DeltaTime());
		if (_attacktime >= 0.5)
		{
			_state = Monster_Lion_State::Idle;
			if (_Dir == 1)
				at->PlayAnimation(L"Lion_SpearIdle", true);
			else
				at->PlayAnimation(L"Lion_SpearIdleR", true);
			_attacktime = 0;
		}
	}
	void Monster_LionSpear::walk()
	{
		if (_distance > -90 && _distance < 90)
		{
			if (_AttackSellect == 0)
			{
				_state = Monster_Lion_State::AttackA_Ready;
				if (_Dir == 1)
				{
					at->PlayAnimation(L"Lion_SpearAttackA_Ready", false);
					_attackdir = 1;
				}
				else
				{
					at->PlayAnimation(L"Lion_SpearAttackA_ReadyR", false);
					_attackdir = -1;
				}
			}
			else if (_AttackSellect == 1)
			{
				_state = Monster_Lion_State::AttackB_Ready;
				if (_Dir == 1)
				{
					at->PlayAnimation(L"Lion_SpearAttackB_Ready", false);
					_attackdir = 1;
				}
				else
				{
					at->PlayAnimation(L"Lion_SpearAttackB_ReadyR", false);
					_attackdir = -1;
				}				
			}
		}
		else
		{
			if (_distance >= 0.f)
				_pos.x += 250.f * static_cast<float>(Time::DeltaTime());
			else
				_pos.x -= 250.f * static_cast<float>(Time::DeltaTime());
			_tr->SetPosition(_pos);
		}
	}
	void Monster_LionSpear::walk_R()
	{
		if (_walkdistance > -100)
			_pos.x += 80.f * static_cast<float>(Time::DeltaTime());
		else
		{
			_state = Monster_Lion_State::Idle;
			at->PlayAnimation(L"Lion_SpearIdle", true);
			_time = 0; _walkdir *= -1;
		}
	}
	void Monster_LionSpear::walk_L()
	{
		if (_walkdistance < 100)
			_pos.x -= 80.f * static_cast<float>(Time::DeltaTime());
		else
		{
			_state = Monster_Lion_State::Idle;
			at->PlayAnimation(L"Lion_SpearIdleR", true);
			_time = 0; _walkdir *= -1;
		}
	}


	void Monster_LionSpear::SetDirection()
	{
		_tr = GetComponent<Transform>();
		_pos = _tr->GetPosition();
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
	void Monster_LionSpear::Particle_Control()
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
	void Monster_LionSpear::Hpcontrol()
	{
		Transform* hp_tr = Monster_Hp->GetComponent<Transform>();
		hp_tr->SetPosition(Vector3(_pos.x, _pos.y - 70.f, _pos.z - 2.f));

		Transform* hpdamege_tr = Monster_DamegeHp->GetComponent<Transform>();
		hpdamege_tr->SetPosition(Vector3(_pos.x, _pos.y - 70.f, _pos.z - 1.5f));

		Transform* hpfr_tr = Hpbar_Frame->GetComponent<Transform>();
		hpfr_tr->SetPosition(Vector3(_pos.x, _pos.y - 70.f, _pos.z - 1.f));


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
			Hit_Box->SetState(eState::Paused);
			_Die = true;
			this->SetState(eState::Paused);
		}
	}
	void Monster_LionSpear::Effect_Control()
	{
		{
			Transform* _Hit_Effect_TR = _Hit_Effect->GetComponent<Transform>();
			if (_Dir == 1)
				_Hit_Effect_TR->SetPosition(Vector3(_pos.x + 15, _pos.y, _pos.z - 1));
			else
				_Hit_Effect_TR->SetPosition(Vector3(_pos.x - 15, _pos.y, _pos.z - 1));
		}
		{
			Transform* _Effect_TR = _Death_Effect->GetComponent<Transform>();
			_Effect_TR->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 1));
		}
	}



	void Monster_LionSpear::complete_attack()
	{
		_attack_ColA = false;
		_attack_ColB = false;
		as->Stop("Atk_Sword_wariior");
		_rigidbody->ClearVelocity();
		_state = Monster_Lion_State::Idle;
		if (_Dir == 1)
			at->PlayAnimation(L"Lion_SpearIdle", true);
		else
			at->PlayAnimation(L"Lion_SpearIdleR", true);

		_time = 0;
	}
	void Monster_LionSpear::complete_hit()
	{
		_state = Monster_Lion_State::Idle;
		if (_Dir == 1)
			at->PlayAnimation(L"Lion_SpearIdle", true);
		else
			at->PlayAnimation(L"Lion_SpearIdleR", true);

		_time = 0;
	}
}