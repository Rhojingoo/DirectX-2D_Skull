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
		at->CompleteEvent(L"Knight_maleAttack_A") = std::bind(&Knight_male::choicecombo, this);
		at->CompleteEvent(L"Knight_maleAttack_B") = std::bind(&Knight_male::choicecombo, this);
		at->CompleteEvent(L"Knight_maleAttack_C") = std::bind(&Knight_male::choicecombo, this);
		at->CompleteEvent(L"Knight_maleAttack_AR") = std::bind(&Knight_male::choicecombo, this);
		at->CompleteEvent(L"Knight_maleAttack_BR") = std::bind(&Knight_male::choicecombo, this);
		at->CompleteEvent(L"Knight_maleAttack_CR") = std::bind(&Knight_male::choicecombo, this);


		at->CompleteEvent(L"Knight_maleEnergeBall") = std::bind(&Knight_male::choicecombo, this);
		at->CompleteEvent(L"Knight_maleEnergeBallR") = std::bind(&Knight_male::choicecombo, this);
		at->CompleteEvent(L"Knight_maleExplosion_Loop") = std::bind(&Knight_male::choicecombo, this);
		at->CompleteEvent(L"Knight_maleExplosion_LoopR") = std::bind(&Knight_male::choicecombo, this); 

		at->CompleteEvent(L"Knight_maleUltimateSkill_Motion") = std::bind(&Knight_male::complete_ultimate, this);
		at->CompleteEvent(L"Knight_maleUltimateSkill_MotionR") = std::bind(&Knight_male::complete_ultimate, this);

		at->CompleteEvent(L"Knight_maleGlorggy") = std::bind(&Knight_male::complete_gloggy, this);
		at->CompleteEvent(L"Knight_maleGlorggyR") = std::bind(&Knight_male::complete_gloggy, this);
		
		at->CompleteEvent(L"Knight_maleHit") = std::bind(&Knight_male::complete_hit, this);
		at->CompleteEvent(L"Knight_maleHitR") = std::bind(&Knight_male::complete_hit, this);
		
		//at->CompleteEvent(L"Skul_BasicAttackBR") = std::bind(&Skul_Basic::attack_choice, this);
		//at->CompleteEvent(L"Skul_BasicJumpAttack") = std::bind(&Skul_Basic::attack_choice, this);
		//at->CompleteEvent(L"Skul_BasicJumpAttackR") = std::bind(&Skul_Basic::attack_choice, this);
		//at->CompleteEvent(L"Skul_BasicSkill") = std::bind(&Skul_Basic::attack_choice, this);		 
		//at->CompleteEvent(L"Skul_BasicSkillR") = std::bind(&Skul_Basic::attack_choice, this);
		//at->CompleteEvent(L"Skul_BasicSwitch") = std::bind(&Skul_Basic::switch_on_off, this);
		//at->CompleteEvent(L"Skul_BasicSwitchR") = std::bind(&Skul_Basic::switch_on_off, this);
	
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
			Ultimate_Aura = new Kngiht_Ultimate_Aura;
			Ultimate_Aura->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, Ultimate_Aura);
			Transform* bullet_tr = Ultimate_Aura->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205));
			Ultimate_Aura->SetState(eState::Paused);
		}

		{
			Ultimate_AuraSmoke = new Kngiht_Ultimate_AuraSmoke;
			Ultimate_AuraSmoke->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, Ultimate_AuraSmoke);
			Transform* bullet_tr = Ultimate_AuraSmoke->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205));
			Ultimate_AuraSmoke->SetState(eState::Paused);
		}
		{
			UltimateSkill_Effect_Complete = new Kngiht_UltimateSkill_Effect_Complete;
			UltimateSkill_Effect_Complete->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, UltimateSkill_Effect_Complete);
			Transform* bullet_tr = UltimateSkill_Effect_Complete->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205));
			UltimateSkill_Effect_Complete->SetState(eState::Paused);
		}
		{
			UltimateSkill_Effect_Fail = new Knight_UltimateSkill_Effect_Fail;
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
	
		at->PlayAnimation(L"Knight_maleIdle", true);
		GameObject::Initialize();
	}
	
	
	void Knight_male::Update()
	{
		tr = GetComponent<Transform>();
		pos = tr->GetPosition();
		_velocity = _rigidbody->GetVelocity();
		_playerpos;
		_distance = _playerpos.x - pos.x;
		if (_distance >= 0.f)
			mDir = 1;
		else
			mDir = -1;

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

		case jk::Knight_male::Knight_State::Glorggy:
			glorggy();
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
		GameObject::LateUpdate();
	}
	void Knight_male::Render()
	{
		GameObject::Render();
	}
	void Knight_male::OnCollisionEnter(Collider2D* other)
	{
		if (Attack_HitBox* player = dynamic_cast<Attack_HitBox*>(other->GetOwner()))
		{
			if (!(_state == Knight_State::Idle))
				return;
			
			if (_state == Knight_State::Idle)
			{
				_state = Knight_State::Hit;
				if (mDir == 1)
				{
					at->PlayAnimation(L"Knight_maleHit", true);
					_hit_switch = true;	_number_of_attack++;
					pos.x -= 50.0f * Time::DeltaTime();
					tr->SetPosition(pos);
				}
				if (mDir == -1)
				{
					at->PlayAnimation(L"Knight_maleHitR", true);
					_hit_switch = true;	_number_of_attack++;
					pos.x += 50.0f * Time::DeltaTime();
					tr->SetPosition(pos);
				}
				if (_number_of_attack >= 2)
					int a = 0;
			}
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
	}
	void Knight_male::OnCollisionExit(Collider2D* other)
	{
	}

	void Knight_male::idle()
	{
		_time += Time::DeltaTime();

		//_choicecombo = random(0, 2);

		_choicecombo = 3;

			if (_number_of_attack >= 3)
			{
				_time = 0;							
				if (mDir == -1)
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
					_rigidbody->SetVelocity(Vector2(-250.f, 250.f));
					_rigidbody->SetGround(false);	
					_Ground_check = false;
					_BackDash = true;
					_state = Knight_State::BackDash;
				}
				_number_of_attack = 0;			
			}
			else
			{
				if (_time > 3.f)
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
		
		//else
		//{
		//	if (_time > 3.f)
		//	{
		//		if ((_distance >= 250 || _distance <= -250))
		//		{
		//			if (_choicecombo == 1)
		//			{
		//				if (_dash == false || _dash == true)
		//					energyball();
		//				_attackorder++;
		//			}
		//			else
		//			{
		//				_state = Knight_State::Dash;
		//				if (mDir == 1)
		//				{
		//					at->PlayAnimation(L"Knight_maleDash", true);
		//					_rigidbody->SetVelocity(Vector2(250.f, 0.f));
		//				}
		//				else
		//				{
		//					at->PlayAnimation(L"Knight_maleDashR", true);
		//					_rigidbody->SetVelocity(Vector2(-250.f, 0.f));
		//				}
		//				_dash = true;
		//			}
		//		}
		//		else
		//		{
		//			_attack = true;
		//			choicecombo();
		//		}
		//	}
		//}
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
				bullet_gr->SetVelocity(Vector2(attackrotation_PLAYER.x * 100.f, attackrotation_PLAYER.y * 150));
				Vector2 vel = bullet_gr->GetVelocity();
			}
			else
			{
				//Bullet->SetState(eState::Paused);
				_Attacktime = 0;
				_attackorder = 0;
				_attack = false;
				Bullet->_BoomSwitch = true;
				_state = Knight_State::Idle;
				if (mDir == 1)
					at->PlayAnimation(L"Knight_maleIdle", true);
				else
					at->PlayAnimation(L"Knight_maleIdleR", true);
			}
		}
	}

	void Knight_male::explosion_loop()
	{
		_attackorder = 0;
		_attack = false;
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
				bullet_tr->SetPosition(Vector3(pos.x, pos.y - 25, pos.z - 1.1));
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
		_state = Knight_State::Glorggy;
		if (mDir == 1)
			at->PlayAnimation(L"Knight_maleGlorggy", false);
		else
			at->PlayAnimation(L"Knight_maleGlorggyR", false);
	}

	void Knight_male::Finishing_Move()
	{		
		_state = Knight_State::Idle;
		if (mDir == 1)
			at->PlayAnimation(L"Knight_maleIdle", true);
		else
			at->PlayAnimation(L"Knight_maleIdleR", true);
	}

	void Knight_male::glorggy()
	{
		_Attacktime += Time::DeltaTime();
		if (_Attacktime >= 3.5)
		{
			_state = Knight_State::Idle;
			if (mDir == 1)
				at->PlayAnimation(L"Knight_maleIdle", true);
			else
				at->PlayAnimation(L"Knight_maleIdleR", true);
			_Attacktime = 0;
		}
	}

	void Knight_male::hit()
	{

	}

	void Knight_male::intro()
	{
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

	void Knight_male::choicecombo()
	{
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
			//if (_number_of_attack >= 3)
			//{
			//	_time = 0;
			//	_number_of_attack = 0;
			//}

			_state = Knight_State::Idle;
			if (mDir == 1)
				at->PlayAnimation(L"Knight_maleIdle", true);
			else
				at->PlayAnimation(L"Knight_maleIdleR", true);
		}	
	}

	void Knight_male::combo()
	{
		if (_attackorder == 1)
		{
			_state = Knight_State::Attack_A;
			if (mDir == 1)
			{
				at->PlayAnimation(L"Knight_maleAttack_A", true);
				_rigidbody->SetVelocity(Vector2(150.f,0.f));
			}
			else
			{
				at->PlayAnimation(L"Knight_maleAttack_AR", true);
				_rigidbody->SetVelocity(Vector2(-150.f, 0.f));
			}
		}
		if (_attackorder == 2)
		{ 
			_state = Knight_State::Attack_B;
			if (mDir == 1)
			{
				at->PlayAnimation(L"Knight_maleAttack_B", true);
				_rigidbody->SetVelocity(Vector2(150.f, 0.f));
			}
			else
			{
				at->PlayAnimation(L"Knight_maleAttack_BR", true);
				_rigidbody->SetVelocity(Vector2(-150.f, 0.f));
			}
		}
		if (_attackorder == 3)
		{
			_state = Knight_State::Attack_C;
			if (mDir == 1)
			at->PlayAnimation(L"Knight_maleAttack_C", true);	
			else
			at->PlayAnimation(L"Knight_maleAttack_CR", true);
		}
	}

	void Knight_male::energyball()
	{
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
			_state = Knight_State::Explosion_Loop;
			at->PlayAnimation(L"Knight_maleExplosion_Loop", true);
		}
		Transform* bullet_tr = Energe_Blast->GetComponent<Transform>();
		bullet_tr->SetPosition(Vector3(pos.x, pos.y-10, pos.z - 1));
		Energe_Blast->SetState(eState::Active);
	}

	void Knight_male::finishingmove_set()
	{
		if (_attackorder == 1)
		{
			_state = Knight_State::Finishing_Move_Ready;
			at->PlayAnimation(L"Knight_maleFinish_Move", true);
			_Ultimate = true;

			_number_of_hit = 9;
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

}