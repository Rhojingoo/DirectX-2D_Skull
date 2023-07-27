#include "Skul_Spear.h"
#include "jkInput.h"
#include "jkTime.h"


namespace jk
{
	int Skul_Spear::mDir = 1;

	Skul_Spear::Skul_Spear()
		: _attack(0)
		, _time(0.f)
		, _State(Skul_Spear_State::Idle)
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
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Spear\\AttackB", this) ;
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Spear\\AttackC", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Spear\\Dash", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Spear\\Fall", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Spear\\FallRepeat", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Spear\\Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Spear\\Jump", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Spear\\JumpAttack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Spear\\Skill", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Spear\\Switch", this);
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
		//at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Spear\\Switch", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Spear\\Walk", this, 1);


		//´ë½¬
		//at->PlayAnimation(L"Skul_BasicDash", true);
		//at->PlayAnimation(L"Skul_BasicDashR", true);			



		at->PlayAnimation(L"SpearSkill", true);
		at->CompleteEvent(L"SpearAttackA") = std::bind(&Skul_Spear::attack_choice, this);
		at->CompleteEvent(L"SpearAttackAR") = std::bind(&Skul_Spear::attack_choice, this);
		at->CompleteEvent(L"SpearAttackB") = std::bind(&Skul_Spear::attack_choice, this);
		at->CompleteEvent(L"SpearAttackBR") = std::bind(&Skul_Spear::attack_choice, this);
		at->CompleteEvent(L"SpearAttackC") = std::bind(&Skul_Spear::attack_choice, this);
		at->CompleteEvent(L"SpearAttackCR") = std::bind(&Skul_Spear::attack_choice, this);
		//at->CompleteEvent(L"Skul_BasicDash") = std::bind(&Skul_Basic::dash_check, this);
		//at->CompleteEvent(L"Skul_BasicDashR") = std::bind(&Skul_Basic::dash_check, this);
		GameObject::Initialize();
	}
	void Skul_Spear::Update()
	{
		tr = GetComponent<Transform>();
		pos = tr->GetPosition();


		switch (_State)
		{
		case jk::Skul_Spear::Skul_Spear_State::Idle:idle();
			break;

		case jk::Skul_Spear::Skul_Spear_State::Move:move();
			break;

		case jk::Skul_Spear::Skul_Spear_State::Jump:jump();
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

		case jk::Skul_Spear::Skul_Spear_State::Death:death();
			break;

		default:
			break;
		}
		Input_move();
		tr->SetPosition(pos);

		GameObject::Update();
	}
	void Skul_Spear::LateUpdate()
	{
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
	}
	void Skul_Spear::jump()
	{
	}
	void Skul_Spear::falling()
	{
	}
	void Skul_Spear::dash()
	{
		_time += Time::DeltaTime();
		if (_time > 0.7f)
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
			_time = 0;
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
	}
	void Skul_Spear::skill_b()
	{
	}

	void Skul_Spear::death()
	{
	}
	void Skul_Spear::OnCollisionEnter(Collider2D* other)
	{
	}
	void Skul_Spear::OnCollisionStay(Collider2D* other)
	{
	}
	void Skul_Spear::OnCollisionExit(Collider2D* other)
	{
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
		if (Input::GetKey(eKeyCode::LEFT))
		{

			pos.x -= 150.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			//_rigidbody->SetFriction(100.f);
			//_rigidbody->AddForce(Vector2(150.f, 0.f));
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
			if (mDir == 1)
				_rigidbody->AddForce(Vector2(50.f, 150.f));
			else
				_rigidbody->AddForce(Vector2(-55.f, 150.f));
			_rigidbody->SetGround(false);
		}

		if (Input::GetKey(eKeyCode::C))
		{
			_rigidbody->AddForce(Vector2(0.f, 180.f));
			_rigidbody->SetGround(false);
		}		
	}
}