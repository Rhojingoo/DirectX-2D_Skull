#include "Skul_Wolf.h"
#include "Particle_DamageEffect.h"


namespace jk
{
	int Skul_Wolf::mDir = 1;
	bool Skul_Wolf::_switch = false;

	Skul_Wolf::Skul_Wolf()
		: _State(Skul_Wolf_State::Idle)
		, at(nullptr)
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Basic_Skul"));
	}
	Skul_Wolf::~Skul_Wolf()
	{
	}
	void Skul_Wolf::Initialize()
	{	
		CameraScript* cam = AddComponent<CameraScript>();
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Wolf\\AttackA", this,0,0.065);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Wolf\\AttackB", this,0,0.065);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Wolf\\Dash", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Wolf\\Dash_End", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Wolf\\Fall", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Wolf\\FallRepeat", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Wolf\\Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Wolf\\Jump", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Wolf\\JumpAttack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Wolf\\SkillA", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Wolf\\SkillB", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Wolf\\Switch", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Wolf\\Walk", this);


		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Wolf\\AttackA", this, 1,0.07);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Wolf\\AttackB", this, 1,0.07);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Wolf\\Dash", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Wolf\\Dash_End", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Wolf\\Fall", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Wolf\\FallRepeat", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Wolf\\Idle", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Wolf\\Jump", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Wolf\\JumpAttack", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Wolf\\SkillA", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Wolf\\SkillB", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Wolf\\Switch", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Wolf\\Walk", this, 1);
	
		at->PlayAnimation(L"WolfIdle", true);
		at->CompleteEvent(L"WolfAttackA") = std::bind(&Skul_Wolf::attack_choice, this);
		at->CompleteEvent(L"WolfAttackAR") = std::bind(&Skul_Wolf::attack_choice, this);
		at->CompleteEvent(L"WolfAttackB") = std::bind(&Skul_Wolf::attack_choice, this);
		at->CompleteEvent(L"WolfAttackBR") = std::bind(&Skul_Wolf::attack_choice, this);
		at->CompleteEvent(L"WolfSwitch") = std::bind(&Skul_Wolf::attack_choice, this);
		at->CompleteEvent(L"WolfSwitchR") = std::bind(&Skul_Wolf::attack_choice, this);
		at->CompleteEvent(L"WolfSkillA") = std::bind(&Skul_Wolf::attack_choice, this);
		at->CompleteEvent(L"WolfSkillAR") = std::bind(&Skul_Wolf::attack_choice, this);
		at->CompleteEvent(L"WolfSkillB") = std::bind(&Skul_Wolf::attack_choice, this);
		at->CompleteEvent(L"WolfSkillBR") = std::bind(&Skul_Wolf::attack_choice, this);
		at->CompleteEvent(L"WolfJumpAttack") = std::bind(&Skul_Wolf::attack_choice, this);
		at->CompleteEvent(L"WolfJumpAttackR") = std::bind(&Skul_Wolf::attack_choice, this);
		at->CompleteEvent(L"WolfDash") = std::bind(&Skul_Wolf::dash_check, this);
		at->CompleteEvent(L"WolfDashR") = std::bind(&Skul_Wolf::dash_check, this);


		{
			for (int i = 0; i < 10; i++)
			{
				AfterImage_TEST[i] = new Player_AfterImage();
				AfterImage_TEST[i]->Initialize();
				Scene* scene = SceneManager::GetActiveScene();
				scene->AddGameObject(eLayerType::Effect, AfterImage_TEST[i]);
				AfterImage_TEST[i]->Set_Owner(this);
				AfterImage_TEST[i]->SetState(eState::Paused);
			}
		}
		{
			Hit_Box = new HitBox_Player();
			Hit_Box->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Hitbox, Hit_Box);
			Hit_Box->SetState(eState::Paused);
		}




		{
			_Hit_Effect = new Player_Hit_Effect;
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
			_Knight_Slash = new Slash_Effect;
			_Knight_Slash->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, _Knight_Slash);
			_Knight_Slash->SetState(eState::Paused);
		}
		{
			_DarkKnight = new Hit_DarkPaladin;
			_DarkKnight->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, _DarkKnight);
			_DarkKnight->SetState(eState::Paused);
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
	void Skul_Wolf::Update()
	{
		tr = GetComponent<Transform>();
		pos = tr->GetPosition();
		_velocity = _rigidbody->GetVelocity();

		 if (_switch == true)
		 {
			 _State = Skul_Wolf::Skul_Wolf_State::Switch;
			 if (mDir == 1)
			 {
				 _rigidbody->SetVelocity(Vector2(350.f, 250.f));
				 _rigidbody->SetGround(false);
				 at->PlayAnimation(L"WolfSwitch", false);
				 _switch = false;
				 _Ground_check = false;
			 }
			 else
			 {
				 at->PlayAnimation(L"WolfSwitchR", false);
				 _rigidbody->SetVelocity(Vector2(-350.f, 250.f));
				 _rigidbody->SetGround(false);
				_switch = false;
				_Ground_check = false;
			 }
		 }

		switch (_State)
		{
		case jk::Skul_Wolf::Skul_Wolf_State::Idle:idle();
			break;

		case jk::Skul_Wolf::Skul_Wolf_State::Move:move();
			break;

		case jk::Skul_Wolf::Skul_Wolf_State::Jump:jump();
			break;

		case jk::Skul_Wolf::Skul_Wolf_State::Fall:fall();
			break;

		case jk::Skul_Wolf::Skul_Wolf_State::Falling:falling();
			break;

		case jk::Skul_Wolf::Skul_Wolf_State::Dash:dash();
			break;

		case jk::Skul_Wolf::Skul_Wolf_State::Attack_A:attack_a();
			break;

		case jk::Skul_Wolf::Skul_Wolf_State::Attack_B:attack_b();
			break;

		case jk::Skul_Wolf::Skul_Wolf_State::JumpAttack:jumpattack();
			break;

		case jk::Skul_Wolf::Skul_Wolf_State::Skill_A:skill_a();
			break;

		case jk::Skul_Wolf::Skul_Wolf_State::Skill_B:skill_b();
			break;

		case jk::Skul_Wolf::Skul_Wolf_State::Switch:change();
			break;

		case jk::Skul_Wolf::Skul_Wolf_State::Death:death();
			break;

		default:
			break;
		}			
		
		Input_move();
		_Pos = pos;
		tr->SetPosition(pos);
		GameObject::Update();
	}
	void Skul_Wolf::LateUpdate()
	{
		Transform* HitBox_TR = Hit_Box->GetComponent<Transform>();
		if (_attack_Acheck == true)
		{
			Hit_Box->SetSize(Vector2(75.f, 75.f));
			Hit_Box->SetState(eState::Active);
			if (mDir == 1)
				HitBox_TR->SetPosition(Vector3(pos.x + 20, pos.y, pos.z));
			else
				HitBox_TR->SetPosition(Vector3(pos.x - 20, pos.y, pos.z));
		}
		else if (_attack_Bcheck == true)
		{
			Hit_Box->SetSize(Vector2(75.f, 75.f));
			Hit_Box->SetState(eState::Active);
			if (mDir == 1)
				HitBox_TR->SetPosition(Vector3(pos.x + 20, pos.y, pos.z));
			else
				HitBox_TR->SetPosition(Vector3(pos.x - 20, pos.y, pos.z));
		}
		else if (_attack_Ccheck == true)
		{
			Hit_Box->SetSize(Vector2(110.f, 75.f));
			Hit_Box->SetState(eState::Active);
			if (mDir == 1)
				HitBox_TR->SetPosition(Vector3(pos.x , pos.y, pos.z));
			else
				HitBox_TR->SetPosition(Vector3(pos.x , pos.y, pos.z));
		}
		else
		{
			Hit_Box->SetState(eState::Paused);
		}


		_collider->SetSize(Vector2(0.35f, 0.55f));
		_collider->SetCenter(Vector2(0.0f, -0.1f));
		GameObject::LateUpdate();
	}

	void Skul_Wolf::Render()
	{
		GameObject::Render();
	}

	void Skul_Wolf::idle()
	{
		if (Input::GetKey(eKeyCode::RIGHT)
			|| Input::GetKey(eKeyCode::LEFT))
		{
			_State = Skul_Wolf_State::Move;
			if (Input::GetKey(eKeyCode::RIGHT))
			{
				at->PlayAnimation(L"WolfWalk", true);
				mDir = 1;
			}
			else if (Input::GetKey(eKeyCode::LEFT))
			{
				at->PlayAnimation(L"WolfWalkR", true);
				mDir = -1;
			}
		}

		if (Input::GetKey(eKeyCode::A))
		{	
			_State = Skul_Wolf_State::Skill_A;	
			if (mDir == 1)
			{
				at->PlayAnimation(L"WolfSkillA", true); mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"WolfSkillAR", true); mDir = -1;				
			}					
		}
		if (Input::GetKey(eKeyCode::S))
		{
			_State = Skul_Wolf_State::Skill_B;
			if (mDir == 1)
			{
				at->PlayAnimation(L"WolfSkillB", true); mDir = 1;
				_rigidbody->SetVelocity(Vector2(100.f, 0.f));
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"WolfSkillBR", true); mDir = -1;
				_rigidbody->SetVelocity(Vector2(-100.f, 0.f));
			}
		}
	
		if (Input::GetKey(eKeyCode::X))
		{
			_State = Skul_Wolf_State::Attack_A;
			if (mDir == 1)
			{
				at->PlayAnimation(L"WolfAttackA", true);
				mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"WolfAttackAR", true);
				mDir = -1;
			}
		}

		if (Input::GetKeyDown(eKeyCode::C))
		{
			_State = Skul_Wolf_State::Jump;
			if (mDir == 1)
			{
				at->PlayAnimation(L"WolfJump", true);

				_rigidbody->SetVelocity(Vector2(0.f, 400.f));
				_rigidbody->SetGround(false);	mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"WolfJumpR", true);	

				_rigidbody->SetVelocity(Vector2(0.f, 400.f));
				_rigidbody->SetGround(false);	mDir = -1;
			}
			_jump++;
		}

		if (Input::GetKeyDown(eKeyCode::Z))
		{
			_State = Skul_Wolf_State::Dash;
			if (mDir == 1)
			{
				at->PlayAnimation(L"WolfDash", false);
				_rigidbody->SetVelocity(Vector2(350.f, 250.f));
				_rigidbody->SetGround(false);	mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"WolfDashR", false);
				_rigidbody->SetVelocity(Vector2(-350.f, 250.f));
				_rigidbody->SetGround(false);	mDir = -1;
			}
		}
	}

	void Skul_Wolf::move()
	{
		if (Input::GetKeyUp(eKeyCode::RIGHT)
			|| Input::GetKeyUp(eKeyCode::LEFT))
		{
			_State = Skul_Wolf_State::Idle;
			if (Input::GetKeyUp(eKeyCode::RIGHT))
			{
				at->PlayAnimation(L"WolfIdle", true);
				mDir = 1;
			}
			else if (Input::GetKeyUp(eKeyCode::LEFT))
			{
				at->PlayAnimation(L"WolfIdleR", true);
				mDir = -1;
			}
		}

		if (Input::GetKey(eKeyCode::X))
		{
			_State = Skul_Wolf_State::Attack_A;
			if (mDir == 1)
			{
				at->PlayAnimation(L"WolfAttackA", true);
				mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"WolfAttackAR", true);
				mDir = -1;
			}
		}

		if (Input::GetKeyDown(eKeyCode::C))
		{
			_State = Skul_Wolf_State::Jump;
			if (mDir == 1)
			{
				at->PlayAnimation(L"WolfJump", true);

				_rigidbody->SetVelocity(Vector2(0.f, 400.f));
				_rigidbody->SetGround(false);	mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"WolfJumpR", true);

				_rigidbody->SetVelocity(Vector2(0.f, 400.f));
				_rigidbody->SetGround(false);	mDir = -1;
			}
			_jump++;
		}

		if (Input::GetKeyDown(eKeyCode::Z))
		{
			_State = Skul_Wolf_State::Dash;
			if (mDir == 1)
			{
				at->PlayAnimation(L"WolfDash", false);
				_rigidbody->SetVelocity(Vector2(350.f, 250.f));
				_rigidbody->SetGround(false);	mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"WolfDashR", false);
				_rigidbody->SetVelocity(Vector2(-350.f, 250.f));
				_rigidbody->SetGround(false);	mDir = -1;;
			}
		}
	}

	void Skul_Wolf::jump()
	{
		_Ground_check = false;
		if ((_velocity.y <= 0.f) || (_jump >= 2))
		{
			_State = Skul_Wolf_State::Fall;
			if (mDir == 1)
			{
				at->PlayAnimation(L"WolfFall", false);
				mDir = 1;
			}
			if (mDir == -1)
			{
				at->PlayAnimation(L"WolfFallR", false);
				mDir = -1;
			}
			_jump = 0;
		}

		if (_jump < 3)
		{
			if (Input::GetKeyDown(eKeyCode::C))
			{
				_State = Skul_Wolf_State::Jump;
				if (mDir == 1)
				{
					at->PlayAnimation(L"WolfJump", true);

					_rigidbody->SetVelocity(Vector2(0.f, 400.f));
					_rigidbody->SetGround(false);	mDir = 1;
				}
				else if (mDir == -1)
				{
					at->PlayAnimation(L"WolfJumpR", true);

					_rigidbody->SetVelocity(Vector2(0.f, 400.f));
					_rigidbody->SetGround(false);	mDir = -1;
				}
				_jump++;
			}
		}

		if (Input::GetKeyDown(eKeyCode::X))
		{
			if (mDir == 1)
			{
				_State = Skul_Wolf_State::JumpAttack;
				at->PlayAnimation(L"WolfJumpAttack", true);
			}
			if (mDir == -1)
			{
				_State = Skul_Wolf_State::JumpAttack;
				at->PlayAnimation(L"WolfJumpAttackR", true);
			}			
		}

		if (Input::GetKeyDown(eKeyCode::Z))
		{
			_State = Skul_Wolf_State::Dash;
			if (mDir == 1)
			{
				at->PlayAnimation(L"WolfDash", false);
				_rigidbody->SetVelocity(Vector2(250.f, 150.f));
				_rigidbody->SetGround(false);	mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"WolfDashR", false);
				_rigidbody->SetVelocity(Vector2(-250.f, 150.f));
				_rigidbody->SetGround(false);	mDir = -1;
			}
		}
	}

	void Skul_Wolf::fall()
	{
		_time += Time::DeltaTime();
		if (_time > 3.f)
		{
			_State = Skul_Wolf_State::Falling;
			if (mDir == 1)
			{
				at->PlayAnimation(L"WolfFallRepeat", true);

				mDir = 1;  _fallcheck = 2;
			}
			if (mDir == -1)
			{
				at->PlayAnimation(L"WolfFallRepeatR", true);

				mDir = -1; _fallcheck = 2;
			}
			_time = 0;
		}

		if (_jump < 3)
		{
			if (Input::GetKeyDown(eKeyCode::C))
			{
				if (Input::GetKeyDown(eKeyCode::C))
				{
					_State = Skul_Wolf_State::Jump;
					if (mDir == 1)
					{
						at->PlayAnimation(L"WolfJump", true);

						_rigidbody->SetVelocity(Vector2(0.f, 400.f));
						_rigidbody->SetGround(false);	mDir = 1;
					}
					else if (mDir == -1)
					{
						at->PlayAnimation(L"WolfJumpR", true);

						_rigidbody->SetVelocity(Vector2(0.f, 400.f));
						_rigidbody->SetGround(false);	mDir = -1;
					}
					_jump++;
				}
			}
		}

		if (Input::GetKeyDown(eKeyCode::X))
		{
			_State = Skul_Wolf_State::JumpAttack;
			if (mDir == 1)							
				at->PlayAnimation(L"WolfJumpAttack", true);			

			if (mDir == -1)				
				at->PlayAnimation(L"WolfJumpAttackR", true);			
		}

		if (Input::GetKeyDown(eKeyCode::Z))
		{
			_State = Skul_Wolf_State::Dash;
			if (mDir == 1)
			{
				at->PlayAnimation(L"WolfDash", false);
				_rigidbody->SetVelocity(Vector2(350.f, 250.f));
				_rigidbody->SetGround(false);	mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"WolfDashR", false);
				_rigidbody->SetVelocity(Vector2(-350.f, 250.f));
				_rigidbody->SetGround(false);	mDir = -1;				
			}
		}
	}

	void Skul_Wolf::falling()
	{

		if (_jump < 3)
		{
			if (Input::GetKeyDown(eKeyCode::C))
			{
				_State = Skul_Wolf_State::Jump;
				if (mDir == 1)
				{
					at->PlayAnimation(L"WolfJump", true);

					_rigidbody->SetVelocity(Vector2(0.f, 400.f));
					_rigidbody->SetGround(false);	mDir = 1;
				}
				else if (mDir == -1)
				{
					at->PlayAnimation(L"WolfJumpR", true);

					_rigidbody->SetVelocity(Vector2(0.f, 400.f));
					_rigidbody->SetGround(false);	mDir = -1;
				}
				_jump++;
			}
		}

		if (Input::GetKeyDown(eKeyCode::X))
		{
			if (mDir == 1)
			{
				_State = Skul_Wolf_State::JumpAttack;
				at->PlayAnimation(L"WolfJumpAttack", true);
			}
			if (mDir == -1)
			{
				_State = Skul_Wolf_State::JumpAttack;
				at->PlayAnimation(L"WolfJumpAttackR", true);
			}
		}

		if (Input::GetKeyDown(eKeyCode::Z))
		{
			_State = Skul_Wolf_State::Dash;
			if (mDir == 1)
			{
				at->PlayAnimation(L"WolfDash", false);
				_rigidbody->SetVelocity(Vector2(250.f, 150.f));
				_rigidbody->SetGround(false);	mDir = 1;
				mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"WolfDashR", false);
				_rigidbody->SetVelocity(Vector2(-250.f, 150.f));
				_rigidbody->SetGround(false);	mDir = -1;
				mDir = -1;
			}
		}
	}

	void Skul_Wolf::dash()
	{
		_dash = true;
		_Ground_check = false;
		if (Input::GetKeyDown(eKeyCode::Z))
		{			
			if (mDir == 1)
			{			
				_rigidbody->SetVelocity(Vector2(350.f, 250.f));
				_rigidbody->SetGround(false);	mDir = 1;				
			}
			else if (mDir == -1)
			{				
				_rigidbody->SetVelocity(Vector2(-350.f, 250.f));
				_rigidbody->SetGround(false);	mDir = -1;				
			}
		}
		{
			timeSinceLastImage += Time::DeltaTime();
			if (timeSinceLastImage >= delayBetweenImages)
			{
				for (int i = 0; i < 10; i++)
				{
					if (AfterImage_TEST[i]->_AfterImage == false)
					{
						int direction = (mDir == 1) ? 1 : -1;
						AfterImage_TEST[i]->Set_Wolf_Dash(direction, Vector3(pos.x, pos.y, pos.z + 1));
						AfterImage_TEST[i]->SetState(eState::Active);
						AfterImage_TEST[i]->_AfterImage = true;
						timeSinceLastImage = 0.0f;  // 시간 초기화
						break;  // 하나의 잔상만 생성한 후 for문 종료					
					}
				}
			}
		}
	}

	void Skul_Wolf::attack_a()
	{
		_attack_Acheck = true;

		if (Input::GetKeyDown(eKeyCode::X))
		{
			_attack = true;
		}
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mDir = 1;
		}
		else if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mDir = -1;
		}
	}

	void Skul_Wolf::attack_b()
	{
		_attack_Bcheck = true;
		_attack = false;
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mDir = 1;
		}
		else if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mDir = -1;
		}
	}

	void Skul_Wolf::jumpattack()
	{
		_attack_Ccheck = true;
	}

	void Skul_Wolf::skill_a()
	{
	}

	void Skul_Wolf::skill_b()
	{
	}

	void Skul_Wolf::change()
	{
		if (_switch == true)
		{
			//if (mDir == 1)
			//{
			//	_rigidbody->SetVelocity(Vector2(350.f, 250.f));
			//	_rigidbody->SetGround(false);
			//	_switch = false;
			//	_Ground_check = false;

			//}
			//else
			//{
			//	_rigidbody->SetVelocity(Vector2(-350.f, 250.f));
			//	_rigidbody->SetGround(false);
			//	_switch = false;
			//	_Ground_check = false;
			//}
		}
	}

	void Skul_Wolf::death()
	{
	}

	void Skul_Wolf::stun()
	{
		_attack_time += Time::DeltaTime();
		if (_attack_time > 1.0)
		{
			_State = Skul_Wolf_State::Idle;
			_attack_time = 0;
			_Leftmove_Lock = false;
			_Rightmove_Lock = false;
		}
	}

	void Skul_Wolf::hit()
	{
	}

	void Skul_Wolf::OnCollisionEnter(Collider2D* other)
	{
		//Monster
		if (HitBox_Monster* _Monster = dynamic_cast<HitBox_Monster*>(other->GetOwner()))
		{
			Transform* hittr = _Monster->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
			{
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));
				_Hit_Effect->_effect_animation = true;
				_Hit_Effect->SetDirection(1);
				_Hit_Effect->SetState(eState::Active);
			}
			else
			{
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));
				_Hit_Effect->_effect_animation = true;
				_Hit_Effect->SetDirection(-1);
				_Hit_Effect->SetState(eState::Active);
			}
		}

		if (Monster_Hammer* Hammer = dynamic_cast<Monster_Hammer*>(other->GetOwner()))
		{
			hammer_st = Hammer->GetState();
			if (hammer_st == Monster_Hammer::Monster_Hammer_State::Tackle)
			{
				Transform* hittr = Hammer->GetComponent<Transform>();
				Vector3 hitpos = hittr->GetPosition();
				if (hitpos.x > pos.x)
				{
					_rigidbody->SetVelocity(Vector2(-50.f, 0.f));
					_Hit_Effect->_effect_animation = true;
					_Hit_Effect->SetDirection(1);
					_Hit_Effect->SetState(eState::Active);
				}
				else
				{
					_rigidbody->SetVelocity(Vector2(50.f, 0.f));
					_Hit_Effect->_effect_animation = true;
					_Hit_Effect->SetDirection(-1);
					_Hit_Effect->SetState(eState::Active);
				}
			}
		}

		if (Monster_GoldHammer* GoldHammer = dynamic_cast<Monster_GoldHammer*>(other->GetOwner()))
		{
			Goldham_st = GoldHammer->GetState();
			if (Goldham_st == Monster_GoldHammer::Monster_GoldHammer_State::Tackle)
			{
				Transform* hittr = GoldHammer->GetComponent<Transform>();
				Vector3 hitpos = hittr->GetPosition();
				if (hitpos.x > pos.x)
				{
					_rigidbody->SetVelocity(Vector2(-50.f, 0.f));
					_Hit_Effect->_effect_animation = true;
					_Hit_Effect->SetDirection(1);
					_Hit_Effect->SetState(eState::Active);
				}
				else
				{
					_rigidbody->SetVelocity(Vector2(50.f, 0.f));
					_Hit_Effect->_effect_animation = true;
					_Hit_Effect->SetDirection(-1);
					_Hit_Effect->SetState(eState::Active);
				}
			}
		}

		if (Monster_Bullet* Bullet = dynamic_cast<Monster_Bullet*>(other->GetOwner()))
		{
			if (_State == Skul_Wolf_State::Dash)
				return;

			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
			{
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));
				_Hit_Effect->_effect_animation = true;
				_Hit_Effect->SetDirection(1);
				_Hit_Effect->SetState(eState::Active);
			}
			else
			{
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));
				_Hit_Effect->_effect_animation = true;
				_Hit_Effect->SetDirection(-1);
				_Hit_Effect->SetState(eState::Active);
			}
		}

		if (Monster_Ent_GroundAttack* Bullet = dynamic_cast<Monster_Ent_GroundAttack*>(other->GetOwner()))
		{
			if (_State == Skul_Wolf_State::Dash)
				return;

			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
			{
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));
				_Hit_Effect->_effect_animation = true;
				_Hit_Effect->SetDirection(1);
				_Hit_Effect->SetState(eState::Active);
			}
			else
			{
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));
				_Hit_Effect->_effect_animation = true;
				_Hit_Effect->SetDirection(-1);
				_Hit_Effect->SetState(eState::Active);
			}
		}

		//MiniBoss
		if (MiniBoss_Bullet_Archer* Bullet = dynamic_cast<MiniBoss_Bullet_Archer*>(other->GetOwner()))
		{
			if (_State == Skul_Wolf_State::Dash)
				return;

			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
			{
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));
				_Hit_Sword->_effect_animation = true;
				_Hit_Sword->SetDirection(-1);
				_Hit_Sword->SetState(eState::Active);
			}
			else
			{
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));
				_Hit_Sword->_effect_animation = true;
				_Hit_Sword->SetDirection(1);
				_Hit_Sword->SetState(eState::Active);
			}
		}

		if (Archer_Trap* Bullet = dynamic_cast<Archer_Trap*>(other->GetOwner()))
		{
			if (_State == Skul_Wolf_State::Dash)
				return;
			else
			{
				_State = Skul_Wolf_State::Stun;
				_Leftmove_Lock = true;
				_Rightmove_Lock = true;
				if (mDir == 1)
					at->PlayAnimation(L"Skul_BasicIdle", true);
				else
					at->PlayAnimation(L"Skul_BasicIdleR", true);
			}
		}

		if (HitBox_Knight* HitBox = dynamic_cast<HitBox_Knight*>(other->GetOwner()))
		{
			if (_State == Skul_Wolf_State::Dash)
				return;

			Transform* hittr = HitBox->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
			{
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));
				_Hit_Effect->_effect_animation = true;
				_Knight_Slash->SetDirection(1);
				_Knight_Slash->SetState(eState::Active);
			}
			else
			{
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));
				_Knight_Slash->_effect_animation = true;
				_Knight_Slash->SetDirection(-1);
				_Knight_Slash->SetState(eState::Active);
			}
		}

		if (MiniBoss_Bullet_Knight* Bullet = dynamic_cast<MiniBoss_Bullet_Knight*>(other->GetOwner()))
		{
			if (_State == Skul_Wolf_State::Dash)
				return;

			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
			{
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));
				_Hit_Sword->_effect_animation = true;
				_Hit_Sword->SetDirection(-1);
				_Hit_Sword->SetState(eState::Active);
			}
			else
			{
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));
				_Hit_Sword->_effect_animation = true;
				_Hit_Sword->SetDirection(1);
				_Hit_Sword->SetState(eState::Active);
			}
		}

		if (Knight_Energe_Blast* Bullet = dynamic_cast<Knight_Energe_Blast*>(other->GetOwner()))
		{
			if (_State == Skul_Wolf_State::Dash)
				return;

			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
				HitDir = -1;
			else
				HitDir = 1;
			_State = Skul_Wolf_State::Hit;
		}

		if (Knight_UltimateSkill_Projectile* Bullet = dynamic_cast<Knight_UltimateSkill_Projectile*>(other->GetOwner()))
		{
			if (_State == Skul_Wolf_State::Dash)
				return;

			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
			{
				HitDir = -1;
				_rigidbody->SetVelocity(Vector2(-50.f, 50.f));

				_DarkKnight->_effect_animation = true;
				_DarkKnight->SetDirection(-1);
				_DarkKnight->SetState(eState::Active);
			}
			else
			{
				HitDir = 1;
				_rigidbody->SetVelocity(Vector2(50.f, 50.f));

				_DarkKnight->_effect_animation = true;
				_DarkKnight->SetDirection(1);
				_DarkKnight->SetState(eState::Active);
			}
			_State = Skul_Wolf_State::Hit;
		}

		if (Cleric_HolyThunder* Bullet = dynamic_cast<Cleric_HolyThunder*>(other->GetOwner()))
		{
			if (_State == Skul_Wolf_State::Dash)
				return;

			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
				HitDir = -1;
			else
				HitDir = 1;
			_State = Skul_Wolf_State::Hit;
		}

		if (HitBox_Mage* Bullet = dynamic_cast<HitBox_Mage*>(other->GetOwner()))
		{
			if (_State == Skul_Wolf_State::Dash)
				return;

			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
				HitDir = -1;
			else
				HitDir = 1;
			_State = Skul_Wolf_State::Hit;
		}

		if (Mage_FireBoom* Bullet = dynamic_cast<Mage_FireBoom*>(other->GetOwner()))
		{

			if (_State == Skul_Wolf_State::Dash)
				return;

			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
				HitDir = -1;
			else
				HitDir = 1;
			_State = Skul_Wolf_State::Hit;
		}

		if (Mage_FireBall* Bullet = dynamic_cast<Mage_FireBall*>(other->GetOwner()))
		{
			if (_State == Skul_Wolf_State::Dash)
				return;

			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));
			else
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));
		}

		if (Ultimate_On_Fire_Projectile* Bullet = dynamic_cast<Ultimate_On_Fire_Projectile*>(other->GetOwner()))
		{
			if (_State == Skul_Wolf_State::Dash)
				return;

			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));
			else
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));
		}


		//Boss_YggDrasil
		if (HitBox_YggDrasil* Hit_Boss = dynamic_cast<HitBox_YggDrasil*>(other->GetOwner()))
		{
			if (_State == Skul_Wolf_State::Dash)
				return;

			Transform* hittr = Hit_Boss->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
				HitDir = -1;
			else
				HitDir = 1;

			_State = Skul_Wolf_State::Hit;
		}


		//Boss_Layana
		if (HitBox_Layana* Hit_Boss = dynamic_cast<HitBox_Layana*>(other->GetOwner()))
		{
			if (_State == Skul_Wolf_State::Dash)
				return;

			Transform* hittr = Hit_Boss->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
			{
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));
				_Hit_Effect->_effect_animation = true;
				_Hit_Effect->SetDirection(1);
				_Hit_Effect->SetState(eState::Active);
			}
			else
			{
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));
				_Hit_Effect->_effect_animation = true;
				_Hit_Effect->SetDirection(1);
				_Hit_Effect->SetState(eState::Active);
			}
		}

		if (Homing_Pierce_LongHair* Bullet = dynamic_cast<Homing_Pierce_LongHair*>(other->GetOwner()))
		{
			if (_State == Skul_Wolf_State::Dash)
				return;

			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));
			else
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));
		}

		if (Homing_Pierce_ShortHair* Bullet = dynamic_cast<Homing_Pierce_ShortHair*>(other->GetOwner()))
		{
			if (_State == Skul_Wolf_State::Dash)
				return;

			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));
			else
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));
		}

		if (TwinMeteor_Effect* Bullet = dynamic_cast<TwinMeteor_Effect*>(other->GetOwner()))
		{
			if (_State == Skul_Wolf_State::Dash)
				return;

			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
			{
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));

				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetDirection(1);
				Transform* bulltr = _Critical_Middle->GetComponent<Transform>();
				bulltr->SetPosition(Vector3(pos.x + 20, pos.y, pos.z - 1));
				_Critical_Middle->SetState(eState::Active);
			}
			else
			{
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));

				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetDirection(-1);
				Transform* bulltr = _Critical_Middle->GetComponent<Transform>();
				bulltr->SetPosition(Vector3(pos.x - 20, pos.y, pos.z - 1));
				_Critical_Middle->SetState(eState::Active);
			}
		}

		if (Dimension_Pierce_BulletEffect* Bullet = dynamic_cast<Dimension_Pierce_BulletEffect*>(other->GetOwner()))
		{
			if (_State == Skul_Wolf_State::Dash)
				return;

			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
			{
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));

				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetDirection(1);
				Transform* bulltr = _Critical_Middle->GetComponent<Transform>();
				bulltr->SetPosition(Vector3(pos.x + 20, pos.y, pos.z - 1));
				_Critical_Middle->SetState(eState::Active);
			}
			else
			{
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));

				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetDirection(-1);
				Transform* bulltr = _Critical_Middle->GetComponent<Transform>();
				bulltr->SetPosition(Vector3(pos.x - 20, pos.y, pos.z - 1));
				_Critical_Middle->SetState(eState::Active);
			}
		}

		if (Rising_Pierce* Bullet = dynamic_cast<Rising_Pierce*>(other->GetOwner()))
		{
			if (_State == Skul_Wolf_State::Dash)
				return;

			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
			{
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));

				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetDirection(1);
				Transform* bulltr = _Critical_Middle->GetComponent<Transform>();
				bulltr->SetPosition(Vector3(pos.x + 20, pos.y, pos.z - 1));
				_Critical_Middle->SetState(eState::Active);
			}
			else
			{
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));

				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetDirection(-1);
				Transform* bulltr = _Critical_Middle->GetComponent<Transform>();
				bulltr->SetPosition(Vector3(pos.x - 20, pos.y, pos.z - 1));
				_Critical_Middle->SetState(eState::Active);
			}
		}

		if (Golden_Meteor_Bullet* Bullet = dynamic_cast<Golden_Meteor_Bullet*>(other->GetOwner()))
		{
			if (_State == Skul_Wolf_State::Dash)
				return;

			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
			{
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));

				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetDirection(1);
				Transform* bulltr = _Critical_Middle->GetComponent<Transform>();
				bulltr->SetPosition(Vector3(pos.x + 20, pos.y, pos.z - 1));
				_Critical_Middle->SetState(eState::Active);
			}
			else
			{
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));

				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetDirection(-1);
				Transform* bulltr = _Critical_Middle->GetComponent<Transform>();
				bulltr->SetPosition(Vector3(pos.x - 20, pos.y, pos.z - 1));
				_Critical_Middle->SetState(eState::Active);
			}
		}

		if (Latana_Awake_Rush_Bullet* Bullet = dynamic_cast<Latana_Awake_Rush_Bullet*>(other->GetOwner()))
		{
			if (_State == Skul_Wolf_State::Dash)
				return;

			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
			{
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));

				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetDirection(1);
				Transform* bulltr = _Critical_Middle->GetComponent<Transform>();
				bulltr->SetPosition(Vector3(pos.x + 20, pos.y, pos.z - 1));
				_Critical_Middle->SetState(eState::Active);
			}
			else
			{
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));

				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetDirection(-1);
				Transform* bulltr = _Critical_Middle->GetComponent<Transform>();
				bulltr->SetPosition(Vector3(pos.x - 20, pos.y, pos.z - 1));
				_Critical_Middle->SetState(eState::Active);
			}
		}

		if (Layana_Ground_Thunder* Bullet = dynamic_cast<Layana_Ground_Thunder*>(other->GetOwner()))
		{
			if (_State == Skul_Wolf_State::Dash)
				return;

			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
			{
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));

				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetDirection(1);
				Transform* bulltr = _Critical_Middle->GetComponent<Transform>();
				bulltr->SetPosition(Vector3(pos.x + 20, pos.y, pos.z - 1));
				_Critical_Middle->SetState(eState::Active);
			}
			else
			{
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));

				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetDirection(-1);
				Transform* bulltr = _Critical_Middle->GetComponent<Transform>();
				bulltr->SetPosition(Vector3(pos.x - 20, pos.y, pos.z - 1));
				_Critical_Middle->SetState(eState::Active);
			}
		}

		if (Layana_Awaken_Meteor_Projectile* Bullet = dynamic_cast<Layana_Awaken_Meteor_Projectile*>(other->GetOwner()))
		{
			if (_State == Skul_Wolf_State::Dash)
				return;

			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
			{
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));

				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetDirection(1);
				Transform* bulltr = _Critical_Middle->GetComponent<Transform>();
				bulltr->SetPosition(Vector3(pos.x + 20, pos.y, pos.z - 1));
				_Critical_Middle->SetState(eState::Active);
			}
			else
			{
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));

				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetDirection(-1);
				Transform* bulltr = _Critical_Middle->GetComponent<Transform>();
				bulltr->SetPosition(Vector3(pos.x - 20, pos.y, pos.z - 1));
				_Critical_Middle->SetState(eState::Active);
			}
		}

		if (Layana_Awaken_Homing_Attac* Bullet = dynamic_cast<Layana_Awaken_Homing_Attac*>(other->GetOwner()))
		{
			if (_State == Skul_Wolf_State::Dash)
				return;

			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
			{
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));

				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetDirection(1);
				Transform* bulltr = _Critical_Middle->GetComponent<Transform>();
				bulltr->SetPosition(Vector3(pos.x + 20, pos.y, pos.z - 1));
				_Critical_Middle->SetState(eState::Active);
			}
			else
			{
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));

				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetDirection(-1);
				Transform* bulltr = _Critical_Middle->GetComponent<Transform>();
				bulltr->SetPosition(Vector3(pos.x - 20, pos.y, pos.z - 1));
				_Critical_Middle->SetState(eState::Active);
			}
		}

		if (Dark_DimensionPierce_BulletEffect* Bullet = dynamic_cast<Dark_DimensionPierce_BulletEffect*>(other->GetOwner()))
		{
			if (_State == Skul_Wolf_State::Dash)
				return;

			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
			{
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));

				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetDirection(1);
				Transform* bulltr = _Critical_Middle->GetComponent<Transform>();
				bulltr->SetPosition(Vector3(pos.x + 20, pos.y, pos.z - 1));
				_Critical_Middle->SetState(eState::Active);
			}
			else
			{
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));

				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetDirection(-1);
				Transform* bulltr = _Critical_Middle->GetComponent<Transform>();
				bulltr->SetPosition(Vector3(pos.x - 20, pos.y, pos.z - 1));
				_Critical_Middle->SetState(eState::Active);
			}
		}









		if (Ground_and_Wall* mGround = dynamic_cast<Ground_and_Wall*>(other->GetOwner()))
		{
			_Wall_check = true;
			_rigidbody->ClearVelocity();
			Transform* Ground_TR = other->GetOwner()->GetComponent<Transform>();
			Vector3 wall_pos = Ground_TR->GetPosition();
			if (_Wall_check == true)
			{
				if (pos.x < wall_pos.x)
				{
					_Rightmove_Lock = true;
					at->PlayAnimation(L"WolfIdle", true);
				}
				else if (pos.x > wall_pos.x)
				{
					_Leftmove_Lock = true;
					at->PlayAnimation(L"WolfIdleR", true);
				}
			}
		}

		if (Sky_Ground* mGround = dynamic_cast<Sky_Ground*>(other->GetOwner()))
		{			
			{
				Transform* Ground_TR = other->GetOwner()->GetComponent<Transform>();
				Collider2D* Ground_Col = other->GetOwner()->GetComponent<Collider2D>();
				Vector3 Ground_pos = Ground_TR->GetPosition();
				float Gr_Size = Ground_Col->GetScale().y / 2;
				float Gr_Top_pos = Ground_pos.y + Gr_Size;
				float Skul_halfsize = _collider->GetScale().y / 2;
				float skul_footpos = pos.y - Skul_halfsize;

				if (skul_footpos > Gr_Top_pos)
				{
					_fallcheck = 0;	_jump = 0;
					_rigidbody->SetGround(true);
					_Ground_check = _rigidbody->GetGround();
					_rigidbody->ClearVelocity();
					_State = Skul_Wolf_State::Idle;
					if (mDir == 1)
						at->PlayAnimation(L"WolfIdle", true);
					else
						at->PlayAnimation(L"WolfIdleR", true);
				}
			}
		}
	}

	void Skul_Wolf::OnCollisionStay(Collider2D* other)
	{
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{
			if (_Ground_check == false)
			{
				_Ground_On = true;
				mGround->_SkullOn = true;
				
				_Player_GRpos = pos;
				_fallcheck = 0;	_jump = 0;
				_rigidbody->SetGround(true);
				_Ground_check = true;
				_rigidbody->ClearVelocity();


				_State = Skul_Wolf_State::Idle;
				if (mDir == 1)
					at->PlayAnimation(L"WolfIdle", true);
				else
					at->PlayAnimation(L"WolfIdleR", true);
			}
			else
			{			
				if (_State == Skul_Wolf_State::Hit)
				{
					_Ground_check = false;
					_rigidbody->SetGround(false);
					if (HitDir == 1)
						_rigidbody->SetVelocity(Vector2(-75.f, 175.f));

					if (HitDir == -1)
						_rigidbody->SetVelocity(Vector2(75.f, 175.f));
				}
			}
		}
		
		if (Ground_Map* mGround = dynamic_cast<Ground_Map*>(other->GetOwner()))
		{
			if (_Ground_check == false)
			{
				_Ground_On = true;
				mGround->_SkullOn = true;
				_Player_GRpos = pos;
				_fallcheck = 0;	_jump = 0;
				_rigidbody->SetGround(true);
				_Ground_check = true;
				_rigidbody->ClearVelocity();


				_State = Skul_Wolf_State::Idle;
				if (mDir == 1)
					at->PlayAnimation(L"WolfIdle", true);
				else
					at->PlayAnimation(L"WolfIdleR", true);
			}
			else
			{
				if (_State == Skul_Wolf_State::Hit)
				{
					_Ground_check = false;
					_rigidbody->SetGround(false);
					if (HitDir == 1)
						_rigidbody->SetVelocity(Vector2(-75.f, 175.f));

					if (HitDir == -1)
						_rigidbody->SetVelocity(Vector2(75.f, 175.f));
				}
			}
		}
		
		if (Sky_Ground* mGround = dynamic_cast<Sky_Ground*>(other->GetOwner()))
		{
			Transform* Ground_TR = other->GetOwner()->GetComponent<Transform>();
			Collider2D* Ground_Col = other->GetOwner()->GetComponent<Collider2D>();
			Vector3 Ground_pos = Ground_TR->GetPosition();
			float Gr_Size = Ground_Col->GetScale().y / 2;
			float Gr_Top_pos = Ground_pos.y + Gr_Size;
			float Skul_halfsize = _collider->GetScale().y / 2;
			float skul_footpos = pos.y - Skul_halfsize;

			if (_Ground_check == false)
			{
				if (skul_footpos > Gr_Top_pos)
				{
					_Ground_On = true;
					mGround->_SkullOn = true;
					_Player_GRpos = pos;
					_fallcheck = 0;	_jump = 0;
					_rigidbody->ClearVelocity();
					_Ground_check = true;
					_rigidbody->SetGround(true);
					mGround->_SkullOn = true;
					_Ground_check = true;
				}
			}
			else
			{
				if (Input::GetKey(eKeyCode::V))
				{
					_rigidbody->SetVelocity(Vector2(0.f, -150.f));
					_Ground_check = false;
					_rigidbody->SetGround(false);
				}
				if (_State == Skul_Wolf_State::Hit)
				{
					_Ground_check = false;
					_rigidbody->SetGround(false);
					if (HitDir == 1)
						_rigidbody->SetVelocity(Vector2(-75.f, 175.f));

					if (HitDir == -1)
						_rigidbody->SetVelocity(Vector2(75.f, 175.f));
				}
			}

		}
	}

	void Skul_Wolf::OnCollisionExit(Collider2D* other)
	{
		if (Ground_and_Wall* mGround = dynamic_cast<Ground_and_Wall*>(other->GetOwner()))
		{
			_Wall_check = false;
			_Rightmove_Lock = false;
			_Leftmove_Lock = false;
		}

		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{
			_Wall_check = false;
			_Rightmove_Lock = false;
			_Leftmove_Lock = false;
			_Ground_On = false;

			if(_wolf_act == true)
				mGround->_SkullOn = false;
		}
		if (Ground_Map* mGround = dynamic_cast<Ground_Map*>(other->GetOwner()))
		{
			_Ground_check = false;
			_rigidbody->SetGround(false);
			_Ground_On = false;

			if (_wolf_act == true)
				mGround->_SkullOn = false;
		}
		if (Sky_Ground* mGround = dynamic_cast<Sky_Ground*>(other->GetOwner()))
		{
			_Ground_On = false;
			_Ground_check = false;
			_rigidbody->SetGround(false);

			if (_wolf_act == true)
				mGround->_SkullOn = false;
		}
	}

	void Skul_Wolf::attack_choice()
	{
		_attack_Acheck = false;
		_attack_Bcheck = false;
		_attack_Ccheck = false;
		Hit_Box->SetState(eState::Paused);
		if (_attack == true)
		{
			_State = Skul_Wolf_State::Attack_B;
			if (mDir == 1)
			{
				at->PlayAnimation(L"WolfAttackB", true);
				mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"WolfAttackBR", true);
				mDir = -1;
			}
		}
		if (_attack == false)
		{
			if (Input::GetKeyDown(eKeyCode::Z))
			{
				_State = Skul_Wolf_State::Dash;
				if (mDir == 1)
				{
					at->PlayAnimation(L"WolfDash", false);
					mDir = 1;
				}
				else if (mDir == -1)
				{
					at->PlayAnimation(L"WolfDashR", false);
					mDir = -1;
				}
			}

			if (Input::GetKey(eKeyCode::RIGHT)
				|| Input::GetKey(eKeyCode::LEFT))
			{
				_State = Skul_Wolf_State::Move;
				if (Input::GetKey(eKeyCode::RIGHT))
				{
					at->PlayAnimation(L"WolfWalk", true);
					mDir = 1;
				}
				else if (Input::GetKey(eKeyCode::LEFT))
				{
					at->PlayAnimation(L"WolfWalkR", true);
					mDir = -1;
				}
			}
			else
			{
				_State = Skul_Wolf_State::Idle;
				if (mDir == 1)
				{
					at->PlayAnimation(L"WolfIdle", true);
					mDir = 1;
				}
				else if (mDir == -1)
				{
					at->PlayAnimation(L"WolfIdleR", true);
					mDir = -1;
				}
			}
		}
	}

	void Skul_Wolf::dash_check()
	{
	}

	void Skul_Wolf::Input_move()
	{
		if (_Leftmove_Lock == false)
		{
			if (Input::GetKey(eKeyCode::LEFT))
			{
				mDir = -1;
				pos.x -= 150.0f * Time::DeltaTime();
			}
		}
		if (_Rightmove_Lock == false)
		{
			if (Input::GetKey(eKeyCode::RIGHT))
			{
				mDir = 1;
				pos.x += 150.0f * Time::DeltaTime();
			}
		}
		if (Input::GetKey(eKeyCode::DOWN))
			pos.y -= 100.0f * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::UP))
			pos.y += 100.0f * Time::DeltaTime();

		//if (Input::GetKeyDown(eKeyCode::C))
		//{
		//	_rigidbody->AddForce(Vector2(0.f, 350.f));
		//	_rigidbody->SetGround(false);
		//}

		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			SetPlay_List(PlayerList::basic_Skul,PlayerList::wolf_Skul, true, mDir);
			SetPlayer_Pos(pos);
		}
	}
}