#include "Yggdrasil_Body.h"


namespace jk
{
	Yggdrasil_Body::Yggdrasil_Body()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}
	Yggdrasil_Body::~Yggdrasil_Body()
	{
	}
	void Yggdrasil_Body::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		tr = GetComponent<Transform>();
		_pos = Vector3(0.f, -50.f, -200.f);
		tr->SetPosition(_pos);
		_savepos = Vector3(0.f, -50.f, -200.f);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Body\\YggdrasilBody_Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Body\\YggdrasilBody_Attack_C", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Body\\YggdrasilBody_Change", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Body\\YggdrasilBody_Die_Effect", this);

		//bind ºÎºÐ
		//at->CompleteEvent(L"ArcherAttack_A") = std::bind(&Archer::choicecombo, this);
		//at->CompleteEvent(L"ArcherAttack_B") = std::bind(&Archer::choicecombo, this);
		//at->CompleteEvent(L"ArcherAttack_C") = std::bind(&Archer::choicecombo, this);


		at->PlayAnimation(L"BodyYggdrasilBody_Idle", true);
		GameObject::Initialize();
	}


	void Yggdrasil_Body::Update()
	{
		SetPos(_pos);		


		switch (_state)
		{
		case jk::Yggdrasil::Yggdrasil_State::Idle:
			Yggdrasil_Body::idle();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Set:
			Yggdrasil_Body::attack_a_set();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Ready:
			Yggdrasil_Body::attack_a_ready();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Right:
			Yggdrasil_Body::attack_a_right();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Left:
			Yggdrasil_Body::attack_a_left();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Loading:
			Yggdrasil_Body::attack_a_loading();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Finish:
			Yggdrasil_Body::attack_a_finish();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B_Set:
			Yggdrasil_Body::attack_b_set();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B_Ready:
			Yggdrasil_Body::attack_b_ready();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B_Right:
			Yggdrasil_Body::attack_b_right();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B_Left:
			Yggdrasil_Body::attack_b_left();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B_Finish:
			Yggdrasil_Body::attack_b_finish();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C_Set:
			attack_c_set();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C_Ready:
			Yggdrasil_Body::attack_c_ready();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C:
			Yggdrasil_Body::attack_c();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C_Finish:
			Yggdrasil_Body::attack_c_finish();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Groggy_Start:
			Yggdrasil_Body::groggy_start();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Groggy_End:
			Yggdrasil_Body::groggy_end();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Intro:
			Yggdrasil_Body::intro();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Die:
			Yggdrasil_Body::die();
			break;

		default:
			break;
		}
		Yggdrasil::SetRotation(_BodyRotation);
		tr->SetPosition(_pos);
		GameObject::Update();
	}


	void Yggdrasil_Body::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}


	void Yggdrasil_Body::Render()
	{
		GameObject::Render();
	}


	void Yggdrasil_Body::OnCollisionEnter(Collider2D* other)
	{
	}
	void Yggdrasil_Body::OnCollisionStay(Collider2D* other)
	{
	}
	void Yggdrasil_Body::OnCollisionExit(Collider2D* other)
	{
	}

	void Yggdrasil_Body::idle()
	{
	}


	void Yggdrasil_Body::attack_a_set()
	{
	}
	void Yggdrasil_Body::attack_a_ready()
	{
	}
	void Yggdrasil_Body::attack_a_right()
	{
	}
	void Yggdrasil_Body::attack_a_left()
	{
	}
	void Yggdrasil_Body::attack_a_loading()
	{
	}
	void Yggdrasil_Body::attack_a_finish()
	{
	}


	void Yggdrasil_Body::attack_b_set()
	{
	}
	void Yggdrasil_Body::attack_b_ready()
	{
	}
	void Yggdrasil_Body::attack_b_left()
	{
	}
	void Yggdrasil_Body::attack_b_right()
	{
	}
	void Yggdrasil_Body::attack_b_finish()
	{
	}


	void Yggdrasil_Body::attack_c_set()
	{
	}
	void Yggdrasil_Body::attack_c_ready()
	{
	}
	void Yggdrasil_Body::attack_c()
	{
	}
	void Yggdrasil_Body::attack_c_finish()
	{
	}


	void Yggdrasil_Body::groggy_start()
	{
		if (_groggy_body == false)
		{
			body_down();
		}
	}
	void Yggdrasil_Body::groggy_end()
	{
	}


	void Yggdrasil_Body::intro()
	{
	}
	void Yggdrasil_Body::body_down()
	{
		if (_pos.y>=-100.f)
			_pos.y -= 25 * Time::DeltaTime();
		if (_BodyRotation.z < 35.f)
			_BodyRotation.z += 20*Time::DeltaTime();
		tr->SetRotation(_BodyRotation);
	}
	void Yggdrasil_Body::body_up()
	{
	}
	void Yggdrasil_Body::die()
	{
	}

}
