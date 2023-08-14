#include "Homing_Pierce.h"

namespace jk
{
	int Homing_Pierce::mDir = 1;

	Homing_Pierce::Homing_Pierce()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Homing_Pierce::~Homing_Pierce()
	{
	}
	void Homing_Pierce::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Bullet\\Homing_pierce", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Bullet\\Homing_pierce", this, 1);

		at->PlayAnimation(L"BulletHoming_pierce", true);
		GameObject::Initialize();
	}
	void Homing_Pierce::Update()
	{
		if(mDir ==1)
			at->PlayAnimation(L"BulletHoming_pierce", true);
		else 
			at->PlayAnimation(L"BulletHoming_pierceR", true);

		GameObject::Update();
	}
	void Homing_Pierce::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Homing_Pierce::Render()
	{
		GameObject::Render();
	}
	void Homing_Pierce::OnCollisionEnter(Collider2D* other)
	{
	}
	void Homing_Pierce::OnCollisionStay(Collider2D* other)
	{
	}
	void Homing_Pierce::OnCollisionExit(Collider2D* other)
	{
	}

}