#include "Spring_Effect.h"

namespace jk
{
	Spring_Effect::Spring_Effect()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Spring_Effect::~Spring_Effect()
	{
	}
	void Spring_Effect::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Spring\\Spring_EF", this, 0,0.07f);
		at->CompleteEvent(L"SpringSpring_EF") = std::bind(&Spring_Effect::Compelete, this);

		at->PlayAnimation(L"SpringSpring_EF", true);
		GameObject::Initialize();
	}
	void Spring_Effect::Update()
	{
		if (_effect_On == true)
		{
			at->PlayAnimation(L"SpringSpring_EF", true);
			_effect_On = false;
		}
		GameObject::Update();
	}
	void Spring_Effect::LateUpdate()
	{
		_collider->SetSize(Vector2(0.f, 0.f));
		_collider->SetCenter(Vector2(0.f, 0.f));
		GameObject::LateUpdate();
	}
	void Spring_Effect::Render()
	{
		GameObject::Render();
	}
	void Spring_Effect::OnCollisionEnter(Collider2D* other)
	{
	}
	void Spring_Effect::OnCollisionStay(Collider2D* other)
	{
	}
	void Spring_Effect::OnCollisionExit(Collider2D* other)
	{
	}
	void Spring_Effect::Compelete()
	{
		this->SetState(eState::Paused);
	}
}