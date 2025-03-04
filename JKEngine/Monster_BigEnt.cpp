#include "Monster_BigEnt.h"
#include "Particle_DamageEffect.h"
#include "Include_Common.h"
#include "Monster_BigEnt_EnergeBall.h"
#include "Monster_GiganticEnt_Stamp.h"
#include "Monster_Hit_Effect.h"
#include "Monster_Death_Effect.h"
#include "Monster_Hp_Bar.h"
#include "HP_Frame.h"
#include "..\Engine_SOURCE\jkAudioSource.h"

namespace jk
{
	int Monster_BigEnt::mDir = 1;

	Monster_BigEnt::Monster_BigEnt()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}
	Monster_BigEnt::~Monster_BigEnt()
	{
	}
	void Monster_BigEnt::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);



		as = AddComponent<AudioSource>();
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\Stage1\\GiganticEnt\\GiganticEnt_MeleeAttackReady.wav", "GiganticEnt_MeleeAttackReady");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\Stage1\\GiganticEnt\\Atk_Stomp_Large.wav", "Atk_Stomp_Large");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\Stage1\\GiganticEnt\\GiganticEnt_RangeAttackReady.wav", "GiganticEnt_RangeAttackReady");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\Stage1\\GiganticEnt\\GiganticEnt_RangeAttack.wav", "GiganticEnt_RangeAttack");


		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\Common_Dead\\Enemy_Dead.wav", "Enemy_Dead");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\Common_Hit\\Hit_Blunt_Small.wav", "Hit_Blunt_Small");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\Common_Hit\\Hit_Sword_Small.wav", "Hit_Sword_Small");


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GiganticEnt\\Attack_Melee_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GiganticEnt\\Attack_Melee", this);
		
		
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GiganticEnt\\Attack_Range_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GiganticEnt\\Attack_Range", this);


		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GiganticEnt\\Dead", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GiganticEnt\\Idle", this);

		at->CompleteEvent(L"GiganticEntAttack_Melee") = std::bind(&Monster_BigEnt::attack_idle, this);
		at->CompleteEvent(L"GiganticEntAttack_Range") = std::bind(&Monster_BigEnt::attack_idle, this);

		at->PlayAnimation(L"GiganticEntIdle", true);
		Scene* scene = SceneManager::GetInitializeScene();
		//ü�°���
		{
			Hpbar_Frame = new HP_Frame(L"EnemyHealthBar_BigFrame");
			scene->AddGameObject(eLayerType::Monster, Hpbar_Frame);
			Hpbar_Frame->SetName(L"hp_bar_frame");
			Transform* hp_tr = Hpbar_Frame->GetComponent<Transform>();
			hp_tr->SetPosition(Vector3(_pos.x, _pos.y + 50, _pos.z - 1));
			hp_tr->SetScale(85, 5, 0);
			Hpbar_Frame->SetState(eState::Paused);
		}

		{
			Monster_DamegeHp = new Monster_Hp_Bar(L"EnemyHealthBar_Damage");
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
			scene->AddGameObject(eLayerType::Monster, Monster_Hp);
			Monster_Hp->SetName(L"warrior_hp_bar");
			Transform* hp_tr = Monster_Hp->GetComponent<Transform>();
			hp_tr->SetPosition(Vector3(_pos.x, _pos.y + 50.f, _pos.z - 1.f));
			hp_tr->SetScale(80.f, 3.f, 0.f);
			Monster_Hp->Set_Max_Hp(_MaxHp);
			Monster_Hp->Set_Current_Hp(_MaxHp);
			Monster_Hp->SetState(eState::Paused);
		}






		{
			Hit_Box = new HitBox_Monster();
			Hit_Box->Initialize();
			scene->AddGameObject(eLayerType::Hitbox, Hit_Box);
			Hit_Box->SetSound(1);
			Hit_Box->SetState(eState::Paused);
		}
		{
			for (int i = 0; i < 8; i++)
			{
				Energe_Ball[i] = new Monster_BigEnt_EnergeBall;
				Energe_Ball[i]->Initialize();
				scene->AddGameObject(eLayerType::Bullet, Energe_Ball[i]);
				Transform* bullet_tr = Energe_Ball[i]->GetComponent<Transform>();
				bullet_tr->SetPosition(Vector3(_pos.x, _pos.y, -205.f));				
				Energe_Ball[i]->SetState(eState::Paused);
				set_energeball_Vellocity();
			}
		}
		{
			Attack_Stamp =  new Monster_GiganticEnt_Stamp;
			Attack_Stamp->Initialize();
			scene->AddGameObject(eLayerType::Effect, Attack_Stamp);
			Transform* bullet_tr = Attack_Stamp->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(_pos.x, _pos.y, -205.f));			
			Attack_Stamp->SetState(eState::Paused);
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
	void Monster_BigEnt::Update()
	{
		SetDirection();
		Particle_Control();
		Hpcontrol();
		Effect_Control();


		switch (_state)
		{
		case jk::Monster_BigEnt::Monster_BigEnt_State::Idle:idle();
			break;

		case jk::Monster_BigEnt::Monster_BigEnt_State::AttackA_Ready:
			attackA_ready();
			break;

		case jk::Monster_BigEnt::Monster_BigEnt_State::AttackA:
			attackA();
			break;

		case jk::Monster_BigEnt::Monster_BigEnt_State::AttackA_End:
			attackA_end();
			break;

		case jk::Monster_BigEnt::Monster_BigEnt_State::AttackB_Ready:
			attackB_ready();
			break;

		case jk::Monster_BigEnt::Monster_BigEnt_State::AttackB:
			attackB();
			break;

		case jk::Monster_BigEnt::Monster_BigEnt_State::Dead:dead();
			break;

		case jk::Monster_BigEnt::Monster_BigEnt_State::Hit:hit();
			break;

		case jk::Monster_BigEnt::Monster_BigEnt_State::Walk:walk();
			break;

		default:
			break;
		}
		GameObject::Update();
	}
	void Monster_BigEnt::LateUpdate()
	{
		Transform* HitBox_TR = Hit_Box->GetComponent<Transform>();
		if (_attack_Col == true)
		{
			Hit_Box->SetSize(Vector2(300.f, 30.f));
			HitBox_TR->SetPosition(Vector3(_pos.x, _pos.y-50, _pos.z));
			Hit_Box->SetState(eState::Active);
		}
		else
		{
			Hit_Box->SetState(eState::Paused);
		}

		if (_state == Monster_BigEnt_State::Dead)
		{
			_collider->SetSize(Vector2(0.f, 0.f));
			_collider->SetCenter(Vector2(0.f, 0.1f));
		}
		else
		{
			_collider->SetSize(Vector2(0.5f, 0.9f));
			_collider->SetCenter(Vector2(1.f, 0.1f));
		}




		GameObject::LateUpdate();
	}
	void Monster_BigEnt::Render()
	{
		GameObject::Render();
	}
	void Monster_BigEnt::OnCollisionEnter(Collider2D* other)
	{
		if (HitBox_Player* player = dynamic_cast<HitBox_Player*>(other->GetOwner()))
		{
			if (_state == Monster_BigEnt_State::Dead)
				return;

			_Damage = player->GetDamage();

			Particle_DamageEffect* mr = Hit_Particle->GetComponent<Particle_DamageEffect>();
			
			if (mDir == 1)
			{			
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
				at->PlayAnimation(L"GiganticEntDead", false);
				as->Stop("Enemy_Dead");
				_state = Monster_BigEnt_State::Dead;
				_Hit_Effect->_effect_animation = true;
				_Death_Effect->SetState(eState::Active);
			}
			
		}

		if (Skul_head* player = dynamic_cast<Skul_head*>(other->GetOwner()))
		{
			if (_state == Monster_BigEnt_State::Dead)
				return;

			_Damage = player->GetDamage();

			Particle_DamageEffect* mr = Hit_Particle->GetComponent<Particle_DamageEffect>();
			
			if (player->_Head_Attack == false && _bulletcheck == 0)
			{
				if (player->_Ground_check == true)
					return;
										
				as->Play("Hit_Blunt_Small");
				if (mDir == 1)
				{
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
					as->Stop("Enemy_Dead");
					at->PlayAnimation(L"GiganticEntDead", false);
					_state = Monster_BigEnt_State::Dead;
					_Hit_Effect->_effect_animation = true;
				}
				_bulletcheck++;
			}
			
		}
	}
	void Monster_BigEnt::OnCollisionStay(Collider2D* other)
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
	void Monster_BigEnt::OnCollisionExit(Collider2D* other)
	{
		if (Skul_head* player = dynamic_cast<Skul_head*>(other->GetOwner()))
		{
			_bulletcheck = 0;
		}
	}

	void Monster_BigEnt::idle()
	{
		_time += static_cast<float>(Time::DeltaTime());;
		if (_time > 2.f)
		{

			if ((_distance <= 200) && (_distance >= -200))
			{
				if (_choiceattack == 0)
				{
					_state = Monster_BigEnt_State::AttackA_Ready;
					at->PlayAnimation(L"GiganticEntAttack_Melee_Ready", false);
				}
				else if (_choiceattack == 1)
				{
					_state = Monster_BigEnt_State::AttackB_Ready;
					as->Play("GiganticEnt_RangeAttackReady");
					at->PlayAnimation(L"GiganticEntAttack_Range_Ready", false);
				}
			}
			else
			{
				_state = Monster_BigEnt_State::AttackB_Ready;
				as->Play("GiganticEnt_RangeAttackReady");
				at->PlayAnimation(L"GiganticEntAttack_Range_Ready", false);
			}
		}		
	}


	void Monster_BigEnt::attackA_ready()
	{
		_attack_time += static_cast<float>(Time::DeltaTime());
		if (_attack_time > 1.0)
		{
			_state = Monster_BigEnt_State::AttackA;
			as->Play("GiganticEnt_MeleeAttackReady");
			at->PlayAnimation(L"GiganticEntAttack_Melee", true);		
			_attack_time = 0;
		}
	}
	void Monster_BigEnt::attackA()
	{
		Transform* bullet_tr = Attack_Stamp->GetComponent<Transform>();
		bullet_tr->SetPosition(Vector3(_pos.x, _pos.y-25, _pos.z - 1));
		Attack_Stamp->SetState(eState::Active);
		_attack_Col = true;
	}
	void Monster_BigEnt::attackA_end()
	{
	}

	void Monster_BigEnt::attackB_ready()
	{
		_attack_time += static_cast<float>(Time::DeltaTime());
		if (_attack_time > 1.0)
		{
			set_energeball_pos();
			energeball_attack();
			_state = Monster_BigEnt_State::AttackB;
			as->Play("GiganticEnt_RangeAttack");			
			at->PlayAnimation(L"GiganticEntAttack_Range", false);
			_attack_time = 0;
		}
	}
	void Monster_BigEnt::attackB()
	{
		_attack_time += static_cast<float>(Time::DeltaTime());
		if (_attack_time > 2.0)
		{
			_state = Monster_BigEnt_State::Idle;
			at->PlayAnimation(L"GiganticEntIdle", true);
			_attack_time = 0;
			_time = 0;
			_choiceattack = 1;
		}
	}

	void Monster_BigEnt::dead()
	{
		_Die = true;
	}
	void Monster_BigEnt::hit()
	{
	}
	void Monster_BigEnt::walk()
	{
	}


	void Monster_BigEnt::SetDirection()
	{
		tr = GetComponent<Transform>();
		_pos = tr->GetPosition();
		_velocity = _rigidbody->GetVelocity();
		_distance = _playerpos.x - _pos.x;
		if (_distance >= 0.f)
			mDir = 1;
		else
			mDir = -1;
	}
	void Monster_BigEnt::Particle_Control()
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
	void Monster_BigEnt::Hpcontrol()
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
	void Monster_BigEnt::Effect_Control()
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



	void Monster_BigEnt::attack_idle()
	{
		_attack_Col = false;
		as->Play("Atk_Stomp_Large");
		_state = Monster_BigEnt_State::Idle;
		at->PlayAnimation(L"GiganticEntIdle", true);
		_time = 0;
		_choiceattack = 0;
	}
	void Monster_BigEnt::set_energeball_pos()
	{
		for (int i = 0; i < 8; i++)
		{
			Transform* bullet_tr = Energe_Ball[i]->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 1));
		}
	}
	void Monster_BigEnt::energeball_attack()
	{
		for (int i = 0; i < 8; i++)
		{
			Transform* bullet_tr = Energe_Ball[i]->GetComponent<Transform>();
			RigidBody* bullet_rg = Energe_Ball[i]->GetComponent<RigidBody>();
			Energe_Ball[i]->_bullet_Life = true;
			Energe_Ball[i]->SetState(eState::Active);
			bullet_rg->SetGravity(true);
			bullet_rg->SetFriction(true);
			bullet_rg->SetVelocity(basic_pos[i]);
		}
	}
	void Monster_BigEnt::set_energeball_Vellocity()
	{
		basic_pos[0] = Vector2(0.f, 150.f);
		basic_pos[1] = Vector2(110.f, 110.f);
		basic_pos[2] = Vector2(150.f, 0.f);
		basic_pos[3] = Vector2(110.f, -110.f);
		basic_pos[4] = Vector2(0.f, -150.f);
		basic_pos[5] = Vector2(-110.f, -110.f);
		basic_pos[6] = Vector2(-150.f, 0.f);
		basic_pos[7] = Vector2(-110.f, 110.f);
	}
}