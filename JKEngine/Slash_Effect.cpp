#include "Slash_Effect.h"


namespace jk
{
	Slash_Effect::Slash_Effect()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Slash_Effect::~Slash_Effect()
	{
	}
	void Slash_Effect::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Effect\\Hit_Slash_Effect", this, 0);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Effect\\Hit_Slash_Effect", this, 1);

		at->CompleteEvent(L"EffectHit_Slash_Effect") = std::bind(&Slash_Effect::Compelete, this);
		at->CompleteEvent(L"EffectHit_Slash_EffectR") = std::bind(&Slash_Effect::Compelete, this);

		at->PlayAnimation(L"EffectHit_Slash_Effect", true);

		GameObject::Initialize();
	}
	void Slash_Effect::Update()
	{
		if (_effect_animation == true)
		{
			if (_dir == 1)
				at->PlayAnimation(L"EffectHit_Slash_Effect", true);
			else
				at->PlayAnimation(L"EffectHit_Slash_EffectR", true);
			_effect_animation = false;
		}

		GameObject::Update();
	}
	void Slash_Effect::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Slash_Effect::Render()
	{
		GameObject::Render();
	}
	void Slash_Effect::OnCollisionEnter(Collider2D* other)
	{
	}
	void Slash_Effect::OnCollisionStay(Collider2D* other)
	{
	}
	void Slash_Effect::OnCollisionExit(Collider2D* other)
	{
	}
	void Slash_Effect::Compelete()
	{
		this->SetState(eState::Paused);
	}
}