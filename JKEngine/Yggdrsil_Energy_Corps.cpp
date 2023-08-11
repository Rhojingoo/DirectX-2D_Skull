#include "Yggdrsil_Energy_Corps.h"

namespace jk
{
	Yggdrsil_Energy_Corps::Yggdrsil_Energy_Corps()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Yggdrsil_Energy_Corps::~Yggdrsil_Energy_Corps()
	{
	}
	void Yggdrsil_Energy_Corps::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Bullet\\Energy_Corps", this);

		at->PlayAnimation(L"BulletEnergy_Corps", true);
		GameObject::Initialize();
	}
	void Yggdrsil_Energy_Corps::Update()
	{
		GameObject::Update();
	}
	void Yggdrsil_Energy_Corps::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Yggdrsil_Energy_Corps::Render()
	{
		GameObject::Render();
	}
	void Yggdrsil_Energy_Corps::OnCollisionEnter(Collider2D* other)
	{
	}
	void Yggdrsil_Energy_Corps::OnCollisionStay(Collider2D* other)
	{
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{
			_rigidbody->SetGround(true);
			_rigidbody->ClearVelocity();
		}
	}
	void Yggdrsil_Energy_Corps::OnCollisionExit(Collider2D* other)
	{
	}
}