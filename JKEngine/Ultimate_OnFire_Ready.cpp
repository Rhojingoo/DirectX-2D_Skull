#include "Ultimate_OnFire_Ready.h"
#include "Include_Common.h"

namespace jk
{
	Ultimate_OnFire_Ready::Ultimate_OnFire_Ready()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Ultimate_OnFire_Ready::~Ultimate_OnFire_Ready()
	{
	}
	void Ultimate_OnFire_Ready::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Effect\\World_On_Fire_Ready", this);
		at->CompleteEvent(L"EffectWorld_On_Fire_Ready") = std::bind(&Ultimate_OnFire_Ready::Compelete, this);

		at->PlayAnimation(L"EffectWorld_On_Fire_Ready", true);

		GameObject::Initialize();
	}
	void Ultimate_OnFire_Ready::Update()
	{
		GameObject::Update();
	}
	void Ultimate_OnFire_Ready::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Ultimate_OnFire_Ready::Render()
	{
		GameObject::Render();
	}
	void Ultimate_OnFire_Ready::OnCollisionEnter(Collider2D* other)
	{
	}
	void Ultimate_OnFire_Ready::OnCollisionStay(Collider2D* other)
	{
	}
	void Ultimate_OnFire_Ready::OnCollisionExit(Collider2D* other)
	{
	}
	void Ultimate_OnFire_Ready::Compelete()
	{
		this->SetState(eState::Paused);
	}
}