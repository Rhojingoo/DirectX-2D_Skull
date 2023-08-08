#include "Skul_Thief.h"

namespace jk
{
	int Skul_Thief::mDir = 1;
	bool Skul_Thief::_switch = false;

	Skul_Thief::Skul_Thief()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Basic_Skul"));
	}
	Skul_Thief::~Skul_Thief()
	{
	}
	void Skul_Thief::Initialize()
	{
		CameraScript* cam = AddComponent<CameraScript>();
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);


		at = AddComponent<Animator>();

		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Thief\\AttackA", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Thief\\AttackB", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Thief\\Dash", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Thief\\Fall", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Thief\\FallRepeat", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Thief\\Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Thief\\Jump", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Thief\\JumpAttack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Thief\\SkillA_Attack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Thief\\SkillA_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Thief\\SkillB", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Thief\\SkillC_Attack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Thief\\SkillC_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Thief\\Switch", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Thief\\Walk", this);


		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Thief\\AttackA", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Thief\\AttackB", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Thief\\Dash", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Thief\\Fall", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Thief\\FallRepeat", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Thief\\Idle", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Thief\\Jump", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Thief\\JumpAttack", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Thief\\SkillA_Attack", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Thief\\SkillA_Ready", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Thief\\SkillB", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Thief\\SkillC_Attack", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Thief\\SkillC_Ready", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Thief\\Switch", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Thief\\Walk", this, 1);
		

		at->CompleteEvent(L"ThiefSwitch") = std::bind(&Skul_Thief::switch_on_off, this);
		at->CompleteEvent(L"ThiefSwitchR") = std::bind(&Skul_Thief::switch_on_off, this);
		at->CompleteEvent(L"ThiefAttackA") = std::bind(&Skul_Thief::attack_choice, this);
		at->CompleteEvent(L"ThiefAttackAR") = std::bind(&Skul_Thief::attack_choice, this);
		at->CompleteEvent(L"ThiefAttackB") = std::bind(&Skul_Thief::attack_choice, this);
		at->CompleteEvent(L"ThiefAttackBR") = std::bind(&Skul_Thief::attack_choice, this);
		//at->CompleteEvent(L"SwordSwitch") = std::bind(&Skul_Thief::switch_on_off, this);
		//at->CompleteEvent(L"SwordSwitchR") = std::bind(&Skul_Thief::switch_on_off, this);
		//at->CompleteEvent(L"SwordAttackA") = std::bind(&Skul_Sword::AttackACompleteEvent, this);
		//at->CompleteEvent(L"SwordAttackB") = std::bind(&Skul_Sword::AttackBCompleteEvent, this);
		//at->CompleteEvent(L"SwordAttackC") = std::bind(&Skul_Sword::AttackCCompleteEvent, this);

		at->PlayAnimation(L"ThiefIdle", true);

		GameObject::Initialize();
	}
	void Skul_Thief::Update()
	{
		tr = GetComponent<Transform>();
		pos = tr->GetPosition();
		_velocity = _rigidbody->GetVelocity();

		if (_switch == true)
		{
			_State = Skul_Thief_State::Switch;
			if (mDir == 1)
				at->PlayAnimation(L"ThiefSwitch", true);
			else
				at->PlayAnimation(L"ThiefSwitchR", true);
		}
		
		switch (_State)
		{
		case jk::Skul_Thief::Skul_Thief_State::Idle:
			idle();
			break;

		case jk::Skul_Thief::Skul_Thief_State::Move:
			move();
			break;

		case jk::Skul_Thief::Skul_Thief_State::Jump:
			jump();
			break;

		case jk::Skul_Thief::Skul_Thief_State::Fall:
			fall();
			break;

		case jk::Skul_Thief::Skul_Thief_State::Falling:
			falling();
			break;

		case jk::Skul_Thief::Skul_Thief_State::Dash:
			dash();
			break;

		case jk::Skul_Thief::Skul_Thief_State::Attack_A:
			attack_a();
			break;

		case jk::Skul_Thief::Skul_Thief_State::Attack_B:
			attack_b();
			break;

		case jk::Skul_Thief::Skul_Thief_State::JumpAttack:
			jumpattack();
			break;

		case jk::Skul_Thief::Skul_Thief_State::Skill_A:
			skill_a();
			break;

		case jk::Skul_Thief::Skul_Thief_State::Skill_B:
			skill_b();
			break;

		case jk::Skul_Thief::Skul_Thief_State::Switch:
			change();
			break;

		case jk::Skul_Thief::Skul_Thief_State::Death:
			death();
			break;

		default:
			break;
		}

		Input_move();
		tr->SetPosition(pos);
		GameObject::Update();
	}
	void Skul_Thief::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.05f));
		_collider->SetCenter(Vector2(0.0f, -0.1f));
		GameObject::LateUpdate();
	}
	void Skul_Thief::Render()
	{
		GameObject::Render();
	}

	void Skul_Thief::idle()
	{
		if (Input::GetKey(eKeyCode::RIGHT)
			|| Input::GetKey(eKeyCode::LEFT))
		{
			_State = Skul_Thief_State::Move;
			if (Input::GetKey(eKeyCode::RIGHT))
			{
				at->PlayAnimation(L"ThiefWalk", true);
				mDir = 1;
			}
			else if (Input::GetKey(eKeyCode::LEFT))
			{
				at->PlayAnimation(L"ThiefWalkR", true);
				mDir = -1;
			}
		}

		/*if (Input::GetKey(eKeyCode::A))
		{
			Skul_Thief_State::Skill_A;
			if (mDir == 1)
			{
				at->PlayAnimation(L"ThiefSkillA", true); mDir = 1;
				_rigidbody->SetVelocity(Vector2(300.f, 0.f));
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"ThiefSkillAR", true); mDir = -1;
				_rigidbody->SetVelocity(Vector2(-300.f, 0.f));
			}
		}

		if (Input::GetKey(eKeyCode::S))
		{
			_State = Skul_Thief_State::Skill_B;
			if (mDir == 1)
			{
				at->PlayAnimation(L"ThiefAttackA", true);
				mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"ThiefAttackAR", true);
				mDir = -1;
			}
		}*/

		if (Input::GetKey(eKeyCode::X))
		{
			_State = Skul_Thief_State::Attack_A;
			if (mDir == 1)
			{
				at->PlayAnimation(L"ThiefAttackA", true);
				mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"ThiefAttackAR", true);
				mDir = -1;
			}
		}

		if (Input::GetKeyDown(eKeyCode::C))
		{
			_State = Skul_Thief_State::Jump;
			if (mDir == 1)
			{
				at->PlayAnimation(L"ThiefJump", true);

				_rigidbody->SetVelocity(Vector2(0.f, 250.f));
				_rigidbody->SetGround(false);	mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"ThiefJumpR", true);

				_rigidbody->SetVelocity(Vector2(0.f, 250.f));
				_rigidbody->SetGround(false);	mDir = -1;
			}
			_jump++;
		}

		if (Input::GetKeyDown(eKeyCode::Z))
		{
			_State = Skul_Thief_State::Dash;
			if (mDir == 1)
			{
				at->PlayAnimation(L"ThiefDash", false);
				_rigidbody->SetVelocity(Vector2(250.f, 0.f));
				mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"ThiefDashR", false);
				_rigidbody->SetVelocity(Vector2(-250.f, 0.f));
				mDir = -1;
			}
		}
	}
	void Skul_Thief::move()
	{
		if (Input::GetKeyUp(eKeyCode::RIGHT)
			|| Input::GetKeyUp(eKeyCode::LEFT))
		{
			_State = Skul_Thief_State::Idle;
			if (Input::GetKeyUp(eKeyCode::RIGHT))
			{
				at->PlayAnimation(L"ThiefIdle", true);
				mDir = 1;
			}
			else if (Input::GetKeyUp(eKeyCode::LEFT))
			{
				at->PlayAnimation(L"ThiefIdleR", true);
				mDir = -1;
			}
		}

		//if (Input::GetKey(eKeyCode::A))
		//{
		//	Skul_Thief_State::Skill_A;
		//	if (mDir == 1)
		//	{
		//		at->PlayAnimation(L"ThiefSkill", true); mDir = 1;
		//		_rigidbody->SetVelocity(Vector2(300.f, 0.f));
		//	}
		//	else if (mDir == -1)
		//	{
		//		at->PlayAnimation(L"ThiefSkillR", true); mDir = -1;
		//		_rigidbody->SetVelocity(Vector2(-300.f, 0.f));
		//	}
		//}
		//if (Input::GetKey(eKeyCode::S))
		//{
		//	_State = Skul_Thief_State::Skill_B;
		//	if (mDir == 1)
		//	{
		//		at->PlayAnimation(L"ThiefAttackA", true);
		//		mDir = 1;
		//	}
		//	else if (mDir == -1)
		//	{
		//		at->PlayAnimation(L"ThiefAttackAR", true);
		//		mDir = -1;
		//	}
		//}


		if (Input::GetKey(eKeyCode::X))
		{
			_State = Skul_Thief_State::Attack_A;
			if (mDir == 1)
			{
				at->PlayAnimation(L"ThiefAttackA", true);
				mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"ThiefAttackAR", true);
				mDir = -1;
			}
		}

		if (Input::GetKeyDown(eKeyCode::C))
		{
			_State = Skul_Thief_State::Jump;
			if (mDir == 1)
			{
				at->PlayAnimation(L"ThiefJump", true);

				_rigidbody->SetVelocity(Vector2(0.f, 250.f));
				_rigidbody->SetGround(false);	mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"ThiefJumpR", true);

				_rigidbody->SetVelocity(Vector2(0.f, 250.f));
				_rigidbody->SetGround(false);	mDir = -1;
			}
			_jump++;
		}

		if (Input::GetKeyDown(eKeyCode::Z))
		{
			_State = Skul_Thief_State::Dash;
			if (mDir == 1)
			{
				at->PlayAnimation(L"ThiefDash", false);
				_rigidbody->SetVelocity(Vector2(250.f, 0.f));
				mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"ThiefDashR", false);
				_rigidbody->SetVelocity(Vector2(-250.f, 0.f));
				mDir = -1;
			}
		}
	}
	void Skul_Thief::jump()
	{
		_Ground_check = false;
		if ((_velocity.y <= 0.f) || (_jump >= 2))
		{
			_State = Skul_Thief_State::Fall;
			if (mDir == 1)
			{
				at->PlayAnimation(L"ThiefFall", false);

				mDir = 1;
			}
			if (mDir == -1)
			{
				at->PlayAnimation(L"ThiefFallR", false);
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
				_State = Skul_Thief_State::JumpAttack;
				at->PlayAnimation(L"ThiefJumpAttack", true);
			}
			if (mDir == -1)
			{
				_State = Skul_Thief_State::JumpAttack;
				at->PlayAnimation(L"ThiefJumpAttackR", true);
			}
		}

		if (Input::GetKeyDown(eKeyCode::Z))
		{
			_State = Skul_Thief_State::Dash;
			if (mDir == 1)
			{
				at->PlayAnimation(L"ThiefDash", true);

				_rigidbody->SetVelocity(Vector2(250.f, 0.f));
				mDir = 1;
			}
			if (mDir == -1)
			{
				at->PlayAnimation(L"ThiefDashR", true);
				_rigidbody->SetVelocity(Vector2(-250.f, 0.f));
				mDir = -1;
			}
		}
	}
	void Skul_Thief::fall()
	{
		_Ground_check = false;
		_time += Time::DeltaTime();
		if (_time > 2.f)
		{
			_State = Skul_Thief_State::Falling;
			if (mDir == 1)
			{
				at->PlayAnimation(L"ThiefFallRepeat", true);
				mDir = 1;  _fallcheck = 2;
			}
			if (mDir == -1)
			{
				at->PlayAnimation(L"ThiefFallRepeatR", true);
				mDir = -1; _fallcheck = 2;
			}
			_time = 0;
		}
		if (Input::GetKeyDown(eKeyCode::X))
		{
			if (mDir == 1)
			{
				_State = Skul_Thief_State::JumpAttack;
				at->PlayAnimation(L"ThiefJumpAttack", true);
			}
			if (mDir == -1)
			{
				_State = Skul_Thief_State::JumpAttack;
				at->PlayAnimation(L"ThiefJumpAttackR", true);
			}
		}

		if (Input::GetKeyDown(eKeyCode::Z))
		{
			_State = Skul_Thief_State::Dash;
			if (mDir == 1)
			{
				at->PlayAnimation(L"ThiefDash", true);
				_rigidbody->SetVelocity(Vector2(250.f, 0.f));
				mDir = 1;
			}
			if (mDir == -1)
			{
				at->PlayAnimation(L"ThiefDashR", true);
				_rigidbody->SetVelocity(Vector2(-250.f, 0.f));
				mDir = -1;
			}
		}
	}
	void Skul_Thief::falling()
	{
		_Ground_check = false;
		if (Input::GetKeyDown(eKeyCode::X))
		{
			if (mDir == 1)
			{
				_State = Skul_Thief_State::JumpAttack;
				at->PlayAnimation(L"ThiefJumpAttack", true);
			}
			if (mDir == -1)
			{
				_State = Skul_Thief_State::JumpAttack;
				at->PlayAnimation(L"ThiefJumpAttackR", true);
			}
		}

		if (Input::GetKeyDown(eKeyCode::Z))
		{
			_State = Skul_Thief_State::Dash;
			if (mDir == 1)
			{
				at->PlayAnimation(L"ThiefDash", true);
				_rigidbody->SetVelocity(Vector2(250.f, 0.f));
				mDir = 1;
			}
			if (mDir == -1)
			{
				at->PlayAnimation(L"ThiefDashR", true);
				_rigidbody->SetVelocity(Vector2(-250.f, 0.f));
				mDir = -1;
			}
		}
	}
	void Skul_Thief::dash()
	{
		_Ground_check = false;
		_rigidbody->ClearVelocityY();
		if (mDir == 1 && _velocity.x <= 220.f)
		{
			_State = Skul_Thief_State::Idle;
			at->PlayAnimation(L"ThiefIdle", true);
			_rigidbody->SetGround(false);
			_rigidbody->ClearVelocityX();
			mDir = 1;
		}
		else if (mDir == -1 && _velocity.x >= -220.f)
		{
			_State = Skul_Thief_State::Idle;
			at->PlayAnimation(L"ThiefIdleR", true);
			_rigidbody->SetGround(false);
			_rigidbody->ClearVelocityX();
			mDir = -1;
		}
	}
	void Skul_Thief::attack_a()
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
	void Skul_Thief::attack_b()
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
	void Skul_Thief::jumpattack()
	{
	}
	void Skul_Thief::skill_a()
	{
		_Ground_check = false;
		_rigidbody->ClearVelocityY();
		if (mDir == 1 && _velocity.x <= 280.0)
		{
			_State = Skul_Thief_State::Idle;
			at->PlayAnimation(L"ThiefIdle", true);
			_rigidbody->SetGround(false);
			_rigidbody->ClearVelocityX();
			mDir = 1;
		}
		else if (mDir == -1 && _velocity.x >= -280.0)
		{
			_State = Skul_Thief_State::Idle;
			at->PlayAnimation(L"ThiefIdleR", true);
			_rigidbody->SetGround(false);
			_rigidbody->ClearVelocityX();
			mDir = -1;
		}
	}
	void Skul_Thief::skill_b()
	{
	}
	void Skul_Thief::change()
	{
		_switch = false;
	}
	void Skul_Thief::death()
	{
	}


	void Skul_Thief::OnCollisionEnter(Collider2D* other)
	{
	}
	void Skul_Thief::OnCollisionStay(Collider2D* other)
	{
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{
			if (_Ground_check == false)
			{
				_fallcheck = 0;	_jump = 0;
				_rigidbody->SetGround(true);
				_Ground_check = true;
				_Ground_check = _rigidbody->GetGround();

				if (_State == Skul_Thief_State::JumpAttack || _State == Skul_Thief_State::Fall || _State == Skul_Thief_State::Falling)
				{
					_State = Skul_Thief_State::Idle;
					if (mDir == 1)
						at->PlayAnimation(L"ThiefIdle", true);
					else
						at->PlayAnimation(L"ThiefIdleR", true);
				}
			}
			else
			{
				if (Input::GetKeyDown(eKeyCode::Z))
				{
					_State = Skul_Thief_State::Dash;
					if (mDir == 1)
					{
						at->PlayAnimation(L"ThiefDash", true);
						_rigidbody->SetVelocity(Vector2(250.f, 0.f));
						mDir = 1;
					}
					if (mDir == -1)
					{
						at->PlayAnimation(L"ThiefDashR", true);
						_rigidbody->SetVelocity(Vector2(-250.f, 0.f));
						mDir = -1;
					}
				}
			}
		}
	}
	void Skul_Thief::OnCollisionExit(Collider2D* other)
	{
	}


	void Skul_Thief::attack_choice()
	{
		if (_attack == true)
		{
			_State = Skul_Thief_State::Attack_B;
			if (mDir == 1)
			{
				at->PlayAnimation(L"ThiefAttackB", true);
				mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"ThiefAttackBR", true);
				mDir = -1;
			}
		}
		if (_attack == false)
		{
			if (Input::GetKeyDown(eKeyCode::Z))
			{
				_State = Skul_Thief_State::Dash;
				if (mDir == 1)
				{
					at->PlayAnimation(L"ThiefDash", false);
					mDir = 1;
				}
				else if (mDir == -1)
				{
					at->PlayAnimation(L"ThiefDashR", false);
					mDir = -1;
				}
			}

			if (Input::GetKey(eKeyCode::RIGHT)
				|| Input::GetKey(eKeyCode::LEFT))
			{
				_State = Skul_Thief_State::Move;
				if (Input::GetKey(eKeyCode::RIGHT))
				{
					at->PlayAnimation(L"ThiefWalk", true);
					mDir = 1;
				}
				else if (Input::GetKey(eKeyCode::LEFT))
				{
					at->PlayAnimation(L"ThiefWalkR", true);
					mDir = -1;
				}
			}
			else
			{
				_State = Skul_Thief_State::Idle;
				if (mDir == 1)
				{
					at->PlayAnimation(L"ThiefIdle", true);
					mDir = 1;
				}
				else if (mDir == -1)
				{
					at->PlayAnimation(L"ThiefIdleR", true);
					mDir = -1;
				}
			}
		}
	}
	void Skul_Thief::Input_move()
	{
		if (Input::GetKey(eKeyCode::LEFT))
		{
			mDir = -1;
			pos.x -= 150.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			mDir = 1;
			pos.x += 150.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::DOWN))
			pos.y -= 100.0f * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::UP))
			pos.y += 100.0f * Time::DeltaTime();


		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			//SetPlay_List(PlayerList::wolf_Skul,PlayerList::basic_Skul, true, mDir);
			//SetPlay_List(PlayerList::basic_Skul, PlayerList::sowrd_Skul, true, mDir);
			SetPlay_List(PlayerList::basic_Skul, PlayerList::thief_Skul, true, mDir);
			SetPlayer_Pos(pos);
		}
	}
	void Skul_Thief::switch_on_off()
	{
		if (_switch == false)
		{
			_State = Skul_Thief_State::Idle;
			if (mDir == 1)
			{
				at->PlayAnimation(L"ThiefIdle", true);
				mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"ThiefIdleR", true);
				mDir = -1;
			}
			_rigidbody->ClearVelocity();
		}
	}
}