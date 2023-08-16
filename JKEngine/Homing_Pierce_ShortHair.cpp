#include "Homing_Pierce_ShortHair.h"

namespace jk
{
	int Homing_Pierce_ShortHair::mDir = 1;

	Homing_Pierce_ShortHair::Homing_Pierce_ShortHair()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Homing_Pierce_ShortHair::~Homing_Pierce_ShortHair()
	{
	}
	void Homing_Pierce_ShortHair::Initialize()
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
	void Homing_Pierce_ShortHair::Update()
	{
		if (mDir == 1)
			at->PlayAnimation(L"BulletHoming_pierce", true);
		else
			at->PlayAnimation(L"BulletHoming_pierceR", true);

		GameObject::Update();
	}
	void Homing_Pierce_ShortHair::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Homing_Pierce_ShortHair::Render()
	{
		GameObject::Render();
	}
	void Homing_Pierce_ShortHair::OnCollisionEnter(Collider2D* other)
	{
	}
	void Homing_Pierce_ShortHair::OnCollisionStay(Collider2D* other)
	{
	}
	void Homing_Pierce_ShortHair::OnCollisionExit(Collider2D* other)
	{
	}

}