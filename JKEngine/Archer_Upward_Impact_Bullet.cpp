#include "Archer_Upward_Impact_Bullet.h"
#include "Include_Common.h"


namespace jk
{
	Archer_Upward_Impact_Bullet::Archer_Upward_Impact_Bullet()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Archer_Upward_Impact_Bullet::~Archer_Upward_Impact_Bullet()
	{
	}
	void Archer_Upward_Impact_Bullet::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		tr = this->GetComponent<Transform>();


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Bullet\\Archer_Upward_Impact", this);
		at->CompleteEvent(L"BulletArcher_Upward_Impact") = std::bind(&Archer_Upward_Impact_Bullet::complete, this);


		at->PlayAnimation(L"BulletArcher_Upward_Impact", true);
		GameObject::Initialize();
	}
	void Archer_Upward_Impact_Bullet::Update()
	{
		GameObject::Update();
	}
	void Archer_Upward_Impact_Bullet::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.9f));
		_collider->SetCenter(Vector2(0.0f, -0.07f));
		GameObject::LateUpdate();
	}
	void Archer_Upward_Impact_Bullet::Render()
	{
		GameObject::Render();
	}
	void Archer_Upward_Impact_Bullet::OnCollisionEnter(Collider2D* other)
	{
	}
	void Archer_Upward_Impact_Bullet::OnCollisionStay(Collider2D* other)
	{
	}
	void Archer_Upward_Impact_Bullet::OnCollisionExit(Collider2D* other)
	{
	}
	void Archer_Upward_Impact_Bullet::complete()
	{
		this->SetState(eState::Paused);
		_bullet_On = false;
	}
}