#include "Knight_male.h"
#include <iostream>


namespace jk
{
	int Knight_male::mDir = 1;
	bool Knight_male::_switch = false;
	


	Knight_male::Knight_male()
		:_state()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}
	Knight_male::~Knight_male()
	{
	}
	void Knight_male::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);

		
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Attack_A", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Attack_B", this); 
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Attack_C", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Attack_D", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Attack_E", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\BackDash", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Dash", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Die", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\EnergeBall", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Explosion_Loop", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Glorggy", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Hit", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Intro", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Jump", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Potion", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Stinger", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Stinger_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Finish_Move", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\UltimateSkill_Motion", this);
		
		
		

		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Attack_A", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Attack_B", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Attack_C", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Attack_D", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Attack_E", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\BackDash", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Dash", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Die", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\EnergeBall", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Explosion_Loop", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Glorggy", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Hit", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Idle", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Intro", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Jump", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Potion", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Stinger", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Stinger_Ready", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Finish_Move", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\UltimateSkill_Motion", this,1);
		
			
		//bind 부분
		at->CompleteEvent(L"Knight_maleAttack_A") = std::bind(&Knight_male::complete_Attack_A, this);
		at->CompleteEvent(L"Knight_maleAttack_B") = std::bind(&Knight_male::complete_Attack_B, this);
		at->CompleteEvent(L"Knight_maleAttack_C") = std::bind(&Knight_male::complete_Attack_C, this);
		at->CompleteEvent(L"Knight_maleAttack_AR") = std::bind(&Knight_male::complete_Attack_A, this);
		at->CompleteEvent(L"Knight_maleAttack_BR") = std::bind(&Knight_male::complete_Attack_B, this);
		at->CompleteEvent(L"Knight_maleAttack_CR") = std::bind(&Knight_male::complete_Attack_C, this);


		at->CompleteEvent(L"Knight_maleEnergeBall") = std::bind(&Knight_male::choicecombo, this);
		at->CompleteEvent(L"Knight_maleEnergeBallR") = std::bind(&Knight_male::choicecombo, this);

		at->CompleteEvent(L"Knight_maleUltimateSkill_Motion") = std::bind(&Knight_male::complete_ultimate, this);
		at->CompleteEvent(L"Knight_maleUltimateSkill_MotionR") = std::bind(&Knight_male::complete_ultimate, this);

		
		at->CompleteEvent(L"Knight_maleHit") = std::bind(&Knight_male::complete_hit, this);
		at->CompleteEvent(L"Knight_maleHitR") = std::bind(&Knight_male::complete_hit, this);

		at->CompleteEvent(L"Knight_maleIntro") = std::bind(&Knight_male::complete_Intro, this);
		at->CompleteEvent(L"Knight_maleIntroR") = std::bind(&Knight_male::complete_Intro, this);
		
		//UI 및 체력관련		
		{
			_MbossFace = new AdventureUI();
			_MbossFace->Initialize();
			_MbossFace->Set_animation(true);
			_MbossFace->Set_UISelect(4);
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::UI, _MbossFace);
			_MbossFace->SetName(L"_MbossFace");
			Transform* face_tr = _MbossFace->GetComponent<Transform>();
			face_tr->SetPosition(Vector3(762.f, 375.f, pos.z));
			face_tr->SetScale(26 * 2, 26.f * 2, 0);
		}

		{
			_State_UI = new MiniBoss_State_UI();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::UI, _State_UI);
			_State_UI->SetName(L"hp_bar_frame");
			Transform* hp_tr = _State_UI->GetComponent<Transform>();
			hp_tr->SetPosition(Vector3(685.f, 375.f, pos.z));
			hp_tr->SetScale(108.f * 2, 30.f * 2, 0);
		}
		{
			Monster_UIHp = new Monster_Hp_Bar(L"EnemyHealthBar");
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::UI, Monster_UIHp);
			Monster_UIHp->SetName(L"warrior_hp_bar");
			Transform* hp_tr = Monster_UIHp->GetComponent<Transform>();
			hp_tr->SetPosition(Vector3(pos.x, pos.y + 50, pos.z - 1));
			hp_tr->SetScale(137, 12.5, 0);
			Monster_UIHp->Set_Max_Hp(_MaxHp);
			Monster_UIHp->Set_Current_Hp(_MaxHp);

		}
		{
			Monster_UIDamegeHp = new Monster_Hp_Bar(L"EnemyHealthBar_Damage");
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::UI, Monster_UIDamegeHp);
			Monster_UIDamegeHp->SetName(L"warrior_hp_bar");
			Transform* hp_tr = Monster_UIDamegeHp->GetComponent<Transform>();
			hp_tr->SetPosition(Vector3(pos.x, pos.y + 50, pos.z - 1.5));
			hp_tr->SetScale(137, 12.5, 0);
			Monster_UIDamegeHp->Set_Max_Hp(_MaxHp);
			Monster_UIDamegeHp->Set_Current_Hp(_MaxHp);
			Monster_UIDamegeHp->Set_Type(1);
		}

		{
			Hpbar_Frame = new HP_Frame(L"EnemyHealthBar_Frame");
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Monster, Hpbar_Frame);
			Hpbar_Frame->SetName(L"hp_bar_frame");
			Transform* hp_tr = Hpbar_Frame->GetComponent<Transform>();
			hp_tr->SetPosition(Vector3(pos.x, pos.y - 90, pos.z - 1));
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
			hp_tr->SetPosition(Vector3(pos.x, pos.y + 50, pos.z - 1));
			hp_tr->SetScale(48, 3, 0);
			Monster_Hp->Set_Max_Hp(_MaxHp);
			Monster_Hp->Set_Current_Hp(_MaxHp);
			Monster_Hp->SetState(eState::Paused);
		}



	
		{
			Bullet = new Knight_male_EnergeBall;
			Bullet->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Bullet, Bullet);
			Transform* bullet_tr = Bullet->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205));
			Bullet->SetState(eState::Paused);
		}
		{
			Bullet_effect = new Knight_EnergyBall_StartEffect;
			Bullet_effect->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, Bullet_effect);
			Transform* bullet_tr = Bullet_effect->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205));
			Bullet_effect->SetState(eState::Paused);
		}
		{
			Energe_Blast = new Knight_Energe_Blast;
			Energe_Blast->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Bullet, Energe_Blast);
			Transform* bullet_tr = Energe_Blast->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205));
			Energe_Blast->SetState(eState::Paused);
		}

		{
			Ultimate_Aura = new Public_Ultimate_Aura;
			Ultimate_Aura->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, Ultimate_Aura);
			Transform* bullet_tr = Ultimate_Aura->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205));
			Ultimate_Aura->SetState(eState::Paused);
		}

		{
			Ultimate_AuraSmoke = new Public_Ultimate_AuraSmoke;
			Ultimate_AuraSmoke->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, Ultimate_AuraSmoke);
			Transform* bullet_tr = Ultimate_AuraSmoke->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205));
			Ultimate_AuraSmoke->SetState(eState::Paused);
		}
		{
			UltimateSkill_Effect_Complete = new Public_UltimateSkill_Effect_Complete;
			UltimateSkill_Effect_Complete->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, UltimateSkill_Effect_Complete);
			Transform* bullet_tr = UltimateSkill_Effect_Complete->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205));
			UltimateSkill_Effect_Complete->SetState(eState::Paused);
		}
		{
			UltimateSkill_Effect_Fail = new Public_UltimateSkill_Effect_Fail;
			UltimateSkill_Effect_Fail->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, UltimateSkill_Effect_Fail);
			Transform* bullet_tr = UltimateSkill_Effect_Fail->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205));
			UltimateSkill_Effect_Fail->SetState(eState::Paused);
		}

		{
			UltimateSkill_Projectile = new Knight_UltimateSkill_Projectile;
			UltimateSkill_Projectile->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Bullet, UltimateSkill_Projectile);
			Transform* bullet_tr = UltimateSkill_Projectile->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205));
			UltimateSkill_Projectile->SetState(eState::Paused);
		}

		{
			Hit_Box = new HitBox_Knight();
			Hit_Box->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Hitbox, Hit_Box);
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
			_Hit_Effect_player = new Player_Hit_Effect;
			_Hit_Effect_player->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, _Hit_Effect_player);
			_Hit_Effect_player->SetState(eState::Paused);
		}

		

		{
			_Hit_Sword = new Hit_Sword;
			_Hit_Sword->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, _Hit_Sword);
			_Hit_Sword->SetState(eState::Paused);
		}

		{
			_Critical_Middle = new Hit_Critical_Middle;
			_Critical_Middle->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, _Critical_Middle);
			_Critical_Middle->SetState(eState::Paused);
		}
		{
			_Critical_High = new Hit_Critical_High;
			_Critical_High->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, _Critical_High);
			_Critical_High->SetState(eState::Paused);
		}

		{
			_Death_Effect = new Monster_Death_Effect;
			_Death_Effect->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, _Death_Effect);
			_Death_Effect->SetState(eState::Paused);
		}


		
		at->PlayAnimation(L"Knight_maleIdle", true);
		GameObject::Initialize();
	}	
	
	void Knight_male::Update()
	{
		SetDirection();
		Particle_Control();
		Hpcontrol();
		Effect_Control();


		ground_distance_L = Left_Ground.x - pos.x;
		ground_distance_R = Right_Ground.x - pos.x;


		switch (_state)
		{
		case jk::Knight_male::Knight_State::Idle:
			idle();
			break;

		case jk::Knight_male::Knight_State::Dash:
			dash();
			break;

		case jk::Knight_male::Knight_State::BackDash:
			backdash();
			break;

		case jk::Knight_male::Knight_State::Jump:
			jump();
			break;

		case jk::Knight_male::Knight_State::JumpAttack:
			jumpattack();
			break;

		case jk::Knight_male::Knight_State::Die:die();
			break;

		case jk::Knight_male::Knight_State::Attack_A:
			attack_a();
			break;

		case jk::Knight_male::Knight_State::Attack_B:
			attack_b();
			break;

		case jk::Knight_male::Knight_State::Attack_C:
			attack_c();
			break;

		case jk::Knight_male::Knight_State::Attack_D:
			attack_d();
			break;

		case jk::Knight_male::Knight_State::Attack_E:
			attack_e();
			break;

		case jk::Knight_male::Knight_State::EnergeBall:
			energeball();
			break;

		case jk::Knight_male::Knight_State::Explosion_Loop_Ready:
			explosion_loop_ready();
			break;

		case jk::Knight_male::Knight_State::Explosion_Loop:
			explosion_loop();
			break;

		case jk::Knight_male::Knight_State::Finishing_Move_Ready:
			Finishing_Move_Ready();
			break;

		case jk::Knight_male::Knight_State::Finishing_Move_Succes:
			Finishing_Move_Succes();
			break;

		case jk::Knight_male::Knight_State::Finishing_Move_Fail:
			Finishing_Move_Fail();
			break;

		case jk::Knight_male::Knight_State::Finishing_Move:
			Finishing_Move();
			break;

		case jk::Knight_male::Knight_State::Groggy:
			Groggy();
			break;

		case jk::Knight_male::Knight_State::Hit:
			hit();
			break;

		case jk::Knight_male::Knight_State::Intro:
			intro();
			break;

		case jk::Knight_male::Knight_State::Potion:
			potion();
			break;

		case jk::Knight_male::Knight_State::Stinger:
			stinger();
			break;

		case jk::Knight_male::Knight_State::Stinger_Ready:
			stinger_Ready();
			break;

		default:
			break;
		}

		Mini_Boss::Update();
	}
	void Knight_male::LateUpdate()
	{
		_collider->SetSize(Vector2(0.35f, 0.4f));
		_collider->SetCenter(Vector2(0.0f, -30.5f));


		Transform* HitBox_TR = Hit_Box->GetComponent<Transform>();
		if (_attack_Col == true)
		{
			Hit_Box->SetSize(Vector2(50.f, 85.f));
			//Hit_Box->SetCenter(Vector3(100.f, -150.f, -250.f));
			//_attackdir
			Hit_Box->SetState(eState::Active);
			if (_attackdir == 1)
				HitBox_TR->SetPosition(Vector3(pos.x + 50, pos.y - 30, pos.z));
			else
				HitBox_TR->SetPosition(Vector3(pos.x - 50, pos.y - 30, pos.z));
		}
		else
		{
			Hit_Box->SetState(eState::Paused);
		}

		GameObject::LateUpdate();
	}
	void Knight_male::Render()
	{
		GameObject::Render();
	}


	void Knight_male::OnCollisionEnter(Collider2D* other)
	{
		if (HitBox_Player* player = dynamic_cast<HitBox_Player*>(other->GetOwner()))
		{
			if (_state == Knight_State::Die)
				return;

			_Damage = player->GetDamage();
			bool attack = player->Geteffect();
			bool attack_Cri_Mid = player->Geteffect_Mid();
			bool attack_Cri_High = player->Geteffect_Hight();


			if (_state == Knight_State::Idle)
			{
				_state = Knight_State::Hit;
				_Hit_Effect->_effect_animation = true;
				_Critical_Middle->_effect_animation = true;
				_Critical_High->_effect_animation = true;

				_CurrenHp = _CurrenHp - _Damage;
				Monster_Hp->_HitOn = true;
				Monster_Hp->SetHitDamage(_Damage);
				Monster_DamegeHp->_HitOn = true;
				Monster_DamegeHp->Set_Target(_CurrenHp);

				Monster_UIHp->_HitOn = true;
				Monster_UIHp->SetHitDamage(_Damage);
				Monster_UIDamegeHp->_HitOn = true;
				Monster_UIDamegeHp->Set_Target(_CurrenHp);
				_Hp_control = true;
				Hpbar_Frame->SetState(eState::Active);
				Monster_DamegeHp->SetState(eState::Active);
				Monster_Hp->SetState(eState::Active);

				if (mDir == 1)
				{
					at->PlayAnimation(L"Knight_maleHit", true);
					if (_number_of_hit < 2)
						_rigidbody->SetVelocity(Vector2(-50.f, 0.f));
					_hit_switch = true;	_number_of_hit++;

					_Hit_Effect->SetDirection(-1);
					_Critical_Middle->SetDirection(-1);
					_Critical_High->SetDirection(-1);

				}
				if (mDir == -1)
				{
					at->PlayAnimation(L"Knight_maleHitR", true);
					if (_number_of_hit < 2)
						_rigidbody->SetVelocity(Vector2(50.f, 0.f));
					_hit_switch = true;	_number_of_hit++;

					_Hit_Effect->SetDirection(1);
					_Critical_Middle->SetDirection(1);
					_Critical_High->SetDirection(1);
				}
			}
			else
			{
				_number_of_hit++;
				_Hit_Effect->_effect_animation = true;
				_Critical_Middle->_effect_animation = true;
				_Critical_High->_effect_animation = true;

				_CurrenHp = _CurrenHp - _Damage;
				Monster_Hp->_HitOn = true;
				Monster_Hp->SetHitDamage(_Damage);
				Monster_DamegeHp->_HitOn = true;
				Monster_DamegeHp->Set_Target(_CurrenHp);

				Monster_UIHp->_HitOn = true;
				Monster_UIHp->SetHitDamage(_Damage);
				Monster_UIDamegeHp->_HitOn = true;
				Monster_UIDamegeHp->Set_Target(_CurrenHp);
				_Hp_control = true;
				Hpbar_Frame->SetState(eState::Active);
				Monster_DamegeHp->SetState(eState::Active);
				Monster_Hp->SetState(eState::Active);

				if (mDir == 1)
				{
					_Hit_Effect->SetDirection(-1);
					_Critical_Middle->SetDirection(-1);
					_Critical_High->SetDirection(-1);
				}
				else
				{
					_Hit_Effect->SetDirection(1);
					_Critical_Middle->SetDirection(1);
					_Critical_High->SetDirection(1);
				}
			}

			if (attack == true)
			{
				_Hit_Effect->_effect_animation = true;
				_Hit_Effect->SetState(eState::Active);
			}
			if (attack_Cri_Mid == true)
			{
				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetState(eState::Active);
			}
			if (attack_Cri_High == true)
			{
				_Critical_High->_effect_animation = true;
				_Critical_High->SetState(eState::Active);
			}

			if (_CurrenHp <= 0)
			{
				_state = Knight_State::Die;
				_Hit_Effect->_effect_animation = true;
				if (mDir == 1)
				{
					at->PlayAnimation(L"Knight_maleDie", false);
					_Hit_Effect->SetDirection(-1);
				}
				else
				{
					at->PlayAnimation(L"Knight_maleDieR", false);
					_Hit_Effect->SetDirection(1);
				}
				_Death_Effect->SetState(eState::Active);
			}
		}

		if (Skul_head* player = dynamic_cast<Skul_head*>(other->GetOwner()))
		{
			if (_state == Knight_State::Die)
				return;

			bool attack = false;
			bool attack_Cri_Mid = false;
			bool attack_Cri_High = false;

			_HitType = random(1, 10);
			if (_HitType >= 1 && _HitType < 6)
			{
				_Damage = 25;
				attack = true;
			}
			if (_HitType >= 6 && _HitType < 9)
			{
				_Damage = random(35, 40);
				attack_Cri_Mid = true;
			}
			if (_HitType >= 9 && _HitType <= 10)
			{
				_Damage = random(50, 70);
				attack_Cri_High = true;
			}


			if (player->_Head_Attack == false && _bulletcheck == 0)
			{
				if (player->_Ground_check == true)
					return;

				if ((_state == Knight_State::Finishing_Move_Ready) || (_state == Knight_State::BackDash))
				{
					_number_of_hit++;
					_Hit_Effect->_effect_animation = true;
					_Critical_Middle->_effect_animation = true;
					_Critical_High->_effect_animation = true;

					if (mDir == 1)
					{
						Monster_Hp->_HitOn = true;
						Monster_Hp->SetHitDamage(_Damage);
						_CurrenHp = _CurrenHp - _Damage;
						_Hit_Effect->SetDirection(-1);
						_Critical_Middle->SetDirection(-1);
						_Critical_High->SetDirection(-1);
					}
					else
					{
						Monster_Hp->_HitOn = true;
						Monster_Hp->SetHitDamage(_Damage);
						_CurrenHp = _CurrenHp - _Damage;
						_Hit_Effect->SetDirection(1);
						_Critical_Middle->SetDirection(1);
						_Critical_High->SetDirection(1);
					}
					if (attack == true)
					{
						_Hit_Effect->_effect_animation = true;
						_Hit_Effect->SetState(eState::Active);
					}
					if (attack_Cri_Mid == true)
					{
						_Critical_Middle->_effect_animation = true;
						_Critical_Middle->SetState(eState::Active);
					}
					if (attack_Cri_High == true)
					{
						_Critical_High->_effect_animation = true;
						_Critical_High->SetState(eState::Active);
					}
				}
				if (_state == Knight_State::Idle)
				{
					_hit_switch = true;	_number_of_hit++;
					_Hit_Effect->_effect_animation = true;
					_Critical_Middle->_effect_animation = true;
					_Critical_High->_effect_animation = true;
					_state = Knight_State::Hit;
					if (mDir == 1)
					{
						at->PlayAnimation(L"Knight_maleHit", true);
						if (_number_of_hit < 2)
							_rigidbody->SetVelocity(Vector2(-50.f, 0.f));

						Monster_Hp->_HitOn = true;
						Monster_Hp->SetHitDamage(_Damage);
						_CurrenHp = _CurrenHp - _Damage;
						_Hit_Effect->SetDirection(-1);
						_Critical_Middle->SetDirection(-1);
						_Critical_High->SetDirection(-1);

					}
					if (mDir == -1)
					{
						at->PlayAnimation(L"Knight_maleHitR", true);
						if (_number_of_hit < 2)
							_rigidbody->SetVelocity(Vector2(50.f, 0.f));

						Monster_Hp->_HitOn = true;
						Monster_Hp->SetHitDamage(_Damage);
						_CurrenHp = _CurrenHp - _Damage;
						_Hit_Effect->SetDirection(1);
						_Critical_Middle->SetDirection(1);
						_Critical_High->SetDirection(1);
					}
					if (attack == true)
					{
						_Hit_Effect->_effect_animation = true;
						_Hit_Effect->SetState(eState::Active);
					}
					if (attack_Cri_Mid == true)
					{
						_Critical_Middle->_effect_animation = true;
						_Critical_Middle->SetState(eState::Active);
					}
					if (attack_Cri_High == true)
					{
						_Critical_High->_effect_animation = true;
						_Critical_High->SetState(eState::Active);
					}
				}
				if (!((_state == Knight_State::Idle) || (_state == Knight_State::Finishing_Move_Ready) || (_state == Knight_State::BackDash)))
				{
					_number_of_hit++;
					_Hit_Effect->_effect_animation = true;
					_Critical_Middle->_effect_animation = true;
					_Critical_High->_effect_animation = true;

					if (mDir == 1)
					{
						_rigidbody->SetVelocity(Vector2(-20.f, 0.f));

						Monster_Hp->_HitOn = true;
						Monster_Hp->SetHitDamage(_Damage);
						_CurrenHp = _CurrenHp - _Damage;
						_Hit_Effect->SetDirection(-1);
						_Critical_Middle->SetDirection(-1);
						_Critical_High->SetDirection(-1);
					}
					else
					{
						_rigidbody->SetVelocity(Vector2(20.f, 0.f));

						Monster_Hp->_HitOn = true;
						Monster_Hp->SetHitDamage(_Damage);
						_CurrenHp = _CurrenHp - _Damage;
						_Hit_Effect->SetDirection(1);
						_Critical_Middle->SetDirection(1);
						_Critical_High->SetDirection(1);
					}
					if (attack == true)
					{
						_Hit_Effect->_effect_animation = true;
						_Hit_Effect->SetState(eState::Active);
					}
					if (attack_Cri_Mid == true)
					{
						_Critical_Middle->_effect_animation = true;
						_Critical_Middle->SetState(eState::Active);
					}
					if (attack_Cri_High == true)
					{
						_Critical_High->_effect_animation = true;
						_Critical_High->SetState(eState::Active);
					}
				}
				if (_CurrenHp <= 0)
				{
					_state = Knight_State::Die;
					_Hit_Effect->_effect_animation = true;
					if (mDir == 1)
					{
						at->PlayAnimation(L"Knight_maleDie", false);
						_Hit_Effect->SetDirection(-1);
					}
					else
					{
						at->PlayAnimation(L"Knight_maleDieR", false);
						_Hit_Effect->SetDirection(1);
					}
					_Death_Effect->SetState(eState::Active);
				}
			}
		}

		if (Ground_and_Wall* mGround = dynamic_cast<Ground_and_Wall*>(other->GetOwner()))
		{
			_rigidbody->ClearVelocity();
		}
		
	}
	void Knight_male::OnCollisionStay(Collider2D* other)
	{
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{
			if (_Ground_check == false)
			{
				_rigidbody->SetGround(true);
				_Ground_check = true;
				_rigidbody->ClearVelocity();
			}
			if (_state == Knight_State::BackDash)
			{
				if (_Ground_check == true)				
				_BackDash = false;
			}
		}

		if (Ground_Map* Ground = dynamic_cast<Ground_Map*>(other->GetOwner()))
		{
			if (_Ground_check == false)
			{
				_rigidbody->SetGround(true);
				_Ground_check = true;
				_rigidbody->ClearVelocity();
			}
			if (_state == Knight_State::BackDash)
			{
				if (_Ground_check == true)
					_BackDash = false;
			}
		}
	}
	void Knight_male::OnCollisionExit(Collider2D* other)
	{
	}


	void Knight_male::idle()
	{
		_attack_Col = false;
		_time += Time::DeltaTime();
		_Attacktime = 0;
		_choicecombo = random(0, 3);
		//_choicecombo = 3;
	
		if (_Intro == false)
		{
			_state = Knight_State::Intro;
			at->PlayAnimation(L"Knight_maleIntro", true);
		}
		else
		{
			if (_number_of_hit >= 8)
			{
				_time = 0;
				if (mDir == -1)
				{
					if (ground_distance_R > 100)
					{
						at->PlayAnimation(L"Knight_maleBackDashR", true);
						_rigidbody->SetVelocity(Vector2(250.f, 250.f));
						_rigidbody->SetGround(false);
						_Ground_check = false;
						_BackDash = true;
						_state = Knight_State::BackDash;
					}
					else
					{
						at->PlayAnimation(L"Knight_maleBackDash", true);
						_rigidbody->SetVelocity(Vector2(-350.f, 250.f));
						_rigidbody->SetGround(false);
						_Ground_check = false;
						_BackDash = true;
						_state = Knight_State::BackDash;
					}
				}
				else
				{
					if (ground_distance_L < -100)
					{
						at->PlayAnimation(L"Knight_maleBackDash", true);
						_rigidbody->SetVelocity(Vector2(-250.f, 250.f));
						_rigidbody->SetGround(false);
						_Ground_check = false;
						_BackDash = true;
						_state = Knight_State::BackDash;
					}
					else
					{
						at->PlayAnimation(L"Knight_maleBackDashR", true);
						_rigidbody->SetVelocity(Vector2(350.f, 250.f));
						_rigidbody->SetGround(false);
						_Ground_check = false;
						_BackDash = true;
						_state = Knight_State::BackDash;
					}
				}
				_number_of_hit = 0;
			}
			else
			{
				if (_time > 1.f)
				{
					if ((_distance >= 150 || _distance <= -150))
					{
						if (_choicecombo == 1)
						{
							if (_dash == false || _dash == true)
								_attackorder++;
							_number_of_attack++;
							_attack = true;
							energyball();
						}
						else
						{
							_state = Knight_State::Dash;
							if (mDir == 1)
							{
								at->PlayAnimation(L"Knight_maleDash", true);
								_rigidbody->SetVelocity(Vector2(250.f, 0.f));
							}
							else
							{
								at->PlayAnimation(L"Knight_maleDashR", true);
								_rigidbody->SetVelocity(Vector2(-250.f, 0.f));
							}
							_dash = true;
						}
					}
					else
					{
						_attack = true;
						choicecombo();
					}
				}
			}
		}		
	}
	void Knight_male::dash()
	{
		_rigidbody->ClearVelocityY();
		if (mDir == 1 && _velocity.x <= 200.0)
		{
			_state = Knight_State::Idle;
			at->PlayAnimation(L"Knight_maleIdle", true);			
			_rigidbody->ClearVelocityX();			
		}
		else if (mDir == -1 && _velocity.x >= -200.0)
		{
			_state = Knight_State::Idle;
			at->PlayAnimation(L"Knight_maleIdleR", true);			
			_rigidbody->ClearVelocityX();			
		}
		_dash = false;
	}
	void Knight_male::backdash()
	{

		if (_BackDash == false)
		{
			_state = Knight_State::Idle;
			if (mDir == 1)
				at->PlayAnimation(L"Knight_maleIdle", true);
			else
				at->PlayAnimation(L"Knight_maleIdleR", true);
			_Attacktime = 0;
		}
		/*else
			_Ground_check = false;*/
	}

	void Knight_male::jump()
	{
	}
	void Knight_male::jumpattack()
	{
	}
	void Knight_male::die()
	{
		_Die = true;
		Ultimate_Aura->SetState(eState::Paused);
		Ultimate_AuraSmoke->SetState(eState::Paused);
		_attack_Col = false;
	}

	void Knight_male::attack_a()
	{		
	}
	void Knight_male::attack_b()
	{		
	}
	void Knight_male::attack_c()
	{		
		_attackorder = 0;
		_attack = false;
	}
	void Knight_male::attack_d()
	{
	}
	void Knight_male::attack_e()
	{
	}

	void Knight_male::energeball()
	{
		if (Bullet_effect->_effect_switch== false)
		{
			Transform* bullet_tr = Bullet->GetComponent<Transform>();
			if(mDir == 1)
				bullet_tr->SetPosition(Vector3(pos.x+20, pos.y-20, -205));
			else
				bullet_tr->SetPosition(Vector3(pos.x - 20, pos.y - 20, -205));

			Bullet->_EffectSwitch = true;
			Bullet->_BoomSwitch = false;
			Bullet->SetState(eState::Active);
			_attack = false;
			_state = Knight_State::EnergeBall;
			Bullet_effect->_effect_switch = true;
		}
		if (Bullet_effect->_effect_switch == true)
		{
			_Attacktime += Time::DeltaTime();
			if (_Attacktime < 5)
			{
				Transform* bullet_tr = Bullet->GetComponent<Transform>();
				RigidBody* bullet_gr = Bullet->GetComponent<RigidBody>();
				Vector3 attack = bullet_tr->GetPosition();
				Vector2 attackrotation_PLAYER = Vector2(_playerpos.x - attack.x, _playerpos.y - attack.y);

				float dis = abs(_playerpos.x - attack.x);
				if (dis < 70)
				{
					if(mDir ==1)
					attackrotation_PLAYER.x = 60;
					else
					attackrotation_PLAYER.x = -60;
				}
				attackrotation_PLAYER.Normalize();
				bullet_gr->SetGround(false);
				bullet_gr->SetVelocity(Vector2(attackrotation_PLAYER.x * 175.f, attackrotation_PLAYER.y * 200));
				Vector2 vel = bullet_gr->GetVelocity();
			}
			else
			{
				//Bullet->SetState(eState::Paused);
				_Attacktime = 0;
				_attackorder = 0;
				_attack = false;
				Bullet->_BoomSwitch = true;
				//Bullet_effect->_effect_switch = false;
				_state = Knight_State::Idle;
				if (mDir == 1)
					at->PlayAnimation(L"Knight_maleIdle", true);
				else
					at->PlayAnimation(L"Knight_maleIdleR", true);
			}
		}
	}
	void Knight_male::explosion_loop_ready()
	{
		_Attacktime += Time::DeltaTime();
		if (_Attacktime >= 0.7)
		{
			_state = Knight_State::Explosion_Loop;
			Transform* bullet_tr = Energe_Blast->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(pos.x, pos.y - 10, pos.z - 1));
			Energe_Blast->SetState(eState::Active);
			_Attacktime = 0;
		}
	}
	void Knight_male::explosion_loop()
	{
		_Attacktime += Time::DeltaTime();
		if (_Attacktime >= 1.5)
		{
			_attackorder = 0;
			_attack = false;
			_Attacktime = 0;
			choicecombo();
		}			
	}

	void Knight_male::Finishing_Move_Ready()
	{		
		if (_Ultimate == true)
		{
			{
				Transform* bullet_tr = Ultimate_Aura->GetComponent<Transform>();
				bullet_tr->SetPosition(Vector3(pos.x, pos.y - 30, pos.z - 1));
				Ultimate_Aura->_effect_animation = true;
				if (mDir == 1)
					Ultimate_Aura->SetDirection(1);
				else
					Ultimate_Aura->SetDirection(-1);
				Ultimate_Aura->SetState(eState::Active); 
			}

			{
				Transform* bullet_tr = Ultimate_AuraSmoke->GetComponent<Transform>();
				bullet_tr->SetPosition(Vector3(pos.x, pos.y-55, pos.z - 1.1));
				if (mDir == 1)
					Ultimate_AuraSmoke->SetDirection(1);
				else
					Ultimate_AuraSmoke->SetDirection(-1);
				Ultimate_AuraSmoke->SetState(eState::Active);
			}

			_Ultimate = false;
		}

		// 기모으는 이펙트를 넣을것(7초간 지속상태 만들기)
		_Attacktime += Time::DeltaTime();
		if (_Attacktime >= 7.5)
		{
			Ultimate_Aura->SetState(eState::Paused);
			Ultimate_AuraSmoke->SetState(eState::Paused);
			if (_number_of_hit > 8)
			{				
				// 이펙트 설정시 9번 hit가 된다면 깨지는 이미지로 넘어간뒤 그로기 상태로넘겨줘야한다.
				Transform* bullet_tr = UltimateSkill_Effect_Fail->GetComponent<Transform>();
				bullet_tr->SetPosition(Vector3(pos.x, pos.y - 25, pos.z - 1.1));
				if (mDir == 1)
					UltimateSkill_Effect_Fail->SetDirection(1);
				else
					UltimateSkill_Effect_Fail->SetDirection(-1);
				UltimateSkill_Effect_Fail->SetState(eState::Active);

				_state = Knight_State::Finishing_Move_Fail;
				_Attacktime = 0.f;				
			}
			else
			{
				// 이펙트 설정시 5초가 10번이상의 타격이 없다면 석세스로 넘어간뒤 검격공격을 날려야한다.
				Transform* bullet_tr = UltimateSkill_Effect_Complete->GetComponent<Transform>();
				bullet_tr->SetPosition(Vector3(pos.x, pos.y - 35, pos.z - 1.1));
				if (mDir == 1)
					UltimateSkill_Effect_Complete->SetDirection(1);
				else
					UltimateSkill_Effect_Complete->SetDirection(-1);
				UltimateSkill_Effect_Complete->SetState(eState::Active);	
				
				if(mDir ==1)
					at->PlayAnimation(L"Knight_maleUltimateSkill_Motion", false);
				else
					at->PlayAnimation(L"Knight_maleUltimateSkill_MotionR", false);
				_state = Knight_State::Finishing_Move_Succes;	
				_Attacktime = 0.f;
			}
		}	
	}
	void Knight_male::Finishing_Move_Succes()
	{		
		if (_Ultimate_Skill == false)
		{
			Transform* bullet_tr = UltimateSkill_Projectile->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(pos.x, pos.y - 25, pos.z - 1.1));
			UltimateSkill_Projectile->_effect_animation = true;
			if (mDir == 1)
				UltimateSkill_Projectile->SetDirection(1);
			else
				UltimateSkill_Projectile->SetDirection(-1);
			UltimateSkill_Projectile->SetState(eState::Active);
			_Ultimate_Skill = true;
		}
		else
		{
			_Attacktime += Time::DeltaTime();
			if (_Attacktime <= 3.0)
			{
				Transform* bullet_tr = UltimateSkill_Projectile->GetComponent<Transform>();
				float BulletX = bullet_tr->GetPosition().x;
				if(mDir ==1)
					BulletX  += 350 * Time::DeltaTime();
				else
					BulletX -= 350 * Time::DeltaTime();
				bullet_tr->SetPosition(Vector3(BulletX, pos.y - 25, pos.z - 1.1));
			}
			else
			{
				UltimateSkill_Projectile->SetState(eState::Paused);
				_state = Knight_State::Finishing_Move;
				_Ultimate_Skill = false;
				_Attacktime = 0;
			}
		}
	}
	void Knight_male::Finishing_Move_Fail()
	{
		_state = Knight_State::Groggy;
		if (mDir == 1)
			at->PlayAnimation(L"Knight_maleGlorggy", true);
		else
			at->PlayAnimation(L"Knight_maleGlorggyR", true);
	}
	void Knight_male::Finishing_Move()
	{		
		//_state = Knight_State::Idle;
		//if (mDir == 1)
		//	at->PlayAnimation(L"Knight_maleIdle", true);
		//else
		//	at->PlayAnimation(L"Knight_maleIdleR", true);
		//_time = 0;
		_attackorder = 0;
		_attack = false;
		choicecombo();
	}


	void Knight_male::Groggy()
	{
		_Attacktime += Time::DeltaTime();
		if (_Attacktime >= 3.5)
		{
			_Attacktime = 0;
			_attackorder = 0;
			_attack = false;
			choicecombo();
		}
	}
	void Knight_male::hit()
	{

	}

	void Knight_male::intro()
	{
		if (_Intro == true)
		{
			_state = Knight_State::Idle;
			if (mDir == 1)
				at->PlayAnimation(L"Knight_maleIdle", true);
			else
				at->PlayAnimation(L"Knight_maleIdleR", true);
		}
	}
	void Knight_male::potion()
	{
	}
	void Knight_male::stinger()
	{
	}

	void Knight_male::stinger_Ready()
	{
	}


	void Knight_male::SetDirection()
	{
		tr = GetComponent<Transform>();
		pos = tr->GetPosition();
		_velocity = _rigidbody->GetVelocity();
		_playerpos = Player::GetPlayer_Pos();
		_distance = _playerpos.x - pos.x;
		if (_distance >= 0.f)
			mDir = 1;
		else
			mDir = -1;
	}
	void Knight_male::Particle_Control()
	{
	}
	void Knight_male::Hpcontrol()
	{
		Transform* STATEUI_tr = _State_UI->GetComponent<Transform>();
		Transform* STATEUIhp_tr1 = Monster_UIHp->GetComponent<Transform>();
		Transform* STATEUIhp_tr2 = Monster_UIDamegeHp->GetComponent<Transform>();
		Transform* face_tr = _MbossFace->GetComponent<Transform>();

		if (_UIstate == 0)//1번
		{
			STATEUI_tr->SetPosition(Vector3(685.f, 375.f, 10));
			STATEUIhp_tr1->SetPosition(Vector3(650.f, 354.f, 5));
			STATEUIhp_tr2->SetPosition(Vector3(650.f, 354.f, 6));
			face_tr->SetPosition(Vector3(762.f, 375.f, 1));
		}
		if (_UIstate == 1)//2번
		{
			STATEUI_tr->SetPosition(Vector3(685.f, 275.f, 10));
			STATEUIhp_tr1->SetPosition(Vector3(650.f, 254.f, 5));
			STATEUIhp_tr2->SetPosition(Vector3(650.f, 254.f, 6));
			face_tr->SetPosition(Vector3(762.f, 275.f, 1));

		}
		if (_UIstate == 2)//3번
		{
			STATEUI_tr->SetPosition(Vector3(685.f, 175.f, 10));
			STATEUIhp_tr1->SetPosition(Vector3(650.f, 154.f, 5));
			STATEUIhp_tr2->SetPosition(Vector3(650.f, 154.f, 6));
			face_tr->SetPosition(Vector3(762.f, 175.f, 1));
		}



		Transform* hp_tr = Monster_Hp->GetComponent<Transform>();
		hp_tr->SetPosition(Vector3(pos.x, pos.y - 90, pos.z - 2));

		Transform* hpdamege_tr = Monster_DamegeHp->GetComponent<Transform>();
		hpdamege_tr->SetPosition(Vector3(pos.x, pos.y - 90, pos.z - 1.5));

		Transform* hpfr_tr = Hpbar_Frame->GetComponent<Transform>();
		hpfr_tr->SetPosition(Vector3(pos.x, pos.y - 90, pos.z - 1));


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
			Hpbar_Frame->SetState(eState::Paused);
			Monster_DamegeHp->SetState(eState::Paused);
			Monster_Hp->SetState(eState::Paused);
			_Die = true;
			_attack_Col = false;
			_MbossFace->Set_animation(true);
			_MbossFace->Set_UISelect(5);
		}
	}
	void Knight_male::Effect_Control()
	{
		{
			Transform* _Hit_Effect_TR = _Hit_Effect->GetComponent<Transform>();
			if (mDir == 1)
				_Hit_Effect_TR->SetPosition(Vector3(pos.x + 20, pos.y - 30, pos.z - 1));
			else
				_Hit_Effect_TR->SetPosition(Vector3(pos.x - 20, pos.y - 30, pos.z - 1));
		}
		{
			Transform* _Hit_Effect_TR = _Hit_Effect_player->GetComponent<Transform>();
			if (mDir == 1)
				_Hit_Effect_TR->SetPosition(Vector3(pos.x + 20, pos.y - 30, pos.z - 1));
			else
				_Hit_Effect_TR->SetPosition(Vector3(pos.x - 20, pos.y - 30, pos.z - 1));
		}
		{
			Transform* _Hit_Effect_TR = _Critical_Middle->GetComponent<Transform>();
			if (mDir == 1)
				_Hit_Effect_TR->SetPosition(Vector3(pos.x + 20, pos.y - 30, pos.z - 1));
			else
				_Hit_Effect_TR->SetPosition(Vector3(pos.x - 20, pos.y - 30, pos.z - 1));
		}
		{
			Transform* _Hit_Effect_TR = _Critical_High->GetComponent<Transform>();
			if (mDir == 1)
				_Hit_Effect_TR->SetPosition(Vector3(pos.x + 20, pos.y - 30, pos.z - 1));
			else
				_Hit_Effect_TR->SetPosition(Vector3(pos.x - 20, pos.y - 30, pos.z - 1));
		}
		{
			Transform* _Effect_TR = _Death_Effect->GetComponent<Transform>();
			_Effect_TR->SetPosition(Vector3(pos.x, pos.y, pos.z - 1));
		}
	}


	void Knight_male::choicecombo()
	{
		_attack_Col = false;
		_Attacktime = 0;		
		if (_attack == true)
		{			
			if (_choicecombo == 0)
			{
				if (_dash == false)
				combo();
					_attackorder++;
			}
			if (_choicecombo == 1)
			{
				if (_dash == false || _dash==true)
				energyball();
				_attackorder++;						
			}
			if (_choicecombo == 2)
			{
				if (_dash == false)
					explosionloop();
				_attackorder++;						
			}		
			if (_choicecombo == 3)
			{
				if (_dash == false)
					finishingmove_set();
				_attackorder++;
			}
		}
		else
		{	
			_number_of_attack++;
			if (_number_of_attack >= 3)
			{
				_time = 0;
				_number_of_attack = 0;
			}
			{
				_state = Knight_State::Idle;
				if (mDir == 1)
					at->PlayAnimation(L"Knight_maleIdle", true);
				else
					at->PlayAnimation(L"Knight_maleIdleR", true);
			}
		}	
	}
	void Knight_male::combo()
	{
		_attack_Col = true;
		if (_attackorder == 1)
		{
			_state = Knight_State::Attack_A;			
			if (mDir == 1)
			{
				_attackdir = 1;
				at->PlayAnimation(L"Knight_maleAttack_A", true);
				_rigidbody->SetVelocity(Vector2(150.f,0.f));
			}
			else
			{
				_attackdir = -1;
				at->PlayAnimation(L"Knight_maleAttack_AR", true);
				_rigidbody->SetVelocity(Vector2(-150.f, 0.f));
			}
		}
		if (_attackorder == 2)
		{ 
			_state = Knight_State::Attack_B;		
			if (mDir == 1)
			{
				_attackdir = 1;
				at->PlayAnimation(L"Knight_maleAttack_B", true);
				_rigidbody->SetVelocity(Vector2(150.f, 0.f));
			}
			else
			{
				_attackdir = -1;
				at->PlayAnimation(L"Knight_maleAttack_BR", true);
				_rigidbody->SetVelocity(Vector2(-150.f, 0.f));
			}
		}
		if (_attackorder == 3)
		{
			_state = Knight_State::Attack_C;			
			if (mDir == 1)
			{
				_attackdir = 1;
				at->PlayAnimation(L"Knight_maleAttack_C", true);
			}
			else
			{
				_attackdir = -1;
				at->PlayAnimation(L"Knight_maleAttack_CR", true);
			}
		}
	}
	void Knight_male::energyball()
	{
		_Attacktime = 0;
		if (_attackorder == 1)
		{
			if (mDir == 1)
				at->PlayAnimation(L"Knight_maleEnergeBall", false);
			else
				at->PlayAnimation(L"Knight_maleEnergeBallR", false);

		
			Bullet_effect->_effect_switch = true;
			Transform* bullet_tr = Bullet_effect->GetComponent<Transform>();
			if (mDir == 1)
			{
				Bullet_effect->_effect_animation = true;
				Bullet_effect->SetDirection(1);
				bullet_tr->SetPosition(Vector3(pos.x + 40, pos.y - 20, -205));
			}
			else
			{
				Bullet_effect->_effect_animation = true;
				Bullet_effect->SetDirection(-1);
				bullet_tr->SetPosition(Vector3(pos.x - 40, pos.y - 20, -205));
			}
			Bullet_effect->SetState(eState::Active);
			_state = Knight_State::EnergeBall;
		}		
	}
	void Knight_male::explosionloop()
	{
		if (_attackorder == 1)
		{
			_state = Knight_State::Explosion_Loop_Ready;
			if(mDir==1)
				at->PlayAnimation(L"Knight_maleExplosion_Loop", true);
			else
				at->PlayAnimation(L"Knight_maleExplosion_LoopR", true);
		}
	}
	void Knight_male::finishingmove_set()
	{
		if (_attackorder == 1)
		{
			_state = Knight_State::Finishing_Move_Ready;
			if (mDir == 1)
				at->PlayAnimation(L"Knight_maleFinish_Move", true);
			else
				at->PlayAnimation(L"Knight_maleFinish_MoveR", true);
			_Ultimate = true;

			//_number_of_hit = 9;
		}
	}
	void Knight_male::complete_ultimate()
	{
		if (_Ultimate_Skill == false)
		{
			Transform* bullet_tr = UltimateSkill_Projectile->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(pos.x, pos.y - 25, pos.z - 1.1));
			if (mDir == 1)
				UltimateSkill_Projectile->SetDirection(1);
			else
				UltimateSkill_Projectile->SetDirection(-1);
			UltimateSkill_Projectile->SetState(eState::Active);
			_Ultimate_Skill = true;
		}
	}
	void Knight_male::complete_gloggy()
	{
		//_state = Knight_State::Idle;
		//if (mDir == 1)
		//	at->PlayAnimation(L"Knight_maleIdle", true);
		//else
		//	at->PlayAnimation(L"Knight_maleIdleR", true);
	}
	void Knight_male::complete_hit()
	{
		_state = Knight_State::Idle;
		if (mDir == 1)
			at->PlayAnimation(L"Knight_maleIdle", true);
		else
			at->PlayAnimation(L"Knight_maleIdleR", true);
	}
	void Knight_male::complete_Intro()
	{
		_Intro = true;
	}
	void Knight_male::complete_Attack_A()
	{
		_attack_Col = false;
		choicecombo();
	}
	void Knight_male::complete_Attack_B()
	{
		_attack_Col = false;
		choicecombo();
	}
	void Knight_male::complete_Attack_C()
	{
		_attack_Col = false;
		choicecombo();
	}

}