#include "Homing_Impact.h"


namespace jk
{
	Homing_Impact::Homing_Impact()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Homing_Impact::~Homing_Impact()
	{
	}
	void Homing_Impact::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Effect\\Homing_Impact", this, 0, 0.05f);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Effect\\Homing_Impact", this, 1, 0.05f);

		at->CompleteEvent(L"EffectHoming_Impact") = std::bind(&Homing_Impact::Compelete_Pierce, this);
		at->CompleteEvent(L"EffectHoming_ImpactR") = std::bind(&Homing_Impact::Compelete_Pierce, this);

		at->PlayAnimation(L"EffectHoming_Impact", true);
		GameObject::Initialize();
	}
	void Homing_Impact::Update()
	{
		if (_SwitchOn == true)
		{
			if (mDir == 1)
				at->PlayAnimation(L"EffectHoming_Impact", true);
			else
				at->PlayAnimation(L"EffectHoming_ImpactR", true);
			_SwitchOn = false;
		}
		GameObject::Update();
	}
	void Homing_Impact::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Homing_Impact::Render()
	{
		GameObject::Render();
	}
	void Homing_Impact::OnCollisionEnter(Collider2D* other)
	{
	}
	void Homing_Impact::OnCollisionStay(Collider2D* other)
	{
	}
	void Homing_Impact::OnCollisionExit(Collider2D* other)
	{
	}
	void Homing_Impact::Compelete_Pierce()
	{
		this->SetState(eState::Paused);
	}
}