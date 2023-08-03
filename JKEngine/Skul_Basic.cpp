#include "Skul_Basic.h"
#include "jktime.h"

namespace jk
{
	int Skul_Basic::mDir = 1;
	bool Skul_Basic::_switch = false;

	Skul_Basic::Skul_Basic()
		: _State(Skul_Basic_State::Idle)
		, at(nullptr)
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Basic_Skul"));
	}
	Skul_Basic::~Skul_Basic()
	{
	}
	void Skul_Basic::Initialize()
	{
		CameraScript* cam = AddComponent<CameraScript>();
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);

		Skul_Head = new Skul_head();
		Skul_Head->Initialize();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(eLayerType::Item, Skul_Head);
		Transform* tr_head = Skul_Head->GetComponent<Transform>();
		tr_head->SetPosition(Vector3(pos.x, pos.y, -250.f));
		Skul_Head->GetComponent<Transform>()->SetScale(Vector3(15.f, 13.f, 0.f));
		Skul_Head->SetState(eState::Paused);


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\AttackA", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\AttackB", this) ;
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\Dash", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\Fall", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\FallRepeat", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\Jump", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\JumpAttack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\Skill", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\Switch", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\Walk", this);


		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\AttackA", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\AttackB", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\Dash", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\Fall", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\FallRepeat", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\Idle", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\Jump", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\JumpAttack", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\Skill", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\Switch", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\Walk", this, 1);


		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\NoHead\\AttackA", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\NoHead\\AttackB", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\NoHead\\Dash", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\NoHead\\Fall", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\NoHead\\FallRepeat", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\NoHead\\Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\NoHead\\Jump", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\NoHead\\JumpAttack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\NoHead\\Walk", this);


		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\NoHead\\AttackA", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\NoHead\\AttackB", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\NoHead\\Dash", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\NoHead\\Fall", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\NoHead\\FallRepeat", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\NoHead\\Idle", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\NoHead\\Jump", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\NoHead\\JumpAttack", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\NoHead\\Walk", this, 1);
				
		//대쉬
		//at->PlayAnimation(L"Skul_BasicDash", true);
		//at->PlayAnimation(L"Skul_BasicDashR", true);			




		//테스트 남자기사
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Attack_A", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Attack_B", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Attack_C", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Attack_D", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Attack_E", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\BackDash", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Dash", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Die", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\EnergeBall", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Explosion_Loop", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Glorggy", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Hit", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Idle", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Intro", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Jump", this);	
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Potion", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Stinger", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Stinger_Ready", this);


		//궁수
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Attack_A", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Attack_B", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Attack_C", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\BackStep", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Die", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Groggy", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Hit", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Idle", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Intro", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Potion", this);

		//at->PlayAnimation(L"ArcherPotion", true);



		at->PlayAnimation(L"Skul_BasicIdle", true);
		at->CompleteEvent(L"Skul_BasicAttackA") = std::bind(&Skul_Basic::attack_choice, this);		
		at->CompleteEvent(L"Skul_BasicAttackAR") = std::bind(&Skul_Basic::attack_choice, this);
		at->CompleteEvent(L"Skul_BasicAttackB") = std::bind(&Skul_Basic::attack_choice, this);
		at->CompleteEvent(L"Skul_BasicAttackBR") = std::bind(&Skul_Basic::attack_choice, this);
		at->CompleteEvent(L"Skul_BasicJumpAttack") = std::bind(&Skul_Basic::attack_choice, this);
		at->CompleteEvent(L"Skul_BasicJumpAttackR") = std::bind(&Skul_Basic::attack_choice, this);
		at->CompleteEvent(L"Skul_BasicSkill") = std::bind(&Skul_Basic::attack_choice, this);
		at->CompleteEvent(L"Skul_BasicSkillR") = std::bind(&Skul_Basic::attack_choice, this);
		at->CompleteEvent(L"Skul_BasicSwitch") = std::bind(&Skul_Basic::switch_on_off, this);
		at->CompleteEvent(L"Skul_BasicSwitchR") = std::bind(&Skul_Basic::switch_on_off, this);

		at->CompleteEvent(L"NoHeadAttackA") = std::bind(&Skul_Basic::attack_choice, this);
		at->CompleteEvent(L"NoHeadAttackAR") = std::bind(&Skul_Basic::attack_choice, this);
		at->CompleteEvent(L"NoHeadAttackB") = std::bind(&Skul_Basic::attack_choice, this);
		at->CompleteEvent(L"NoHeadAttackBR") = std::bind(&Skul_Basic::attack_choice, this);	

		//at->CompleteEvent(L"Skul_BasicDash") = std::bind(&Skul_Basic::dash_check, this);
		//at->CompleteEvent(L"Skul_BasicDashR") = std::bind(&Skul_Basic::dash_check, this);


		GameObject::Initialize();
	}

	void Skul_Basic::Update()
	{
		tr = GetComponent<Transform>();
		pos = tr->GetPosition();
		SetPlayer_Pos(pos);
		_velocity = _rigidbody->GetVelocity();

		if (_switch == true)
		{
			_State = Skul_Basic::Skul_Basic_State::Switch;
			if (mDir == 1)
				at->PlayAnimation(L"Skul_BasicSwitch", true);
			else
				at->PlayAnimation(L"Skul_BasicSwitchR", true);
		}

		switch (_State)
		{
		case jk::Skul_Basic::Skul_Basic_State::Idle:idle();
			break;

		case jk::Skul_Basic::Skul_Basic_State::Move:move();
			break;

		case jk::Skul_Basic::Skul_Basic_State::Jump:jump();
			break;

		case jk::Skul_Basic::Skul_Basic_State::Fall:fall();
			break;

		case jk::Skul_Basic::Skul_Basic_State::Falling:falling();
			break;

		case jk::Skul_Basic::Skul_Basic_State::Dash:dash();
			break;

		case jk::Skul_Basic::Skul_Basic_State::Attack_A:attack_a();
			break;

		case jk::Skul_Basic::Skul_Basic_State::Attack_B:attack_b();
			break;

		case jk::Skul_Basic::Skul_Basic_State::JumpAttack:jumpattack();
			break;

		case jk::Skul_Basic::Skul_Basic_State::Skill_A:skill_a();
			break;

		case jk::Skul_Basic::Skul_Basic_State::Skill_B:skill_b();
			break;

		case jk::Skul_Basic::Skul_Basic_State::Switch:change();
			break;

		case jk::Skul_Basic::Skul_Basic_State::Death:death();
			break;

		default:
			break;
		}

		Input_move();
		tr->SetPosition(pos);
		GameObject::Update();
	}

	void Skul_Basic::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.05f));
		_collider->SetCenter(Vector2(0.0f, -0.1f));
		GameObject::LateUpdate();
	}

	void Skul_Basic::Render()
	{
		GameObject::Render();
	}

	void Skul_Basic::idle()
	{
		_attackcheck = false;

		if (Input::GetKey(eKeyCode::RIGHT)
			|| Input::GetKey(eKeyCode::LEFT))
		{
			_State = Skul_Basic_State::Move;
			if (Input::GetKey(eKeyCode::RIGHT))
			{
				at->PlayAnimation(L"Skul_BasicWalk", true);
			
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadWalk", true);
				mDir = 1;

			}
			else if (Input::GetKey(eKeyCode::LEFT))
			{
				at->PlayAnimation(L"Skul_BasicWalkR", true);
				
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadWalkR", true);
				mDir = -1;
			}
		}


		if (Input::GetKeyDown(eKeyCode::C))
		{
			_State = Skul_Basic_State::Jump;
			if (mDir == 1)
			{
				at->PlayAnimation(L"Skul_BasicJump", true);
				
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadJump", true);
				
				_rigidbody->SetVelocity(Vector2(0.f, 250.f));
				_rigidbody->SetGround(false);	mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"Skul_BasicJumpR", true);

				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadJumpR", true);

				_rigidbody->SetVelocity(Vector2(0.f, 250.f));
				_rigidbody->SetGround(false);	mDir = -1;
			}
			_jump++;
		}

		if (Input::GetKey(eKeyCode::X))
		{
			_attackcheck = true;
			_State = Skul_Basic_State::Attack_A;
			if (mDir == 1)
			{
				at->PlayAnimation(L"Skul_BasicAttackA", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadAttackA", true);
				mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"Skul_BasicAttackAR", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadAttackAR", true);
				mDir = -1;
			}
		}


		if (Input::GetKeyDown(eKeyCode::Z))
		{
			_State = Skul_Basic_State::Dash;
			if (mDir == 1)
			{
				at->PlayAnimation(L"Skul_BasicDash", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadDash", true);
				_rigidbody->SetVelocity(Vector2(250.f, 0.f));
				mDir = 1;
			}
			if (mDir == -1)
			{
				at->PlayAnimation(L"Skul_BasicDashR", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadDashR", true);
				_rigidbody->SetVelocity(Vector2(-250.f, 0.f));
				mDir = -1;
			}						
		}

		if (Input::GetKey(eKeyCode::A))
		{
			if (_Skulhead == false)
			{
				_State = Skul_Basic_State::Skill_A;
				RigidBody* head_rjg = Skul_Head->Getrigidbody();
				head_rjg->SetGround(false);
				Skul_Head->SetState(eState::Active);
				if (mDir == 1)
				{
					at->PlayAnimation(L"Skul_BasicSkill", true);
					mDir = 1; _Skulhead = true;			
					Skul_Head->Setattack(true);
					Skul_Head->GetComponent<Transform>()->SetPositionXY(Vector2{ tr->GetPosition().x+35, tr->GetPosition().y +10 });
					Skul_Head->GetComponent<RigidBody>()->SetVelocity(Vector2{ 350.f, 0.0f });
				}
				else if (mDir == -1)
				{
					at->PlayAnimation(L"Skul_BasicSkillR", true);
					mDir = -1; _Skulhead = true;		
					Skul_Head->Setattack(true);
					Skul_Head->GetComponent<Transform>()->SetPositionXY(Vector2{ tr->GetPosition().x-35, tr->GetPosition().y + 10 });
					Skul_Head->GetComponent<RigidBody>()->SetVelocity(Vector2{ -350.f, 0.0f });
				}					
			}
			else
			{
			}
		}

		if (Input::GetKey(eKeyCode::S))
		{
			if (_Skulhead == true)
			{
				_State = Skul_Basic_State::Skill_B;
				if (mDir == 1)
				{
					at->PlayAnimation(L"NoHeadFall", false);
					mDir = 1; 
				}
				else if (mDir == -1)
				{
					at->PlayAnimation(L"NoHeadFallR", false);
					mDir = -1; 
				}
				pos.x = Skul_Head->GetPosition().x;
				pos.y = Skul_Head->GetPosition().y+100;
				Skul_Head->Setattack(true);
				Skul_Head->SetDirection(mDir);
			}
			else
			{
			}
		}

	}

	void Skul_Basic::move()
	{
		if (Input::GetKeyUp(eKeyCode::RIGHT)
			|| Input::GetKeyUp(eKeyCode::LEFT))
		{
			_State = Skul_Basic_State::Idle;
			if (Input::GetKeyUp(eKeyCode::RIGHT))
			{
				at->PlayAnimation(L"Skul_BasicIdle", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadIdle", true);
				mDir = 1;
			}
			else if (Input::GetKeyUp(eKeyCode::LEFT))
			{
				at->PlayAnimation(L"Skul_BasicIdleR", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadIdleR", true);
				mDir = -1;
			}
		}

		if (Input::GetKeyDown(eKeyCode::C))
		{
			_State = Skul_Basic_State::Jump;
			if (mDir == 1)
			{
				at->PlayAnimation(L"Skul_BasicJump", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadJump", true);
				_rigidbody->SetVelocity(Vector2(0.f, 250.f));
				_rigidbody->SetGround(false);	mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"Skul_BasicJumpR", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadJumpR", true);
				_rigidbody->SetVelocity(Vector2(0.f, 250.f));
				_rigidbody->SetGround(false);	mDir = -1;
			}
			_jump++;
		}


		if (Input::GetKey(eKeyCode::X))
		{
			_State = Skul_Basic_State::Attack_A;
			if (mDir == 1)
			{
				at->PlayAnimation(L"Skul_BasicAttackA", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadAttackA", true);
				mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"Skul_BasicAttackAR", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadAttackAR", true);
				mDir = -1;
			}
		}

		if (Input::GetKeyDown(eKeyCode::Z))
		{
			_State = Skul_Basic_State::Dash;
			if (mDir == 1)
			{
				at->PlayAnimation(L"Skul_BasicDash", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadDash", true);
				_rigidbody->SetVelocity(Vector2(250.f, 0.f));
				mDir = 1;
			}
			if (mDir == -1)
			{
				at->PlayAnimation(L"Skul_BasicDashR", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadDashR", true);
				_rigidbody->SetVelocity(Vector2(-250.f, 0.f));
				mDir = -1;
			}
		}
	}

	void Skul_Basic::jump()
	{		
		_Ground_check = false;
		if((_velocity.y <= 0.f)||(_jump>=2))
		{
			_State = Skul_Basic_State::Fall;
			if (mDir == 1)
			{
				at->PlayAnimation(L"Skul_BasicFall", false);	
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadFall", false);
				mDir = 1;
			}
			if (mDir == -1)
			{
				at->PlayAnimation(L"Skul_BasicFallR", false);		
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadFallR", false);
				mDir = -1;
			}
			_jump = 0;
		}

		if (_jump < 3)
		{
			if (Input::GetKeyDown(eKeyCode::C))
			{
				if (mDir == 1)
				{
					_rigidbody->SetVelocity(Vector2(0.f, 250.f));
					mDir = 1;
				}
				else if (mDir == -1)
				{
					_rigidbody->SetVelocity(Vector2(0.f, 250.f));
					mDir = -1;
				}
				_jump++;
			}
		}

		if (Input::GetKeyDown(eKeyCode::X))
		{
			if (mDir == 1)
			{
				_State = Skul_Basic_State::JumpAttack;
				at->PlayAnimation(L"Skul_BasicJumpAttack", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadJumpAttack", true);
			}
			if (mDir == -1)
			{
				_State = Skul_Basic_State::JumpAttack;
				at->PlayAnimation(L"Skul_BasicJumpAttackR", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadJumpAttackR", true);
			}
		}

		if (Input::GetKeyDown(eKeyCode::Z))
		{
			_State = Skul_Basic_State::Dash;
			if (mDir == 1)
			{
				at->PlayAnimation(L"Skul_BasicDash", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadDash", true);
				_rigidbody->SetVelocity(Vector2(250.f, 0.f));
				mDir = 1;
			}
			if (mDir == -1)
			{
				at->PlayAnimation(L"Skul_BasicDashR", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadDashR", true);
				_rigidbody->SetVelocity(Vector2(-250.f, 0.f));
				mDir = -1;
			}
		}

	}

	void Skul_Basic::fall()
	{
		_Ground_check = false;
		_time += Time::DeltaTime();
		if (_time > 2.f)
		{
			_State = Skul_Basic_State::Falling;
			if (mDir == 1)
			{
				at->PlayAnimation(L"Skul_BasicFallRepeat", true);	
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadFallRepeat", true);
				mDir = 1;  _fallcheck = 2;
			}
			if (mDir == -1)
			{
				at->PlayAnimation(L"Skul_BasicFallRepeatR", true);	
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadFallRepeatR", true);
				mDir = -1; _fallcheck = 2;
			}
			_time = 0;
		}
		if (Input::GetKeyDown(eKeyCode::X))
		{
			if (mDir == 1)
			{
				_State = Skul_Basic_State::JumpAttack;
				at->PlayAnimation(L"Skul_BasicJumpAttack", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadJumpAttack", true);
			}
			if (mDir == -1)
			{
				_State = Skul_Basic_State::JumpAttack;
				at->PlayAnimation(L"Skul_BasicJumpAttackR", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadJumpAttackR", true);
			}
		}

		if (Input::GetKeyDown(eKeyCode::Z))
		{
			_State = Skul_Basic_State::Dash;
			if (mDir == 1)
			{
				at->PlayAnimation(L"Skul_BasicDash", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadJumpDash", true);
				_rigidbody->SetVelocity(Vector2(250.f, 0.f));
				mDir = 1;
			}
			if (mDir == -1)
			{
				at->PlayAnimation(L"Skul_BasicDashR", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadJumpDashR", true);
				_rigidbody->SetVelocity(Vector2(-250.f, 0.f));
				mDir = -1;
			}
		}

	}

	void Skul_Basic::falling()
	{
		_Ground_check = false;
		if (Input::GetKeyDown(eKeyCode::X))
		{
			if (mDir == 1)
			{
				_State = Skul_Basic_State::JumpAttack;
				at->PlayAnimation(L"Skul_BasicJumpAttack", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadJumpAttack", true);
			}
			if (mDir == -1)
			{
				_State = Skul_Basic_State::JumpAttack;
				at->PlayAnimation(L"Skul_BasicJumpAttackR", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadJumpAttackR", true);
			}
		}

		if (Input::GetKeyDown(eKeyCode::Z))
		{
			_State = Skul_Basic_State::Dash;
			if (mDir == 1)
			{
				at->PlayAnimation(L"Skul_BasicDash", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadDash", true);
				_rigidbody->SetVelocity(Vector2(250.f, 0.f));
				mDir = 1;
			}
			if (mDir == -1)
			{
				at->PlayAnimation(L"Skul_BasicDashR", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadDashR", true);
				_rigidbody->SetVelocity(Vector2(-250.f, 0.f));
				mDir = -1;
			}
		}
	}

	void Skul_Basic::dash()
	{		 
		_Ground_check = false;
		_rigidbody->ClearVelocityY();
		if (mDir == 1 && _velocity.x <= 220.0)
		{
			_State = Skul_Basic_State::Idle;
			at->PlayAnimation(L"Skul_BasicIdle", true);
			if (_Skulhead == true)
				at->PlayAnimation(L"NoHeadIdle", true);
			_rigidbody->SetGround(false);
			_rigidbody->ClearVelocityX();
			mDir = 1;
		}
		else if (mDir == -1 && _velocity.x >= -220.0)
		{
			_State = Skul_Basic_State::Idle;
			at->PlayAnimation(L"Skul_BasicIdleR", true);
			if (_Skulhead == true)
				at->PlayAnimation(L"NoHeadIdleR", true);
			_rigidbody->SetGround(false);
			_rigidbody->ClearVelocityX();
			mDir = -1;
		}				
	}

	void Skul_Basic::attack_a()
	{
		_attackcheck = true;
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

	void Skul_Basic::attack_b()
	{
		_attackcheck = true;
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

	void Skul_Basic::jumpattack()
	{
		_attackcheck = true;
	}

	void Skul_Basic::skill_a()
	{
		RigidBody* head_rjg = Skul_Head->Getrigidbody();
		head_rjg->ClearVelocityY();
		Vector2 _velocity_head = head_rjg->GetVelocity();
		Skul_Head->Setgroundcheck(false);
		
		if (mDir == 1 && _velocity_head.x <= 220.0)
		{
			head_rjg->SetGround(false);
			head_rjg->ClearVelocityX();
			mDir = 1;
		}
		else if (mDir == -1 && _velocity_head.x >= -220.0)
		{
			head_rjg->SetGround(false);
			head_rjg->ClearVelocityX();
			mDir = -1;
		}


	}

	void Skul_Basic::skill_b()
	{
	}

	void Skul_Basic::change()
	{
		{
			if (mDir == 1)
			{
				_rigidbody->SetVelocity(Vector2(100.f, 0.f));				
				_switch = false; _Ground_check = false;
			}
			else
			{
				_rigidbody->SetVelocity(Vector2(-100.f, 0.f));				
				_switch = false; _Ground_check = false;
			}
		}
	}

	void Skul_Basic::death()
	{

	}


	void Skul_Basic::OnCollisionEnter(Collider2D* other)
	{		
		if (Skul_head* _head = dynamic_cast<Skul_head*>(other->GetOwner()))
		{
			if (_Skulhead == true)
			{
				_State = Skul_Basic_State::Idle;
				if (mDir == 1)
					at->PlayAnimation(L"Skul_BasicIdle", true);
				else
					at->PlayAnimation(L"Skul_BasicIdleR", true);
				Setskillcheck(false);
				_Skulhead = false;
				Skul_Head->SetState(eState::Paused);
			}
		}
	}

	void Skul_Basic::OnCollisionStay(Collider2D* other)
	{
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{

			if (_Ground_check == false)
			{
				_fallcheck = 0;	_jump = 0;
				_rigidbody->SetGround(true);
				_Ground_check = true;
				_Ground_check = _rigidbody->GetGround();

				if (_State == Skul_Basic_State::JumpAttack || _State == Skul_Basic_State::Fall || _State == Skul_Basic_State::Falling)
				{
					_State = Skul_Basic_State::Idle;
					if (mDir == 1)
						at->PlayAnimation(L"Skul_BasicIdle", true);
					else
						at->PlayAnimation(L"Skul_BasicIdleR", true);
				}
			}
			else
			{
				if (Input::GetKeyDown(eKeyCode::Z))
				{
					_State = Skul_Basic_State::Dash;
					if (mDir == 1)
					{
						at->PlayAnimation(L"Skul_BasicDash", true);
						if (_Skulhead == true)
							at->PlayAnimation(L"NoHeadDash", true);
						_rigidbody->SetVelocity(Vector2(250.f, 0.f));
						mDir = 1;
					}
					if (mDir == -1)
					{
						at->PlayAnimation(L"Skul_BasicDashR", true);
						if (_Skulhead == true)
							at->PlayAnimation(L"NoHeadDashR", true);
						_rigidbody->SetVelocity(Vector2(-250.f, 0.f));
						mDir = -1;
					}
				}
			}
		}
	}

	void Skul_Basic::OnCollisionExit(Collider2D* other)
	{
	}

	void Skul_Basic::attack_choice()
	{
		if (_attack == true)
		{
			_State = Skul_Basic_State::Attack_B;
			if (mDir == 1)
			{
				at->PlayAnimation(L"Skul_BasicAttackB", true);
				mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"Skul_BasicAttackBR", true);
				mDir = -1;
			}
		}
		if (_attack == false)
		{
			if (Input::GetKeyDown(eKeyCode::Z))
			{
				_State = Skul_Basic_State::Dash;
				if (mDir == 1)
				{
					at->PlayAnimation(L"Skul_BasicDash", false);
					mDir = 1;
				}
				else if (mDir == -1)
				{
					at->PlayAnimation(L"Skul_BasicDashR", false);
					mDir = -1;
				}
			}

			if (_fallcheck == 1)
			{				
				_State = Skul_Basic_State::Fall;
				if (mDir == 1)
				{
					at->PlayAnimation(L"Skul_BasicFall", false);					
				}
				else if (mDir == -1)
				{
					at->PlayAnimation(L"Skul_BasicFallR", false);					
				}				
			}
			if (_fallcheck == 2)
			{
				_State = Skul_Basic_State::Falling;
				if (mDir == 1)
				{
					at->PlayAnimation(L"Skul_BasicFallRepeat", true);
					mDir = 1;
				}
				else if (mDir == -1)
				{
					at->PlayAnimation(L"Skul_BasicFallRepeatR", true);
					mDir = -1;
				}				
			}

			if (Input::GetKey(eKeyCode::RIGHT)
				|| Input::GetKey(eKeyCode::LEFT))
			{
				_State = Skul_Basic_State::Move;
				if (Input::GetKey(eKeyCode::RIGHT))
				{
					at->PlayAnimation(L"Skul_BasicWalk", true);
					mDir = 1;
				}
				else if (Input::GetKey(eKeyCode::LEFT))
				{
					at->PlayAnimation(L"Skul_BasicWalkR", true);
					mDir = -1;
				}
			}
			else
			{
				_State = Skul_Basic_State::Idle;
				if (mDir == 1)
				{
					at->PlayAnimation(L"Skul_BasicIdle", true);
					if (_Skulhead == true)
						at->PlayAnimation(L"NoHeadIdle", true);


					mDir = 1;
				}
				else if (mDir == -1)
				{
					at->PlayAnimation(L"Skul_BasicIdleR", true);

					if (_Skulhead == true)
						at->PlayAnimation(L"NoHeadIdleR", true);

					mDir = -1;
				}
			}
		}
	}
	void Skul_Basic::Input_move()
	{
		if (Input::GetKey(eKeyCode::LEFT))
			pos.x -= 150.0f * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::RIGHT))
			pos.x += 150.0f * Time::DeltaTime();
	
		if (Input::GetKey(eKeyCode::DOWN))
			pos.y -= 100.0f * Time::DeltaTime();
		
		if (Input::GetKey(eKeyCode::UP))		
			pos.y += 100.0f * Time::DeltaTime();


		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			SetPlay_List(PlayerList::wolf_Skul,PlayerList::basic_Skul, true, mDir);
			//SetPlay_List(PlayerList::spere_Skul, PlayerList::basic_Skul, true, mDir);
			SetPlayer_Pos(pos);
		}
	}
	void Skul_Basic::switch_on_off()
	{
		if(_switch == false)
		{
			_State = Skul_Basic_State::Idle;
			if (mDir == 1)
			{
				at->PlayAnimation(L"Skul_BasicIdle", true);
				mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"Skul_BasicIdleR", true);
				mDir = -1;
			}
			_rigidbody->ClearVelocity();
		}
	}
}
