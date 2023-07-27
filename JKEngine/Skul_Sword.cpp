#include "Skul_Sword.h"

namespace jk
{
	Skul_Sword::Skul_Sword()
	{
	}
	Skul_Sword::~Skul_Sword()
	{
	}
	void Skul_Sword::Initialize()
	{
		CameraScript* cam = AddComponent<CameraScript>();
		//at = AddComponent<Animator>();

		//at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\AttackA", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\AttackB", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\AttackC", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\Dash", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\Fall", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\FallRepeat", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\Idle", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\Jump", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\JumpAttack", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\SkillA", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\SkillB", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\SlashBack", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\SlashFront", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\Switch", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Sword\\Walk", this);

		//at->CompleteEvent(L"SwordAttackA") = std::bind(&Skul_Sword::attack_A_choice, this);
		//at->CompleteEvent(L"SwordAttackB") = std::bind(&Skul_Sword::attack_B_choice, this);
		//at->CompleteEvent(L"SwordAttackC") = std::bind(&Skul_Sword::attack_B_choice, this);

		//at->PlayAnimation(L"SwordIdle", true);

		GameObject::Initialize();
	}
	void Skul_Sword::Update()
	{
		switch (_State)
		{
		case jk::Skul_Sword::Skul_Sword_State::Idle:idle();
			break;

		case jk::Skul_Sword::Skul_Sword_State::Move:move();
			break;

		case jk::Skul_Sword::Skul_Sword_State::Jump:jump();
			break;

		case jk::Skul_Sword::Skul_Sword_State::Falling:falling();
			break;

		case jk::Skul_Sword::Skul_Sword_State::Dash:dash();
			break;

		case jk::Skul_Sword::Skul_Sword_State::Attack_A:attack_a();
			break;

		case jk::Skul_Sword::Skul_Sword_State::Attack_B:attack_b();
			break;

		case jk::Skul_Sword::Skul_Sword_State::JumpAttack:jumpattack();
			break;

		case jk::Skul_Sword::Skul_Sword_State::Skill_A:skill_a();
			break;

		case jk::Skul_Sword::Skul_Sword_State::Skill_B:skill_b();
			break;

		case jk::Skul_Sword::Skul_Sword_State::Death:death();
			break;

		default:
			break;
		}

		GameObject::Update();
	}
	void Skul_Sword::LateUpdate()
	{
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
	}
	void Skul_Sword::jump()
	{
	}
	void Skul_Sword::falling()
	{
	}
	void Skul_Sword::dash()
	{
		_time += Time::DeltaTime();
		if (_time > 0.7f)
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
			_time = 0;
		}
	}
	void Skul_Sword::attack_a()
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
	void Skul_Sword::attack_b()
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
	void Skul_Sword::attack_c()
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
	void Skul_Sword::jumpattack()
	{
	}
	void Skul_Sword::skill_a()
	{
	}
	void Skul_Sword::skill_b()
	{
	}
	void Skul_Sword::death()
	{
	}

	void Skul_Sword::OnCollisionEnter(Collider2D* other)
	{
	}

	void Skul_Sword::OnCollisionStay(Collider2D* other)
	{
	}

	void Skul_Sword::OnCollisionExit(Collider2D* other)
	{
	}

	void Skul_Sword::attack_A_choice()
	{
		if (_attack == true)
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
			_attack = false;
		}
		if (_attack == false)
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
		if (_attack == true)
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
		if (_attack == false)
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
	void Skul_Sword::dash_check()
	{
	}
}