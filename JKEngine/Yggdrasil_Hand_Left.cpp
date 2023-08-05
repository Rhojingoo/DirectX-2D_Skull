#include "Yggdrasil_Hand_Left.h"

namespace jk
{
	bool Yggdrasil_Hand_Left::_Attackswitch = false;

	Yggdrasil_Hand_Left::Yggdrasil_Hand_Left()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}
	Yggdrasil_Hand_Left::~Yggdrasil_Hand_Left()
	{
	}
	void Yggdrasil_Hand_Left::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		_pos = Vector3(GetPos().x - 150.f, GetPos().y, -203.f);
		_Savepointpos = _pos;
		tr = GetComponent<Transform>();
		tr->SetPosition(Vector3(_pos));


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\1_HandIdle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\1_HandRock", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\1_HandAttack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\1_HandAntlion", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\1_HandBullet", this);

		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\HandIdle_Change", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\HandRock_Change", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\HandAttack_Change", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\HandAntlion_Change", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\HandBullet_Change", this);

		//bind ºÎºÐ
		//at->CompleteEvent(L"ArcherAttack_A") = std::bind(&Archer::choicecombo, this);
		//at->CompleteEvent(L"ArcherAttack_B") = std::bind(&Archer::choicecombo, this);
		//at->CompleteEvent(L"ArcherAttack_C") = std::bind(&Archer::choicecombo, this);

		//at->PlayAnimation(L"Hand1_HandIdleR", true);
		at->PlayAnimation(L"Hand1_HandIdle", true);

		GameObject::Initialize();
	}
	void Yggdrasil_Hand_Left::Update()
	{
		tr = GetComponent<Transform>();
		_pos = tr->GetPosition();
		_velocity = _rigidbody->GetVelocity();

		_Yggdrasildistance = GetPos() - _pos;
		_Playerdistance = _playerpos - _pos;


		switch (_state)
		{
		case jk::Yggdrasil::Yggdrasil_State::Idle:
			Yggdrasil_Hand_Left::idle();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A:
			Yggdrasil_Hand_Left::attack_a();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B:
			Yggdrasil_Hand_Left::attack_b();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C:
			Yggdrasil_Hand_Left::attack_c();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Intro:
			Yggdrasil_Hand_Left::intro();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Die:
			Yggdrasil_Hand_Left::die();
			break;

		default:
			break;
		}

		tr->SetPosition(_pos);	
		GameObject::Update();
	}
	void Yggdrasil_Hand_Left::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}

	void Yggdrasil_Hand_Left::Render()
	{
		GameObject::Render();
	}

	void Yggdrasil_Hand_Left::OnCollisionEnter(Collider2D* other)
	{
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{

			if (_Ground_check == false)
			{
				_rigidbody->SetGround(true);
				_rigidbody->ClearVelocity();
				_Ground_check = true;
				_Ground_check = _rigidbody->GetGround();
			}
			else
			{

			}
		}
	}

	void Yggdrasil_Hand_Left::OnCollisionStay(Collider2D* other)
	{
	}

	void Yggdrasil_Hand_Left::OnCollisionExit(Collider2D* other)
	{
	}

	void Yggdrasil_Hand_Left::idle()
	{		
	}

	void Yggdrasil_Hand_Left::attack_a()
	{
		//at->PlayAnimation(L"Hand1_HandRock", true);
		if (_Attackswitch == true)
		{
			at->PlayAnimation(L"Hand1_HandRock", true);
			_rigidbody->SetVelocity(Vector2(0.f, 500.f));
			_rigidbody->SetGround(false);
			_Attackswitch = false;
			_Ground_check = false;
		}

		if (_Yggdrasildistance.y <= -137.f)
		{
			//_rigidbody->SetGround(true);
			_rigidbody->SetVelocity(Vector2(250.f, -150.f));
		}

		if (_Attackswitch == false && _Ground_check == true)
		{
			_Savepointpos.x;
			if (_pos.x < _Savepointpos.x)
				_pos.x -= 150.0f * Time::DeltaTime();
			if (_pos.y < _Savepointpos.y)
				_pos.y += 150.0f * Time::DeltaTime();
			tr->SetPosition(Vector3(_pos));

			if (_Savepointpos.x <= _pos.x)
				_pos.x = _Savepointpos.x;
			if (_Savepointpos.y <= _pos.y)
				_pos.y = _Savepointpos.y;

			if ((_pos.x == _Savepointpos.x) && (_pos.y == _Savepointpos.y))
			{
				at->PlayAnimation(L"Hand1_HandIdle", true);
				_state = Yggdrasil_State::Idle;
				Yggdrasil::_time = 0.f;
			}

			tr->SetPosition(Vector3(_pos));
		}
	}

	void Yggdrasil_Hand_Left::attack_b()
	{
	}
	void Yggdrasil_Hand_Left::attack_c()
	{
	}

	void Yggdrasil_Hand_Left::intro()
	{
	}

	void Yggdrasil_Hand_Left::die()
	{
	}
}
