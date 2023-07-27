#include "Skul_Basic.h"
#include "jktime.h"

namespace jk
{
	Skul_Basic::Skul_Basic()
		: mDir(1)
		, _attack(0)
		, _time(0.f)
		, _State(Skul_Basic_State::Idle)
		, at(nullptr)
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Basic_Skul"));
		//RigidBody* mRigidBody = AddComponent<RigidBody>();
		//Vector2 mSize = mr->GetMaterial()->GetTexture()->GetTexSize();
		//GetComponent<Transform>()->SetScale(Vector3(mSize.x, mSize.y, 1.0f));
	}
	Skul_Basic::~Skul_Basic()
	{
	}
	void Skul_Basic::Initialize()
	{
		/*at = AddComponent<Animator>();
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
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\Walk", this, 1);*/


		//´ë½¬
		//at->PlayAnimation(L"Skul_BasicDash", true);
		//at->PlayAnimation(L"Skul_BasicDashR", true);			



		//at->PlayAnimation(L"Skul_BasicIdle", true);
		//at->CompleteEvent(L"Skul_BasicAttackA") = std::bind(&Skul_Basic::attack_choice, this);		
		//at->CompleteEvent(L"Skul_BasicAttackAR") = std::bind(&Skul_Basic::attack_choice, this);
		//at->CompleteEvent(L"Skul_BasicAttackB") = std::bind(&Skul_Basic::attack_choice, this);
		//at->CompleteEvent(L"Skul_BasicAttackBR") = std::bind(&Skul_Basic::attack_choice, this);
		//at->CompleteEvent(L"Skul_BasicDash") = std::bind(&Skul_Basic::dash_check, this);
		//at->CompleteEvent(L"Skul_BasicDashR") = std::bind(&Skul_Basic::dash_check, this);
		GameObject::Initialize();
	}

	void Skul_Basic::Update()
	{
		switch (_State)
		{
		case jk::Skul_Basic::Skul_Basic_State::Idle:idle();
			break;

		case jk::Skul_Basic::Skul_Basic_State::Move:move();
			break;

		case jk::Skul_Basic::Skul_Basic_State::Jump:jump();
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

		case jk::Skul_Basic::Skul_Basic_State::Death:death();
			break;

		default:
			break;
		}
		GameObject::Update();
	}
	void Skul_Basic::LateUpdate()
	{
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
				mDir = 1;
			}
			else if (Input::GetKey(eKeyCode::LEFT))
			{
				at->PlayAnimation(L"Skul_BasicWalkR", true);
				mDir = -1;
			}
		}

		if (Input::GetKey(eKeyCode::X))
		{
			_State = Skul_Basic_State::Attack_A;
			if (mDir == 1)
			{
				at->PlayAnimation(L"Skul_BasicAttackA", true);
				mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"Skul_BasicAttackAR", true);
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
				mDir = 1;
			}
			else if (Input::GetKeyUp(eKeyCode::LEFT))
			{
				at->PlayAnimation(L"Skul_BasicIdleR", true);
				mDir = -1;
			}
		}

		if (Input::GetKey(eKeyCode::X))
		{
			_State = Skul_Basic_State::Attack_A;
			if (mDir == 1)
			{
				at->PlayAnimation(L"Skul_BasicAttackA", true);
				mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"Skul_BasicAttackAR", true);
				mDir = -1;
			}
		}

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
	}
	void Skul_Basic::jump()
	{
	}
	void Skul_Basic::falling()
	{
	}
	void Skul_Basic::dash()
	{
		_time += Time::DeltaTime();
		if (_time > 0.7f)
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
			_time = 0;
		}
	}
	void Skul_Basic::attack_a()
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
	void Skul_Basic::attack_b()
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
	void Skul_Basic::jumpattack()
	{
	}
	void Skul_Basic::skill_a()
	{
	}
	void Skul_Basic::skill_b()
	{
	}
	void Skul_Basic::death()
	{

	}

	void Skul_Basic::OnCollisionEnter(Collider2D* other)
	{
	}

	void Skul_Basic::OnCollisionStay(Collider2D* other)
	{
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
					mDir = 1;
				}
				else if (mDir == -1)
				{
					at->PlayAnimation(L"Skul_BasicIdleR", true);
					mDir = -1;
				}
			}
		}
	}
	void Skul_Basic::dash_check()
	{
	}
	void Skul_Basic::Input_move()
	{
	}
}
