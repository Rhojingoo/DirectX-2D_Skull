#include "Yggdrasil_Face.h"

namespace jk
{
	Vector3 Yggdrasil_Face::_pos = Vector3(0.f, 0.f, 0.f);;
	Yggdrasil_Face::Yggdrasil_Face()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}
	Yggdrasil_Face::~Yggdrasil_Face()
	{
	}
	void Yggdrasil_Face::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		Yggdrasil_pos = Yggdrasil::GetPos();
		//_pos.y = Yggdrasil_pos.y - 5.f;
		tr = GetComponent<Transform>();
		tr->SetPosition(Vector3(_pos.x, _pos.y, -201.f));

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Face\\YggdrasilFace_Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Face\\YggdrasilFace_groggy", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Face\\YggdrasilFace_Change", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Face\\YggdrasilFace_Die", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Face\\YggdrasilFace_Die_Effect", this);


		//bind ºÎºÐ
		//at->CompleteEvent(L"ArcherAttack_A") = std::bind(&Archer::choicecombo, this);
		//at->CompleteEvent(L"ArcherAttack_B") = std::bind(&Archer::choicecombo, this);
		//at->CompleteEvent(L"ArcherAttack_C") = std::bind(&Archer::choicecombo, this);


		at->PlayAnimation(L"FaceYggdrasilFace_Idle", true);

		GameObject::Initialize();
	}
	void Yggdrasil_Face::Update()
	{
		switch (_state)
		{
		case jk::Yggdrasil::Yggdrasil_State::Idle:
			Yggdrasil_Face::idle();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A:
			Yggdrasil_Face::attack_a();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B:
			Yggdrasil_Face::attack_b();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C:
			Yggdrasil_Face::attack_c();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Intro:
			Yggdrasil_Face::intro();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Die:
			Yggdrasil_Face::die();
			break;

		default:
			break;
		}
		GameObject::Update();
	}
	void Yggdrasil_Face::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Yggdrasil_Face::Render()
	{
		GameObject::Render();
	}
	void Yggdrasil_Face::OnCollisionEnter(Collider2D* other)
	{
	}
	void Yggdrasil_Face::OnCollisionStay(Collider2D* other)
	{
	}
	void Yggdrasil_Face::OnCollisionExit(Collider2D* other)
	{
	}
	void Yggdrasil_Face::idle()
	{
	}
	void Yggdrasil_Face::attack_a()
	{
	}
	void Yggdrasil_Face::attack_b()
	{
	}
	void Yggdrasil_Face::attack_c()
	{
	}
	void Yggdrasil_Face::intro()
	{
	}
	void Yggdrasil_Face::die()
	{
	}
}