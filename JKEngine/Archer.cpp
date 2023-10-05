#include "Archer.h"



namespace jk
{
	int Archer::mDir = 1;
	bool Archer::_switch = false;
	
	Archer::Archer()
		: _state()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}
	Archer::~Archer()
	{
	}


	void Archer::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(false);
		_tr = GetComponent<Transform>();

		
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Attack_A", this,0);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Attack_B", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Attack_C", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\BackStep", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Dash", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Die", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Groggy", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Hit", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Intro", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Potion", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Ultimate", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Ultimate_Ready", this);
		
		
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Attack_A", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Attack_B", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Attack_C", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\BackStep", this, 1);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Dash", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Die", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Groggy", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Hit", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Idle", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Intro", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Potion", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Ultimate", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Ultimate_Ready", this, 1);
		

		//bind 부분
		at->CompleteEvent(L"ArcherAttack_A") = std::bind(&Archer::choicecombo, this);
		at->CompleteEvent(L"ArcherAttack_AR") = std::bind(&Archer::choicecombo, this);

		at->CompleteEvent(L"ArcherAttack_C") = std::bind(&Archer::choicecombo, this);
		at->CompleteEvent(L"ArcherAttack_CR") = std::bind(&Archer::choicecombo, this);		


		at->CompleteEvent(L"ArcherHit") = std::bind(&Archer::complete_hit, this);
		at->CompleteEvent(L"ArcherHitR") = std::bind(&Archer::complete_hit, this);

		at->CompleteEvent(L"ArcherIntro") = std::bind(&Archer::CompleteArcherIntro, this);
		at->CompleteEvent(L"ArcherIntroR") = std::bind(&Archer::CompleteArcherIntro, this);
		

		//UI 및 체력관련		
		{
			_MbossFace = new AdventureUI();
			_MbossFace->Initialize();
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
			hp_tr->SetScale(108.f*2, 30.f*2,0);		
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
			hp_tr->SetPosition(Vector3(pos.x, pos.y -90, pos.z - 1));
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
			_archer_arrow = new Archer_Arrow;
			_archer_arrow->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Bullet, _archer_arrow);
			Transform* EffectTR = _archer_arrow->GetComponent<Transform>();
			EffectTR->SetPosition(_tr->GetPosition());
			_archer_arrow->SetState(eState::Paused);
		}
		{
			Upward_Sign = new Archer_Arrow_Upward_Sign;
			Upward_Sign->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, Upward_Sign);
			Transform* EffectTR = Upward_Sign->GetComponent<Transform>();
			EffectTR->SetPosition(_tr->GetPosition());
			Upward_Sign->SetState(eState::Paused);
		}
		{
			Upward_Impact_Bullet = new Archer_Upward_Impact_Bullet;
			Upward_Impact_Bullet->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Bullet, Upward_Impact_Bullet);
			Transform* EffectTR = Upward_Impact_Bullet->GetComponent<Transform>();
			EffectTR->SetPosition(_tr->GetPosition());
			Upward_Impact_Bullet->SetState(eState::Paused);
		}
		{
			Arrow_Bye_effect = new Archer_Arrow_Bye;
			Arrow_Bye_effect->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, Arrow_Bye_effect);
			Transform* EffectTR = Arrow_Bye_effect->GetComponent<Transform>();
			EffectTR->SetPosition(_tr->GetPosition());
			Arrow_Bye_effect->SetState(eState::Paused);
		}
		{
			for (int i = 0; i < 6; i++)
			{
				Bullet_Trap[i] = new Archer_Trap;
				Bullet_Trap[i]->Initialize();
				Scene * scene = SceneManager::GetActiveScene();
				scene->AddGameObject(eLayerType::Bullet, Bullet_Trap[i]);
				Transform* EffectTR = Bullet_Trap[i]->GetComponent<Transform>();
				EffectTR->SetPosition(_tr->GetPosition());
				Bullet_Trap[i]->SetState(eState::Paused);
			}
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
			Utimate_Sign = new Archer_Utimate_Sign;
			Utimate_Sign->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, Utimate_Sign);
			Transform* bullet_tr = Utimate_Sign->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205));
			Utimate_Sign->SetState(eState::Paused);
		}

		{
			for (int i = 0; i < 40; i++)
			{
				Ultimate_Upward_ImpactBullet[i] = new Archer_Upward_Impact_Bullet;
				Ultimate_Upward_ImpactBullet[i]->Initialize();
				Scene* scene = SceneManager::GetActiveScene();
				scene->AddGameObject(eLayerType::Bullet, Ultimate_Upward_ImpactBullet[i]);
				Transform* EffectTR = Ultimate_Upward_ImpactBullet[i]->GetComponent<Transform>();
				EffectTR->SetPosition(_tr->GetPosition());
				Ultimate_Upward_ImpactBullet[i]->SetState(eState::Paused);
			}
		}
			
		{
			for (int i = 0; i < 40; i++)
			{
				Ultimate_ArrowBye_effect[i] = new Archer_Arrow_Bye;
				Ultimate_ArrowBye_effect[i]->Initialize();
				Scene* scene = SceneManager::GetActiveScene();
				scene->AddGameObject(eLayerType::Effect, Ultimate_ArrowBye_effect[i]);
				Transform* EffectTR = Ultimate_ArrowBye_effect[i]->GetComponent<Transform>();
				EffectTR->SetPosition(_tr->GetPosition());
				Ultimate_ArrowBye_effect[i]->SetState(eState::Paused);
			}
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



		at->PlayAnimation(L"ArcherIdle", true);
		GameObject::Initialize();
	}
	void Archer::Update()
	{
		SetDirection();
		Particle_Control();
		Hpcontrol();
		Effect_Control();

		ground_distance_L = Left_Ground.x - pos.x;
		ground_distance_R = Right_Ground.x - pos.x;

		switch (_state)
		{
		case jk::Archer::Archer_State::Idle:
			idle();
			break;

		case jk::Archer::Archer_State::BackDash:
			backdash();
			break;

		case jk::Archer::Archer_State::Die:
			die();
			break;

		case jk::Archer::Archer_State::Attack_A_Ready:
			attack_a_ready();
			break;

		case jk::Archer::Archer_State::Attack_A:
			attack_a();
			break;

		case jk::Archer::Archer_State::Attack_A_End:
			attack_a_end();
			break;

		case jk::Archer::Archer_State::Attack_B_Ready:
			attack_b_ready();
			break;

		case jk::Archer::Archer_State::Attack_B:
			attack_b();
			break;

		case jk::Archer::Archer_State::Attack_B_End:
			attack_b_end();
			break;

		case jk::Archer::Archer_State::Attack_C:
			attack_c();
			break;

		case jk::Archer::Archer_State::Finishing_Move_Ready:
			Finishing_Move_Ready();
			break;

		case jk::Archer::Archer_State::Finishing_Move_Succes:
			Finishing_Move_Succes();
			break;

		case jk::Archer::Archer_State::Finishing_Move_Fail:
			Finishing_Move_Fail();
			break;

		case jk::Archer::Archer_State::Finishing_Move:
			Finishing_Move();
			break;

		case jk::Archer::Archer_State::Groggy:
			groggy();
			break;

		case jk::Archer::Archer_State::Hit:
			hit();
			break;

		case jk::Archer::Archer_State::Intro:
			intro();
			break;

		case jk::Archer::Archer_State::Potion:
			potion();
			break;

		default:
			break;
		}		
		_tr->SetPosition(Vector3(pos));
		GameObject::Update();
	}
	void Archer::LateUpdate()
	{
		_collider->SetSize(Vector2(0.5f, 0.5f));
		if(mDir ==1)
			_collider->SetCenter(Vector2(0.0f, -25.f));
		else
			_collider->SetCenter(Vector2(0.0f, -25.f));

		GameObject::LateUpdate();
	}
	void Archer::Render()
	{
		GameObject::Render();
	}


	void Archer::OnCollisionEnter(Collider2D* other)
	{	
		if (HitBox_Player* player = dynamic_cast<HitBox_Player*>(other->GetOwner()))
		{
			if (_state == Archer_State::Die)
				return;

			_Damage = player->GetDamage();
			bool attack = player->Geteffect();
			bool attack_Cri_Mid = player->Geteffect_Mid();
			bool attack_Cri_High = player->Geteffect_Hight();
		
			if (_state == Archer_State::Idle)
			{
				_state = Archer_State::Hit;
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
					at->PlayAnimation(L"ArcherHit", true);
					if (_hit < 2)
					_rigidbody->SetVelocity(Vector2(-50.f, 0.f));
					_hit_switch = true;	_hit++;

					_Hit_Effect->SetDirection(-1);
					_Critical_Middle->SetDirection(-1);
					_Critical_High->SetDirection(-1);

				}
				if (mDir == -1)
				{
					at->PlayAnimation(L"ArcherHitR", true);
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
				attack = false;
				player->Seteffect(false);
			}
			if (attack_Cri_Mid == true)
			{
				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetState(eState::Active);
				attack_Cri_Mid = false;
				player->Seteffect_Mid(false);
			}
			if (attack_Cri_High == true)
			{
				_Critical_High->_effect_animation = true;
				_Critical_High->SetState(eState::Active);
				attack_Cri_High = false;
				player->Seteffect_Hight(false);
			}

			if (_CurrenHp <= 0)
			{
				_state = Archer_State::Die;
				_Hit_Effect->_effect_animation = true;
				if (mDir == 1)
				{
					at->PlayAnimation(L"ArcherDie", false);
					_Hit_Effect->SetDirection(-1);
				}
				else
				{
					at->PlayAnimation(L"ArcherDieR", false);
					_Hit_Effect->SetDirection(1);
				}
				_Death_Effect->SetState(eState::Active);
			}
		}

		if (Skul_head* player = dynamic_cast<Skul_head*>(other->GetOwner()))
		{
			if (_state == Archer_State::Die)
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

				if ((_state == Archer_State::Finishing_Move_Ready) || (_state == Archer_State::BackDash))
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
				if (_state == Archer_State::Idle)
				{
					_hit_switch = true;	_hit++;
					_Hit_Effect->_effect_animation = true;
					_Critical_Middle->_effect_animation = true;
					_Critical_High->_effect_animation = true;
					_state = Archer_State::Hit;
					if (mDir == 1)
					{
						at->PlayAnimation(L"ArcherHit", true);
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
						at->PlayAnimation(L"ArcherHitR", true);
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
				if (!((_state == Archer_State::Idle) || (_state == Archer_State::Finishing_Move_Ready) || (_state == Archer_State::BackDash)))
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
					_state = Archer_State::Die;
					_Hit_Effect->_effect_animation = true;
					if (mDir == 1)
					{
						at->PlayAnimation(L"ArcherDie", false);
						_Hit_Effect->SetDirection(-1);
					}
					else
					{
						at->PlayAnimation(L"ArcherDieR", false);
						_Hit_Effect->SetDirection(1);
					}
					_Death_Effect->SetState(eState::Active);
				}
			}
		}		

		if (Skul_Spear* player = dynamic_cast<Skul_Spear*>(other->GetOwner())){}

		if (Skul_Wolf* player = dynamic_cast<Skul_Wolf*>(other->GetOwner())){}

	}
	void Archer::OnCollisionStay(Collider2D* other)
	{
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{
			if (_Ground_check == false)
			{
				_rigidbody->SetGround(true);
				_Ground_check = true;
				_rigidbody->ClearVelocity();
			}
			if (_state == Archer_State::BackDash)
			{
				if (_Ground_check == true)
				{
					_BackDash = false;
				}
			}
		}		

		if (Ground_Map* mGround = dynamic_cast<Ground_Map*>(other->GetOwner()))
		{
			if (_Ground_check == false)
			{
				_rigidbody->SetGround(true);
				_Ground_check = true;
				_rigidbody->ClearVelocity();
			}
			if (_state == Archer_State::BackDash)
			{
				if (_Ground_check == true)				
					_BackDash = false;

			}
		}
	}
	void Archer::OnCollisionExit(Collider2D* other)
	{
	}


	void Archer::idle()
	{
		_time += Time::DeltaTime();
	
		_hit_switch = false;

		if (_Intro == false)
		{
			_state = Archer_State::Intro;
			at->PlayAnimation(L"ArcherIntroR", true);
		}
		else
		{
			if (_hit >= 3)
			{
				if (_Numberof_BackDash <= 2)
				{
					if (mDir == 1)
					{
						if (ground_distance_L < -100)
						{
							at->PlayAnimation(L"ArcherBackStep", false);
							_rigidbody->SetVelocity(Vector2(-200.f, 200.f));
							_rigidbody->AddForce(Vector2(-10, 20));
							_Ground_check = false;
							_rigidbody->SetGround(false);
							_BackDash = true;
							_state = Archer_State::BackDash;
							_Numberof_BackDash++;
						}
						else
						{
							at->PlayAnimation(L"ArcherBackStepR", false);
							_rigidbody->SetVelocity(Vector2(350.f, 200.f));
							_rigidbody->AddForce(Vector2(10, 20));
							_Ground_check = false;
							_rigidbody->SetGround(false);
							_BackDash = true;
							_state = Archer_State::BackDash;			
							_Numberof_BackDash++;
						}
					}
					else
					{
						if (ground_distance_R > 100)
						{
							at->PlayAnimation(L"ArcherBackStepR", false);
							_rigidbody->SetVelocity(Vector2(200.f, 200.f));
							_rigidbody->AddForce(Vector2(10, 20));
							_Ground_check = false;
							_rigidbody->SetGround(false);
							_BackDash = true;
							_state = Archer_State::BackDash;
							_Numberof_BackDash++;
						}
						else
						{
							at->PlayAnimation(L"ArcherBackStep", false);
							_rigidbody->SetVelocity(Vector2(-350.f, 200.f));
							_rigidbody->AddForce(Vector2(-10, 20));
							_Ground_check = false;
							_rigidbody->SetGround(false);
							_BackDash = true;
							_state = Archer_State::BackDash;
							_Numberof_BackDash++;
						}
					}
				}
				else
				{
					_hit = 0; _Numberof_BackDash = 0;
				}
			}
			else
			{
				if (_time > 3.f)
				{
					if ((_distance <= 80 && _distance >= -80))
					{
						_choicecombo = 2;
					}
					else
					{
						_choicecombo = random(0, 3);						
						_attack = true;
						choicecombo();
					}
				}
			}
		}
	}
	void Archer::backdash()
	{
		if (_BackDash == false)
		{
			for (int i = 0; i < 6; i++)
			{
				if (Bullet_Trap[i]->_Bullet_Life == true)
					continue;
				else/* if (Bullet_Trap[i]->_Bullet_Life == false)*/
				{
					Transform* EffectTR = Bullet_Trap[i]->GetComponent<Transform>();
					RigidBody* Effectrb = Bullet_Trap[i]->GetComponent<RigidBody>();
					EffectTR->SetPosition(_tr->GetPosition());
					Bullet_Trap[i]->_Bullet_Life = true;
					Effectrb->SetGround(false);
					Bullet_Trap[i]->SetState(eState::Active);
					break;
				}
			}

			_state = Archer_State::Idle;
			if (mDir == 1)
				at->PlayAnimation(L"ArcherIdle", true);
			else
				at->PlayAnimation(L"ArcherIdleR", true);
		}	
	}
	void Archer::die()
	{
		_Die = true;
		Ultimate_Aura->SetState(eState::Paused);
		Ultimate_AuraSmoke->SetState(eState::Paused);
	}


	void Archer::attack_a_ready()
	{
		_attack_time += Time::DeltaTime();
		if (_attack_time > 0.7)
		{
			_state = Archer_State::Attack_A;
			_attack_time = 0;
		}
	}
	void Archer::attack_a()
	{
		Transform* EffectTR = _archer_arrow->GetComponent<Transform>();
		RigidBody* EffectRG = _archer_arrow->GetComponent<RigidBody>();
		if (_attack_a == false)
		{			
			if (mDir == 1)
			{
				_attackDir = 1;
				_archer_arrow->_bullet_animation= true;
				_archer_arrow->SetDirection(1);
				EffectTR->SetPosition(pos.x + 20, pos.y - 30, pos.z - 1);
			}
			if (mDir == -1)
			{
				_attackDir = -1;
				_archer_arrow->_bullet_animation = true;
				_archer_arrow->SetDirection(-1);
				EffectTR->SetPosition(pos.x - 20, pos.y - 30, pos.z - 1);
			}
			_archer_arrow->SetState(eState::Active);
			_attack_a = true;
		}
		if (_attack_a == true)
		{
			Vector3 arrowpos = EffectTR->GetPosition();
			_attack_time += Time::DeltaTime();
			if (_attack_time < 2)
			{		
				if (_attackDir == 1)
				{
					EffectRG->SetFriction(true);
					EffectRG->SetGravity(true);
					EffectRG->SetVelocity(Vector2(450.f, 0.f));
				}
				else
				{
					EffectRG->SetFriction(true);
					EffectRG->SetGravity(true);
					EffectRG->SetVelocity(Vector2(-450.f, 0.f));
				}	
			}		
			else
			{
				EffectRG->ClearVelocity();
				EffectRG->SetFriction(false);
				EffectRG->SetGravity(false);
				_archer_arrow->SetState(eState::Paused);
				_state = Archer_State::Attack_A_End;
				_attack_time = 0;				
			}
		}	
	}
	void Archer::attack_a_end()
	{
		_attack_a = false;
		_attack = false;
		choicecombo();
	}


	void Archer::attack_b_ready()
	{		
		_attack_time += Time::DeltaTime();
		if (_attack_time > 1)
		{
			Transform* EffectTR = Upward_Sign->GetComponent<Transform>();
			EffectTR->SetPosition(_playerpos.x, _playerpos.y, _playerpos.z - 1);
			Upward_Sign->_effect_On = true;
			Upward_Sign->SetState(eState::Active);

			if (mDir == 1)
				at->PlayAnimation(L"ArcherIdle", true);
			if(mDir ==-1)
				at->PlayAnimation(L"ArchereIdleR", false);

			_attack_b_sign = true;
			_state = Archer_State::Attack_B;
			_attack_time = 0;
		}		
	}
	void Archer::attack_b()
	{
		if (_attack_b_sign == true)
		{
			_attack_time += Time::DeltaTime();
			if (_attack_time > 1)
			{
				Transform* EffectTR = Upward_Sign->GetComponent<Transform>();
				Vector3 effect = EffectTR->GetPosition();
				Transform* BullettTR = Upward_Impact_Bullet->GetComponent<Transform>();
				BullettTR->SetPosition(effect.x, effect.y+145, effect.z - 1);
				Upward_Impact_Bullet->_bullet_On = true;
				Upward_Impact_Bullet->SetState(eState::Active);				
				_state = Archer_State::Attack_B_End;
				_attack_time = 0;
			}			
		}	
	}
	void Archer::attack_b_end()
	{
		if (Upward_Impact_Bullet->_bullet_On == false)
		{
			Transform* BullettTR = Upward_Impact_Bullet->GetComponent<Transform>();
			Vector3 bullet = BullettTR -> GetPosition();		

			Upward_Sign->SetState(eState::Paused);
			Transform* EffectTR = Arrow_Bye_effect->GetComponent<Transform>();
			EffectTR->SetPosition(bullet.x, bullet.y-125, bullet.z);
			Arrow_Bye_effect->_effect_On = true;
			Arrow_Bye_effect->SetState(eState::Active);

			_attack = false;
			_attack_b_sign = false;
			choicecombo();
		}
	}


	void Archer::attack_c()
	{
		//_attackorder = 0;
		_attack = false;
	}


	void Archer::Finishing_Move_Ready()
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
					bullet_tr->SetPosition(Vector3(pos.x, pos.y - 30, pos.z - 1));
				}
				Ultimate_Aura->SetState(eState::Active);
			}

			{
				Transform* bullet_tr = Ultimate_AuraSmoke->GetComponent<Transform>();
				bullet_tr->SetPosition(Vector3(pos.x, pos.y - 55, pos.z - 1.1));
				if (mDir == 1)
				{
					Ultimate_AuraSmoke->SetDirection(1);
					bullet_tr->SetPosition(Vector3(pos.x, pos.y - 50, pos.z - 1));
				}					
				else
				{
					Ultimate_AuraSmoke->SetDirection(-1);
					bullet_tr->SetPosition(Vector3(pos.x, pos.y - 50, pos.z - 1));
				}					
				Ultimate_AuraSmoke->SetState(eState::Active);
			}
			_Ultimate = false;
		}
		// 기모으는 이펙트를 넣을것(7초간 지속상태 만들기)
		_attack_time += Time::DeltaTime();
		if (_attack_time >= 4.5)
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

				_state = Archer_State::Finishing_Move_Fail;
				_attack_time = 0.f;				
			}
			else
			{
				// 이펙트 설정시 5초가 10번이상의 타격이 없다면 석세스로 넘어간뒤 활공격을 날려야한다.
				Transform* bullet_tr = UltimateSkill_Effect_Complete->GetComponent<Transform>();
				bullet_tr->SetPosition(Vector3(pos.x, pos.y - 25, pos.z - 1.1));
				if (mDir == 1)
					UltimateSkill_Effect_Complete->SetDirection(1);
				else
					UltimateSkill_Effect_Complete->SetDirection(-1);
				UltimateSkill_Effect_Complete->SetState(eState::Active);

				if (mDir == 1)
					at->PlayAnimation(L"ArcherUltimate", false);
				else
					at->PlayAnimation(L"ArcherUltimateR", false);
				_state = Archer_State::Finishing_Move_Succes;
				_attack_time = 0.f;
			}
		}
	}
	void Archer::Finishing_Move_Succes()
	{
		if (_Ultimate_Skill == false)
		{
			Transform* bullet_tr = Utimate_Sign->GetComponent<Transform>();
			Ultimate_Skill_pos = Vector3(_playerpos.x, _playerpos.y-20, _playerpos.z-1);
			bullet_tr->SetPosition(Ultimate_Skill_pos);
			Utimate_Sign->_effect_On = true;
			Utimate_Sign->SetState(eState::Active);


			for (int i = 0; i < 40; i++)
			{
				int Ultimate_skill = random(_playerpos.x - 75, _playerpos.x +75);
				Ultimate_Skill_pos.x = Ultimate_skill;

				Transform* BulletTR = Ultimate_Upward_ImpactBullet[i]->GetComponent<Transform>();	
				Ultimate_Upward_ImpactBullet[i]->_bullet_On = true;
				BulletTR->SetPosition(Vector3(Ultimate_skill, Ultimate_Skill_pos.y+150, Ultimate_Skill_pos.z));

				Transform* EffectTR = Ultimate_ArrowBye_effect[i]->GetComponent<Transform>();			
				EffectTR->SetPosition(Vector3(Ultimate_skill, Ultimate_Skill_pos.y+40, Ultimate_Skill_pos.z));
				
				if(i == 39)
					_Ultimate_Skill = true;
			}			
		}
		else
		{
			if (Utimate_Sign->_effect_On == false)
			{

				_attack_time += Time::DeltaTime();
				if (_attack_time < 7.f)
				{
					for (int i = 0; i < 40; i++)
					{
						Ultimate_ArrowBye_effect[i]->_effect_On = true;
						if (_attack_time >= (1.0f + 0.2f * i))
						{
							if (Ultimate_Upward_ImpactBullet[i]->_bullet_On == true)
								Ultimate_Upward_ImpactBullet[i]->SetState(eState::Active);
							if (Ultimate_Upward_ImpactBullet[i]->_bullet_On == false)
							{
								Ultimate_Upward_ImpactBullet[i]->SetState(eState::Paused);
								if (Ultimate_ArrowBye_effect[i]->_effect_On == true)
									Ultimate_ArrowBye_effect[i]->SetState(eState::Active);
							}			
						}	
					}
				}
				else
				{
					_state = Archer_State::Finishing_Move;
					_attack_time = 0;
					_Ultimate_Skill = false;
				}
			}
		}
	}
	void Archer::Finishing_Move_Fail()
	{
		_state = Archer_State::Groggy;
		if (mDir == 1)
			at->PlayAnimation(L"ArcherGroggy", true);
		else
			at->PlayAnimation(L"ArcherGroggyR", true);
		_hit = 0;
	}
	void Archer::Finishing_Move()
	{
		_attack = false;
		choicecombo();
	}


	void Archer::groggy()
	{
		_attack_time += Time::DeltaTime();
		if (_attack_time >= 3.5)
		{
			_attack_time = 0;	
			_attack = false;
			choicecombo();
		}
	}
	void Archer::hit()
	{	
	}
	void Archer::intro()
	{
		_Intro = true;
	}
	void Archer::potion()
	{
	}
	void Archer::choicecombo()
	{
		if (_attack == true)
		{
			if (_choicecombo == 0)
			{
				_number_of_attack++;
				shootbow_forward();
			}
			if (_choicecombo == 1)
			{
				_number_of_attack++;
				shootbow_upward();
			}
			if (_choicecombo == 2)
			{
				_number_of_attack++;
				ultimate();
			}
			if (_choicecombo == 3)
			{				
				dash_combo();
			}

			if (_choicecombo == 10)
			{
				_number_of_attack++;
				pushaway();
			}
		}
		else
		{			
			if (_number_of_attack >= 3)
			{
				_number_of_attack = 0;
				_time = 0.f;
			}
			_state = Archer_State::Idle;
			if (mDir == 1)
				at->PlayAnimation(L"ArcherIdle", true);
			else
				at->PlayAnimation(L"ArcherIdleR", true);
		}
	}


	void Archer::shootbow_forward()
	{
		_state = Archer_State::Attack_A_Ready;
		if (mDir == 1)
			at->PlayAnimation(L"ArcherAttack_A", false);
		else
			at->PlayAnimation(L"ArcherAttack_AR", false);
	}
	void Archer::shootbow_upward()
	{
		_state = Archer_State::Attack_B_Ready;
		if (mDir == 1)
			at->PlayAnimation(L"ArcherAttack_B", false);
		if (mDir == -1)
			at->PlayAnimation(L"ArcherAttack_BR", false);
	}
	void Archer::pushaway()
	{
		_state = Archer_State::Attack_C;
		if (mDir == 1)
			at->PlayAnimation(L"ArcherAttack_C", true);
		else
			at->PlayAnimation(L"ArcherAttack_CR", true);
	}
	void Archer::ultimate()
	{
		_state = Archer_State::Finishing_Move_Ready;
		if (mDir == 1)
			at->PlayAnimation(L"ArcherUltimate_Ready", false);
		else
			at->PlayAnimation(L"ArcherUltimate_ReadyR", false);
		_Ultimate = true;	
		//_hit = 9;
	}
	void Archer::dash_combo()
	{
		if (mDir == 1)
		{
			at->PlayAnimation(L"ArcherBackStep", false);
			_rigidbody->SetVelocity(Vector2(-200.f, 200.f));
			_rigidbody->AddForce(Vector2(-10, 10));
			_Ground_check = false;
			_rigidbody->SetGround(false);
			_BackDash = true;
			_state = Archer_State::BackDash;
			_Numberof_BackDash++;
		}
		else
		{
			at->PlayAnimation(L"ArcherBackStepR", false);
			_rigidbody->SetVelocity(Vector2(200.f, 200.f));
			_rigidbody->AddForce(Vector2(10, 10));
			_Ground_check = false;
			_rigidbody->SetGround(false);
			_BackDash = true;
			_state = Archer_State::BackDash;
			_Numberof_BackDash++;
		}
	}


	void Archer::CompleteArcherIntro()
	{
		_state = Archer_State::Idle;
		if (mDir == 1)
			at->PlayAnimation(L"ArcherIdle", true);
		else
			at->PlayAnimation(L"ArcherIdleR", true);
	}


	void Archer::SetDirection()
	{
		_tr = GetComponent<Transform>();
		pos = _tr->GetPosition();
		_velocity = _rigidbody->GetVelocity();
		_playerpos = Player::GetPlayer_Pos();
		_distance = _playerpos.x - pos.x;
		if (_distance >= 0.f)
			mDir = 1;
		else
			mDir = -1;
	}
	void Archer::Particle_Control()
	{
	}
	void Archer::Hpcontrol()
	{
		Transform* STATEUI_tr = _State_UI->GetComponent<Transform>();
		Transform* STATEUIhp_tr1 = Monster_UIHp->GetComponent<Transform>();
		Transform* STATEUIhp_tr2 = Monster_UIDamegeHp->GetComponent<Transform>();
		Transform* face_tr = _MbossFace->GetComponent<Transform>();

		if (_UIstate == 0)//1번
		{
			STATEUI_tr->SetPosition(Vector3(685.f, 375.f, 10));
			STATEUIhp_tr1->SetPosition(Vector3(650.f, 354.f, 5 ));
			STATEUIhp_tr2->SetPosition(Vector3(650.f, 354.f, 6));
			face_tr->SetPosition(Vector3(762.f, 375.f,1));
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
			_MbossFace->Set_UISelect(1);
		}
	}
	void Archer::Effect_Control()
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




	void Archer::complete_hit()
	{
		if (mDir == 1)
			at->PlayAnimation(L"ArcherIdle", true);
		else
			at->PlayAnimation(L"ArcherIdleR", true);
		_state = Archer_State::Idle;

	}
	void Archer::complete_attackA()
	{
	
	}
}