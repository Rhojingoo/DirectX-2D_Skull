#include "Awaken_SmokeEffect.h"

namespace jk
{
	Awaken_SmokeEffect::Awaken_SmokeEffect()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Awaken_SmokeEffect::~Awaken_SmokeEffect()
	{
	}
	void Awaken_SmokeEffect::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Change_Effect\\Awaken_Smoke", this, 0, 0.035);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Change_Effect\\Awaken_Smoke", this, 1, 0.035);
		at->CompleteEvent(L"Change_EffectAwaken_Smoke") = std::bind(&Awaken_SmokeEffect::Compelete_Pierce, this);
		at->CompleteEvent(L"Change_EffectAwaken_SmokeR") = std::bind(&Awaken_SmokeEffect::Compelete_Pierce, this);

		at->PlayAnimation(L"Change_EffectAwaken_Smoke", true);
		GameObject::Initialize();
	}
	void Awaken_SmokeEffect::Update()
	{
		if (_SwitchOn == true)
		{
			if (mDir == 1)
				at->PlayAnimation(L"Change_EffectAwaken_Smoke", true);
			else
				at->PlayAnimation(L"Change_EffectAwaken_SmokeR", true);
			_SwitchOn = false;
		}
		GameObject::Update();
	}
	void Awaken_SmokeEffect::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Awaken_SmokeEffect::Render()
	{
		GameObject::Render();
	}
	void Awaken_SmokeEffect::OnCollisionEnter(Collider2D* other)
	{
	}
	void Awaken_SmokeEffect::OnCollisionStay(Collider2D* other)
	{
	}
	void Awaken_SmokeEffect::OnCollisionExit(Collider2D* other)
	{
	}
	void Awaken_SmokeEffect::Compelete_Pierce()
	{
		//this->SetState(eState::Paused);
	}
}