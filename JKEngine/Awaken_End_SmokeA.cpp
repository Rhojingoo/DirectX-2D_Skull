#include "Awaken_End_SmokeA.h"

namespace jk
{
	Awaken_End_SmokeA::Awaken_End_SmokeA()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Awaken_End_SmokeA::~Awaken_End_SmokeA()
	{
	}
	void Awaken_End_SmokeA::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Change_Effect\\Awaken_End_SmokeA", this, 0, 0.075);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Change_Effect\\Awaken_End_SmokeA", this, 1, 0.075);
		at->CompleteEvent(L"Change_EffectAwaken_End_SmokeA") = std::bind(&Awaken_End_SmokeA::Compelete_Pierce, this);
		at->CompleteEvent(L"Change_EffectAwaken_End_SmokeAR") = std::bind(&Awaken_End_SmokeA::Compelete_Pierce, this);

		at->PlayAnimation(L"Change_EffectAwaken_End_SmokeA", true);
		GameObject::Initialize();
	}
	void Awaken_End_SmokeA::Update()
	{
		if (_SwitchOn == true)
		{
			if (mDir == 1)
				at->PlayAnimation(L"Change_EffectAwaken_End_SmokeA", true);
			else
				at->PlayAnimation(L"Change_EffectAwaken_End_SmokeAR", true);
			_SwitchOn = false;
		}
		GameObject::Update();
	}
	void Awaken_End_SmokeA::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Awaken_End_SmokeA::Render()
	{
		GameObject::Render();
	}
	void Awaken_End_SmokeA::OnCollisionEnter(Collider2D* other)
	{
	}
	void Awaken_End_SmokeA::OnCollisionStay(Collider2D* other)
	{
	}
	void Awaken_End_SmokeA::OnCollisionExit(Collider2D* other)
	{
	}
	void Awaken_End_SmokeA::Compelete_Pierce()
	{
		this->SetState(eState::Paused);
	}
}