#include "Ultimate_OnFire.h"

namespace jk
{
	Ultimate_OnFire::Ultimate_OnFire()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Ultimate_OnFire::~Ultimate_OnFire()
	{
	}
	void Ultimate_OnFire::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Effect\\World_On_Fire_v", this);
		//at->CompleteEvent(L"EffectWorld_On_Fire_v") = std::bind(&Ultimate_OnFire::Compelete, this);

		at->PlayAnimation(L"EffectWorld_On_Fire_v", true);

		GameObject::Initialize();
	}
	void Ultimate_OnFire::Update()
	{
		GameObject::Update();
	}
	void Ultimate_OnFire::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Ultimate_OnFire::Render()
	{
		GameObject::Render();
	}
	void Ultimate_OnFire::OnCollisionEnter(Collider2D* other)
	{
	}
	void Ultimate_OnFire::OnCollisionStay(Collider2D* other)
	{
	}
	void Ultimate_OnFire::OnCollisionExit(Collider2D* other)
	{
	}
	void Ultimate_OnFire::Compelete()
	{
	}
}