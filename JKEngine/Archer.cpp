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
		//_playerpos = oWner->GetComponent<Transform>()->GetPosition();

		//Skul_Head = new Skul_head();
		//Skul_Head->Initialize();
		//Scene* scene = SceneManager::GetActiveScene();
		//scene->AddGameObject(eLayerType::Item, Skul_Head);
		//Transform* tr_head = Skul_Head->GetComponent<Transform>();
		//tr_head->SetPosition(Vector3(pos.x, pos.y, -250.f));
		//Skul_Head->GetComponent<Transform>()->SetScale(Vector3(15.f, 13.f, 0.f));
		//Skul_Head->SetState(eState::Paused);

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
		//at->CompleteEvent(L"ArcherAttack_B") = std::bind(&Archer::choicecombo, this);
		//at->CompleteEvent(L"ArcherAttack_BR") = std::bind(&Archer::choicecombo, this);
		at->CompleteEvent(L"ArcherAttack_C") = std::bind(&Archer::choicecombo, this);
		at->CompleteEvent(L"ArcherAttack_CR") = std::bind(&Archer::choicecombo, this);		


		at->CompleteEvent(L"ArcherHit") = std::bind(&Archer::complete_hit, this);
		at->CompleteEvent(L"ArcherHitR") = std::bind(&Archer::complete_hit, this);

		at->CompleteEvent(L"ArcherIntro") = std::bind(&Archer::CompleteArcherIntro, this);
		at->CompleteEvent(L"ArcherIntroR") = std::bind(&Archer::CompleteArcherIntro, this);
		
		//at->CompleteEvent(L"Knight_maleExplosion_Loop") = std::bind(&Knight_male::choicecombo, this);
		//at->CompleteEvent(L"Knight_maleExplosion_LoopR") = std::bind(&Knight_male::choicecombo, this);

		
		
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

		at->PlayAnimation(L"ArcherIdle", true);
		GameObject::Initialize();
	}
	void Archer::Update()
	{
		_tr = GetComponent<Transform>();
		pos = _tr->GetPosition();
		_velocity = _rigidbody->GetVelocity();
		_playerpos;
		_distance = _playerpos.x - pos.x;
		if (_distance >= 0.f)
			mDir = 1;
		else
			mDir = -1;		

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
			if (!(_state == Archer_State::Idle))
				return;

			if (_state == Archer_State::Idle)
			{
				_state = Archer_State::Hit;
				if (mDir == 1)
				{
					at->PlayAnimation(L"ArcherHit", true);
					_hit_switch = true;	_hit++;
					pos.x -= 50.0f * Time::DeltaTime();
					_tr->SetPosition(pos);
				}
				if (mDir == -1)
				{
					at->PlayAnimation(L"ArcherHitR", true);
					_hit_switch = true;	_hit++;
					pos.x += 50.0f * Time::DeltaTime();
					_tr->SetPosition(pos);
				}
				if (_hit >= 2)
					int a = 0;
			}
		}
		if (Skul_head* player = dynamic_cast<Skul_head*>(other->GetOwner())){}

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
				int a = 0;
				if (_Numberof_BackDash <= 2)
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
						_choicecombo = random(0, 2);
						//_choicecombo = 3;
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
				at->PlayAnimation(L"ArchereIdleR", true);
		}	
	}

	void Archer::die()
	{
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
		if (_attack_a == false)
		{			
			if (mDir == 1)
			{
				_archer_arrow->_bullet_animation= true;
				_archer_arrow->SetDirection(1);
				EffectTR->SetPosition(pos.x + 20, pos.y - 30, pos.z - 1);
			}
			if (mDir == -1)
			{
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
				if (mDir == 1)
					arrowpos.x += 450 * Time::DeltaTime();
				else
					arrowpos.x -= 450 * Time::DeltaTime();
				EffectTR->SetPosition(arrowpos);		
			}		
			else
			{
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


		//if ( /*&& _velocity.x >= -240.0 */)
		//{
		//	_state = Archer_State::Idle;
		//	at->PlayAnimation(L"ArcherIdle", true);
		//	_rigidbody->ClearVelocityX();
		//}
		//else if (mDir == -1 /*&& _velocity.x <= 240.0*/)
		//{
		//	_state = Archer_State::Idle;
		//	at->PlayAnimation(L"ArchereIdleR", true);
		//	_rigidbody->ClearVelocityX();
		//}				
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

	void Archer::CompleteArcherIntro()
	{
		_state = Archer_State::Idle;
		if (mDir == 1)
			at->PlayAnimation(L"ArcherIdle", true);
		else
			at->PlayAnimation(L"ArcherIdleR", true);
	}

	void Archer::complete_hit()
	{
		if (mDir == 1)
		{
			_state = Archer_State::Idle;
			at->PlayAnimation(L"ArcherIdle", true);
		}
		else if (mDir == -1)
		{
			_state = Archer_State::Idle;
			at->PlayAnimation(L"ArchereIdleR", true);
		}
	}
	void Archer::complete_attackA()
	{
	
	}
}