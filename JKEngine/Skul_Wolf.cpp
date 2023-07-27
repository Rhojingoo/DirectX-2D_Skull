#include "Skul_Wolf.h"

namespace jk
{
	Skul_Wolf::Skul_Wolf()
		: mDir(1)
		, _attack(0)
		, _time(0.f)
		, _State(Skul_Wolf_State::Idle)
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


		//´ë½¬
		//at->PlayAnimation(L"Skul_BasicDash", true);
		//at->PlayAnimation(L"Skul_BasicDashR", true);			



		at->PlayAnimation(L"WolfIdle", true);
		at->CompleteEvent(L"WolfAttackA") = std::bind(&Skul_Wolf::attack_choice, this);
		at->CompleteEvent(L"WolfAttackAR") = std::bind(&Skul_Wolf::attack_choice, this);
		at->CompleteEvent(L"WolfAttackB") = std::bind(&Skul_Wolf::attack_choice, this);
		at->CompleteEvent(L"WolfAttackBR") = std::bind(&Skul_Wolf::attack_choice, this);
		//at->CompleteEvent(L"Skul_BasicDash") = std::bind(&Skul_Basic::dash_check, this);
		//at->CompleteEvent(L"Skul_BasicDashR") = std::bind(&Skul_Basic::dash_check, this);
		GameObject::Initialize();
	}
	void Skul_Wolf::Update()
	{
		 tr = GetComponent<Transform>();
		 pos = tr->GetPosition();


		switch (_State)
		{
		case jk::Skul_Wolf::Skul_Wolf_State::Idle:idle();
			break;

		case jk::Skul_Wolf::Skul_Wolf_State::Move:move();
			break;

		case jk::Skul_Wolf::Skul_Wolf_State::Jump:jump();
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

		case jk::Skul_Wolf::Skul_Wolf_State::Death:death();
			break;

		default:
			break;
		}
		
		Input_move();
		tr->SetPosition(pos);

		GameObject::Update();
	}
	void Skul_Wolf::LateUpdate()
	{
		_collider->SetSize(Vector2(0.07f, 0.05f));
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

		//if (Input::GetKeyDown(eKeyCode::C))
		//{
		//	_State = Skul_Basic_State::Jump;
		//	//if (mDir == 1)
		//	//{
		//	//	mAnimator->Play(L"", true);
		//	//	mDir = 1;
		//	//}
		//	//else if (mDir == -1)
		//	//{
		//	//	mAnimator->Play(L"", true);
		//	//	mDir = -1;
		//	//}
		//}

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
	}
	void Skul_Wolf::jump()
	{
	}
	void Skul_Wolf::falling()
	{
	}
	void Skul_Wolf::dash()
	{
		_time += Time::DeltaTime();
		if (_time > 0.7f)
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
			_time = 0;
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
	void Skul_Wolf::death()
	{
	}
	void Skul_Wolf::OnCollisionEnter(Collider2D* other)
	{
		int a;
		
		if (Input::GetKey(eKeyCode::Z)|| (Input::GetKey(eKeyCode::C)))
			_rigidbody->SetGround(false);
		else
		_rigidbody->SetGround(true);

	}
	void Skul_Wolf::OnCollisionStay(Collider2D* other)
	{
	}
	void Skul_Wolf::OnCollisionExit(Collider2D* other)
	{
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
		if (Input::GetKey(eKeyCode::LEFT))
		{

			pos.x -= 150.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			_rigidbody->SetFriction(100.f);
			_rigidbody->AddForce(Vector2(150.f, 0.f));
			pos.x += 150.0f * Time::DeltaTime();
			
		}
		if (Input::GetKey(eKeyCode::DOWN))
		{
			pos.y -= 100.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::UP))
		{
			pos.y += 100.0f * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::Z))
		{
			if(mDir == 1)
			_rigidbody->AddForce(Vector2(550.f, 1500.f));
			else
			_rigidbody->AddForce(Vector2(-550.f, 1500.f));
			_rigidbody->SetGround(false);
		}

		if (Input::GetKey(eKeyCode::C))
		{
			_rigidbody->AddForce(Vector2(0.f, 1800.f));
			_rigidbody->SetGround(false);

		}
	}
}