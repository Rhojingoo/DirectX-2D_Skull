#include "Skul_Wolf.h"



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

		//Vector2 mSize = mr->GetMaterial()->GetTexture()->GetTexSize();
		//GetComponent<Transform>()->SetScale(Vector3(mSize.x, mSize.y, 1.0f));
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
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Wolf\\AttackA", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Wolf\\AttackB", this);
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


		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Wolf\\AttackA", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Wolf\\AttackB", this, 1);
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

	void Skul_Wolf::OnCollisionEnter(Collider2D* other)
	{
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
			else
			{			
			}
		}
		
		if (Ground_Map* mGround = dynamic_cast<Ground_Map*>(other->GetOwner()))
		{
			if (_Ground_check == false)
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
			else
			{
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
					_Ground_check = true;
					_rigidbody->SetGround(true);
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
		if (Sky_Ground* mGround = dynamic_cast<Sky_Ground*>(other->GetOwner()))
		{
			_Ground_check = false;
			_rigidbody->SetGround(false);
		}
	}

	void Skul_Wolf::attack_choice()
	{
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