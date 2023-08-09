#include "Monster_BlossomEnt.h"


namespace jk
{
	int Monster_BlossomEnt::mDir = 1;
	bool Monster_BlossomEnt::_switch = false;

	Monster_BlossomEnt::Monster_BlossomEnt()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}

	Monster_BlossomEnt::~Monster_BlossomEnt()
	{
	}

	void Monster_BlossomEnt::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\BlossomEnt\\Attack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\BlossomEnt\\Attack_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\BlossomEnt\\Effect", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\BlossomEnt\\Hit", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\BlossomEnt\\Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\BlossomEnt\\Walk", this);

		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\BlossomEnt\\Attack", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\BlossomEnt\\Attack_Ready", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\BlossomEnt\\Effect", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\BlossomEnt\\Hit", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\BlossomEnt\\Idle", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\BlossomEnt\\Walk", this, 1);


		at->CompleteEvent(L"BlossomEntAttack_Ready") = std::bind(&Monster_BlossomEnt::attack_setting, this);
		at->CompleteEvent(L"BlossomEntAttack_ReadyR") = std::bind(&Monster_BlossomEnt::attack_setting, this);
		at->CompleteEvent(L"BlossomEntAttack") = std::bind(&Monster_BlossomEnt::attack_idle, this);
		at->CompleteEvent(L"BlossomEntAttackR") = std::bind(&Monster_BlossomEnt::attack_idle, this);

		_first_place = _pos;
		at->PlayAnimation(L"BlossomEntIdle", true);
		GameObject::Initialize();
	}

	void Monster_BlossomEnt::Update()
	{
		tr = GetComponent<Transform>();
		_pos = tr->GetPosition();
		_velocity = _rigidbody->GetVelocity();
		_walkdistance = _first_place.x - _pos.x;
		if (_walkdistance >= 0.f)
			_walkdir = 1;
		else
			_walkdir = -1;

		_distance = _playerpos.x - _pos.x;
		if (_distance >= 0.f)
			mDir = 1;
		else
			mDir = -1;

		switch (_state)
		{
		case Monster_BlossomEnt::Monster_BlossomEnt_State::Idle:
			idle();
			break;

		case Monster_BlossomEnt::Monster_BlossomEnt_State::Attack_Ready:
			attack_ready();
			break;

		case Monster_BlossomEnt::Monster_BlossomEnt_State::Attack:
			attack();
			break;

		case Monster_BlossomEnt::Monster_BlossomEnt_State::Dead:
			dead();
			break;

		case Monster_BlossomEnt::Monster_BlossomEnt_State::Hit:
			hit();
			break;

		case Monster_BlossomEnt::Monster_BlossomEnt_State::WalkR:
			walk_R();
			break;

		case Monster_BlossomEnt::Monster_BlossomEnt_State::WalkL:
			walk_L();
			break;

		default:
			break;
		}
		tr->SetPosition(_pos);
		GameObject::Update();
	}

	void Monster_BlossomEnt::LateUpdate()
	{
		_collider->SetSize(Vector2(0.03f, 0.08f));
		_collider->SetCenter(Vector2(1.f, 0.05f));
		GameObject::LateUpdate();
	}

	void Monster_BlossomEnt::Render()
	{
		GameObject::Render();
	}

	void Monster_BlossomEnt::OnCollisionEnter(Collider2D* other)
	{
	}
	void Monster_BlossomEnt::OnCollisionStay(Collider2D* other)
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
	void Monster_BlossomEnt::OnCollisionExit(Collider2D* other)
	{
	}

	void Monster_BlossomEnt::idle()
	{
		_time += Time::DeltaTime();

		if (((_distance <= 50) && (_distance >= -50)))
		{
			_state = Monster_BlossomEnt_State::Attack_Ready;
			if (mDir == 1)
				at->PlayAnimation(L"BlossomEntAttack_Ready", true);
			else
				at->PlayAnimation(L"BlossomEntAttack_ReadyR", true);
		}

		if (_time > 3.f)
		{
			if (_walkdir == 1)
			{
				_state = Monster_BlossomEnt_State::WalkR;
				at->PlayAnimation(L"BlossomEntWalk", true);
			}
			else if (_walkdir == -1)
			{
				_state = Monster_BlossomEnt_State::WalkL;
				at->PlayAnimation(L"BlossomEntWalkR", true);
			}
		}
	}

	void Monster_BlossomEnt::attack_ready()
	{
		_Attackset = 0;
	}

	void Monster_BlossomEnt::attack()
	{
		_Attackset = 0;
	}

	void Monster_BlossomEnt::dead()
	{
	}

	void Monster_BlossomEnt::hit()
	{
	}

	void Monster_BlossomEnt::walk_R()
	{
		if (_walkdistance > -100)
			_pos.x += 80.f * Time::DeltaTime();
		else
		{
			_state = Monster_BlossomEnt_State::Idle;
			at->PlayAnimation(L"BlossomEntIdle", true);
			_time = 0; _walkdir *= -1;
		}
	}

	void Monster_BlossomEnt::walk_L()
	{
		if (_walkdistance < 100)
			_pos.x -= 80.f * Time::DeltaTime();
		else
		{
			_state = Monster_BlossomEnt_State::Idle;
			at->PlayAnimation(L"BlossomEntIdleR", true);
			_time = 0; _walkdir *= -1;
		}
	}

	void Monster_BlossomEnt::attack_setting()
	{
		_Attackset += Time::DeltaTime();
		

		//if (_Attackset >= 3)
		//{
			if (mDir == 1)
			{
				_state = Monster_BlossomEnt_State::Attack;
				at->PlayAnimation(L"BlossomEntAttack", true);
			}
			else if (mDir == -1)
			{
				_state = Monster_BlossomEnt_State::Attack;
				at->PlayAnimation(L"BlossomEntAttackR", true);
			}
		//}
	}

	void Monster_BlossomEnt::attack_idle()
	{
		_state = Monster_BlossomEnt_State::Idle;
		if (mDir == 1)
			at->PlayAnimation(L"BlossomEntIdle", true);
		else
			at->PlayAnimation(L"BlossomEntIdleR", true);
		_Attackset = 0;
	}
}