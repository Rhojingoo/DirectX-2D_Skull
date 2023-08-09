#include "Monster_BigEnt.h"
#include <iostream>
#include <random>

namespace jk
{
	int Monster_BigEnt::mDir = 1;
	bool Monster_BigEnt::_switch = false;

	Monster_BigEnt::Monster_BigEnt()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}
	Monster_BigEnt::~Monster_BigEnt()
	{
	}
	void Monster_BigEnt::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GiganticEnt\\Attack_Melee", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GiganticEnt\\Attack_Range", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GiganticEnt\\Dead", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GiganticEnt\\Idle", this);

		at->CompleteEvent(L"GiganticEntAttack_Melee") = std::bind(&Monster_BigEnt::attack_idle, this);
		at->CompleteEvent(L"GiganticEntAttack_Range") = std::bind(&Monster_BigEnt::attack_idle, this);

		at->PlayAnimation(L"GiganticEntIdle", true);
		GameObject::Initialize();
	}
	void Monster_BigEnt::Update()
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
		case jk::Monster_BigEnt::Monster_BigEnt_State::Idle:idle();
			break;

		case jk::Monster_BigEnt::Monster_BigEnt_State::AttackA:attackA();
			break;

		case jk::Monster_BigEnt::Monster_BigEnt_State::AttackB:attackB();
			break;

		case jk::Monster_BigEnt::Monster_BigEnt_State::Dead:dead();
			break;

		case jk::Monster_BigEnt::Monster_BigEnt_State::Hit:hit();
			break;

		case jk::Monster_BigEnt::Monster_BigEnt_State::Walk:walk();
			break;

		default:
			break;
		}
		GameObject::Update();
	}
	void Monster_BigEnt::LateUpdate()
	{
		_collider->SetSize(Vector2(0.03f, 0.08f));
		_collider->SetCenter(Vector2(1.f, 0.05f));
		GameObject::LateUpdate();
	}
	void Monster_BigEnt::Render()
	{
		GameObject::Render();
	}
	void Monster_BigEnt::OnCollisionEnter(Collider2D* other)
	{
	}
	void Monster_BigEnt::OnCollisionStay(Collider2D* other)
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
	void Monster_BigEnt::OnCollisionExit(Collider2D* other)
	{
	}

	void Monster_BigEnt::idle()
	{
		_time += Time::DeltaTime();

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> distribution(0, 1);
		_choiceattack = distribution(gen);

		if ((_distance >= 250) || (_distance <= -250))
			_choiceattack = 1;

		if (_time > 3.f)
		{
			if (_choiceattack == 0)
			{				
				_state = Monster_BigEnt_State::AttackA;
				at->PlayAnimation(L"GiganticEntAttack_Melee", true);
			}
			else if (_choiceattack == 1)
			{				
				_state = Monster_BigEnt_State::AttackB;
				at->PlayAnimation(L"GiganticEntAttack_Range", true);			
			}
		}
	}
	void Monster_BigEnt::attackA()
	{
	}

	void Monster_BigEnt::attackB()
	{
	}

	void Monster_BigEnt::dead()
	{
	}
	void Monster_BigEnt::hit()
	{
	}
	void Monster_BigEnt::walk()
	{
	}
	void Monster_BigEnt::attack_idle()
	{
		_state = Monster_BigEnt_State::Idle;
		at->PlayAnimation(L"GiganticEntIdle", true);
		_time = 0;
	}
}