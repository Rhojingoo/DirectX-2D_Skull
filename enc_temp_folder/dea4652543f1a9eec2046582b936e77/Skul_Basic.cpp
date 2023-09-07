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
		//_rigidbody->SetFriction(true);
		{
			Skul_Head = new Skul_head();
			Skul_Head->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Player, Skul_Head);
			Transform* tr_head = Skul_Head->GetComponent<Transform>();
			tr_head->SetPosition(Vector3(pos.x, pos.y, -250.f));
			Skul_Head->GetComponent<Transform>()->SetScale(Vector3(15.f, 13.f, 0.f));
			Skul_Head->SetState(eState::Paused);
		}
		{
			Hit_Box = new HitBox_Player();
			Hit_Box->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Hitbox, Hit_Box);
			Hit_Box->SetState(eState::Active);
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
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, _Knight_Slash);
			_Knight_Slash->SetState(eState::Paused);
		}
		{
			_DarkKnight = new Hit_DarkPaladin;
			_DarkKnight->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, _DarkKnight);
			_DarkKnight->SetState(eState::Paused);
		}
		
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


		GameObject::Initialize();
	}

	void Skul_Basic::Update()
	{
		tr = GetComponent<Transform>();
		pos = tr->GetPosition();
		SetPlayer_Pos(pos);
		_velocity = _rigidbody->GetVelocity();
		_Ground_On = _Ground_check;

		{
			Transform* _Hit_Effect_TR = _Hit_Effect->GetComponent<Transform>();
			if (mDir == 1)
				_Hit_Effect_TR->SetPosition(Vector3(pos.x + 15, pos.y, pos.z - 1));
			else
				_Hit_Effect_TR->SetPosition(Vector3(pos.x - 15, pos.y, pos.z - 1));
		}
		{
			Transform* _Hit_Effect_TR = _Hit_Sword->GetComponent<Transform>();
			if (mDir == 1)
				_Hit_Effect_TR->SetPosition(Vector3(pos.x + 15, pos.y, pos.z - 1));
			else
				_Hit_Effect_TR->SetPosition(Vector3(pos.x - 15, pos.y, pos.z - 1));
		}

		{
			Transform * _Hit_Effect_TR = _Knight_Slash->GetComponent<Transform>();
			if (mDir == 1)
				_Hit_Effect_TR->SetPosition(Vector3(pos.x + 15, pos.y, pos.z - 1));
			else
				_Hit_Effect_TR->SetPosition(Vector3(pos.x - 15, pos.y, pos.z - 1));
		}

		{
			Transform* _Hit_Effect_TR = _DarkKnight->GetComponent<Transform>();
			if (mDir == 1)
				_Hit_Effect_TR->SetPosition(Vector3(pos.x + 15, pos.y, pos.z - 1));
			else
				_Hit_Effect_TR->SetPosition(Vector3(pos.x - 15, pos.y, pos.z - 1));
		}
		
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

		case jk::Skul_Basic::Skul_Basic_State::Stun:stun();
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
		Transform* HitBox_TR = Hit_Box->GetComponent<Transform>();
		if (_attack_Acheck==true)
		{	
			Hit_Box->SetState(eState::Active);
			if (mDir == 1)			
				HitBox_TR->SetPosition(Vector3(pos.x + 50, pos.y, pos.z));			
			else			
				HitBox_TR->SetPosition(Vector3(pos.x - 50, pos.y, pos.z));			
		}
		else if (_attack_Bcheck==true)
		{
			Hit_Box->SetState(eState::Active);
			if (mDir == 1)
				HitBox_TR->SetPosition(Vector3(pos.x + 50, pos.y, pos.z));
			else
				HitBox_TR->SetPosition(Vector3(pos.x - 50, pos.y, pos.z));
		}
		else
		{
			Hit_Box->SetState(eState::Paused);			
		}		
		
		_collider->SetSize(Vector2(0.1f, 0.5f));
		_collider->SetCenter(Vector2(0.0f, -2.5f));

		GameObject::LateUpdate();
		
	}

	void Skul_Basic::Render()
	{
		GameObject::Render();
	}



	void Skul_Basic::idle()
	{
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
				
				_rigidbody->SetVelocity(Vector2(0.f, 350.f));
				_rigidbody->SetGround(false);	mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"Skul_BasicJumpR", true);

				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadJumpR", true);

				_rigidbody->SetVelocity(Vector2(0.f, 350.f));
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

		if (Input::GetKey(eKeyCode::A))
		{
			if (_Skulhead == false)
			{
				_State = Skul_Basic_State::Skill_A;
				RigidBody* head_rjg = Skul_Head->Getrigidbody();
				head_rjg->SetGround(false);				
				if (mDir == 1)
				{
					at->PlayAnimation(L"Skul_BasicSkill", true);
					_Skulhead = true;
					Skul_Head->Setattack(true);				
					Skul_Head->SetHead = true;
					Skul_Head->SetDirection(1);
					Skul_Head->SetState(eState::Active);
					Skul_Head->SetBeforeAttackPos(pos);
					Skul_Head->GetComponent<Transform>()->SetPositionXY(Vector2{ tr->GetPosition().x+45, tr->GetPosition().y +10 });
					Skul_Head->GetComponent<RigidBody>()->SetVelocity(Vector2{ 450.f, 0.0f });
					Skul_Head->GetComponent<RigidBody>()->SetFriction(true);
					Skul_Head->GetComponent<RigidBody>()->SetGravity(true);
					_skulheadtemp = pos;
				}
				else if (mDir == -1)
				{
					at->PlayAnimation(L"Skul_BasicSkillR", true);
					_Skulhead = true;		
					Skul_Head->SetHead = true;
					Skul_Head->Setattack(true);
					Skul_Head->SetDirection(-1);
					Skul_Head->SetState(eState::Active);
					Skul_Head->SetBeforeAttackPos(pos);
					Skul_Head->GetComponent<Transform>()->SetPositionXY(Vector2{ tr->GetPosition().x-45, tr->GetPosition().y + 10 });		
					Skul_Head->GetComponent<RigidBody>()->SetVelocity(Vector2{ -450.f, 0.0f });
					Skul_Head->GetComponent<RigidBody>()->SetFriction(true);
					Skul_Head->GetComponent<RigidBody>()->SetGravity(true);
					_skulheadtemp = pos;
				}					
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
				Transform* tr_head = Skul_Head->GetComponent<Transform>();
				Vector3 headbullet = tr_head->GetPosition();
				pos = Vector3(headbullet.x, headbullet.y+30, headbullet.z);
				Skul_Head->Setattack(true);
				Skul_Head->SetDirection(mDir);
				_rigidbody->SetGround(false);
				_Ground_check = false;
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
				_rigidbody->SetVelocity(Vector2(0.f, 350.f));
				_rigidbody->SetGround(false);	mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"Skul_BasicJumpR", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadJumpR", true);
				_rigidbody->SetVelocity(Vector2(0.f, 350.f));
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
		_SkyGround_check = false;
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
					at->PlayAnimation(L"Skul_BasicJump", true);
					if (_Skulhead == true)
						at->PlayAnimation(L"NoHeadJump", true);
					_rigidbody->SetVelocity(Vector2(0.f, 350.f));
					_rigidbody->SetGround(false);	mDir = 1;
				}
				else if (mDir == -1)
				{
					at->PlayAnimation(L"Skul_BasicJumpR", true);
					if (_Skulhead == true)
						at->PlayAnimation(L"NoHeadJumpR", true);
					_rigidbody->SetVelocity(Vector2(0.f, 350.f));
					_rigidbody->SetGround(false);	mDir = -1;
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
		_SkyGround_check = false;
		if (_jump < 3)
		{
			if (Input::GetKeyDown(eKeyCode::C))
			{
				if (mDir == 1)
				{
					at->PlayAnimation(L"Skul_BasicJump", true);
					if (_Skulhead == true)
						at->PlayAnimation(L"NoHeadJump", true);
					_rigidbody->SetVelocity(Vector2(0.f, 350.f));
					_rigidbody->SetGround(false);	mDir = 1;
				}
				else if (mDir == -1)
				{
					at->PlayAnimation(L"Skul_BasicJumpR", true);
					if (_Skulhead == true)
						at->PlayAnimation(L"NoHeadJumpR", true);
					_rigidbody->SetVelocity(Vector2(0.f, 350.f));
					_rigidbody->SetGround(false);	mDir = -1;
				}
				_jump++;
			}
		}


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
		_SkyGround_check = false;
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
		_Leftmove_Lock = false;
		_Rightmove_Lock = false;
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
	void Skul_Basic::attack_b()
	{	
		_attack = false;
		_attack_Bcheck = true;
		//if (Input::GetKeyDown(eKeyCode::X))
		//{
		//	_attack = true;
		//}
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
		
	}


	void Skul_Basic::skill_a()
	{
		//Transform* tr_head = Skul_Head->GetComponent<Transform>();
		//Vector3 currenthead = tr_head->GetPosition();
		//RigidBody* head_rjg = Skul_Head->Getrigidbody();
		//head_rjg->ClearVelocityY();
		//Vector2 _velocity_head = head_rjg->GetVelocity();
		//Skul_Head->Setgroundcheck(false);
		
		//float Headdis =_skulheadtemp.x - currenthead.x;		
		//if (mDir == 1 && Headdis <= -500)
		//{			
		//	head_rjg->SetGround(false);
		//	head_rjg->ClearVelocityX();
		//	mDir = 1;
		//}
		//else if (mDir == -1 && Headdis >= 500.0)
		//{
		//	head_rjg->SetGround(false);
		//	head_rjg->ClearVelocityX();
		//	mDir = -1;
		//}
	}
	void Skul_Basic::skill_b()
	{
	}

	void Skul_Basic::stun()
	{
		_attack_time += Time::DeltaTime();
		if (_attack_time > 1.5)
		{
			_State = Skul_Basic_State::Idle;
			_attack_time = 0;
			_Leftmove_Lock = false;
			_Rightmove_Lock = false;
		}
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
				_switch = false; _Ground_check = false; _rigidbody->SetGround(false);
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
				if (_State == Skul_Basic_State::Dash)
				{
				}
				else
				{
					_State = Skul_Basic_State::Idle;
					if (mDir == 1)
						at->PlayAnimation(L"Skul_BasicIdle", true);
					else
						at->PlayAnimation(L"Skul_BasicIdleR", true);
				}
					Setskillcheck(false);
				_Skulhead = false;
				Skul_Head->SetState(eState::Paused);
			}
		}

		if (HitBox_Monster* _Monster = dynamic_cast<HitBox_Monster*>(other->GetOwner()))
		{		
			if (mDir == 1)
			{			
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));	

				_Hit_Effect->_effect_animation = true;
				_Hit_Effect->SetDirection(1);
				_Hit_Effect->SetState(eState::Active);
			}
			if (mDir == -1)
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
				if (mDir == 1)
				{
					_rigidbody->SetVelocity(Vector2(-50.f, 0.f));

					_Hit_Effect->_effect_animation = true;
					_Hit_Effect->SetDirection(1);
					_Hit_Effect->SetState(eState::Active);
				}
				if (mDir == -1)
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
				if (mDir == 1)
				{
					_rigidbody->SetVelocity(Vector2(-50.f, 0.f));
					_Hit_Effect->_effect_animation = true;
					_Hit_Effect->SetDirection(1);
					_Hit_Effect->SetState(eState::Active);
				}
				if (mDir == -1)
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
			if (mDir == 1)
			{
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));

				_Hit_Effect->_effect_animation = true;
				_Hit_Effect->SetDirection(1);
				_Hit_Effect->SetState(eState::Active);
			}
			if (mDir == -1)
			{
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));

				_Hit_Effect->_effect_animation = true;
				_Hit_Effect->SetDirection(-1);
				_Hit_Effect->SetState(eState::Active);
			}			
		}

		if (Mini_Boss*  Boss = dynamic_cast<Mini_Boss*>(other->GetOwner()))
		{
			//Goldham_st = GoldHammer->GetState();
			//if (Goldham_st == Monster_GoldHammer::Monster_GoldHammer_State::Tackle)
			//{
			//	if (mDir == 1)
			//	{
			//		_rigidbody->SetVelocity(Vector2(-50.f, 0.f));
			//		_Hit_Effect_player->_effect_animation = true;
			//		_Hit_Effect_player->SetDirection(1);
			//		_Hit_Effect_player->SetState(eState::Active);
			//	}
			//	if (mDir == -1)
			//	{
			//		_rigidbody->SetVelocity(Vector2(50.f, 0.f));
			//		_Hit_Effect_player->_effect_animation = true;
			//		_Hit_Effect_player->SetDirection(-1);
			//		_Hit_Effect_player->SetState(eState::Active);
			//	}
			//}
		}

		if (MiniBoss_Bullet_Archer* Bullet = dynamic_cast<MiniBoss_Bullet_Archer*>(other->GetOwner()))
		{
			if (mDir == 1)
			{
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));

				_Hit_Sword->_effect_animation = true;
				_Hit_Sword->SetDirection(-1);
				_Hit_Sword->SetState(eState::Active);
			}
			if (mDir == -1)
			{
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));

				_Hit_Sword->_effect_animation = true;
				_Hit_Sword->SetDirection(1);
				_Hit_Sword->SetState(eState::Active);
			}
		}

		if (Archer_Trap* Bullet = dynamic_cast<Archer_Trap*>(other->GetOwner()))
		{
			if (_State == Skul_Basic_State::Dash)
				return;
			else
			{
				_State = Skul_Basic_State::Stun;
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
			if (mDir == 1)
			{
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));
				_Hit_Effect->_effect_animation = true;
				_Knight_Slash->SetDirection(1);
				_Knight_Slash->SetState(eState::Active);
			}
			if (mDir == -1)
			{
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));
				_Knight_Slash->_effect_animation = true;
				_Knight_Slash->SetDirection(-1);
				_Knight_Slash->SetState(eState::Active);
			}
		}

		if (MiniBoss_Bullet_Knight* Bullet = dynamic_cast<MiniBoss_Bullet_Knight*>(other->GetOwner()))
		{
			if (mDir == 1)
			{
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));

				_Hit_Sword->_effect_animation = true;
				_Hit_Sword->SetDirection(-1);
				_Hit_Sword->SetState(eState::Active);
			}
			if (mDir == -1)
			{
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));

				_Hit_Sword->_effect_animation = true;
				_Hit_Sword->SetDirection(1);
				_Hit_Sword->SetState(eState::Active);
			}
		}

		if (Knight_Energe_Blast* Bullet = dynamic_cast<Knight_Energe_Blast*>(other->GetOwner()))
		{
			if (mDir == 1)
			{
				_rigidbody->SetVelocity(Vector2(-50.f, 155.f));
				_rigidbody->AddForce(Vector2(0.f, 15));
				_rigidbody->SetGround(false);
				_Ground_check = false;

				_Hit_Sword->_effect_animation = true;
				_Hit_Sword->SetDirection(-1);
				_Hit_Sword->SetState(eState::Active);
			}
			if (mDir == -1)
			{
				_rigidbody->SetVelocity(Vector2(50.f, 155.f));
				_rigidbody->AddForce(Vector2(0.f, 15));
				_rigidbody->SetGround(false);
				_Ground_check = false;

				_Hit_Sword->_effect_animation = true;
				_Hit_Sword->SetDirection(1);
				_Hit_Sword->SetState(eState::Active);
			}
		}

		if (Knight_UltimateSkill_Projectile* Bullet = dynamic_cast<Knight_UltimateSkill_Projectile*>(other->GetOwner()))
		{
			if (mDir == 1)
			{
				_rigidbody->SetVelocity(Vector2(-50.f, 50.f));

				_DarkKnight->_effect_animation = true;
				_DarkKnight->SetDirection(-1);
				_DarkKnight->SetState(eState::Active);
			}
			if (mDir == -1)
			{
				_rigidbody->SetVelocity(Vector2(50.f, 50.f));

				_DarkKnight->_effect_animation = true;
				_DarkKnight->SetDirection(1);
				_DarkKnight->SetState(eState::Active);
			}
		}


		if (Ground_Map* mGround = dynamic_cast<Ground_Map*>(other->GetOwner()))
		{
			_Wall_check = true;
			_rigidbody->ClearVelocity();
			Transform* Ground_TR = other->GetOwner()->GetComponent<Transform>();
			Collider2D* Ground_Col = other->GetOwner()->GetComponent<Collider2D>();
			Vector3 Ground_pos = Ground_TR->GetPosition();
			float Gr_Size = Ground_Col->GetScale().y / 2;
			float Gr_Top_pos = Ground_pos.y + Gr_Size;
			float Skul_halfsize = _collider->GetScale().y / 2;
			float skul_footpos = pos.y - Skul_halfsize;

			//if (skul_footpos > Gr_Top_pos)
			//{
			//	_Ground_check = false;
			//}
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
					at->PlayAnimation(L"Skul_BasicIdle", true);
					if (_Skulhead == true)
						at->PlayAnimation(L"NoHeadIdle", true);
				}
				else if (pos.x > wall_pos.x)
				{
					_Leftmove_Lock = true;
					at->PlayAnimation(L"Skul_BasicIdleR", true);
					if (_Skulhead == true)
						at->PlayAnimation(L"NoHeadIdleR", true);
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
					_rigidbody->ClearVelocity();
					_Ground_check = true;
					_SkyGround_check = true;
			;		_rigidbody->SetGround(true);

					if (_State == Skul_Basic_State::JumpAttack || _State == Skul_Basic_State::Fall || _State == Skul_Basic_State::Falling)
					{
						_State = Skul_Basic_State::Idle;
						if (mDir == 1)
							at->PlayAnimation(L"Skul_BasicIdle", true);
						else
							at->PlayAnimation(L"Skul_BasicIdleR", true);
					}
				}				
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

		if (Ground_Map* mGround = dynamic_cast<Ground_Map*>(other->GetOwner()))
		{
			if (_Ground_check == false)
			{
				_Player_GRpos = pos;
				_fallcheck = 0;	_jump = 0;
				_rigidbody->SetGround(true);
				_Ground_check = true;				
				mGround->_SkullOn = true;
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
				_Player_GRpos = pos;
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

		if (Sky_Ground* mGround = dynamic_cast<Sky_Ground*>(other->GetOwner()))
		{
			Transform* Ground_TR = other->GetOwner()->GetComponent<Transform>();
			Collider2D* Ground_Col = other->GetOwner()->GetComponent<Collider2D>();
			Vector3 Ground_pos = Ground_TR->GetPosition();
			float Gr_Size = Ground_Col->GetScale().y / 2;
			float Gr_Top_pos = Ground_pos.y + Gr_Size +10;
			float Skul_halfsize = _collider->GetScale().y / 2;
			float skul_footpos = pos.y - Skul_halfsize;

			if (_SkyGround_check == true)
			{
				_Player_GRpos = pos;
				mGround->_SkullOn = true;
				_Ground_check = true;		
				_rigidbody->SetGround(true);
				if (_State == Skul_Basic_State::JumpAttack || _State == Skul_Basic_State::Fall || _State == Skul_Basic_State::Falling)
				{
					_State = Skul_Basic_State::Idle;
					if (mDir == 1)
						at->PlayAnimation(L"Skul_BasicIdle", true);
					else
						at->PlayAnimation(L"Skul_BasicIdleR", true);
				}

				if (Input::GetKey(eKeyCode::V))
				{
					_rigidbody->SetVelocity(Vector2(0.f, -150.f));
					_Ground_check = false;
					_rigidbody->SetGround(false);
					_SkyGround_check = false;
				}
			}

			
		}
	}
	void Skul_Basic::OnCollisionExit(Collider2D* other)
	{
		if (Ground_and_Wall* mGround = dynamic_cast<Ground_and_Wall*>(other->GetOwner()))
		{
			_Wall_check = false;
			_Rightmove_Lock = false;
			_Leftmove_Lock = false;
		}

		if (Ground_Map* mGround = dynamic_cast<Ground_Map*>(other->GetOwner()))
		{
			_Ground_check = false;
			mGround->_SkullOn = false;
			_rigidbody->SetGround(false);
		}
		 
		if (Sky_Ground* mGround = dynamic_cast<Sky_Ground*>(other->GetOwner()))
		{
			_Ground_check = false;
			mGround->_SkullOn = false;
			_rigidbody->SetGround(false);
		}


	}


	void Skul_Basic::attack_choice()
	{
		_attack_Acheck = false;
		_attack_Bcheck = false;
		Hit_Box->SetState(eState::Paused);
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
		if (_Leftmove_Lock == false)
		{
			if (Input::GetKey(eKeyCode::LEFT))
			{
				mDir = -1;
				pos.x -= 150.0f * Time::DeltaTime();
				//_rigidbody->SetVelocity(Vector2(-150.f, 0.f));
			}
		}
		if (_Rightmove_Lock == false)
		{
			if (Input::GetKey(eKeyCode::RIGHT))
			{
				mDir = 1;
				pos.x += 150.0f * Time::DeltaTime();
				//_rigidbody->SetVelocity(Vector2(150.f, 0.f));
			}
		}
		if (Input::GetKey(eKeyCode::DOWN))
		{
			_rigidbody->SetGround(true);
			_Ground_check = true;
			pos.y -= 100.0f * Time::DeltaTime();
		}
		
		if (Input::GetKey(eKeyCode::UP))
		{
			_rigidbody->SetGround(true);
			_Ground_check = true;
			pos.y += 100.0f * Time::DeltaTime();
		}
		

		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			//SetPlay_List(PlayerList::wolf_Skul,PlayerList::basic_Skul, true, mDir);
			SetPlay_List(PlayerList::spere_Skul, PlayerList::basic_Skul, true, mDir);
			//SetPlay_List(PlayerList::sowrd_Skul, PlayerList::basic_Skul, true, mDir);
			//SetPlay_List(PlayerList::thief_Skul, PlayerList::basic_Skul, true, mDir);
			pos.y = pos.y + 5;
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
