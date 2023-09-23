#include "Intro_Aura_Layana.h"

namespace jk
{
	Intro_Aura_Layana::Intro_Aura_Layana()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Intro_Aura_Layana::~Intro_Aura_Layana()
	{
	}
	void Intro_Aura_Layana::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Effect\\Intro_Aura", this, 0, 0.05);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Effect\\Intro_Aura", this, 1, 0.05);
		at->CompleteEvent(L"EffectIntro_Aura") = std::bind(&Intro_Aura_Layana::Compelete_Pierce, this);
		at->CompleteEvent(L"EffectIntro_AuraR") = std::bind(&Intro_Aura_Layana::Compelete_Pierce, this);

		at->PlayAnimation(L"EffectIntro_Aura", true);
		GameObject::Initialize();
	}
	void Intro_Aura_Layana::Update()
	{
		if (_SwitchOn == true)
		{
			if (mDir == 1)
				at->PlayAnimation(L"EffectIntro_Aura", true);
			else
				at->PlayAnimation(L"EffectIntro_AuraR", true);
			_SwitchOn = false;
		}
		GameObject::Update();
	}
	void Intro_Aura_Layana::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Intro_Aura_Layana::Render()
	{
		GameObject::Render();
	}
	void Intro_Aura_Layana::OnCollisionEnter(Collider2D* other)
	{
	}
	void Intro_Aura_Layana::OnCollisionStay(Collider2D* other)
	{
	}
	void Intro_Aura_Layana::OnCollisionExit(Collider2D* other)
	{
	}
	void Intro_Aura_Layana::Compelete_Pierce()
	{
		this->SetState(eState::Paused);
	}
}