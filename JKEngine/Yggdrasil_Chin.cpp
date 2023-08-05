#include "Yggdrasil_Chin.h"


namespace jk
{
	int Yggdrasil_Chin:: mDir = 1;		
	Yggdrasil_Chin::Yggdrasil_Chin()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}
	Yggdrasil_Chin::~Yggdrasil_Chin()
	{
	}
	void Yggdrasil_Chin::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		Yggdrasil_pos = Yggdrasil::GetPos();
		_pos.x = Yggdrasil_pos.x + 2.5f;
		_pos.y = Yggdrasil_pos.y - 5.f;
		_pos.z = -202.f;
		mCenterpos = _pos;
		tr = GetComponent<Transform>();
		tr->SetPosition(Vector3(_pos));


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Chind\\YggdrasilChin_Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Chind\\YggdrasilChin_Attac_C", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Chind\\YggdrasilChin_Change", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Chind\\YggdrasilChin_Change_Die_Effect", this);

		//bind ºÎºÐ
		//at->CompleteEvent(L"ArcherAttack_A") = std::bind(&Archer::choicecombo, this);
		//at->CompleteEvent(L"ArcherAttack_B") = std::bind(&Archer::choicecombo, this);
		//at->CompleteEvent(L"ArcherAttack_C") = std::bind(&Archer::choicecombo, this);


		at->PlayAnimation(L"ChindYggdrasilChin_Idle", true);

		GameObject::Initialize();
	}
	void Yggdrasil_Chin::Update()
	{
		Yggdrasil_pos = Yggdrasil::GetPos();

		switch (_state)
		{
		case jk::Yggdrasil::Yggdrasil_State::Idle:
			Yggdrasil_Chin::idle();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A:
			Yggdrasil_Chin::attack_a();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B:
			Yggdrasil_Chin::attack_b();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C:
			Yggdrasil_Chin::attack_c();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Intro:
			Yggdrasil_Chin::intro();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Die:
			Yggdrasil_Chin::die();
			break;

		default:
			break;
		}
		GameObject::Update();
	}
	void Yggdrasil_Chin::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));

		GameObject::LateUpdate();
	}
	void Yggdrasil_Chin::Render()
	{
		GameObject::Render();
	}
	void Yggdrasil_Chin::OnCollisionEnter(Collider2D* other)
	{
	}
	void Yggdrasil_Chin::OnCollisionStay(Collider2D* other)
	{
	}
	void Yggdrasil_Chin::OnCollisionExit(Collider2D* other)
	{
	}
	void Yggdrasil_Chin::idle()
	{
		if (mDir == 1)
			Lmove_down();
		else
			Lmove_up();
	}
	void Yggdrasil_Chin::attack_a()
	{
	}
	void Yggdrasil_Chin::attack_b()
	{
	}
	void Yggdrasil_Chin::attack_c()
	{
	}
	void Yggdrasil_Chin::intro()
	{
	}
	void Yggdrasil_Chin::die()
	{
	}

	void Yggdrasil_Chin::Lmove_up()
	{
		Transform* tr = GetComponent<Transform>();

		fDist = mCenterpos.y - _pos.y - _maxdistance;
		_pos.y -= _chinspeed * static_cast<float>(Time::DeltaTime());

		if (fDist >= 5.0f)
			mDir *= -1;		

		tr->SetPosition(_pos);
	}

	void Yggdrasil_Chin::Lmove_down()
	{
		Transform* tr = GetComponent<Transform>();

		fDist = mCenterpos.y - _pos.y - _maxdistance;
		_pos.y += _chinspeed * static_cast<float>(Time::DeltaTime());

		if (fDist <= -1.f)
			mDir *= -1;

		tr->SetPosition(_pos);
	}

}
