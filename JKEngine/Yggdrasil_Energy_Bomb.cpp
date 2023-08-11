#include "Yggdrasil_Energy_Bomb.h"

namespace jk
{
	Yggdrasil_Energy_Bomb::Yggdrasil_Energy_Bomb()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Yggdrasil_Energy_Bomb::~Yggdrasil_Energy_Bomb()
	{
	}
	void Yggdrasil_Energy_Bomb::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Bullet\\Energy_Bomb", this);

		at->PlayAnimation(L"BulletEnergy_Bomb", true);
		GameObject::Initialize();
	}
	void Yggdrasil_Energy_Bomb::Update()
	{
		GameObject::Update();
	}
	void Yggdrasil_Energy_Bomb::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Yggdrasil_Energy_Bomb::Render()
	{
		GameObject::Render();
	}
	void Yggdrasil_Energy_Bomb::OnCollisionEnter(Collider2D* other)
	{

	}
	void Yggdrasil_Energy_Bomb::OnCollisionStay(Collider2D* other)
	{
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{
			_rigidbody->SetGround(true);
			_rigidbody->ClearVelocity();
		}
	}
	void Yggdrasil_Energy_Bomb::OnCollisionExit(Collider2D* other)
	{
	}
}