#include "Cleric_HolyThunder.h"

namespace jk
{
	Cleric_HolyThunder::Cleric_HolyThunder()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Cleric_HolyThunder::~Cleric_HolyThunder()
	{
	}
	void Cleric_HolyThunder::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		tr = this->GetComponent<Transform>();


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Bullet\\HolyThunder", this);
		at->CompleteEvent(L"BulletHolyThunder") = std::bind(&Cleric_HolyThunder::complete, this);


		at->PlayAnimation(L"BulletHolyThunder", true);
		GameObject::Initialize();
	}
	void Cleric_HolyThunder::Update()
	{
		GameObject::Update();
	}
	void Cleric_HolyThunder::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.9f));
		_collider->SetCenter(Vector2(0.0f, -0.07f));
		GameObject::LateUpdate();
	}
	void Cleric_HolyThunder::Render()
	{
		GameObject::Render();
	}
	void Cleric_HolyThunder::OnCollisionEnter(Collider2D* other)
	{
	}
	void Cleric_HolyThunder::OnCollisionStay(Collider2D* other)
	{
	}
	void Cleric_HolyThunder::OnCollisionExit(Collider2D* other)
	{
	}
	void Cleric_HolyThunder::complete()
	{
		this->SetState(eState::Paused);
		_bullet_On = false;
	}
}