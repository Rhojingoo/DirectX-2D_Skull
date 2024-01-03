#include "Skul_Sword.h"

namespace jk
{
	int Skul_Sword::mDir = 1;
	bool Skul_Sword::_switch = false;

	Skul_Sword::Skul_Sword()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Basic_Skul"));
	}
	Skul_Sword::~Skul_Sword()
	{
	}
	void Skul_Sword::Initialize()
	{
		CameraScript* cam = AddComponent<CameraScript>();
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\AttackA", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\AttackB", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\AttackC", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\Dash", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\Fall", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\FallRepeat", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\Jump", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\JumpAttack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\SkillA", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\SkillB", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\SlashBack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\SlashFront", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\Switch", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\Walk", this);


		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\AttackA", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\AttackB", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\AttackC", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\Dash", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\Fall", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\FallRepeat", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\Idle", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\Jump", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\JumpAttack", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\SkillA", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\SkillB", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\SlashBack", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\SlashFront", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\Switch", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\Walk", this, 1);


		at->CompleteEvent(L"SwordAttackA") = std::bind(&Skul_Sword::attack_A_choice, this);
		at->CompleteEvent(L"SwordAttackAR") = std::bind(&Skul_Sword::attack_A_choice, this);
		at->CompleteEvent(L"SwordAttackB") = std::bind(&Skul_Sword::attack_B_choice, this);
		at->CompleteEvent(L"SwordAttackBR") = std::bind(&Skul_Sword::attack_B_choice, this);
		at->CompleteEvent(L"SwordAttackC") = std::bind(&Skul_Sword::attack_B_choice, this);
		at->CompleteEvent(L"SwordAttackCR") = std::bind(&Skul_Sword::attack_B_choice, this);
		at->CompleteEvent(L"SwordSwitch") = std::bind(&Skul_Sword::switch_on_off, this);
		at->CompleteEvent(L"SwordSwitchR") = std::bind(&Skul_Sword::switch_on_off, this);
		at->PlayAnimation(L"SwordIdle", true);

		GameObject::Initialize();
	}
	void Skul_Sword::Update()
	{
		tr = GetComponent<Transform>();
		pos = tr->GetPosition();
		_velocity = _rigidbody->GetVelocity();

		if (_switch == true)
		{
			_State = Skul_Sword_State::Switch;
			if (mDir == 1)
				at->PlayAnimation(L"SwordSwitch", true);
			else
				at->PlayAnimation(L"SwordSwitchR", true);
		}

		switch (_State)
		{
		case jk::Skul_Sword::Skul_Sword_State::Idle:
			idle();
			break;

		case jk::Skul_Sword::Skul_Sword_State::Move:
			move();
			break;

		case jk::Skul_Sword::Skul_Sword_State::Jump:
			jump();
			break;

		case jk::Skul_Sword::Skul_Sword_State::Fall:
			fall();
			break;

		case jk::Skul_Sword::Skul_Sword_State::Falling:
			falling();
			break;

		case jk::Skul_Sword::Skul_Sword_State::Dash:
			dash();
			break;

		case jk::Skul_Sword::Skul_Sword_State::Attack_A:
			attack_a();
			break;

		case jk::Skul_Sword::Skul_Sword_State::Attack_B:
			attack_b();
			break;

		case jk::Skul_Sword::Skul_Sword_State::Attack_C:
			attack_c();
			break;

		case jk::Skul_Sword::Skul_Sword_State::JumpAttack:
			jumpattack();
			break;

		case jk::Skul_Sword::Skul_Sword_State::Skill_A:
			skill_a();
			break;

		case jk::Skul_Sword::Skul_Sword_State::Skill_B:
			skill_b();
			break;

		case jk::Skul_Sword::Skul_Sword_State::Switch:
			change();
			break;

		case jk::Skul_Sword::Skul_Sword_State::Death:
			death();
			break;

		default:
			break;
		}

		Input_move();
		tr->SetPosition(pos);
		GameObject::Update();
	}
	void Skul_Sword::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.05f));
		_collider->SetCenter(Vector2(0.0f, -0.1f));
		GameObject::LateUpdate();
	}
	void Skul_Sword::Render()
	{
		GameObject::Render();
	}


	void Skul_Sword::idle()
	{
		if (Input::GetKey(eKeyCode::RIGHT)
			|| Input::GetKey(eKeyCode::LEFT))
		{
			_State = Skul_Sword_State::Move;
			if (Input::GetKey(eKeyCode::RIGHT))
			{
				at->PlayAnimation(L"SwordWalk", true);
				mDir = 1;
			}
			else if (Input::GetKey(eKeyCode::LEFT))
			{
				at->PlayAnimation(L"SwordWalkR", true);
				mDir = -1;
			}
		}

		if (Input::GetKey(eKeyCode::A))
		{
			Skul_Sword_State::Skill_A;
			if (mDir == 1)
			{
				at->PlayAnimation(L"SwordSkillA", true); mDir = 1;
				_rigidbody->SetVelocity(Vector2(300.f, 0.f));
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"SwordSkillAR", true); mDir = -1;
				_rigidbody->SetVelocity(Vector2(-300.f, 0.f));
			}
		}

		if (Input::GetKey(eKeyCode::S))
		{
			_State = Skul_Sword_State::Skill_B;
			if (mDir == 1)
			{
				at->PlayAnimation(L"SwordAttackA", true);
				mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"SwordAttackAR", true);
				mDir = -1;
			}
		}

		if (Input::GetKey(eKeyCode::X))
		{
			_State = Skul_Sword_State::Attack_A;
			if (mDir == 1)
			{
				at->PlayAnimation(L"SwordAttackA", true);
				mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"SwordAttackAR", true);
				mDir = -1;
			}
		}

		if (Input::GetKeyDown(eKeyCode::C))
		{
			_State = Skul_Sword_State::Jump;
			if (mDir == 1)
			{
				at->PlayAnimation(L"SwordJump", true);

				_rigidbody->SetVelocity(Vector2(0.f, 250.f));
				_rigidbody->SetGround(false);	mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"SwordJumpR", true);

				_rigidbody->SetVelocity(Vector2(0.f, 250.f));
				_rigidbody->SetGround(false);	mDir = -1;
			}
			_jump++;
		}

		if (Input::GetKeyDown(eKeyCode::Z))
		{
			_State = Skul_Sword_State::Dash;
			if (mDir == 1)
			{
				at->PlayAnimation(L"SwordDash", false);
				_rigidbody->SetVelocity(Vector2(250.f, 0.f));
				mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"SwordDashR", false);
				_rigidbody->SetVelocity(Vector2(-250.f, 0.f));
				mDir = -1;
			}
		}
	}
	void Skul_Sword::move()
	{
		if (Input::GetKeyUp(eKeyCode::RIGHT)
			|| Input::GetKeyUp(eKeyCode::LEFT))
		{
			_State = Skul_Sword_State::Idle;
			if (Input::GetKeyUp(eKeyCode::RIGHT))
			{
				at->PlayAnimation(L"SwordIdle", true);
				mDir = 1;
			}
			else if (Input::GetKeyUp(eKeyCode::LEFT))
			{
				at->PlayAnimation(L"SwordIdleR", true);
				mDir = -1;
			}
		}

		if (Input::GetKey(eKeyCode::A))
		{
			Skul_Sword_State::Skill_A;
			if (mDir == 1)
			{
				at->PlayAnimation(L"SwordSkill", true); mDir = 1;
				_rigidbody->SetVelocity(Vector2(300.f, 0.f));
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"SwordSkillR", true); mDir = -1;
				_rigidbody->SetVelocity(Vector2(-300.f, 0.f));
			}
		}

		if (Input::GetKey(eKeyCode::S))
		{
			_State = Skul_Sword_State::Skill_B;
			if (mDir == 1)
			{
				at->PlayAnimation(L"SwordAttackA", true);
				mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"SwordAttackAR", true);
				mDir = -1;
			}
		}

		if (Input::GetKey(eKeyCode::X))
		{
			_State = Skul_Sword_State::Attack_A;
			if (mDir == 1)
			{
				at->PlayAnimation(L"SwordAttackA", true);
				mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"SwordAttackAR", true);
				mDir = -1;
			}
		}

		if (Input::GetKeyDown(eKeyCode::C))
		{
			_State = Skul_Sword_State::Jump;
			if (mDir == 1)
			{
				at->PlayAnimation(L"SwordJump", true);

				_rigidbody->SetVelocity(Vector2(0.f, 250.f));
				_rigidbody->SetGround(false);	mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"SwordJumpR", true);

				_rigidbody->SetVelocity(Vector2(0.f, 250.f));
				_rigidbody->SetGround(false);	mDir = -1;
			}
			_jump++;
		}

		if (Input::GetKeyDown(eKeyCode::Z))
		{
			_State = Skul_Sword_State::Dash;
			if (mDir == 1)
			{
				at->PlayAnimation(L"SwordDash", false);
				_rigidbody->SetVelocity(Vector2(250.f, 0.f));
				mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"SwordDashR", false);
				_rigidbody->SetVelocity(Vector2(-250.f, 0.f));
				mDir = -1;
			}
		}
	}
	void Skul_Sword::jump()
	{
		_Ground_check = false;
		if ((_velocity.y <= 0.f) || (_jump >= 2))
		{
			_State = Skul_Sword_State::Fall;
			if (mDir == 1)
			{
				at->PlayAnimation(L"SwordFall", false);

				mDir = 1;
			}
			if (mDir == -1)
			{
				at->PlayAnimation(L"SwordFallR", false);
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
				_State = Skul_Sword_State::JumpAttack;
				at->PlayAnimation(L"SwordJumpAttack", true);
			}
			if (mDir == -1)
			{
				_State = Skul_Sword_State::JumpAttack;
				at->PlayAnimation(L"SwordJumpAttackR", true);
			}
		}

		if (Input::GetKeyDown(eKeyCode::Z))
		{
			_State = Skul_Sword_State::Dash;
			if (mDir == 1)
			{
				at->PlayAnimation(L"SwordDash", true);

				_rigidbody->SetVelocity(Vector2(250.f, 0.f));
				mDir = 1;
			}
			if (mDir == -1)
			{
				at->PlayAnimation(L"SwordDashR", true);
				_rigidbody->SetVelocity(Vector2(-250.f, 0.f));
				mDir = -1;
			}
		}
	}
	void Skul_Sword::fall()
	{
		_Ground_check = false;
		_time += static_cast<float>(Time::DeltaTime());
		if (_time > 2.f)
		{
			_State = Skul_Sword_State::Falling;
			if (mDir == 1)
			{
				at->PlayAnimation(L"SwordFallRepeat", true);
				mDir = 1;  _fallcheck = 2;
			}
			if (mDir == -1)
			{
				at->PlayAnimation(L"SwordFallRepeatR", true);
				mDir = -1; _fallcheck = 2;
			}
			_time = 0;
		}
		if (Input::GetKeyDown(eKeyCode::X))
		{
			if (mDir == 1)
			{
				_State = Skul_Sword_State::JumpAttack;
				at->PlayAnimation(L"SwordJumpAttack", true);
			}
			if (mDir == -1)
			{
				_State = Skul_Sword_State::JumpAttack;
				at->PlayAnimation(L"SwordJumpAttackR", true);
			}
		}

		if (Input::GetKeyDown(eKeyCode::Z))
		{
			_State = Skul_Sword_State::Dash;
			if (mDir == 1)
			{
				at->PlayAnimation(L"SwordDash", true);
				_rigidbody->SetVelocity(Vector2(250.f, 0.f));
				mDir = 1;
			}
			if (mDir == -1)
			{
				at->PlayAnimation(L"SwordDashR", true);
				_rigidbody->SetVelocity(Vector2(-250.f, 0.f));
				mDir = -1;
			}
		}
	}
	void Skul_Sword::falling()
	{
		_Ground_check = false;
		if (Input::GetKeyDown(eKeyCode::X))
		{
			if (mDir == 1)
			{
				_State = Skul_Sword_State::JumpAttack;
				at->PlayAnimation(L"SwordJumpAttack", true);	
			}
			if (mDir == -1)
			{
				_State = Skul_Sword_State::JumpAttack;
				at->PlayAnimation(L"SwordJumpAttackR", true);
			}
		}

		if (Input::GetKeyDown(eKeyCode::Z))
		{
			_State = Skul_Sword_State::Dash;
			if (mDir == 1)
			{
				at->PlayAnimation(L"SwordDash", true);
				_rigidbody->SetVelocity(Vector2(250.f, 0.f));
				mDir = 1;
			}
			if (mDir == -1)
			{
				at->PlayAnimation(L"SwordDashR", true);
				_rigidbody->SetVelocity(Vector2(-250.f, 0.f));
				mDir = -1;
			}
		}
	}
	void Skul_Sword::dash()
	{
		_Ground_check = false;
		_rigidbody->ClearVelocityY();
		if (mDir == 1 && _velocity.x <= 220.f)
		{
			_State = Skul_Sword_State::Idle;
			at->PlayAnimation(L"SwordIdle", true);
			_rigidbody->SetGround(false);
			_rigidbody->ClearVelocityX();
			mDir = 1;
		}
		else if (mDir == -1 && _velocity.x >= -220.f)
		{
			_State = Skul_Sword_State::Idle;
			at->PlayAnimation(L"SwordIdleR", true);
			_rigidbody->SetGround(false);
			_rigidbody->ClearVelocityX();
			mDir = -1;
		}
	}

	void Skul_Sword::attack_a()
	{
		if (Input::GetKeyDown(eKeyCode::X))
		{
			_attackB = true;
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
	void Skul_Sword::attack_b()
	{
		_attackB = false;
		if (Input::GetKeyDown(eKeyCode::X))
		{
			_attackC = true;
		}
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mDir = 1;
		}
		else if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mDir = -1;
		}
		int a = 0;
	}
	void Skul_Sword::attack_c()
	{
		_attackC = false;
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mDir = 1;
		}
		else if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mDir = -1;
		}
	}
	void Skul_Sword::jumpattack()
	{
	}
	void Skul_Sword::skill_a()
	{
		_Ground_check = false;
		_rigidbody->ClearVelocityY();
		if (mDir == 1 && _velocity.x <= 280.0)
		{
			_State = Skul_Sword_State::Idle;
			at->PlayAnimation(L"SwordIdle", true);
			_rigidbody->SetGround(false);
			_rigidbody->ClearVelocityX();
			mDir = 1;
		}
		else if (mDir == -1 && _velocity.x >= -280.0)
		{
			_State = Skul_Sword_State::Idle;
			at->PlayAnimation(L"SwordIdleR", true);
			_rigidbody->SetGround(false);
			_rigidbody->ClearVelocityX();
			mDir = -1;
		}
	}
	void Skul_Sword::skill_b()
	{
	}
	void Skul_Sword::change()
	{
		_switch = false;
	}
	void Skul_Sword::death()
	{
	}

	void Skul_Sword::OnCollisionEnter(Collider2D* other)
	{
	}
	void Skul_Sword::OnCollisionStay(Collider2D* other)
	{
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{
			if (_Ground_check == false)
			{
				_fallcheck = 0;	_jump = 0;
				_rigidbody->SetGround(true);
				_Ground_check = true;
				_Ground_check = _rigidbody->GetGround();

				if (_State == Skul_Sword_State::JumpAttack || _State == Skul_Sword_State::Fall || _State == Skul_Sword_State::Falling)
				{
					_State = Skul_Sword_State::Idle;
					if (mDir == 1)
						at->PlayAnimation(L"SwordIdle", true);
					else
						at->PlayAnimation(L"SwordIdleR", true);
				}
			}
			else
			{
				if (Input::GetKeyDown(eKeyCode::Z))
				{
					_State = Skul_Sword_State::Dash;
					if (mDir == 1)
					{
						at->PlayAnimation(L"SwordDash", true);
						_rigidbody->SetVelocity(Vector2(250.f, 0.f));
						mDir = 1;
					}
					if (mDir == -1)
					{
						at->PlayAnimation(L"SwordDashR", true);
						_rigidbody->SetVelocity(Vector2(-250.f, 0.f));
						mDir = -1;
					}
				}
			}
		}
	}
	void Skul_Sword::OnCollisionExit(Collider2D* other)
	{
	}

	void Skul_Sword::attack_A_choice()
	{
		//_attack_Acheck = false;
		//_attack_Bcheck = false;
		//Hit_Box->SetState(eState::Paused);
		if (_attackB == true)
		{
			_State = Skul_Sword_State::Attack_B;
			if (mDir == 1)
			{
				at->PlayAnimation(L"SwordAttackB", true);
				mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"SwordAttackBR", true);
				mDir = -1;
			}			
		}
		if (_attackB == false)
		{
			if (Input::GetKeyDown(eKeyCode::Z))
			{
				_State = Skul_Sword_State::Dash;
				if (mDir == 1)
				{
					at->PlayAnimation(L"SwordDash", false);
					mDir = 1;
				}
				else if (mDir == -1)
				{
					at->PlayAnimation(L"SwordDashR", false);
					mDir = -1;
				}
			}

			if (Input::GetKey(eKeyCode::RIGHT)
				|| Input::GetKey(eKeyCode::LEFT))
			{
				_State = Skul_Sword_State::Move;
				if (Input::GetKey(eKeyCode::RIGHT))
				{
					at->PlayAnimation(L"SwordWalk", true);
					mDir = 1;
				}
				else if (Input::GetKey(eKeyCode::LEFT))
				{
					at->PlayAnimation(L"SwordWalkR", true);
					mDir = -1;
				}
			}
			else
			{
				_State = Skul_Sword_State::Idle;
				if (mDir == 1)
				{
					at->PlayAnimation(L"SwordIdle", true);
					mDir = 1;
				}
				else if (mDir == -1)
				{
					at->PlayAnimation(L"SwordIdleR", true);
					mDir = -1;
				}
			}
		}
	}
	void Skul_Sword::attack_B_choice()
	{
		//_attack_Acheck = false;
		//_attack_Bcheck = false;
		//Hit_Box->SetState(eState::Paused);
		if (_attackC == true)
		{
			_State = Skul_Sword_State::Attack_C;
			if (mDir == 1)
			{
				at->PlayAnimation(L"SwordAttackC", true);
				mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"SwordAttackCR", true);
				mDir = -1;
			}
		}
		if (_attackC == false)
		{
			if (Input::GetKeyDown(eKeyCode::Z))
			{
				_State = Skul_Sword_State::Dash;
				if (mDir == 1)
				{
					at->PlayAnimation(L"SwordDash", false);
					mDir = 1;
				}
				else if (mDir == -1)
				{
					at->PlayAnimation(L"SwordDashR", false);
					mDir = -1;
				}
			}

			if (Input::GetKey(eKeyCode::RIGHT)
				|| Input::GetKey(eKeyCode::LEFT))
			{
				_State = Skul_Sword_State::Move;
				if (Input::GetKey(eKeyCode::RIGHT))
				{
					at->PlayAnimation(L"SwordWalk", true);
					mDir = 1;
				}
				else if (Input::GetKey(eKeyCode::LEFT))
				{
					at->PlayAnimation(L"SwordWalkR", true);
					mDir = -1;
				}
			}
			else
			{
				_State = Skul_Sword_State::Idle;
				if (mDir == 1)
				{
					at->PlayAnimation(L"SwordIdle", true);
					mDir = 1;
				}
				else if (mDir == -1)
				{
					at->PlayAnimation(L"SwordIdleR", true);
					mDir = -1;
				}
			}
		}
	}
	void Skul_Sword::Input_move()
	{
		if (Input::GetKey(eKeyCode::LEFT))
		{
			mDir = -1;
			pos.x -= 150.0f * static_cast<float>(Time::DeltaTime());
		}
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			mDir = 1;
			pos.x += 150.0f * static_cast<float>(Time::DeltaTime());
		}
		if (Input::GetKey(eKeyCode::DOWN))
			pos.y -= 100.0f * static_cast<float>(Time::DeltaTime());

		if (Input::GetKey(eKeyCode::UP))
			pos.y += 100.0f * static_cast<float>(Time::DeltaTime());


		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			//SetPlay_List(PlayerList::wolf_Skul,PlayerList::basic_Skul, true, _Dir);
			SetPlay_List(PlayerList::basic_Skul, PlayerList::sowrd_Skul, true, mDir);
			SetPlayer_Pos(pos);
		}
	}
	void Skul_Sword::switch_on_off()
	{
		if (_switch == false)
		{
			_State = Skul_Sword_State::Idle;
			if (mDir == 1)
			{
				at->PlayAnimation(L"SwordIdle", true);
				mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"SwordIdleR", true);
				mDir = -1;
			}
			_rigidbody->ClearVelocity();
		}
	}
	//void Skul_Sword::attack_choice()
	//{
	//	
	//	if (_attack == true)
	//	{
	//		_State = Skul_Basic_State::Attack_B;
	//		if (_Dir == 1)
	//		{
	//			at->PlayAnimation(L"Skul_BasicAttackB", true);
	//			_Dir = 1;
	//		}
	//		else if (_Dir == -1)
	//		{
	//			at->PlayAnimation(L"Skul_BasicAttackBR", true);
	//			_Dir = -1;
	//		}
	//	}
	//	if (_attack == false)
	//	{
	//		if (Input::GetKeyDown(eKeyCode::Z))
	//		{
	//			_State = Skul_Basic_State::Dash;
	//			if (_Dir == 1)
	//			{
	//				at->PlayAnimation(L"Skul_BasicDash", false);
	//				_Dir = 1;
	//			}
	//			else if (_Dir == -1)
	//			{
	//				at->PlayAnimation(L"Skul_BasicDashR", false);
	//				_Dir = -1;
	//			}
	//		}
	//		if (_fallcheck == 1)
	//		{
	//			_State = Skul_Basic_State::Fall;
	//			if (_Dir == 1)
	//			{
	//				at->PlayAnimation(L"Skul_BasicFall", false);
	//			}
	//			else if (_Dir == -1)
	//			{
	//				at->PlayAnimation(L"Skul_BasicFallR", false);
	//			}
	//		}
	//		if (_fallcheck == 2)
	//		{
	//			_State = Skul_Basic_State::Falling;
	//			if (_Dir == 1)
	//			{
	//				at->PlayAnimation(L"Skul_BasicFallRepeat", true);
	//				_Dir = 1;
	//			}
	//			else if (_Dir == -1)
	//			{
	//				at->PlayAnimation(L"Skul_BasicFallRepeatR", true);
	//				_Dir = -1;
	//			}
	//		}
	//		if (Input::GetKey(eKeyCode::RIGHT)
	//			|| Input::GetKey(eKeyCode::LEFT))
	//		{
	//			_State = Skul_Basic_State::Move;
	//			if (Input::GetKey(eKeyCode::RIGHT))
	//			{
	//				at->PlayAnimation(L"Skul_BasicWalk", true);
	//				_Dir = 1;
	//			}
	//			else if (Input::GetKey(eKeyCode::LEFT))
	//			{
	//				at->PlayAnimation(L"Skul_BasicWalkR", true);
	//				_Dir = -1;
	//			}
	//		}
	//		else
	//		{
	//			_State = Skul_Basic_State::Idle;
	//			if (_Dir == 1)
	//			{
	//				at->PlayAnimation(L"Skul_BasicIdle", true);
	//				if (_Skulhead == true)
	//					at->PlayAnimation(L"NoHeadIdle", true);
	//				_Dir = 1;
	//			}
	//			else if (_Dir == -1)
	//			{
	//				at->PlayAnimation(L"Skul_BasicIdleR", true);
	//				if (_Skulhead == true)
	//					at->PlayAnimation(L"NoHeadIdleR", true);
	//				_Dir = -1;
	//			}
	//		}
	//	}
	//}
}