#include "Awaken_Electric.h"

namespace jk
{
	Awaken_Electric::Awaken_Electric()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Awaken_Electric::~Awaken_Electric()
	{
	}
	void Awaken_Electric::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Change_Effect\\Awaken_Electric", this, 0, 0.075);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Change_Effect\\Awaken_Electric", this, 1, 0.075);
		at->CompleteEvent(L"Change_EffectAwaken_Electric") = std::bind(&Awaken_Electric::Compelete_Pierce, this);
		at->CompleteEvent(L"Change_EffectAwaken_ElectricR") = std::bind(&Awaken_Electric::Compelete_Pierce, this);

		at->PlayAnimation(L"Change_EffectAwaken_Electric", true);
		GameObject::Initialize();
	}
	void Awaken_Electric::Update()
	{
		if (_SwitchOn == true)
		{
			if (mDir == 1)
				at->PlayAnimation(L"Change_EffectAwaken_Electric", true);
			else
				at->PlayAnimation(L"Change_EffectAwaken_ElectricR", true);
			_SwitchOn = false;
		}
		GameObject::Update();
	}
	void Awaken_Electric::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Awaken_Electric::Render()
	{
		GameObject::Render();
	}
	void Awaken_Electric::OnCollisionEnter(Collider2D* other)
	{
	}
	void Awaken_Electric::OnCollisionStay(Collider2D* other)
	{
	}
	void Awaken_Electric::OnCollisionExit(Collider2D* other)
	{
	}
	void Awaken_Electric::Compelete_Pierce()
	{
		this->SetState(eState::Paused);
	}
}