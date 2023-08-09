#include "Monster_Hammer.h"
#include <iostream>
#include <random>

namespace jk
{

	int Monster_Hammer::mDir = 1;
	bool Monster_Hammer::_switch = false;


	Monster_Hammer::Monster_Hammer()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}
	Monster_Hammer::~Monster_Hammer()
	{
	}

	void Monster_Hammer::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Hammer\\Attack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Hammer\\Dead", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Hammer\\Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Hammer\\Tackle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Hammer\\Walk", this);

		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Hammer\\Attack", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Hammer\\Dead", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Hammer\\Idle", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Hammer\\Tackle", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Hammer\\Walk", this, 1);

		//bind ºÎºÐ
		at->CompleteEvent(L"HammerAttack") = std::bind(&Monster_Hammer::attack_idle, this);
		at->CompleteEvent(L"HammerAttackR") = std::bind(&Monster_Hammer::attack_idle, this);

		at->PlayAnimation(L"HammerIdle", true);
		GameObject::Initialize();
	}

	void Monster_Hammer::Update()
	{
		tr = GetComponent<Transform>();
		pos = tr->GetPosition();
		_velocity = _rigidbody->GetVelocity();
		_distance = _playerpos.x - pos.x;
		if (_distance >= 0.f)
			mDir = 1;
		else
			mDir = -1;


		switch (_state)
		{
		case jk::Monster_Hammer::Monster_Hammer_State::Idle:idle();
			break;

		case jk::Monster_Hammer::Monster_Hammer_State::Attack:attack();
			break;

		case jk::Monster_Hammer::Monster_Hammer_State::Dead:dead();
			break;

		case jk::Monster_Hammer::Monster_Hammer_State::Tackle:tackle();
			break;

		case jk::Monster_Hammer::Monster_Hammer_State::Walk:walk();
			break;

		default:
			break;
		}
		GameObject::Update();
	}

	void Monster_Hammer::LateUpdate()
	{
		_collider->SetSize(Vector2(0.03f, 0.08f));
		_collider->SetCenter(Vector2(1.f, 0.05f));
		GameObject::LateUpdate();
	}

	void Monster_Hammer::Render()
	{
		GameObject::Render();
	}

	void Monster_Hammer::OnCollisionEnter(Collider2D* other)
	{		
	}

	void Monster_Hammer::OnCollisionStay(Collider2D* other)
	{
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{
			if (_Ground_check == false)
			{
				_rigidbody->SetGround(true);
				_Ground_check = true;
				_Ground_check = _rigidbody->GetGround();
				_rigidbody->ClearVelocity();
			}
			else
			{
			}
		}
	}

	void Monster_Hammer::OnCollisionExit(Collider2D* other)
	{
	}

	void Monster_Hammer::idle()
	{

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> distribution(0, 1);
		_AttackCheck = distribution(gen);

		_time += Time::DeltaTime();

		if (_time > 1.f)
		{
		
			if ((_distance >= 60 || _distance <= -60))
			{

				_state = Monster_Hammer_State::Walk;
				if (mDir == 1)
					at->PlayAnimation(L"HammerWalk", true);
				else
					at->PlayAnimation(L"HammerWalkR", true);
			}	

		
			if (_distance > -50 && _distance < 50)
			{
				if (_AttackCheck == 0)
				{
				_state = Monster_Hammer_State::Attack;
				if (mDir == 1)
					at->PlayAnimation(L"HammerAttack", true);
				else
					at->PlayAnimation(L"HammerAttackR", true);
				}
				if (_AttackCheck == 1)
				{
					_state = Monster_Hammer_State::Tackle;
					if (mDir == 1)
					{
						at->PlayAnimation(L"HammerTackle", false);
						_rigidbody->SetVelocity(Vector2(250.f, 0.f));
					}
					else
					{
						at->PlayAnimation(L"HammerTackleR", false);
						_rigidbody->SetVelocity(Vector2(250.f, 0.f));
					}
				}
			}			
		}		
	}

	void Monster_Hammer::attack()
	{
	}

	void Monster_Hammer::tackle()
	{
		_rigidbody->ClearVelocityY();
		if (mDir == 1 && _velocity.x <= 100.0)
		{
			_state = Monster_Hammer_State::Idle;
			at->PlayAnimation(L"HammerIdle", true);
			_rigidbody->ClearVelocityX();
		}
		else if (mDir == -1 && _velocity.x >= -100.0)
		{
			_state = Monster_Hammer_State::Idle;
			at->PlayAnimation(L"HammerIdleR", true);
			_rigidbody->ClearVelocityX();
		}		
	}

	void Monster_Hammer::walk()
	{
		if (_distance > -50 && _distance < 50)
		{
			//_state = Monster_Hammer_State::Attack;
			//if (mDir == 1)
			//	at->PlayAnimation(L"HammerAttack", true);
			//else
			//	at->PlayAnimation(L"HammerAttackR", true);
			if (_AttackCheck == 0)
			{
				_state = Monster_Hammer_State::Attack;
				if (mDir == 1)
					at->PlayAnimation(L"HammerAttack", true);
				else
					at->PlayAnimation(L"HammerAttackR", true);
			}
			if (_AttackCheck == 1)
			{
				_state = Monster_Hammer_State::Tackle;
				if (mDir == 1)
				{
					at->PlayAnimation(L"HammerTackle", false);
					_rigidbody->SetVelocity(Vector2(250.f, 0.f));
				}
				else
				{
					at->PlayAnimation(L"HammerTackleR", false);
					_rigidbody->SetVelocity(Vector2(250.f, 0.f));
				}
			}
		}
		else
		{
			if (_distance >= 0.f)
				pos.x += 150.f * Time::DeltaTime();
			else
				pos.x -= 150.f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
	}

	void Monster_Hammer::dead()
	{
	}

	void Monster_Hammer::attack_idle()
	{
		_state = Monster_Hammer_State::Idle;
		if (mDir == 1)
			at->PlayAnimation(L"HammerIdle", true);
		else
			at->PlayAnimation(L"HammerIdleR", true);

		_time = 0;
	}
}