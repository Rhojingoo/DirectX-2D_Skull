#include "Archer_Arrow_Upward_Sign.h"

namespace jk
{
	Archer_Arrow_Upward_Sign::Archer_Arrow_Upward_Sign()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Archer_Arrow_Upward_Sign::~Archer_Arrow_Upward_Sign()
	{
	}
	void Archer_Arrow_Upward_Sign::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Effect\\Upward_Sign", this,0,0.065);
		at->CompleteEvent(L"EffectUpward_Sign") = std::bind(&Archer_Arrow_Upward_Sign::Compelete, this);

		at->PlayAnimation(L"EffectUpward_Sign", false);

		GameObject::Initialize();
	}
	void Archer_Arrow_Upward_Sign::Update()
	{
		GameObject::Update();
	}
	void Archer_Arrow_Upward_Sign::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Archer_Arrow_Upward_Sign::Render()
	{
		GameObject::Render();
	}
	void Archer_Arrow_Upward_Sign::OnCollisionEnter(Collider2D* other)
	{
	}
	void Archer_Arrow_Upward_Sign::OnCollisionStay(Collider2D* other)
	{
	}
	void Archer_Arrow_Upward_Sign::OnCollisionExit(Collider2D* other)
	{
	}
	void Archer_Arrow_Upward_Sign::Compelete()
	{
		//this->SetState(eState::Paused);
	}
}