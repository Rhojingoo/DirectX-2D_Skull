#include "Cleric.h"


namespace jk
{
	int Cleric::mDir = 1;
	Cleric::Cleric()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}
	Cleric::~Cleric()
	{
	}
	void Cleric::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(false);
		tr = GetComponent<Transform>();

		
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Attack_A", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Attack_B", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Basic_Heal", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Attack_C", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Ultimate_Skill_Casting", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Ultimate_Skill", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Ultimate_Skill_End", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Die", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Groggy", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Hit", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Intro", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Potion", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Teleport_In", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Teleport_Out", this);
		
		
		
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Attack_A", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Attack_B", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Basic_Heal", this,1);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Attack_C", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Ultimate_Skill_Casting", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Ultimate_Skill", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Ultimate_Skill_End", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Die", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Groggy", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Hit", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Idle", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Intro", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Potion", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Teleport_In", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Teleport_Out", this, 1);
		
		
		//bind 부분
		at->CompleteEvent(L"ClericAttack_A") = std::bind(&Cleric::complete_attack_a, this);
		at->CompleteEvent(L"ClericAttack_AR") = std::bind(&Cleric::complete_attack_a, this);

		at->CompleteEvent(L"ClericAttack_B") = std::bind(&Cleric::complete_attack_b, this);
		at->CompleteEvent(L"ClericAttack_BR") = std::bind(&Cleric::complete_attack_b, this);

		at->CompleteEvent(L"ClericUltimate_Skill") = std::bind(&Cleric::complete_ultimate_skill, this);
		at->CompleteEvent(L"ClericUltimate_SkillR") = std::bind(&Cleric::complete_ultimate_skill, this);

		//at->CompleteEvent(L"ClericHit") = std::bind(&Cleric::complete_ultimate_skill, this);
		//at->CompleteEvent(L"ClericHitR") = std::bind(&Cleric::complete_ultimate_skill, this);

		at->CompleteEvent(L"ClericTeleport_In") = std::bind(&Cleric::complete_teleport_in, this);
		at->CompleteEvent(L"ClericTeleport_InR") = std::bind(&Cleric::complete_teleport_in, this);
		at->CompleteEvent(L"ClericTeleport_Out") = std::bind(&Cleric::complete_teleport_out, this);
		at->CompleteEvent(L"ClericTeleport_OutR") = std::bind(&Cleric::complete_teleport_out, this);

		at->CompleteEvent(L"ClericIntro") = std::bind(&Cleric::complete_intro, this);
		at->CompleteEvent(L"ClericIntroR") = std::bind(&Cleric::complete_intro, this);

		at->CompleteEvent(L"ClericHit") = std::bind(&Cleric::complete_hit, this);
		at->CompleteEvent(L"ClericHitR") = std::bind(&Cleric::complete_hit, this);

		//UI 및 체력관련		
		{
			_MbossFace = new AdventureUI();
			_MbossFace->Initialize();
			_MbossFace->Set_animation(true);
			_MbossFace->Set_UISelect(2);
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
			_Attack_Sign = new Cleric_Attack_Sign;
			_Attack_Sign->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, _Attack_Sign);
			Transform* bullet_tr = _Attack_Sign->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205));
			_Attack_Sign->SetState(eState::Paused);
		}
		{
			_GraceOfLeonia_Attack_A = new Cleric_HolyThunder;
			_GraceOfLeonia_Attack_A->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Bullet, _GraceOfLeonia_Attack_A);
			Transform* bullet_tr = _GraceOfLeonia_Attack_A->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205));
			_GraceOfLeonia_Attack_A->SetState(eState::Paused);
		}
		{
			_Veteran_Sanctuary_AtaackB = new Cleric_Veteran_Sanctuary;
			_Veteran_Sanctuary_AtaackB->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Bullet, _Veteran_Sanctuary_AtaackB);
			Transform* bullet_tr = _Veteran_Sanctuary_AtaackB->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205));
			_Veteran_Sanctuary_AtaackB->SetState(eState::Paused);
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
			Ultimate_SkillEffect = new Cleric_Ultimate_SkillEffect;
			Ultimate_SkillEffect->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, Ultimate_SkillEffect);
			Transform* bullet_tr = Ultimate_SkillEffect->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(0.f, 0.f, -205));
			Ultimate_SkillEffect->SetState(eState::Paused);
		}
		{
			Ultimate_Heal_Effect = new Public_Heal_Effect;
			Ultimate_Heal_Effect->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, Ultimate_Heal_Effect);
			Transform* bullet_tr = Ultimate_Heal_Effect->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205));
			Ultimate_Heal_Effect->SetState(eState::Paused);
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

		_first_place = pos;
		at->PlayAnimation(L"ClericIdle", true);
		GameObject::Initialize();
	}
	void Cleric::Update()
	{
		SetDirection();
		Particle_Control();
		Hpcontrol();
		Effect_Control();

		ground_distance_L = Left_Ground.x - pos.x;
		ground_distance_R = Right_Ground.x - pos.x;


		switch (_state)
		{
		case jk::Cleric::Cleric_State::Idle:
			idle();
			break;

		case jk::Cleric::Cleric_State::Attack_A_Ready:
			attack_a_ready();
			break;

		case jk::Cleric::Cleric_State::Attack_A:
			attack_a();
			break;

		case jk::Cleric::Cleric_State::Attack_B_Ready:
			attack_b_ready();
			break;

		case jk::Cleric::Cleric_State::Attack_B:
			attack_b();
			break;

		case jk::Cleric::Cleric_State::Attack_C_Ready:
			attack_c_ready();
			break;

		case jk::Cleric::Cleric_State::Attack_C:
			attack_c();
			break;

		case jk::Cleric::Cleric_State::Finishing_Move_Ready:
			Finishing_Move_Ready();
			break;

		case jk::Cleric::Cleric_State::Finishing_Move_Succes:
			Finishing_Move_Succes();
			break;

		case jk::Cleric::Cleric_State::Finishing_Move_Fail:
			Finishing_Move_Fail();
			break;

		case jk::Cleric::Cleric_State::Finishing_Move:
			Finishing_Move();
			break;

		case jk::Cleric::Cleric_State::Casting:
			casting();
			break;

		case jk::Cleric::Cleric_State::Groggy:
			groggy();
			break;			

		case jk::Cleric::Cleric_State::Die:
			die();
			break;

		case jk::Cleric::Cleric_State::Hit:
			hit();
			break;

		case jk::Cleric::Cleric_State::Intro:
			intro();
			break;

		case jk::Cleric::Cleric_State::Potion:
			potion();
			break;

		case jk::Cleric::Cleric_State::Teleport_In:
			teleport_in();
			break;

		case jk::Cleric::Cleric_State::Teleport_Out:
			teleport_out();
			break;

		default:
			break;
		}
		tr->SetPosition(Vector3(pos));
		GameObject::Update();
	}
	void Cleric::LateUpdate()
	{
		_collider->SetSize(Vector2(0.35f, 0.55f));
		_collider->SetCenter(Vector2(0.0f, -28.5f));

		GameObject::LateUpdate();
	}
	void Cleric::Render()
	{
		GameObject::Render();
	}
	void Cleric::OnCollisionEnter(Collider2D* other)
	{
		if (HitBox_Player* player = dynamic_cast<HitBox_Player*>(other->GetOwner()))
		{
			if (_state == Cleric_State::Die)
				return;

			_Damage = player->GetDamage();
			bool attack = player->Geteffect();
			bool attack_Cri_Mid = player->Geteffect_Mid();
			bool attack_Cri_High = player->Geteffect_Hight();
			

			if (_state == Cleric_State::Idle)
			{
				_state = Cleric_State::Hit;
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
					at->PlayAnimation(L"ClericHit", true);
					if (_hit < 2)
						_rigidbody->SetVelocity(Vector2(-50.f, 0.f));
					_hit_switch = true;	_hit++;

					_Hit_Effect->SetDirection(-1);
					_Critical_Middle->SetDirection(-1);
					_Critical_High->SetDirection(-1);

				}
				if (mDir == -1)
				{
					at->PlayAnimation(L"ClericHitR", true);
					if (_hit < 2)
						_rigidbody->SetVelocity(Vector2(50.f, 0.f));
					_hit_switch = true;	_hit++;

					_Hit_Effect->SetDirection(1);
					_Critical_Middle->SetDirection(1);
					_Critical_High->SetDirection(1);
				}

			}
			else
			{
				_hit++;
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
				_state = Cleric_State::Die;
				_Hit_Effect->_effect_animation = true;
				if (mDir == 1)
				{
					at->PlayAnimation(L"ClericDie", false);
					_Hit_Effect->SetDirection(-1);
				}
				else
				{
					at->PlayAnimation(L"ClericDieR", false);
					_Hit_Effect->SetDirection(1);
				}
				_Death_Effect->SetState(eState::Active);
			}

		}

		if (Skul_head* player = dynamic_cast<Skul_head*>(other->GetOwner()))
		{
			if (_state == Cleric_State::Die)
				return;

			bool attack = false;
			bool attack_Cri_Mid = false;
			bool attack_Cri_High = false;

			_HitType = random(1, 10);
			if (_HitType >= 1 && _HitType < 6)
			{
				_Dammege = 25;
				attack = true;
			}
			if (_HitType >= 6 && _HitType < 9)
			{
				_Dammege = random(35, 40);
				attack_Cri_Mid = true;
			}
			if (_HitType >= 9 && _HitType <= 10)
			{
				_Dammege = random(50, 70);
				attack_Cri_High = true;
			}


			if (player->_Head_Attack == false && _bulletcheck == 0)
			{
				if (player->_Ground_check == true)
					return;

				if ((_state == Cleric_State::Finishing_Move_Ready) || (_state == Cleric_State::Teleport_In) || (_state == Cleric_State::Teleport_Out))
				{
					_hit++;
					_Hit_Effect->_effect_animation = true;
					_Critical_Middle->_effect_animation = true;
					_Critical_High->_effect_animation = true;

					if (mDir == 1)
					{
						Monster_Hp->_HitOn = true;
						Monster_Hp->SetHitDamage(_Dammege);
						_CurrenHp = _CurrenHp - _Dammege;
						_Hit_Effect->SetDirection(-1);
						_Critical_Middle->SetDirection(-1);
						_Critical_High->SetDirection(-1);
					}
					else
					{
						Monster_Hp->_HitOn = true;
						Monster_Hp->SetHitDamage(_Dammege);
						_CurrenHp = _CurrenHp - _Dammege;
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
				if (_state == Cleric_State::Idle)
				{
					_hit_switch = true;	_hit++;
					_Hit_Effect->_effect_animation = true;
					_Critical_Middle->_effect_animation = true;
					_Critical_High->_effect_animation = true;
					_state = Cleric_State::Hit;
					if (mDir == 1)
					{
						at->PlayAnimation(L"ClericHit", true);
						if (_hit < 2)
							_rigidbody->SetVelocity(Vector2(-50.f, 0.f));

						Monster_Hp->_HitOn = true;
						Monster_Hp->SetHitDamage(_Dammege);
						_CurrenHp = _CurrenHp - _Dammege;
						_Hit_Effect->SetDirection(-1);
						_Critical_Middle->SetDirection(-1);
						_Critical_High->SetDirection(-1);

					}
					if (mDir == -1)
					{
						at->PlayAnimation(L"ClericHitR", true);
						if (_hit < 2)
							_rigidbody->SetVelocity(Vector2(50.f, 0.f));

						Monster_Hp->_HitOn = true;
						Monster_Hp->SetHitDamage(_Dammege);
						_CurrenHp = _CurrenHp - _Dammege;
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
				if (!((_state == Cleric_State::Idle) || (_state == Cleric_State::Finishing_Move_Ready) || (_state == Cleric_State::Teleport_In) || (_state == Cleric_State::Teleport_Out)))
				{
					_hit++;
					_Hit_Effect->_effect_animation = true;
					_Critical_Middle->_effect_animation = true;
					_Critical_High->_effect_animation = true;

					if (mDir == 1)
					{
						_rigidbody->SetVelocity(Vector2(-20.f, 0.f));

						Monster_Hp->_HitOn = true;
						Monster_Hp->SetHitDamage(_Dammege);
						_CurrenHp = _CurrenHp - _Dammege;
						_Hit_Effect->SetDirection(-1);
						_Critical_Middle->SetDirection(-1);
						_Critical_High->SetDirection(-1);
					}
					else
					{
						_rigidbody->SetVelocity(Vector2(20.f, 0.f));

						Monster_Hp->_HitOn = true;
						Monster_Hp->SetHitDamage(_Dammege);
						_CurrenHp = _CurrenHp - _Dammege;
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
					_state = Cleric_State::Die;
					_Hit_Effect->_effect_animation = true;
					if (mDir == 1)
					{
						at->PlayAnimation(L"ClericDie", false);
						_Hit_Effect->SetDirection(-1);
					}
					else
					{
						at->PlayAnimation(L"ClericDieR", false);
						_Hit_Effect->SetDirection(1);
					}
					_Death_Effect->SetState(eState::Active);
				}
			}
		}

	}
	void Cleric::OnCollisionStay(Collider2D* other)
	{
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{
			_rigidbody->SetGround(true);
			_Ground_check = true;
			_Ground_check = _rigidbody->GetGround();
			_rigidbody->ClearVelocity();
		}


		if (Ground_Map* mGround = dynamic_cast<Ground_Map*>(other->GetOwner()))
		{
			_rigidbody->SetGround(true);
			_Ground_check = true;
			_Ground_check = _rigidbody->GetGround();
			_rigidbody->ClearVelocity();
		}
	}
	void Cleric::OnCollisionExit(Collider2D* other)
	{
	}

	void Cleric::idle()
	{
		_lotationplay = random(0, 3);
		//_lotationplay = 3;

		if (_Intro == false)
		{
			_state = Cleric_State::Intro;
			at->PlayAnimation(L"ClericIntro", true);
		}
		else
		{
			if (_hit >= 3)
			{
				if ((_distance >= -50) && (_distance <= 50))
				{
					_state = Cleric_State::Teleport_In;
					if (mDir == 1)
						at->PlayAnimation(L"ClericTeleport_In", true);
					else
						at->PlayAnimation(L"ClericTeleport_InR", true);
				}
				_hit = 0;
			}
			else
			{
				_time += Time::DeltaTime();
				if (_time >= 3.f)
				{
					//if ((_distance >= -50) && (_distance <= 50))
					//{
					//	_state = Cleric_State::Teleport_In;
					//	if (mDir == 1)
					//		at->PlayAnimation(L"ClericTeleport_In", true);
					//	else
					//		at->PlayAnimation(L"ClericTeleport_InR", true);
					//}
					//else
					{
						if (_lotationplay == 0)
						{
							_state = Cleric_State::Attack_A_Ready;
							if (mDir == 1)
								at->PlayAnimation(L"ClericAttack_A", false);
							else
								at->PlayAnimation(L"ClericAttack_AR", false);
							_attack_sign = true;
						}
						if (_lotationplay == 1)
						{
							_state = Cleric_State::Attack_B_Ready;
							if (mDir == 1)
								at->PlayAnimation(L"ClericAttack_B", false);
							else
								at->PlayAnimation(L"ClericAttack_BR", false);
							_attack_sign = true;
						}
						if (_lotationplay == 2)
						{
							_state = Cleric_State::Attack_C_Ready;
							if (mDir == 1)
								at->PlayAnimation(L"ClericBasic_Heal", true);
							else
								at->PlayAnimation(L"ClericBasic_HealR", true);
						}

						if (_lotationplay == 3)
						{
							_state = Cleric_State::Finishing_Move_Ready;
							if (mDir == 1)
								at->PlayAnimation(L"ClericUltimate_Skill_Casting", true);
							else
								at->PlayAnimation(L"ClericUltimate_Skill_CastingR", true);
							_Ultimate = true;
							//_hit = 9;
						}
					}
				}
			}
		}
	}


	void Cleric::attack_a_ready()
	{

		if(_attack_sign == true)
		{
			Transform* bullet_tr = _Attack_Sign->GetComponent<Transform>();
			_Attack_pos = Vector3(_playerpos.x, _playerpos.y - 20, _playerpos.z - 1);
			bullet_tr->SetPosition(_Attack_pos);
			_Attack_Sign->_effect_On = true;
			_Attack_Sign->SetState(eState::Active);
			_attack_sign = false;
		}
		else
		{
			if (_Attack_Sign->_effect_On == false)
			{
				Transform* bullet_tr = _GraceOfLeonia_Attack_A->GetComponent<Transform>();
				bullet_tr->SetPosition(Vector3(_Attack_pos.x, _Attack_pos.y+60, _Attack_pos.z));
				_GraceOfLeonia_Attack_A->_bullet_On = true;
				_GraceOfLeonia_Attack_A->SetState(eState::Active);
				_state = Cleric_State::Attack_A;
			}
		}

	}
	void Cleric::attack_a()
	{
		if (_GraceOfLeonia_Attack_A->_bullet_On == false)
		{
			_state = Cleric_State::Idle;
			if (mDir == 1)
				at->PlayAnimation(L"ClericIdle", true);
			else
				at->PlayAnimation(L"ClericIdleR", true);

			_time = 0.f;
		}		
	}
	void Cleric::attack_b_ready()
	{
		if (_attack_sign == true)
		{
			Transform* bullet_tr = _Attack_Sign->GetComponent<Transform>();
			_Attack_pos = Vector3(_playerpos.x, _playerpos.y - 20, _playerpos.z - 1);
			bullet_tr->SetPosition(_Attack_pos);
			_Attack_Sign->_effect_On = true;
			_Attack_Sign->SetState(eState::Active);
			_attack_sign = false;
		}
		else
		{
			if (_Attack_Sign->_effect_On == false)
			{
				Transform* bullet_tr = _Veteran_Sanctuary_AtaackB->GetComponent<Transform>();
				bullet_tr->SetPosition(_Attack_pos);
				_Veteran_Sanctuary_AtaackB->_bullet_On = true;
				_Veteran_Sanctuary_AtaackB->SetState(eState::Active);
				_state = Cleric_State::Attack_B;
			}
		}
	}
	void Cleric::attack_b()
	{
		if (_GraceOfLeonia_Attack_A->_bullet_On == false)
		{
			_state = Cleric_State::Idle;
			if (mDir == 1)
				at->PlayAnimation(L"ClericIdle", true);
			else
				at->PlayAnimation(L"ClericIdleR", true);

			_time = 0.f;
		}
	}
	void Cleric::attack_c_ready()
	{
		Transform* bullet_tr = Ultimate_Heal_Effect->GetComponent<Transform>();
		bullet_tr->SetPosition(Vector3(pos.x, pos.y-30, pos.z - 1));
		Ultimate_Heal_Effect->_effect_switch = true;
		if (mDir == 1)
			Ultimate_Heal_Effect->SetDirection(1);
		else
			Ultimate_Heal_Effect->SetDirection(-1);
		
		_CurrenHp = _CurrenHp + 80;
		if (_CurrenHp > _MaxHp)
			_CurrenHp = _MaxHp;
		Ultimate_Heal_Effect->SetState(eState::Active);
		_state = Cleric_State::Attack_C;
	}
	void Cleric::attack_c()
	{
		if (Ultimate_Heal_Effect->_effect_switch == false)
		{
			_state = Cleric_State::Idle;
			if (mDir == 1)
				at->PlayAnimation(L"ClericIdle", true);
			else
				at->PlayAnimation(L"ClericIdleR", true);

			_time = 0.f;
		}
	}


	void Cleric::Finishing_Move_Ready()
	{
		if (_Ultimate == true)
		{
			{
				Transform* bullet_tr = Ultimate_Aura->GetComponent<Transform>();
				Ultimate_Aura->_effect_animation = true;
				if (mDir == 1)
				{
					Ultimate_Aura->SetDirection(1);
					bullet_tr->SetPosition(Vector3(pos.x, pos.y - 30, pos.z - 1));
				}
				else
				{
					Ultimate_Aura->SetDirection(-1);
					bullet_tr->SetPosition(Vector3(pos.x , pos.y - 30, pos.z - 1));
				}
				Ultimate_Aura->SetState(eState::Active);
			}

			{
				Transform* bullet_tr = Ultimate_AuraSmoke->GetComponent<Transform>();
				bullet_tr->SetPosition(Vector3(pos.x, pos.y - 65, pos.z - 1.1));
				if (mDir == 1)
				{
					Ultimate_AuraSmoke->SetDirection(1);
					bullet_tr->SetPosition(Vector3(pos.x, pos.y - 60, pos.z - 1));
				}
				else
				{
					Ultimate_AuraSmoke->SetDirection(-1);
					bullet_tr->SetPosition(Vector3(pos.x, pos.y - 60, pos.z - 1));
				}
				Ultimate_AuraSmoke->SetState(eState::Active);
			}
			_Ultimate = false;
		}

		// 기모으는 이펙트를 넣을것(7초간 지속상태 만들기)
		_attack_time += Time::DeltaTime();
		if (_attack_time >= 7.5)
		{
			Ultimate_Aura->SetState(eState::Paused);
			Ultimate_AuraSmoke->SetState(eState::Paused);
			if (_hit > 8)
			{
				// 이펙트 설정시 9번 hit가 된다면 깨지는 이미지로 넘어간뒤 그로기 상태로넘겨줘야한다.
				Transform* bullet_tr = UltimateSkill_Effect_Fail->GetComponent<Transform>();
				bullet_tr->SetPosition(Vector3(pos.x, pos.y - 25, pos.z - 1.1));
				if (mDir == 1)
					UltimateSkill_Effect_Fail->SetDirection(1);
				else
					UltimateSkill_Effect_Fail->SetDirection(-1);
				UltimateSkill_Effect_Fail->SetState(eState::Active);

				_state = Cleric_State::Finishing_Move_Fail;
				_attack_time = 0.f;
			}
			else
			{
				// 이펙트 설정시 5초가 10번이상의 타격이 없다면 석세스로 넘어간뒤 Effect 날려야한다.
				Transform* bullet_tr = UltimateSkill_Effect_Complete->GetComponent<Transform>();
				bullet_tr->SetPosition(Vector3(pos.x, pos.y - 45, pos.z - 1.1));
				if (mDir == 1)
					UltimateSkill_Effect_Complete->SetDirection(1);
				else
					UltimateSkill_Effect_Complete->SetDirection(-1);
				UltimateSkill_Effect_Complete->SetState(eState::Active);

				if (mDir == 1)
					at->PlayAnimation(L"ClericUltimate_Skill", true);
				else
					at->PlayAnimation(L"ClericUltimate_SkillR", true);
				_Ultimate_Skill = false;
				//_state = Cleric_State::Finishing_Move_Succes;
				_attack_time = 0.f;
			}
		}
	}
	void Cleric::Finishing_Move_Succes()
	{
		if (_Ultimate_Skill == false)
		{
			Transform* bullet_tr = Ultimate_SkillEffect->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(0, 0, -205));
			Ultimate_SkillEffect->_effect_On = true;
			Ultimate_SkillEffect->SetState(eState::Active);
			_Ultimate_Skill = true;
		}
		else
		{
			Transform* bullet_tr = Ultimate_Heal_Effect->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(pos.x, pos.y-30, pos.z-1));
			Ultimate_Heal_Effect->_effect_animation = true;
			if (mDir == 1)
			{
				Ultimate_Heal_Effect->SetDirection(1);
				at->PlayAnimation(L"ClericUltimate_Skill_End", false);
			}
			else
			{
				Ultimate_Heal_Effect->SetDirection(-1);
				at->PlayAnimation(L"ClericUltimate_Skill_EndR", false);
			}
			Ultimate_Heal_Effect->SetState(eState::Active);

			_CurrenHp = _CurrenHp + 150;
			if (_CurrenHp > _MaxHp)
				_CurrenHp = _MaxHp;
			_state = Cleric_State::Finishing_Move;
		}
	}
	void Cleric::Finishing_Move_Fail()
	{
		_state = Cleric_State::Groggy;
		if (mDir == 1)
			at->PlayAnimation(L"ClericGroggy", true);
		else
			at->PlayAnimation(L"ClericGroggy", true);
	}
	void Cleric::Finishing_Move()
	{
		if (Ultimate_SkillEffect->_effect_On == false)
		{
			_state = Cleric_State::Idle;
			if (mDir == 1)
				at->PlayAnimation(L"ClericIdle", true);
			else
				at->PlayAnimation(L"ClericIdleR", true);
			_time = 0.f;
		}
	}
	void Cleric::casting()
	{
	}
	void Cleric::groggy()
	{
		_attack_time += Time::DeltaTime();
		if (_attack_time >= 3.5)
		{
			_attack_time = 0;
			_state = Cleric_State::Idle;
			if (mDir == 1)
				at->PlayAnimation(L"ClericIdle", true);
			else
				at->PlayAnimation(L"ClericIdleR", true);
			_time = 0.f;
		}
	}


	void Cleric::hit()
	{
	}
	void Cleric::die()
	{
		_Die = true;
		Ultimate_Aura->SetState(eState::Paused);
		Ultimate_AuraSmoke->SetState(eState::Paused);	
	}
	void Cleric::intro()
	{
	}
	void Cleric::potion()
	{
	}
	void Cleric::teleport_in()
	{
		if (_Teleport == true)
		{
			int a = 0;
			_state = Cleric_State::Teleport_Out;
			if (mDir == 1)
				at->PlayAnimation(L"ClericTeleport_Out", true);
			else
				at->PlayAnimation(L"ClericTeleport_OutR", true);

			_time = 0.f;
			_Teleport = false;
		}
	}
	void Cleric::teleport_out()
	{
	}



	void Cleric::SetDirection()
	{
		pos = tr->GetPosition();
		_velocity = _rigidbody->GetVelocity();
		_playerpos = Player::GetPlayer_Pos();
		_distance = _playerpos.x - pos.x;
		if (_distance >= 0.f)
			mDir = 1;
		else
			mDir = -1;
	}
	void Cleric::Particle_Control()
	{
	}
	void Cleric::Hpcontrol()
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
			_MbossFace->Set_animation(true);
			_MbossFace->Set_UISelect(3);
		}
	}
	void Cleric::Effect_Control()
	{
		{
			Transform* _Hit_Effect_TR = _Hit_Effect->GetComponent<Transform>();
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



	void Cleric::complete_attack_a()
	{
		_state = Cleric_State::Idle;
		if (mDir == 1)
			at->PlayAnimation(L"ClericIdle", true);
		else
			at->PlayAnimation(L"ClericIdleR", true);

		_time = 0.f;
	}
	void Cleric::complete_attack_b()
	{
		_state = Cleric_State::Idle;
		if (mDir == 1)
			at->PlayAnimation(L"ClericIdle", true);
		else
			at->PlayAnimation(L"ClericIdleR", true);

		_time = 0.f;
	}
	void Cleric::complete_ultimate_skill()
	{
		_state = Cleric_State::Finishing_Move_Succes;
	}
	void Cleric::complete_intro()
	{
		_state = Cleric_State::Idle;
		if (mDir == 1)
			at->PlayAnimation(L"ClericIdle", true);
		else
			at->PlayAnimation(L"ClericIdleR", true);

		_time = 0.f;
		_Intro = true;
	}
	void Cleric::complete_teleport_in()
	{
		if (_Teleport == false)
		{
			if (pos.x >= _first_place.x)
			{
				if (ground_distance_L < -100)
					pos.x = pos.x - 300.f;
				else
					pos.x = pos.x + 400.f;
			}
			else
			{
				if (ground_distance_R > 100)				
					pos.x = pos.x + 300.f;
				else
					pos.x = pos.x - 400.f;
			}
			_Teleport = true;
			//_state = Cleric_State::Teleport_Out;
		}
		tr->SetPositionXY(Vector2(pos.x,pos.y));
	}
	void Cleric::complete_teleport_out()
	{
		if (_Teleport == false)
		{
			_state = Cleric_State::Idle;
			if (mDir == 1)
				at->PlayAnimation(L"ClericIdle", true);
			else
				at->PlayAnimation(L"ClericIdleR", true);
		}
		_time = 0.f;
	}

	void Cleric::complete_hit()
	{
		if (mDir == 1)
			at->PlayAnimation(L"ClericIdle", true);
		else
			at->PlayAnimation(L"ClericIdleR", true);
		_state = Cleric_State::Idle;
	}

}