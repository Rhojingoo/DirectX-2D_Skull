#include "Monster_LionWizard.h"
#include <iostream>
#include <random>
#include "Particle_DamageEffect.h"
#include "Include_Common.h"
#include "Monster_StoneWizard_Teleport.h"
#include "Monster_StoneWizard_Icicle_Effect.h"
#include "Monster_Stone_wizard_IcicleBullet.h"
#include "LionWizard_Bullet_Create.h"
#include "LionWizard_Bullet.h"
#include "Monster_Hp_Bar.h"
#include "HP_Frame.h"
#include "Monster_Hit_Effect.h"
#include "Monster_Death_Effect.h"
#include "..\Engine_SOURCE\jkAudioSource.h"

namespace jk
{
	Monster_LionWizard::Monster_LionWizard()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}

	Monster_LionWizard::~Monster_LionWizard()
	{
	}

	void Monster_LionWizard::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(false);
		tr = GetComponent<Transform>();



		as = AddComponent<AudioSource>();
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\Stage1\\GiganticEnt\\GiganticEnt_RangeAttackReady.wav", "GiganticEnt_RangeAttackReady");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\Stage1\\GiganticEnt\\GiganticEnt_RangeAttack.wav", "GiganticEnt_RangeAttack");

		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\Common_Dead\\Enemy_Dead.wav", "Enemy_Dead");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\Common_Hit\\Hit_Blunt_Small.wav", "Hit_Blunt_Small");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\Common_Hit\\Hit_Sword_Small.wav", "Hit_Sword_Small");

		//as->Play("Recruit_Atk_Ready01");
		//as->Play("Recruit_Atk_Ready02");
		//as->Play("Recruit_Atk_Ready03");
		//as->Play("Recruit_Atk_Ready04");
		//as->Play("Atk_Sword_wariior");



		at = AddComponent<Animator>(); 
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_wizard\\Attack_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_wizard\\Attack_Waiting", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_wizard\\Attack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_wizard\\Hit", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_wizard\\Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_wizard\\Teleport_In", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_wizard\\Teleport_Out", this);

		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_wizard\\Attack_Ready", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_wizard\\Attack_Waiting", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_wizard\\Attack", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_wizard\\Hit", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_wizard\\Idle", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_wizard\\Teleport_In", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_wizard\\Teleport_Out", this, 1);


		//bind 부분
		at->CompleteEvent(L"Lion_wizardAttack_Ready") = std::bind(&Monster_LionWizard::complete_attack_ready, this);
		at->CompleteEvent(L"Lion_wizardAttack_ReadyR") = std::bind(&Monster_LionWizard::complete_attack_ready, this);
		at->CompleteEvent(L"Lion_wizardAttack") = std::bind(&Monster_LionWizard::complete_attack, this);
		at->CompleteEvent(L"Lion_wizardAttackR") = std::bind(&Monster_LionWizard::complete_attack, this);
		at->CompleteEvent(L"Lion_wizardTeleport_In") = std::bind(&Monster_LionWizard::complete_telleport_in, this);
		at->CompleteEvent(L"Lion_wizardTeleport_InR") = std::bind(&Monster_LionWizard::complete_telleport_in, this);
		at->CompleteEvent(L"Lion_wizardTeleport_Out") = std::bind(&Monster_LionWizard::complete_telleport_out, this);
		at->CompleteEvent(L"Lion_wizardTeleport_OutR") = std::bind(&Monster_LionWizard::complete_telleport_out, this);

		at->PlayAnimation(L"Lion_wizardIdle", true);


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
			hp_tr->SetPosition(Vector3(pos.x, pos.y + 50.f, pos.z - 1.5f));
			hp_tr->SetScale(44.f, 3.f, 0.f);
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
			BulletCreate = new LionWizard_Bullet_Create();
			BulletCreate->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, BulletCreate);
			Transform* effect_tr = BulletCreate->GetComponent<Transform>();
			effect_tr->SetPosition(tr->GetPosition());
			BulletCreate->SetState(eState::Paused);
		}

		for(int i = 0; i<3;i++)
		{
			LionBullet[i] = new LionWizard_Bullet();
			LionBullet[i]->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Bullet, LionBullet[i]);
			Transform* effect_tr = LionBullet[i]->GetComponent<Transform>();
			effect_tr->SetPosition(tr->GetPosition());
			LionBullet[i]->SetState(eState::Paused);
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
	void Monster_LionWizard::Update()
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
		case jk::Monster_LionWizard::LionWizard_State::Idle:
			idle();
			break;

		case jk::Monster_LionWizard::LionWizard_State::Attack_Ready:
			attack_ready();
			break;

		case jk::Monster_LionWizard::LionWizard_State::Attack_Waiting:
			attack_waiting();
			break;			

		case jk::Monster_LionWizard::LionWizard_State::Attack:
			attack();
			break;

		case jk::Monster_LionWizard::LionWizard_State::Hit:
			hit();
			break;

		case jk::Monster_LionWizard::LionWizard_State::Teleport_In:
			teleport_in();
			break;

		case jk::Monster_LionWizard::LionWizard_State::Teleport_Out:
			teleport_out();
			break;

		case jk::Monster_LionWizard::LionWizard_State::Dead:
			dead();
			break;

		default:
			break;
		}

		Effect_tr->SetPosition(tr->GetPosition());
		GameObject::Update();
	}
	void Monster_LionWizard::LateUpdate()
	{
		if (_state == LionWizard_State::Dead)
			_collider->SetSize(Vector2(0.f, 0.f));
		else
		{
			_collider->SetSize(Vector2(0.45f, 0.7f));
			_collider->SetCenter(Vector2(1.f, -5.8f));
		}

		GameObject::LateUpdate();
	}
	void Monster_LionWizard::Render()
	{
		GameObject::Render();
	}


	void Monster_LionWizard::OnCollisionEnter(Collider2D* other)
	{
		if (HitBox_Player* player = dynamic_cast<HitBox_Player*>(other->GetOwner()))
		{
			_Damage = player->GetDamage();

			Particle_DamageEffect* mr = Hit_Particle->GetComponent<Particle_DamageEffect>();

			if (!(_state == LionWizard_State::Attack || _state == LionWizard_State::Attack_Ready))
			{
				_state = LionWizard_State::Hit;
				if (_Dir == 1)
				{
					at->PlayAnimation(L"Lion_wizardHit", false);
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
				if (_Dir == -1)
				{
					at->PlayAnimation(L"Lion_wizardHitR", false);
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
					_state = LionWizard_State::Dead;
					as->Stop("Enemy_Dead");
					_Death_Effect->_effect_animation = true;
					_Death_Effect->SetState(eState::Active);
					_CurrenHp = 0;
				}
			}

			if ((_state == LionWizard_State::Attack || _state == LionWizard_State::Attack_Ready))
			{
				if (_Dir == 1)
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
				if (_Dir == -1)
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
					_state = LionWizard_State::Dead;
					as->Stop("Enemy_Dead");
					_Hit_Effect->_effect_animation = true;
					_Death_Effect->SetState(eState::Active);
					_CurrenHp = 0;
				}
			}
		}

		if (Skul_head* player = dynamic_cast<Skul_head*>(other->GetOwner()))
		{
			_Damage = player->GetDamage();

			if (!(_state == LionWizard_State::Attack || _state == LionWizard_State::Attack_Ready))
			{
				if (player->_Head_Attack == false && _bulletcheck == 0)
				{
					if (player->_Ground_check == true)
						return;

					as->Play("Hit_Blunt_Small");
					_state = LionWizard_State::Hit;
					if (_Dir == 1)
					{
						at->PlayAnimation(L"Lion_wizardHit", false);
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
					if (_Dir == -1)
					{
						at->PlayAnimation(L"Lion_wizardHitR", false);
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
						_state = LionWizard_State::Dead;
						as->Stop("Enemy_Dead");
						_Hit_Effect->_effect_animation = true;
						_Death_Effect->SetState(eState::Active);
						_CurrenHp = 0;
					}
					_bulletcheck++;
				}
			}


			if ((_state == LionWizard_State::Attack || _state == LionWizard_State::Attack_Ready))
			{
				if (player->_Head_Attack == false && _bulletcheck == 0)
				{
					if (player->_Ground_check == true)
						return;

					as->Play("Hit_Blunt_Small");
					_state = LionWizard_State::Hit;
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
					}
					if (_CurrenHp <= 0)
					{
						_state = LionWizard_State::Dead;
						as->Stop("Enemy_Dead");
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
	void Monster_LionWizard::OnCollisionStay(Collider2D* other)
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
				Transform* GRTR = mGround->GetComponent<Transform>();
				Vector3 GRpos = GRTR->GetPosition();
				{
					Collider2D* GRCol = mGround->GetComponent<Collider2D>();
					float GrColsize = GRCol->GetScale().y / 2;
					float playercolsize = _collider->GetScale().y / 2;
					float Sizecheck = playercolsize + GrColsize + 5;


					float CheckPos = fabs(pos.y - GRpos.y);
					if (Sizecheck > CheckPos)
					{
						pos.y = GRpos.y + Sizecheck;
						tr->SetPosition(pos);
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

		if (Ground_and_Wall* mGround = dynamic_cast<Ground_and_Wall*>(other->GetOwner()))
		{
			Transform* GRTR = mGround->GetComponent<Transform>();
			Vector3 GRpos = GRTR->GetPosition();
			_rigidbody->ClearVelocity();
		}
	}
	void Monster_LionWizard::OnCollisionExit(Collider2D* other)
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

	void Monster_LionWizard::idle()
	{
		_BulletFire = false;
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> distribution(0, 1);


		_time += static_cast<float>(Time::DeltaTime());

		if (_time > 2.5f)
		{
			if ((_distance < 300 && _distance > -300))
			{
				_state = LionWizard_State::Attack_Ready;
				if (_Dir == 1)
					at->PlayAnimation(L"Lion_wizardAttack_Ready", true);
				else
					at->PlayAnimation(L"Lion_wizardAttack_ReadyR", true);
			}


			if (_distance <= -400 || _distance >= 400)
			{
				if (_teleportCheck == false)
				{
					_state = LionWizard_State::Teleport_In;
					if (_Dir == 1)
					{
						_teleportCheck = true;
						at->PlayAnimation(L"Lion_wizardTeleport_In", true);
						Effect_tr->SetPosition(tr->GetPosition());
					}
					else
					{
						_teleportCheck = true;
						at->PlayAnimation(L"Lion_wizardTeleport_InR", true);
						Effect_tr->SetPosition(tr->GetPosition());
					}
				}
			}
		}
	}
	void Monster_LionWizard::attack_ready()
	{
		if (_attack_ready == true)
		{
			if (_Dir == 1)
			{
				at->PlayAnimation(L"Lion_wizardAttack_Waiting", false);
				_AttackDir = 1;
			}
			else
			{
				at->PlayAnimation(L"Lion_wizardAttack_WaitingR", false);
				_AttackDir = -1;
			}
			
			_attack_ready = false;
			_state = LionWizard_State::Attack_Waiting;
			as->Play("GiganticEnt_RangeAttackReady");
			_attack = true;
		}
	}
	void Monster_LionWizard::attack_waiting()
	{
		if (BulletCreate->_endanimation == true)
		{
			Transform* bulletCreate_tr = BulletCreate->GetComponent<Transform>();

			for (int i = 0; i < 3; i++)
			{
				if (LionBullet[i]->_animationswitch == false)
				{
					Transform* bullet_tr = LionBullet[i]->GetComponent<Transform>();
					bullet_tr->SetPosition(bulletCreate_tr->GetPosition());
					if (_AttackDir == 1)
					{
						LionBullet[i]->SetDirection(1);
						at->PlayAnimation(L"Lion_wizardAttack", true);
					}
					else
					{
						LionBullet[i]->SetDirection(-1);
						at->PlayAnimation(L"Lion_wizardAttackR", true);
					}
					LionBullet[i]->SetState(eState::Active);
					break;
				}
			}
			as->Play("GiganticEnt_RangeAttack");
			_state = LionWizard_State::Attack;
			BulletCreate->_endanimation = false;
		}
	}
	void Monster_LionWizard::attack()
	{
	}
	void Monster_LionWizard::hit()
	{
		_attacktime += static_cast<float>(Time::DeltaTime());
		if (_attacktime >= 1)
		{
			_state = LionWizard_State::Idle;
			if (_Dir == 1)
				at->PlayAnimation(L"Lion_wizardIdle", true);
			else
				at->PlayAnimation(L"Lion_wizardIdleR", true);
			_attacktime = 0;
			_hit_particle = true;
		}
	}
	void Monster_LionWizard::dead()
	{
		_attacktime += static_cast<float>(Time::DeltaTime());
		if (_attacktime >= 1)
		{
			_attacktime = 0;
			_hit_particle = true;
		}
	}


	void Monster_LionWizard::teleport_in()
	{
		if (_teleportCheck == false)
		{
			_attacktime += static_cast<float>(Time::DeltaTime());
			if (_attacktime > 0.15f)
			{
				if (_Dir == 1)
				{
					tr->SetPositionXY(Vector2(_playerpos.x - 100, _playerpos.y + 15));
					_state = LionWizard_State::Teleport_Out;
					at->PlayAnimation(L"Lion_wizardTeleport_Out", true);
					_rigidbody->SetGround(false);
					_Ground_check = false;
				}
				else
				{
					tr->SetPositionXY(Vector2(_playerpos.x + 100, _playerpos.y + 15));
					_state = LionWizard_State::Teleport_Out;
					at->PlayAnimation(L"Lion_wizardTeleport_OutR", true);
					_rigidbody->SetGround(false);
					_Ground_check = false;
				}
				_attacktime = 0;
			}
		}
	}
	void Monster_LionWizard::teleport_out()
	{
		if (_teleportCheck == false)
		{
			if (_Dir == 1)
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

	void Monster_LionWizard::Particle_Control()
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
	void Monster_LionWizard::Hpcontrol()
	{
		Transform* hp_tr = Monster_Hp->GetComponent<Transform>();
		hp_tr->SetPosition(Vector3(pos.x, pos.y - 55.f, pos.z - 2.f));

		Transform* hpdamege_tr = Monster_DamegeHp->GetComponent<Transform>();
		hpdamege_tr->SetPosition(Vector3(pos.x, pos.y - 55.f, pos.z - 1.5f));

		Transform* hpfr_tr = Hpbar_Frame->GetComponent<Transform>();
		hpfr_tr->SetPosition(Vector3(pos.x, pos.y - 55.f, pos.z - 1.f));

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
			for (int i = 0; i < 3; i++)
			{
				LionBullet[i]->SetState(eState::Paused);
			}
			this->SetState(eState::Paused);
		}
	}
	void Monster_LionWizard::Effect_Control()
	{
		{
			Transform* _Hit_Effect_TR = _Hit_Effect->GetComponent<Transform>();
			if (_Dir == 1)
				_Hit_Effect_TR->SetPosition(Vector3(pos.x + 15, pos.y, pos.z - 1));
			else
				_Hit_Effect_TR->SetPosition(Vector3(pos.x - 15, pos.y, pos.z - 1));
		}
		{
			Transform* _Effect_TR = _Death_Effect->GetComponent<Transform>();
			_Effect_TR->SetPosition(Vector3(pos.x, pos.y, pos.z - 1));
		}
	}
	void Monster_LionWizard::SetDirection()
	{
		_distance = _playerpos.x - pos.x;
		if (_distance >= 0.f)
			_Dir = 1;
		else
			_Dir = -1;
	}


	void Monster_LionWizard::complete_telleport_in()
	{
		if (_teleportCheck == true)
		{
			if (_Dir == 1)
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
	void Monster_LionWizard::complete_telleport_out()
	{
		if (_teleportCheck == true)
		{
			if (_Dir == 1)
			{
				_state = LionWizard_State::Idle;
				at->PlayAnimation(L"Lion_wizardIdle", true);
			}
			else
			{
				_state = LionWizard_State::Idle;
				at->PlayAnimation(L"Lion_wizardIdleR", true);
			}
			_teleportCheck = false;
			_time = 0.f;
		}
	}


	void Monster_LionWizard::complete_attack_ready()
	{
		if (_attack_ready == false)
		{
			if (_AttackDir == 1)
			{
				BulletCreate->_effect_On = true;
				BulletCreate->SetDirection(1);
				Transform* effect_tr = BulletCreate->GetComponent<Transform>();
				effect_tr->SetPosition(Vector3(pos.x, pos.y + 30, _playerpos.z - 1));
				BulletCreate->SetState(eState::Active);
			}
			else
			{
				BulletCreate->_effect_On = true;
				BulletCreate->SetDirection(-1);
				Transform* effect_tr = BulletCreate->GetComponent<Transform>();
				effect_tr->SetPosition(Vector3(pos.x, pos.y + 30, _playerpos.z - 1));
				BulletCreate->SetState(eState::Active);
			}
			_attack_ready = true;
		}
	}
	void Monster_LionWizard::complete_attack()
	{
		if (_BulletFire == false)
		{
			for (int i = 0; i < 3; i++)
			{
				if (LionBullet[i]->_animationswitch == false)
				{
					LionBullet[i]->_animationswitch = true;
					Transform* bullet_tr = LionBullet[i]->GetComponent<Transform>();
					Vector3 _Bullet_pos = bullet_tr->GetPosition();
					RigidBody* bullet_Rb = LionBullet[i]->GetComponent<RigidBody>();
					Vector2 attack_pos = Vector2(_playerpos.x - _Bullet_pos.x, _playerpos.y - _Bullet_pos.y);
					attack_pos.Normalize();
					bullet_Rb->SetGround(false);
					bullet_Rb->SetGravity(true);
					bullet_Rb->SetFriction(true);
					bullet_Rb->SetVelocity(Vector2(attack_pos.x * 150.f, attack_pos.y * 150));
					_BulletFire = true;
					break;
				}
			}
		}

		if (_Dir == 1)
		{
			_state = LionWizard_State::Idle;
			at->PlayAnimation(L"Lion_wizardIdle", true);		
		}
		else
		{
			_state = LionWizard_State::Idle;
			at->PlayAnimation(L"Lion_wizardIdleR", true);
		}
		_time = 0.f;
	}
}