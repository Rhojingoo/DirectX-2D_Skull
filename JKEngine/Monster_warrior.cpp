#include "Monster_warrior.h"


namespace jk
{
	int Monster_warrior::mDir = 1;
	bool Monster_warrior::_switch = false;

	Monster_warrior::Monster_warrior()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}

	Monster_warrior::~Monster_warrior()
	{
	}

	void Monster_warrior::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Monster_warrior\\Attack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Monster_warrior\\Dead", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Monster_warrior\\Hit", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Monster_warrior\\Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Monster_warrior\\Walk", this);

		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Monster_warrior\\Attack", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Monster_warrior\\Dead", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Monster_warrior\\Hit", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Monster_warrior\\Idle", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Monster_warrior\\Walk", this, 1);

		//bind ºÎºÐ
		at->CompleteEvent(L"Monster_warriorAttack") = std::bind(&Monster_warrior::attack_idle, this);
		at->CompleteEvent(L"Monster_warriorAttackR") = std::bind(&Monster_warrior::attack_idle, this);

		at->PlayAnimation(L"Monster_warriorIdle", true);
		GameObject::Initialize();
	}

	void Monster_warrior::Update()
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
		case jk::Monster_warrior::Monster_warrior_State::Idle:idle();
			break;

		case jk::Monster_warrior::Monster_warrior_State::Attack:attack();
			break;

		case jk::Monster_warrior::Monster_warrior_State::Dead:dead();
			break;

		case jk::Monster_warrior::Monster_warrior_State::Hit:hit();
			break;

		case jk::Monster_warrior::Monster_warrior_State::Walk:walk();
			break;

		default:
			break;
		}
		GameObject::Update();
	}

	void Monster_warrior::LateUpdate()
	{
		_collider->SetSize(Vector2(0.03f, 0.08f));
		_collider->SetCenter(Vector2(1.f, 0.05f));
		GameObject::LateUpdate();
	}

	void Monster_warrior::Render()
	{
		GameObject::Render();
	}

	void Monster_warrior::OnCollisionEnter(Collider2D* other)
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

	void Monster_warrior::OnCollisionStay(Collider2D* other)
	{
	}

	void Monster_warrior::OnCollisionExit(Collider2D* other)
	{
	}

	void Monster_warrior::idle()
	{
		_time += Time::DeltaTime();

		if (_time > 1.f)
		{
			if ((_distance >= 60 || _distance <= -60))
			{					
				{
					_state = Monster_warrior_State::Walk;
					if (mDir == 1)
					{
						at->PlayAnimation(L"Monster_warriorWalk", true);					
					}
					else
					{
						at->PlayAnimation(L"Monster_warriorWalkR", true);							
					}					
				}
			}
			if (_distance > -50 && _distance < 50)
			{
				_state = Monster_warrior_State::Attack;
				if (mDir == 1)
					at->PlayAnimation(L"Monster_warriorAttack", true);
				else
					at->PlayAnimation(L"Monster_warriorAttackR", true);
			}

		}
	}


	void Monster_warrior::attack()
	{
		//_rigidbody->ClearVelocityY();
		//if (mDir == 1 && _velocity.x >= -100.0)
		//{
		//	_state = Monster_warrior_State::Idle;
		//	at->PlayAnimation(L"ArcherIdle", true);
		//	_rigidbody->ClearVelocityX();
		//}
		//else if (mDir == -1 && _velocity.x <= 100.0)
		//{
		//	_state = Monster_warrior_State::Idle;
		//	at->PlayAnimation(L"ArchereIdleR", true);
		//	_rigidbody->ClearVelocityX();
		//}		
	}

	void Monster_warrior::dead()
	{
	}

	void Monster_warrior::hit()
	{
	}

	void Monster_warrior::walk()
	{
		if (_distance > -50 && _distance <50)
		{
			_state = Monster_warrior_State::Attack;
			if (mDir == 1)			
				at->PlayAnimation(L"Monster_warriorAttack", true);			
			else			
				at->PlayAnimation(L"Monster_warriorAttackR", true);
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
	void Monster_warrior::attack_idle()
	{
		_state = Monster_warrior_State::Idle;
		if (mDir == 1)
			at->PlayAnimation(L"Monster_warriorIdle", true);
		else
			at->PlayAnimation(L"Monster_warriorIdleR", true);

		_time = 0;
	}
}