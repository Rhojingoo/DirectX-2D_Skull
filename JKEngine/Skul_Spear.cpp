#include "Skul_Spear.h"
#include "jkInput.h"
#include "jkTime.h"


namespace jk
{
	int Skul_Spear::mDir = 1;
	bool Skul_Spear::_switch = false;

	Skul_Spear::Skul_Spear()
		: _State(Skul_Spear_State::Idle)
		, at(nullptr)
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Basic_Skul"));
	}
	Skul_Spear::~Skul_Spear()
	{
	}
	void Skul_Spear::Initialize()
	{
		CameraScript* cam = AddComponent<CameraScript>();
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Spear\\AttackA", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Spear\\AttackB", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Spear\\AttackC", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Spear\\Dash", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Spear\\Fall", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Spear\\FallRepeat", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Spear\\Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Spear\\Jump", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Spear\\JumpAttack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Spear\\Skill", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Spear\\Switch", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Spear\\Walk", this);


		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Spear\\AttackA", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Spear\\AttackB", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Spear\\AttackC", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Spear\\Dash", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Spear\\Fall", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Spear\\FallRepeat", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Spear\\Idle", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Spear\\Jump", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Spear\\JumpAttack", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Spear\\Skill", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Spear\\Switch", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Spear\\Walk", this, 1);


		//대쉬
		//at->PlayAnimation(L"Skul_BasicDash", true);
		//at->PlayAnimation(L"Skul_BasicDashR", true);			

		at->PlayAnimation(L"SpearSkill", true);
		at->CompleteEvent(L"SpearAttackA") = std::bind(&Skul_Spear::attack_choice, this);
		at->CompleteEvent(L"SpearAttackAR") = std::bind(&Skul_Spear::attack_choice, this);
		at->CompleteEvent(L"SpearAttackB") = std::bind(&Skul_Spear::attack_choice, this);
		at->CompleteEvent(L"SpearAttackBR") = std::bind(&Skul_Spear::attack_choice, this);
		at->CompleteEvent(L"SpearAttackC") = std::bind(&Skul_Spear::attack_choice, this);
		at->CompleteEvent(L"SpearAttackCR") = std::bind(&Skul_Spear::attack_choice, this);	
		at->CompleteEvent(L"SpearSwitch") = std::bind(&Skul_Spear::switch_on_off, this);
		at->CompleteEvent(L"SpearSwitchR") = std::bind(&Skul_Spear::switch_on_off, this);



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
	void Skul_Spear::Update()
	{
		tr = GetComponent<Transform>();
		pos = tr->GetPosition();
		_velocity = _rigidbody->GetVelocity();

		if (_switch == true)
		{
			_State = Skul_Spear_State::Switch;
			if (mDir == 1)
				at->PlayAnimation(L"SpearSwitch", true);
			else
				at->PlayAnimation(L"SpearSwitchR", true);
		}

	
		switch (_State)
		{
		case jk::Skul_Spear::Skul_Spear_State::Idle:idle();
			break;

		case jk::Skul_Spear::Skul_Spear_State::Move:move();
			break;

		case jk::Skul_Spear::Skul_Spear_State::Jump:jump();
			break;

		case jk::Skul_Spear::Skul_Spear_State::Fall:fall();
			break;

		case jk::Skul_Spear::Skul_Spear_State::Falling:falling();
			break;

		case jk::Skul_Spear::Skul_Spear_State::Dash:dash();
			break;

		case jk::Skul_Spear::Skul_Spear_State::Attack_A:attack_a();
			break;

		case jk::Skul_Spear::Skul_Spear_State::Attack_B:attack_b();
			break;

		case jk::Skul_Spear::Skul_Spear_State::JumpAttack:jumpattack();
			break;

		case jk::Skul_Spear::Skul_Spear_State::Skill_A:skill_a();
			break;

		case jk::Skul_Spear::Skul_Spear_State::Skill_B:skill_b();
			break;

		case jk::Skul_Spear::Skul_Spear_State::Switch:change();
			break;

		case jk::Skul_Spear::Skul_Spear_State::Death:death();
			break;

		default:
			break;
		}
		Input_move();
		_Pos = pos;
		tr->SetPosition(pos);

		GameObject::Update();
	}
	void Skul_Spear::LateUpdate()
	{
		_collider->SetSize(Vector2(0.35f, 0.55f));
		_collider->SetCenter(Vector2(0.0f, -0.1f));
		GameObject::LateUpdate();
	}

	void Skul_Spear::Render()
	{
		GameObject::Render();
	}

	void Skul_Spear::idle()
	{
		if (Input::GetKey(eKeyCode::RIGHT)
			|| Input::GetKey(eKeyCode::LEFT))
		{
			_State = Skul_Spear_State::Move;
			if (Input::GetKey(eKeyCode::RIGHT))
			{
				at->PlayAnimation(L"SpearWalk", true);
				mDir = 1;
			}
			else if (Input::GetKey(eKeyCode::LEFT))
			{
				at->PlayAnimation(L"SpearWalkR", true);
				mDir = -1;
			}
		}

			if (Input::GetKey(eKeyCode::A))
			{
				_State = Skul_Spear_State::Skill_A;
				if (mDir == 1)
				{
					at->PlayAnimation(L"SpearSkill", true); mDir = 1;
					_rigidbody->SetVelocity(Vector2(300.f, 0.f));
				}
				else if (mDir == -1)
				{
					at->PlayAnimation(L"SpearSkillR", true); mDir = -1;
					_rigidbody->SetVelocity(Vector2(-300.f, 0.f));
				}
			}
			//if (Input::GetKey(eKeyCode::S))
			//{
			//	_State = Skul_Wolf_State::Skill_B;
			//	if (_Dir == 1)
			//	{
			//		at->PlayAnimation(L"WolfSkillB", true); _Dir = 1;
			//		_rigidbody->SetVelocity(Vector2(100.f, 0.f));
			//	}
			//	else if (_Dir == -1)
			//	{
			//		at->PlayAnimation(L"WolfSkillBR", true); _Dir = -1;
			//		_rigidbody->SetVelocity(Vector2(-100.f, 0.f));
			//	}
			//}



		if (Input::GetKey(eKeyCode::X))
		{
			_State = Skul_Spear_State::Attack_A;
			if (mDir == 1)
			{
				at->PlayAnimation(L"SpearAttackA", true);
				mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"SpearAttackAR", true);
				mDir = -1;
			}
		}

		if (Input::GetKeyDown(eKeyCode::C))
		{
			_State = Skul_Spear_State::Jump;
			if (mDir == 1)
			{
				at->PlayAnimation(L"SpearJump", true);

				_rigidbody->SetVelocity(Vector2(0.f, 400.f));
				_rigidbody->SetGround(false);	mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"SpearJumpR", true);

				_rigidbody->SetVelocity(Vector2(0.f, 400.f));
				_rigidbody->SetGround(false);	mDir = -1;
			}
			_jump++;
		}

		if (Input::GetKeyDown(eKeyCode::Z))
		{
			_State = Skul_Spear_State::Dash;
			if (mDir == 1)
			{
				at->PlayAnimation(L"SpearDash", false);
				_rigidbody->SetVelocity(Vector2(250.f, 0.f));
				mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"SpearDashR", false);
				_rigidbody->SetVelocity(Vector2(-250.f, 0.f));
				mDir = -1;
			}
		}
	}

	void Skul_Spear::move()
	{
		if (Input::GetKeyUp(eKeyCode::RIGHT)
			|| Input::GetKeyUp(eKeyCode::LEFT))
		{
			_State = Skul_Spear_State::Idle;
			if (Input::GetKeyUp(eKeyCode::RIGHT))
			{
				at->PlayAnimation(L"SpearIdle", true);
				mDir = 1;
			}
			else if (Input::GetKeyUp(eKeyCode::LEFT))
			{
				at->PlayAnimation(L"SpearIdleR", true);
				mDir = -1;
			}
		}

		if (Input::GetKey(eKeyCode::X))
		{
			_State = Skul_Spear_State::Attack_A;
			if (mDir == 1)
			{
				at->PlayAnimation(L"SpearAttackA", true);
				mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"SpearAttackAR", true);
				mDir = -1;
			}
		}

		if (Input::GetKeyDown(eKeyCode::C))
		{
			_State = Skul_Spear_State::Jump;
			if (mDir == 1)
			{
				at->PlayAnimation(L"SpearJump", true);

				_rigidbody->SetVelocity(Vector2(0.f, 400.f));
				_rigidbody->SetGround(false);	mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"SpearJumpR", true);

				_rigidbody->SetVelocity(Vector2(0.f, 400.f));
				_rigidbody->SetGround(false);	mDir = -1;
			}
			_jump++;
		}

		if (Input::GetKeyDown(eKeyCode::Z))
		{
			_State = Skul_Spear_State::Dash;
			if (mDir == 1)
			{
				at->PlayAnimation(L"SpearDash", false);
				_rigidbody->SetVelocity(Vector2(250.f, 0.f));
				mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"SpearDashR", false);
				_rigidbody->SetVelocity(Vector2(-250.f, 0.f));
				mDir = -1;
			}
		}
	}

	void Skul_Spear::jump()
	{
		_Ground_check = false;
		if ((_velocity.y <= 0.f) || (_jump >= 2))
		{
			_State = Skul_Spear_State::Fall;
			if (mDir == 1)
			{
				at->PlayAnimation(L"SpearFall", false);
				mDir = 1;
			}
			if (mDir == -1)
			{
				at->PlayAnimation(L"SpearFallR", false);
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
					at->PlayAnimation(L"SpearJump", true);

					_rigidbody->SetVelocity(Vector2(0.f, 400.f));
					_rigidbody->SetGround(false);	mDir = 1;
				}
				else if (mDir == -1)
				{
					at->PlayAnimation(L"SpearJumpR", true);

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
				_State = Skul_Spear_State::JumpAttack;
				at->PlayAnimation(L"SpearJumpAttack", true);
			}

			if (mDir == -1)
			{
				_State = Skul_Spear_State::JumpAttack;
				at->PlayAnimation(L"SpearJumpAttackR", true);
			}
		}

		if (Input::GetKeyDown(eKeyCode::Z))
		{
			_State = Skul_Spear_State::Dash;
			if (mDir == 1)
			{
				at->PlayAnimation(L"SpearDash", false);
				_rigidbody->SetVelocity(Vector2(250.f, 150.f));
				_rigidbody->SetGround(false);	mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"SpearDashR", false);
				_rigidbody->SetVelocity(Vector2(-250.f, 150.f));
				_rigidbody->SetGround(false);	mDir = -1;
			}
		}
	}

	void Skul_Spear::fall()
	{
		_time += static_cast<float>(Time::DeltaTime());
		if (_time > 2.f)
		{
			_State = Skul_Spear_State::Falling;
			if (mDir == 1)
			{
				at->PlayAnimation(L"SpearFallRepeat", true);
				mDir = 1;  _fallcheck = 2;
			}
			if (mDir == -1)
			{
				at->PlayAnimation(L"SpearFallRepeatR", true);
				mDir = -1; _fallcheck = 2;
			}
			_time = 0;
		}


		if (_jump < 3)
		{
			if (Input::GetKeyDown(eKeyCode::C))
			{
				if (mDir == 1)
				{
					at->PlayAnimation(L"SpearJump", true);

					_rigidbody->SetVelocity(Vector2(0.f, 400.f));
					_rigidbody->SetGround(false);	mDir = 1;
				}
				else if (mDir == -1)
				{
					at->PlayAnimation(L"SpearJumpR", true);

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
				_State = Skul_Spear_State::JumpAttack;
				at->PlayAnimation(L"SpearJumpAttack", true);
			}
			if (mDir == -1)
			{
				_State = Skul_Spear_State::JumpAttack;
				at->PlayAnimation(L"SpearJumpAttackR", true);
			}
		}

		if (Input::GetKeyDown(eKeyCode::Z))
		{
			_State = Skul_Spear_State::Dash;
			if (mDir == 1)
			{
				at->PlayAnimation(L"SpearDash", true);
				_rigidbody->SetVelocity(Vector2(250.f, 0.f));
				mDir = 1;
			}
			if (mDir == -1)
			{
				at->PlayAnimation(L"SpearDashR", true);
				_rigidbody->SetVelocity(Vector2(-250.f, 0.f));
				mDir = -1;
			}
		}
	}

	void Skul_Spear::falling()
	{

		if (_jump < 3)
		{
			if (Input::GetKeyDown(eKeyCode::C))
			{
				if (mDir == 1)
				{
					at->PlayAnimation(L"SpearJump", true);

					_rigidbody->SetVelocity(Vector2(0.f, 400.f));
					_rigidbody->SetGround(false);	mDir = 1;
				}
				else if (mDir == -1)
				{
					at->PlayAnimation(L"SpearJumpR", true);

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
				_State = Skul_Spear_State::JumpAttack;
				at->PlayAnimation(L"SpearJumpAttack", true);
			}
			if (mDir == -1)
			{
				_State = Skul_Spear_State::JumpAttack;
				at->PlayAnimation(L"SpearJumpAttackR", true);
			}
		}

		if (Input::GetKeyDown(eKeyCode::Z))
		{
			_State = Skul_Spear_State::Dash;
			if (mDir == 1)
			{
				at->PlayAnimation(L"SpearDash", true);
				_rigidbody->SetVelocity(Vector2(250.f, 0.f));
				mDir = 1;
			}
			if (mDir == -1)
			{
				at->PlayAnimation(L"SpearDashR", true);
				_rigidbody->SetVelocity(Vector2(-250.f, 0.f));
				mDir = -1;
			}
		}
	}

	void Skul_Spear::dash()
	{
		_Ground_check = false;
		_rigidbody->ClearVelocityY();
		if (mDir == 1 && _velocity.x <= 220.0)
		{
			_State = Skul_Spear_State::Idle;
			at->PlayAnimation(L"SpearIdle", true);
			_rigidbody->SetGround(false);
			_rigidbody->ClearVelocityX();
			mDir = 1;
		}
		else if (mDir == -1 && _velocity.x >= -220.0)
		{
			_State = Skul_Spear_State::Idle;
			at->PlayAnimation(L"SpearIdleR", true);
			_rigidbody->SetGround(false);
			_rigidbody->ClearVelocityX();
			mDir = -1;
		}
		{
			timeSinceLastImage += static_cast<float>(Time::DeltaTime());
			if (timeSinceLastImage >= delayBetweenImages)
			{
				for (int i = 0; i < 10; i++)
				{
					if (AfterImage_TEST[i]->_AfterImage == false)
					{
						int direction = (mDir == 1) ? 1 : -1;
						AfterImage_TEST[i]->Set_Spear_Dash(direction, Vector3(pos.x, pos.y, pos.z + 1));
						AfterImage_TEST[i]->SetState(eState::Active);
						AfterImage_TEST[i]->_AfterImage = true;
						timeSinceLastImage = 0.0f;  // 시간 초기화
						break;  // 하나의 잔상만 생성한 후 for문 종료					
					}
				}
			}
		}
	}

	void Skul_Spear::attack_a()
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

	void Skul_Spear::attack_b()
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

	void Skul_Spear::attack_c()
	{
	}

	void Skul_Spear::jumpattack()
	{
	}

	void Skul_Spear::skill_a()
	{
		_Ground_check = false;
		_rigidbody->ClearVelocityY();
		if (mDir == 1 && _velocity.x <= 280.0)
		{
			_State = Skul_Spear_State::Idle;
			at->PlayAnimation(L"SpearIdle", true);
			_rigidbody->SetGround(false);
			_rigidbody->ClearVelocityX();
			mDir = 1;
		}
		else if (mDir == -1 && _velocity.x >= -280.0)
		{
			_State = Skul_Spear_State::Idle;
			at->PlayAnimation(L"SpearIdleR", true);
			_rigidbody->SetGround(false);
			_rigidbody->ClearVelocityX();
			mDir = -1;
		}
	}

	void Skul_Spear::skill_b()
	{
	}

	void Skul_Spear::change()
	{
		if (_switch == true)
		{	
			if (mDir == 1)
			{
				_rigidbody->SetVelocity(Vector2(250.f, 0.f));
				_switch = false; 
			}
			else
			{
				_rigidbody->SetVelocity(Vector2(-250.f, 0.f));
				_switch = false;
			}
		}
	}

	void Skul_Spear::death()
	{
	}

	void Skul_Spear::OnCollisionEnter(Collider2D* other)
	{
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
					_rigidbody->SetGround(true);

					if (_State == Skul_Spear_State::JumpAttack || _State == Skul_Spear_State::Fall || _State == Skul_Spear_State::Falling)
					{
						_State = Skul_Spear_State::Idle;
						if (mDir == 1)
							at->PlayAnimation(L"SpearIdle", true);
						else
							at->PlayAnimation(L"SpearIdleR", true);
					}
				}
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
					at->PlayAnimation(L"SpearIdle", true);
				}
				else if (pos.x > wall_pos.x)
				{
					_Leftmove_Lock = true;
					at->PlayAnimation(L"SpearIdleR", true);
				}
			}
		}		
	}

	void Skul_Spear::OnCollisionStay(Collider2D* other)
	{
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{
			if (_Ground_check == false)
			{
				_fallcheck = 0;	_jump = 0;
				_rigidbody->SetGround(true);
				_Ground_check = true;
				_Ground_check = _rigidbody->GetGround();

				if (_State == Skul_Spear_State::JumpAttack || _State == Skul_Spear_State::Fall || _State == Skul_Spear_State::Falling)
				{
					_State = Skul_Spear_State::Idle;
					if (mDir == 1)
						at->PlayAnimation(L"SpearIdle", true);
					else
						at->PlayAnimation(L"SpearIdleR", true);
				}
			}
			else
			{
				if (Input::GetKeyDown(eKeyCode::Z))
				{
					_State = Skul_Spear_State::Dash;
					if (mDir == 1)
					{
						at->PlayAnimation(L"SpearDash", true);
						_rigidbody->SetVelocity(Vector2(250.f, 0.f));
						mDir = 1;
					}
					if (mDir == -1)
					{
						at->PlayAnimation(L"SpearDashR", true);
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
				_fallcheck = 0;	_jump = 0;
				_rigidbody->SetGround(true);
				_Ground_check = true;
				_Ground_check = _rigidbody->GetGround();

				if (_State == Skul_Spear_State::JumpAttack || _State == Skul_Spear_State::Fall || _State == Skul_Spear_State::Falling)
				{
					_State = Skul_Spear_State::Idle;
					if (mDir == 1)
						at->PlayAnimation(L"SpearIdle", true);
					else
						at->PlayAnimation(L"SpearIdleR", true);
				}
			}
			else
			{
				if (Input::GetKeyDown(eKeyCode::Z))
				{
					_State = Skul_Spear_State::Dash;
					if (mDir == 1)
					{
						at->PlayAnimation(L"SpearDash", true);
						_rigidbody->SetVelocity(Vector2(250.f, 0.f));
						mDir = 1;
					}
					if (mDir == -1)
					{
						at->PlayAnimation(L"SpearDashR", true);
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
			float Gr_Top_pos = Ground_pos.y + Gr_Size + 10;
			float Skul_halfsize = _collider->GetScale().y / 2;
			float skul_footpos = pos.y - Skul_halfsize;

			if (_Ground_check == false)
			{
				if (skul_footpos > Gr_Top_pos)
				{					
					_Ground_check = true;
					_rigidbody->SetGround(true);
					if (_State == Skul_Spear_State::JumpAttack || _State == Skul_Spear_State::Fall || _State == Skul_Spear_State::Falling)
					{
						_State = Skul_Spear_State::Idle;
						if (mDir == 1)
							at->PlayAnimation(L"SpearIdle", true);
						else
							at->PlayAnimation(L"SpearIdleR", true);
					}
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

	void Skul_Spear::OnCollisionExit(Collider2D* other)
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
			_rigidbody->SetGround(false);
		}

		if (Sky_Ground* mGround = dynamic_cast<Sky_Ground*>(other->GetOwner()))
		{
			_Ground_check = false;
			_rigidbody->SetGround(false);
		}
	}

	void Skul_Spear::attack_choice()
	{
		if (_attack == true)
		{
			_State = Skul_Spear_State::Attack_B;
			if (mDir == 1)
			{
				at->PlayAnimation(L"SpearAttackC", true);
				mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"SpearAttackCR", true);
				mDir = -1;
			}
		}
		if (_attack == false)
		{
			if (Input::GetKeyDown(eKeyCode::Z))
			{
				_State = Skul_Spear_State::Dash;
				if (mDir == 1)
				{
					at->PlayAnimation(L"SpearDash", false);
					mDir = 1;
				}
				else if (mDir == -1)
				{
					at->PlayAnimation(L"SpearDashR", false);
					mDir = -1;
				}
			}

			if (Input::GetKey(eKeyCode::RIGHT)
				|| Input::GetKey(eKeyCode::LEFT))
			{
				_State = Skul_Spear_State::Move;
				if (Input::GetKey(eKeyCode::RIGHT))
				{
					at->PlayAnimation(L"SpearWalk", true);
					mDir = 1;
				}
				else if (Input::GetKey(eKeyCode::LEFT))
				{
					at->PlayAnimation(L"SpearWalkR", true);
					mDir = -1;
				}
			}
			else
			{
				_State = Skul_Spear_State::Idle;
				if (mDir == 1)
				{
					at->PlayAnimation(L"SpearIdle", true);
					mDir = 1;
				}
				else if (mDir == -1)
				{
					at->PlayAnimation(L"SpearIdleR", true);
					mDir = -1;
				}
			}
		}
	}

	void Skul_Spear::dash_check()
	{
	}

	void Skul_Spear::Input_move()
	{

		if (_Leftmove_Lock == false)
		{
			if (Input::GetKey(eKeyCode::LEFT))
			{
				mDir = -1;
				pos.x -= 150.0f * static_cast<float>(Time::DeltaTime());
			}
		}
		if (_Rightmove_Lock == false)
		{
			if (Input::GetKey(eKeyCode::RIGHT))
			{
				mDir = 1;
				pos.x += 150.0f * static_cast<float>(Time::DeltaTime());
			}
		}

		if (Input::GetKey(eKeyCode::DOWN))
			pos.y -= 100.0f * static_cast<float>(Time::DeltaTime());

		if (Input::GetKey(eKeyCode::UP))
			pos.y += 100.0f * static_cast<float>(Time::DeltaTime());

		//if (Input::GetKeyDown(eKeyCode::C))
		//{
		//	_rigidbody->AddForce(Vector2(0.f, 350.f));
		//	_rigidbody->SetGround(false);
		//}

		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			SetPlay_List(PlayerList::basic_Skul, PlayerList::spere_Skul, true, mDir);
			SetPlayer_Pos(pos);
		}
	}

	void jk::Skul_Spear::switch_on_off()
	{
		if (_switch == false)
		{
			_Ground_check = false;			
			_rigidbody->ClearVelocityY();
			if (mDir == 1 && _velocity.x <= 220.0)
			{
				_State = Skul_Spear_State::Idle;
				at->PlayAnimation(L"SpearIdle", true);
				_rigidbody->SetGround(false);
				_rigidbody->ClearVelocityX();
				mDir = 1;
			}
			else if (mDir == -1 && _velocity.x >= -220.0)
			{
				_State = Skul_Spear_State::Idle;
				at->PlayAnimation(L"SpearIdleR", true);
				_rigidbody->SetGround(false);
				_rigidbody->ClearVelocityX();
				mDir = -1;
			}
			
		}
	}
}