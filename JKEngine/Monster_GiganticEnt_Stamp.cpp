#include "Monster_GiganticEnt_Stamp.h"

namespace jk
{
	Monster_GiganticEnt_Stamp::Monster_GiganticEnt_Stamp()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Monster_GiganticEnt_Stamp::~Monster_GiganticEnt_Stamp()
	{
	}
	void Monster_GiganticEnt_Stamp::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		tr = this->GetComponent<Transform>();

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GiganticEnt\\Effect\\GiganticEnt_Stamp", this,0,0.05f);
		at->CompleteEvent(L"EffectGiganticEnt_Stamp") = std::bind(&Monster_GiganticEnt_Stamp::Compelete, this);

		at->PlayAnimation(L"EffectGiganticEnt_Stamp", true);
		GameObject::Initialize();
	}
	void Monster_GiganticEnt_Stamp::Update()
	{
		GameObject::Update();
	}
	void Monster_GiganticEnt_Stamp::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Monster_GiganticEnt_Stamp::Render()
	{
		GameObject::Render();
	}
	void Monster_GiganticEnt_Stamp::OnCollisionEnter(Collider2D* other)
	{
	}
	void Monster_GiganticEnt_Stamp::OnCollisionStay(Collider2D* other)
	{
	}
	void Monster_GiganticEnt_Stamp::OnCollisionExit(Collider2D* other)
	{
	}
	void Monster_GiganticEnt_Stamp::Compelete()
	{
		this->SetState(eState::Paused);
	}
}