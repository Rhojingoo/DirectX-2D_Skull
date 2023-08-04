#include "Stone_wizard.h"
#include <iostream>
#include <random>


namespace jk
{
	int Stone_wizard::mDir = 1;
	bool Stone_wizard::_switch = false;
	Stone_wizard::Stone_wizard()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}

	Stone_wizard::~Stone_wizard()
	{
	}

	void Stone_wizard::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Stone_wizard\\Attack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Stone_wizard\\Hit", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Stone_wizard\\Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Stone_wizard\\Teleport_In", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Stone_wizard\\Teleport_Out", this);

		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Stone_wizard\\Attack", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Stone_wizard\\Hit", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Stone_wizard\\Idle", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Stone_wizard\\Teleport_In", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Stone_wizard\\Teleport_Out", this, 1);

		//bind ºÎºÐ
		at->CompleteEvent(L"Stone_wizardAttack") = std::bind(&Stone_wizard::attack_complete, this);
		at->CompleteEvent(L"Stone_wizardAttackR") = std::bind(&Stone_wizard::attack_complete, this);
		at->CompleteEvent(L"Stone_wizardTeleport_In") = std::bind(&Stone_wizard::teleport_change, this);
		at->CompleteEvent(L"Stone_wizardTeleport_InR") = std::bind(&Stone_wizard::teleport_change, this);
		at->CompleteEvent(L"Stone_wizardTeleport_Out") = std::bind(&Stone_wizard::teleport_change, this);
		at->CompleteEvent(L"Stone_wizardTeleport_OutR") = std::bind(&Stone_wizard::teleport_change, this);

		at->PlayAnimation(L"Stone_wizardIdle", true);
		GameObject::Initialize();
	}

	void Stone_wizard::Update()
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
		case jk::Stone_wizard::Stone_wizard_State::Idle:idle();
			break;

		case jk::Stone_wizard::Stone_wizard_State::Attack:attack();
			break;

		case jk::Stone_wizard::Stone_wizard_State::Hit:hit();
			break;

		case jk::Stone_wizard::Stone_wizard_State::Teleport_In:teleport_in();
			break;

		case jk::Stone_wizard::Stone_wizard_State::Teleport_Out:teleport_out();
			break;

		default:
			break;
		}

		GameObject::Update();
	}

	void Stone_wizard::LateUpdate()
	{
		_collider->SetSize(Vector2(0.03f, 0.08f));
		_collider->SetCenter(Vector2(1.f, 0.05f));
		GameObject::LateUpdate();
	}

	void Stone_wizard::Render()
	{
		GameObject::Render();
	}

	void Stone_wizard::OnCollisionEnter(Collider2D* other)
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

	void Stone_wizard::OnCollisionStay(Collider2D* other)
	{
	}

	void Stone_wizard::OnCollisionExit(Collider2D* other)
	{
	}

	void Stone_wizard::idle()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> distribution(0, 1);
		//_AttackCheck = distribution(gen);

		_time += Time::DeltaTime();

		if (_time > 2.f)
		{

			if ((_distance >= 100 || _distance <= -100))
			{

				_state = Stone_wizard_State::Attack;
				if (mDir == 1)
					at->PlayAnimation(L"Stone_wizardAttack", true);
				else
					at->PlayAnimation(L"Stone_wizardAttackR", true);
			}


			if (_distance <= -250 || _distance >=250)
			{
				if (_teleportCheck == false)
				{
					_state = Stone_wizard_State::Teleport_In;
					if (mDir == 1)
						at->PlayAnimation(L"Stone_wizardTeleport_In", true);
					else
						at->PlayAnimation(L"Stone_wizardTeleport_InR", true);
				}
			}
		}
	}

	void Stone_wizard::attack()
	{
	}

	void Stone_wizard::hit()
	{
	}

	void Stone_wizard::teleport_in()
	{
	}

	void Stone_wizard::teleport_out()
	{
		_teleportCheck = true;
	}
	void Stone_wizard::teleport_change()
	{
		if (_teleportCheck == false)
		{
			if (mDir == 1)
			{
				tr->SetPositionXY(Vector2(_playerpos.x - 100, _playerpos.y));
				_state = Stone_wizard_State::Teleport_Out;
				at->PlayAnimation(L"Stone_wizardTeleport_Out", true);	
			}
			else
			{
				tr->SetPositionXY(Vector2(_playerpos.x + 100, _playerpos.y));
				_state = Stone_wizard_State::Teleport_Out;
				at->PlayAnimation(L"Stone_wizardTeleport_OutR", true);
			}
		}

		if (_teleportCheck == true)
		{
			if (mDir == 1)
			{			
				_state = Stone_wizard_State::Idle;
				at->PlayAnimation(L"Stone_wizardIdle", true);
			}
			else
			{		
				_state = Stone_wizard_State::Idle;
				at->PlayAnimation(L"Stone_wizardIdleR", true);
			}
			_teleportCheck = false;
			_time = 0.f;
		}
	}
	void Stone_wizard::attack_complete()
	{
		if (mDir == 1)
		{
			_state = Stone_wizard_State::Idle;
			at->PlayAnimation(L"Stone_wizardIdle", true);
		}
		else
		{
			_state = Stone_wizard_State::Idle;
			at->PlayAnimation(L"Stone_wizardIdleR", true);
		}
		_time = 0.f;
	}
}