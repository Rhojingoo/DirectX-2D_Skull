////#include "Skul_nohead.h"
////#include "jkTime.h"
////
////namespace jk
////{
////	Skul_Nohead::Skul_Nohead()
////		: mDir(1)
////		, _attack(0)
////		, _time(0.f)
////		, _State(Skul_Nohead_State::Idle)
////		, at(nullptr)
////	{
////	}
////	Skul_Nohead::~Skul_Nohead()
////	{
////		MeshRenderer* mr = AddComponent<MeshRenderer>();
////		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
////		mr->SetMaterial(Resources::Find<Material>(L"Basic_Skul"));
////		//Vector2 mSize = mr->GetMaterial()->GetTexture()->GetTexSize();
////		//GetComponent<Transform>()->SetScale(Vector3(mSize.x, mSize.y, 1.0f));
////	}
////	void Skul_Nohead::Initialize()
////	{
//	/*	at = AddComponent<Animator>();
//		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Nohead\\AttackA", this);
//		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Nohead\\AttackB", this);
//		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Nohead\\Dash", this);
//		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Nohead\\Fall", this);
//		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Nohead\\FallRepeat", this);
//		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Nohead\\Idle", this);
//		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Nohead\\Jump", this);
//		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Nohead\\JumpAttack", this);
//		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Nohead\\Skill", this);
//		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Nohead\\Switch", this);
//		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Nohead\\Walk", this);
//
//
//		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Nohead\\AttackA", this, 1);
//		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Nohead\\AttackB", this, 1);
//		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Nohead\\Dash", this, 1);
//		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Nohead\\Fall", this, 1);
//		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Nohead\\FallRepeat", this, 1);
//		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Nohead\\Idle", this, 1);
//		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Nohead\\Jump", this, 1);
//		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Nohead\\JumpAttack", this, 1);
//		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Nohead\\Skill", this, 1);
//		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Nohead\\Switch", this, 1);
//		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Nohead\\Walk", this, 1);
//
//
//		at->PlayAnimation(L"Skul_NoheadIdle", true);
//		at->CompleteEvent(L"Skul_NoheadAttackA") = std::bind(&Skul_Nohead::attack_choice, this);
//		at->CompleteEvent(L"Skul_NoheadAttackAR") = std::bind(&Skul_Nohead::attack_choice, this);
//		at->CompleteEvent(L"Skul_NoheadAttackB") = std::bind(&Skul_Nohead::attack_choice, this);
//		at->CompleteEvent(L"Skul_NoheadAttackBR") = std::bind(&Skul_Nohead::attack_choice, this);*/
//
//		GameObject::Initialize();
//
//	}
//	void Skul_Nohead::Update()
//	{
//		switch (_State)
//		{
//		case jk::Skul_Nohead::Skul_Nohead_State::Idle:idle();
//			break;
//
//		case jk::Skul_Nohead::Skul_Nohead_State::Move:move();
//			break;
//
//		case jk::Skul_Nohead::Skul_Nohead_State::Jump:jump();
//			break;
//
//		case jk::Skul_Nohead::Skul_Nohead_State::Falling:falling();
//			break;
//
//		case jk::Skul_Nohead::Skul_Nohead_State::Dash:dash();
//			break;
//
//		case jk::Skul_Nohead::Skul_Nohead_State::Attack_A:attack_a();
//			break;
//
//		case jk::Skul_Nohead::Skul_Nohead_State::Attack_B:attack_b();
//			break;
//
//		case jk::Skul_Nohead::Skul_Nohead_State::JumpAttack:jumpattack();
//			break;
//
//		case jk::Skul_Nohead::Skul_Nohead_State::Skill_A:skill_a();
//			break;
//
//		case jk::Skul_Nohead::Skul_Nohead_State::Skill_B:skill_b();
//			break;
//
//		case jk::Skul_Nohead::Skul_Nohead_State::Death:death();
//			break;
//
//		default:
//			break;
//		}
//		GameObject::Update();
//	}
//	void Skul_Nohead::LateUpdate()
//	{
//		GameObject::LateUpdate();
//	}
//	void Skul_Nohead::Render()
//	{
//		GameObject::Render();
//	}
//	void Skul_Nohead::idle()
//	{
//		if (Input::GetKey(eKeyCode::RIGHT)
//			|| Input::GetKey(eKeyCode::LEFT))
//		{
//			_State = Skul_Nohead_State::Move;
//			if (Input::GetKey(eKeyCode::RIGHT))
//			{
//				at->PlayAnimation(L"Skul_NoheadWalk", true);
//				mDir = 1;
//			}
//			else if (Input::GetKey(eKeyCode::LEFT))
//			{
//				at->PlayAnimation(L"Skul_NoheadWalkR", true);
//				mDir = -1;
//			}
//		}
//
//		if (Input::GetKey(eKeyCode::X))
//		{
//			_State = Skul_Nohead_State::Attack_A;
//			if (mDir == 1)
//			{
//				at->PlayAnimation(L"Skul_NoheadAttackA", true);
//				mDir = 1;
//			}
//			else if (mDir == -1)
//			{
//				at->PlayAnimation(L"Skul_NoheadAttackAR", true);
//				mDir = -1;
//			}
//		}
//
//		//if (Input::GetKeyDown(eKeyCode::C))
//		//{
//		//	_State = Skul_Basic_State::Jump;
//		//	//if (mDir == 1)
//		//	//{
//		//	//	mAnimator->Play(L"", true);
//		//	//	mDir = 1;
//		//	//}
//		//	//else if (mDir == -1)
//		//	//{
//		//	//	mAnimator->Play(L"", true);
//		//	//	mDir = -1;
//		//	//}
//		//}
//
//		if (Input::GetKeyDown(eKeyCode::Z))
//		{
//			_State = Skul_Nohead_State::Dash;
//			if (mDir == 1)
//			{
//				at->PlayAnimation(L"Skul_NoheadDash", false);
//				mDir = 1;
//			}
//			else if (mDir == -1)
//			{
//				at->PlayAnimation(L"Skul_NoheadDashR", false);
//				mDir = -1;
//			}
//		}
//	}
//	void Skul_Nohead::move()
//	{
//		if (Input::GetKeyUp(eKeyCode::RIGHT)
//			|| Input::GetKeyUp(eKeyCode::LEFT))
//		{
//			_State = Skul_Nohead_State::Idle;
//			if (Input::GetKeyUp(eKeyCode::RIGHT))
//			{
//				at->PlayAnimation(L"Skul_NoheadIdle", true);
//				mDir = 1;
//			}
//			else if (Input::GetKeyUp(eKeyCode::LEFT))
//			{
//				at->PlayAnimation(L"Skul_NoheadIdleR", true);
//				mDir = -1;
//			}
//		}
//
//		if (Input::GetKey(eKeyCode::X))
//		{
//			_State = Skul_Nohead_State::Attack_A;
//			if (mDir == 1)
//			{
//				at->PlayAnimation(L"Skul_NoheadAttackA", true);
//				mDir = 1;
//			}
//			else if (mDir == -1)
//			{
//				at->PlayAnimation(L"Skul_NoheadAttackAR", true);
//				mDir = -1;
//			}
//		}
//
//		if (Input::GetKeyDown(eKeyCode::Z))
//		{
//			_State = Skul_Nohead_State::Dash;
//			if (mDir == 1)
//			{
//				at->PlayAnimation(L"Skul_NoheadDash", false);
//				mDir = 1;
//			}
//			else if (mDir == -1)
//			{
//				at->PlayAnimation(L"Skul_NoheadDashR", false);
//				mDir = -1;
//			}
//		}
//	}
//	void Skul_Nohead::jump()
//	{
//	}
//	void Skul_Nohead::falling()
//	{
//	}
//	void Skul_Nohead::dash()
//	{
//		_time += Time::DeltaTime();
//		if (_time > 0.7f)
//		{
//			_State = Skul_Nohead_State::Idle;
//			if (mDir == 1)
//			{
//				at->PlayAnimation(L"Skul_NoheadIdle", true);
//				mDir = 1;
//			}
//			else if (mDir == -1)
//			{
//				at->PlayAnimation(L"Skul_NoheadIdleR", true);
//				mDir = -1;
//			}
//			_time = 0;
//		}
//	}
//	void Skul_Nohead::attack_a()
//	{
//		if (Input::GetKeyDown(eKeyCode::X))
//		{
//			_attack = true;
//		}
//		if (Input::GetKeyDown(eKeyCode::RIGHT))
//		{
//			mDir = 1;
//		}
//		else if (Input::GetKeyDown(eKeyCode::LEFT))
//		{
//			mDir = -1;
//		}
//	}
//	void Skul_Nohead::attack_b()
//	{
//		_attack = false;
//		if (Input::GetKeyDown(eKeyCode::RIGHT))
//		{
//			mDir = 1;
//		}
//		else if (Input::GetKeyDown(eKeyCode::LEFT))
//		{
//			mDir = -1;
//		}
//	}
//	void Skul_Nohead::jumpattack()
//	{
//	}
//	void Skul_Nohead::skill_a()
//	{
//	}
//	void Skul_Nohead::skill_b()
//	{
//	}
//	void Skul_Nohead::death()
//	{
//	}
//	void Skul_Nohead::OnCollisionEnter(Collider2D* other)
//	{
//	}
//	void Skul_Nohead::OnCollisionStay(Collider2D* other)
//	{
//	}
//	void Skul_Nohead::OnCollisionExit(Collider2D* other)
//	{
//	}
//	void Skul_Nohead::attack_choice()
//	{
//		if (_attack == true)
//		{
//			_State = Skul_Nohead_State::Attack_B;
//			if (mDir == 1)
//			{
//				at->PlayAnimation(L"Skul_NoheadAttackB", true);
//				mDir = 1;
//			}
//			else if (mDir == -1)
//			{
//				at->PlayAnimation(L"Skul_NoheadAttackBR", true);
//				mDir = -1;
//			}
//		}
//		if (_attack == false)
//		{
//			if (Input::GetKeyDown(eKeyCode::Z))
//			{
//				_State = Skul_Nohead_State::Dash;
//				if (mDir == 1)
//				{
//					at->PlayAnimation(L"Skul_NoheadDash", false);
//					mDir = 1;
//				}
//				else if (mDir == -1)
//				{
//					at->PlayAnimation(L"Skul_NoheadDashR", false);
//					mDir = -1;
//				}
//			}
//
//			if (Input::GetKey(eKeyCode::RIGHT)
//				|| Input::GetKey(eKeyCode::LEFT))
//			{
//				_State = Skul_Nohead_State::Move;
//				if (Input::GetKey(eKeyCode::RIGHT))
//				{
//					at->PlayAnimation(L"Skul_NoheadWalk", true);
//					mDir = 1;
//				}
//				else if (Input::GetKey(eKeyCode::LEFT))
//				{
//					at->PlayAnimation(L"Skul_NoheadWalkR", true);
//					mDir = -1;
//				}
//			}
//			else
//			{
//				_State = Skul_Nohead_State::Idle;
//				if (mDir == 1)
//				{
//					at->PlayAnimation(L"Skul_NoheadIdle", true);
//					mDir = 1;
//				}
//				else if (mDir == -1)
//				{
//					at->PlayAnimation(L"Skul_NoheadIdleR", true);
//					mDir = -1;
//				}
//			}
//		}
//	}
//	void Skul_Nohead::dash_check()
//	{
//	}
//}
