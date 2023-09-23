#include "Rising_Pierce.h"


namespace jk
{	
	Rising_Pierce::Rising_Pierce()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Rising_Pierce::~Rising_Pierce()
	{
	}
	void Rising_Pierce::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Bullet\\Rising_Pierce", this);	
		at->CompleteEvent(L"BulletRising_Pierce") = std::bind(&Rising_Pierce::CompeleteRising_Pierce, this);

		at->PlayAnimation(L"BulletRising_Pierce", true);
		GameObject::Initialize();
	}
	void Rising_Pierce::Update()
	{
		GameObject::Update();
	}
	void Rising_Pierce::LateUpdate()
	{
		_collider->SetSize(Vector2(0.15f, 0.9f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Rising_Pierce::Render()
	{
		GameObject::Render();
	}
	void Rising_Pierce::OnCollisionEnter(Collider2D* other)
	{
	}
	void Rising_Pierce::OnCollisionStay(Collider2D* other)
	{
	}
	void Rising_Pierce::OnCollisionExit(Collider2D* other)
	{
	}

	void Rising_Pierce::CompeleteRising_Pierce()
	{
		this->SetState(eState::Paused);
	}
}