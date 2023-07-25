#include "Skul_Basic.h"
#include "jkAnimator.h"

namespace jk
{
	Skul_Basic::Skul_Basic()
		: mDir(1)
		, _attack(0)
		, _State(Skul_Basic_State::Idle)
		, at(nullptr)
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Basic_Skul"));
		//Vector2 mSize = mr->GetMaterial()->GetTexture()->GetTexSize();
		//GetComponent<Transform>()->SetScale(Vector3(mSize.x, mSize.y, 1.0f));
	}
	Skul_Basic::~Skul_Basic()
	{
	}
	void Skul_Basic::Initialize()
	{
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Normal\\Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Normal\\Walk", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Normal\\AttackA", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Normal\\AttackB", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Normal\\Fall_Dead", this);



		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Normal\\Idle", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Normal\\Walk", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Normal\\AttackA", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Normal\\AttackB", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Normal\\Fall_Dead", this, 1);
		

		at->PlayAnimation(L"NormalIdle", true);
		at->CompleteEvent(L"NormalAttackA") = std::bind(&Skul_Basic::attack_choice, this);
		at->CompleteEvent(L"NormalAttackAR") = std::bind(&Skul_Basic::attack_choice, this);
		at->CompleteEvent(L"NormalAttackB") = std::bind(&Skul_Basic::attack_choice, this);
		at->CompleteEvent(L"NormalAttackBR") = std::bind(&Skul_Basic::attack_choice, this);
		//at->PlayAnimation(L"NormalIdleR", true);
		//at->PlayAnimation(L"NormalWalk", true);

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
		if (Input::GetKeyDown(eKeyCode::RIGHT)
			|| Input::GetKeyDown(eKeyCode::LEFT))
		{
			_State = Skul_Basic_State::Move;
			if (Input::GetKeyDown(eKeyCode::RIGHT))
			{
				at->PlayAnimation(L"NormalWalk", true);
				mDir = 1;
			}
			else if (Input::GetKeyDown(eKeyCode::LEFT))
			{
				at->PlayAnimation(L"NormalWalkR", true);
				mDir = -1;
			}
		}

		if (Input::GetKey(eKeyCode::X))
		{
			_State = Skul_Basic_State::Attack_A;
			if (mDir == 1)
			{
				at->PlayAnimation(L"NormalAttackA", true);
				mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"NormalAttackAR", true);
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
			_State = Skul_Basic_State::Death;
			if (mDir == 1)
			{
				at->PlayAnimation(L"NormalFall_Dead", false);
				mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"NormalFall_DeadR", false);
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
				at->PlayAnimation(L"NormalIdle", true);
				mDir = 1;
			}
			else if (Input::GetKeyUp(eKeyCode::LEFT))
			{
				at->PlayAnimation(L"NormalIdleR", true);
				mDir = -1;
			}
		}

		if (Input::GetKey(eKeyCode::X))
		{
			_State = Skul_Basic_State::Attack_A;
			if (mDir == 1)
			{
				at->PlayAnimation(L"NormalAttackA", true);
				mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"NormalAttackAR", true);
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
		if (Input::GetKeyUp(eKeyCode::Z))
		{
			_State = Skul_Basic_State::Idle;
			if (mDir == 1)
			{
				at->PlayAnimation(L"NormalIdle", true);
				mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"NormalIdleR", true);
				mDir = -1;
			}
		}
	}

	void Skul_Basic::attack_choice()
	{
		if (_attack == true)
		{
			_State = Skul_Basic_State::Attack_B;
			if (mDir == 1)
			{
				at->PlayAnimation(L"NormalAttackB", true);
				mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"NormalAttackBR", true);
				mDir = -1;
			}
		}
		if (_attack == false)
		{
			_State = Skul_Basic_State::Idle;
			if (mDir == 1)
			{
				at->PlayAnimation(L"NormalIdle", true);
				mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"NormalIdleR", true);
				mDir = -1;
			}
		}
	}
}
