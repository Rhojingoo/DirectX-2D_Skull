#include "Cleric_Veteran_Sanctuary.h"

namespace jk
{
	Cleric_Veteran_Sanctuary::Cleric_Veteran_Sanctuary()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Cleric_Veteran_Sanctuary::~Cleric_Veteran_Sanctuary()
	{
	}
	void Cleric_Veteran_Sanctuary::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		tr = this->GetComponent<Transform>();


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Bullet\\Veteran_Sanctuary", this);
		at->CompleteEvent(L"BulletVeteran_Sanctuary") = std::bind(&Cleric_Veteran_Sanctuary::complete, this);


		at->PlayAnimation(L"BulletVeteran_Sanctuary", true);
		GameObject::Initialize();
	}
	void Cleric_Veteran_Sanctuary::Update()
	{
		GameObject::Update();
	}
	void Cleric_Veteran_Sanctuary::LateUpdate()
	{
		_collider->SetSize(Vector2(0.5f, 0.2f));
		_collider->SetCenter(Vector2(0.0f, -3.f));
		GameObject::LateUpdate();
	}
	void Cleric_Veteran_Sanctuary::Render()
	{
		GameObject::Render();
	}
	void Cleric_Veteran_Sanctuary::OnCollisionEnter(Collider2D* other)
	{
	}
	void Cleric_Veteran_Sanctuary::OnCollisionStay(Collider2D* other)
	{
	}
	void Cleric_Veteran_Sanctuary::OnCollisionExit(Collider2D* other)
	{
	}
	void Cleric_Veteran_Sanctuary::complete()
	{
		this->SetState(eState::Paused);
		_bullet_On = false;
	}
}