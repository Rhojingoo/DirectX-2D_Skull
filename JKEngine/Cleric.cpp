#include "Cleric.h"
#include <iostream>
#include <random>


namespace jk
{
	int Cleric::mDir = 1;
	Cleric::Cleric()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}
	Cleric::~Cleric()
	{
	}
	void Cleric::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Attack_A", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Attack_B", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Attack_B_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Attack_C", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Attack_D", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Casting", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Die", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Groggy", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Hit", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Intro", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Potion", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Teleport_In", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Teleport_Out", this);



		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Attack_A", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Attack_B", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Attack_B_Ready", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Attack_C", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Attack_D", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Casting", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Die", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Groggy", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Hit", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Idle", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Intro", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Potion", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Teleport_In", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Teleport_Out", this, 1);

		
		//bind ºÎºÐ
		at->CompleteEvent(L"ClericAttack_A") = std::bind(&Cleric::complete_attack_a, this);
		at->CompleteEvent(L"ClericAttack_AR") = std::bind(&Cleric::complete_attack_a, this);

		at->CompleteEvent(L"ClericAttack_B") = std::bind(&Cleric::complete_attack_b, this);
		at->CompleteEvent(L"ClericAttack_BR") = std::bind(&Cleric::complete_attack_b, this);

		at->CompleteEvent(L"ClericAttack_B_Ready") = std::bind(&Cleric::complete_attack_b_ready, this);
		at->CompleteEvent(L"ClericAttack_B_ReadyR") = std::bind(&Cleric::complete_attack_b_ready, this);

		at->CompleteEvent(L"ClericAttack_C") = std::bind(&Cleric::complete_attack_c, this);
		at->CompleteEvent(L"ClericAttack_CR") = std::bind(&Cleric::complete_attack_c, this);

		at->CompleteEvent(L"ClericAttack_D") = std::bind(&Cleric::complete_attack_d, this);
		at->CompleteEvent(L"ClericAttack_DR") = std::bind(&Cleric::complete_attack_d, this);

		at->CompleteEvent(L"ClericHit") = std::bind(&Cleric::complete_attack_d, this);
		at->CompleteEvent(L"ClericHitR") = std::bind(&Cleric::complete_attack_d, this);

		at->CompleteEvent(L"ClericTeleport_In") = std::bind(&Cleric::complete_teleport_in, this);
		at->CompleteEvent(L"ClericTeleport_InR") = std::bind(&Cleric::complete_teleport_in, this);
		at->CompleteEvent(L"ClericTeleport_Out") = std::bind(&Cleric::complete_teleport_out, this);
		at->CompleteEvent(L"ClericTeleport_OutR") = std::bind(&Cleric::complete_teleport_out, this);

		_first_place = pos;
		at->PlayAnimation(L"ClericIdle", true);
		GameObject::Initialize();
	}
	void Cleric::Update()
	{
		tr = GetComponent<Transform>();
		pos = tr->GetPosition();
		_velocity = _rigidbody->GetVelocity();
		_playerpos;
		_distance = _playerpos.x - pos.x;
		if (_distance >= 0.f)
			mDir = 1;
		else
			mDir = -1;

		switch (_state)
		{
		case jk::Cleric::Cleric_State::Idle:
			idle();
			break;

		case jk::Cleric::Cleric_State::Attack_A:
			attack_a();
			break;

		case jk::Cleric::Cleric_State::Attack_B:
			attack_b();
			break;

		case jk::Cleric::Cleric_State::Attack_B_Ready:
			attack_b_ready();
			break;

		case jk::Cleric::Cleric_State::Attack_C:
			attack_c();
			break;

		case jk::Cleric::Cleric_State::Attack_D:
			attack_d();
			break;

		case jk::Cleric::Cleric_State::Casting:
			casting();
			break;

		case jk::Cleric::Cleric_State::Die:
			die();
			break;

		case jk::Cleric::Cleric_State::Hit:
			hit();
			break;

		case jk::Cleric::Cleric_State::Intro:
			intro();
			break;

		case jk::Cleric::Cleric_State::Potion:
			potion();
			break;

		case jk::Cleric::Cleric_State::Teleport_In:
			teleport_in();
			break;

		case jk::Cleric::Cleric_State::Teleport_Out:
			teleport_out();
			break;

		default:
			break;
		}
		tr->SetPosition(Vector3(pos));
		GameObject::Update();
	}
	void Cleric::LateUpdate()
	{
		_collider->SetSize(Vector2(0.1f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -5.55f));

		GameObject::LateUpdate();
	}
	void Cleric::Render()
	{
		GameObject::Render();
	}
	void Cleric::OnCollisionEnter(Collider2D* other)
	{
	}
	void Cleric::OnCollisionStay(Collider2D* other)
	{
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{
			_rigidbody->SetGround(true);
			_Ground_check = true;
			_Ground_check = _rigidbody->GetGround();
			_rigidbody->ClearVelocity();
		}
	}
	void Cleric::OnCollisionExit(Collider2D* other)
	{
	}

	void Cleric::idle()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> distribution(0, 2);

		_lotationplay = distribution(gen);

		_time += Time::DeltaTime();

		//if (_hit >= 3)
		//{
		//if ((_distance >= -50) && (_distance <= 50))
		//{
		//	_state = Cleric_State::Teleport_In;
		//	if (mDir == 1)					
		//		at->PlayAnimation(L"ClericTeleport_In", true);		
		//	else		
		//		at->PlayAnimation(L"ClericTeleport_InR", false);
		//	
		//}
		//	_hit = 0;
		//}

		if (_time >= 3.f)
		{

			if ((_distance >= -50) && (_distance <= 50))
			{
				_state = Cleric_State::Teleport_In;
				if (mDir == 1)
					at->PlayAnimation(L"ClericTeleport_In", true);
				else
					at->PlayAnimation(L"ClericTeleport_InR", true);
			}
			else
			{
				if (_lotationplay == 0)
				{
					_state = Cleric_State::Attack_A;
					if (mDir == 1)
						at->PlayAnimation(L"ClericAttack_A", true);
					else
						at->PlayAnimation(L"ClericAttack_AR", true);
				}
				if (_lotationplay == 1)
				{
					_state = Cleric_State::Attack_B_Ready;
					if (mDir == 1)
						at->PlayAnimation(L"ClericAttack_B_Ready", true);
					else
						at->PlayAnimation(L"ClericAttack_B_ReadyR", true);
				}
				if (_lotationplay == 2)
				{
					_state = Cleric_State::Attack_D;
					if (mDir == 1)
						at->PlayAnimation(L"ClericAttack_D", true);
					else
						at->PlayAnimation(L"ClericAttack_DR", true);
				}
			}
			//if (_lotationplay == 0)
			//{
			//	_state = Cleric_State::Attack_A;
			//	if (mDir == 1)
			//		at->PlayAnimation(L"ClericAttack_A", true);
			//	else
			//		at->PlayAnimation(L"ClericAttack_AR", true);
			//}
			//if (_lotationplay == 1)
			//{
			//	_state = Cleric_State::Attack_B_Ready;
			//	if (mDir == 1)
			//		at->PlayAnimation(L"ClericAttack_B_Ready", true);
			//	else
			//		at->PlayAnimation(L"ClericAttack_B_ReadyR", true);
			//}
			//if (_lotationplay == 2)
			//{
			//	_state = Cleric_State::Attack_D;
			//	if (mDir == 1)
			//		at->PlayAnimation(L"ClericAttack_D", true);
			//	else
			//		at->PlayAnimation(L"ClericAttack_DR", true);
			//}
		}
	}
	void Cleric::attack_a()
	{
	}
	void Cleric::attack_b_ready()
	{
	}
	void Cleric::attack_b()
	{
	}
	void Cleric::attack_c()
	{
	}
	void Cleric::attack_d()
	{
	}
	void Cleric::casting()
	{
	}
	void Cleric::groggy()
	{
	}
	void Cleric::hit()
	{
	}
	void Cleric::die()
	{
	}
	void Cleric::intro()
	{
	}
	void Cleric::potion()
	{
	}
	void Cleric::teleport_in()
	{
		if (_Teleport == true)
		{
			int a = 0;
			_state = Cleric_State::Teleport_Out;
			if (mDir == 1)
				at->PlayAnimation(L"ClericTeleport_Out", true);
			else
				at->PlayAnimation(L"ClericTeleport_OutR", true);

			_time = 0.f;
			_Teleport = false;
		}
	}
	void Cleric::teleport_out()
	{
	}
	void Cleric::complete_attack_a()
	{
		_state = Cleric_State::Idle;
		if (mDir == 1)
			at->PlayAnimation(L"ClericIdle", true);
		else
			at->PlayAnimation(L"ClericIdleR", true);

		_time = 0.f;
	}
	void Cleric::complete_attack_b()
	{
		_state = Cleric_State::Idle;
		if (mDir == 1)
			at->PlayAnimation(L"ClericIdle", true);
		else
			at->PlayAnimation(L"ClericIdleR", true);

		_time = 0.f;
	}
	void Cleric::complete_attack_b_ready()
	{
		_state = Cleric_State::Attack_B;
		if (mDir == 1)
			at->PlayAnimation(L"ClericAttack_B", true);
		else
			at->PlayAnimation(L"ClericAttack_BR", true);
	}
	void Cleric::complete_attack_c()
	{
		_state = Cleric_State::Idle;
		if (mDir == 1)
			at->PlayAnimation(L"ClericIdle", true);
		else
			at->PlayAnimation(L"ClericIdleR", true);

		_time = 0.f;
	}
	void Cleric::complete_attack_d()
	{
		_state = Cleric_State::Idle;
		if (mDir == 1)
			at->PlayAnimation(L"ClericIdle", true);
		else
			at->PlayAnimation(L"ClericIdleR", true);

		_time = 0.f;
	}
	void Cleric::complete_teleport_in()
	{
		if (_Teleport == false)
		{
			if (pos.x >= _first_place.x)
				pos.x = pos.x - 400.f;
			else
				pos.x = pos.x + 400.f;

			_Teleport = true;
		}
		tr->SetPositionXY(Vector2(pos.x,pos.y));
	}

	void Cleric::complete_teleport_out()
	{
		if (_Teleport == false)
		{
			_state = Cleric_State::Idle;
			if (mDir == 1)
				at->PlayAnimation(L"ClericIdle", true);
			else
				at->PlayAnimation(L"ClericIdleR", true);
		}
		_time = 0.f;
	}

}