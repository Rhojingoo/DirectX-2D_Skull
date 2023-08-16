#include "Homing_Pierce_LongHair.h"

namespace jk
{
	int Homing_Pierce_LongHair::mDir = 1;

	Homing_Pierce_LongHair::Homing_Pierce_LongHair()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Homing_Pierce_LongHair::~Homing_Pierce_LongHair()
	{
	}
	void Homing_Pierce_LongHair::Initialize()
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
	void Homing_Pierce_LongHair::Update()
	{
		if(mDir ==1)
			at->PlayAnimation(L"BulletHoming_pierce", true);
		else 
			at->PlayAnimation(L"BulletHoming_pierceR", true);

		GameObject::Update();
	}
	void Homing_Pierce_LongHair::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Homing_Pierce_LongHair::Render()
	{
		GameObject::Render();
	}
	void Homing_Pierce_LongHair::OnCollisionEnter(Collider2D* other)
	{
	}
	void Homing_Pierce_LongHair::OnCollisionStay(Collider2D* other)
	{
	}
	void Homing_Pierce_LongHair::OnCollisionExit(Collider2D* other)
	{
	}

}