#include "Awaken_End_SmokeB2.h"

namespace jk
{
	Awaken_End_SmokeB2::Awaken_End_SmokeB2()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Awaken_End_SmokeB2::~Awaken_End_SmokeB2()
	{
	}
	void Awaken_End_SmokeB2::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Change_Effect\\Awaken_End_SmokeB2", this, 0, 0.075);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Change_Effect\\Awaken_End_SmokeB2", this, 1, 0.075);
		at->CompleteEvent(L"Change_EffectAwaken_End_SmokeB2") = std::bind(&Awaken_End_SmokeB2::Compelete_Pierce, this);
		at->CompleteEvent(L"Change_EffectAwaken_End_SmokeB2R") = std::bind(&Awaken_End_SmokeB2::Compelete_Pierce, this);

		at->PlayAnimation(L"Change_EffectAwaken_End_SmokeB2", true);
		GameObject::Initialize();
	}
	void Awaken_End_SmokeB2::Update()
	{
		if (_SwitchOn == true)
		{
			if (mDir == 1)
				at->PlayAnimation(L"Change_EffectAwaken_End_SmokeB2", true);
			else
				at->PlayAnimation(L"Change_EffectAwaken_End_SmokeB2R", true);
			_SwitchOn = false;
		}
		GameObject::Update();
	}
	void Awaken_End_SmokeB2::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Awaken_End_SmokeB2::Render()
	{
		GameObject::Render();
	}
	void Awaken_End_SmokeB2::OnCollisionEnter(Collider2D* other)
	{
	}
	void Awaken_End_SmokeB2::OnCollisionStay(Collider2D* other)
	{
	}
	void Awaken_End_SmokeB2::OnCollisionExit(Collider2D* other)
	{
	}
	void Awaken_End_SmokeB2::Compelete_Pierce()
	{
		this->SetState(eState::Paused);
	}
}