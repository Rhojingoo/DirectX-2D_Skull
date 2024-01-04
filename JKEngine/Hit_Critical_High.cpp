#include "Hit_Critical_High.h"
#include "Include_Common.h"

namespace jk
{
	Hit_Critical_High::Hit_Critical_High()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Hit_Critical_High::~Hit_Critical_High()
	{
	}
	void Hit_Critical_High::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Effect\\Hit_Critical_High", this, 0);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Effect\\Hit_Critical_High", this, 1);

		at->CompleteEvent(L"EffectHit_Critical_High") = std::bind(&Hit_Critical_High::Compelete, this);
		at->CompleteEvent(L"EffectHit_Critical_HighR") = std::bind(&Hit_Critical_High::Compelete, this);

		at->PlayAnimation(L"EffectHit_Critical_High", true);

		GameObject::Initialize();
	}
	void Hit_Critical_High::Update()
	{
		if (_effect_animation == true)
		{
			if (_dir == 1)
				at->PlayAnimation(L"EffectHit_Critical_High", true);
			else
				at->PlayAnimation(L"EffectHit_Critical_HighR", true);
			_effect_animation = false;
		}

		GameObject::Update();
	}
	void Hit_Critical_High::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Hit_Critical_High::Render()
	{
		GameObject::Render();
	}
	void Hit_Critical_High::OnCollisionEnter(Collider2D* other)
	{
	}
	void Hit_Critical_High::OnCollisionStay(Collider2D* other)
	{
	}
	void Hit_Critical_High::OnCollisionExit(Collider2D* other)
	{
	}
	void Hit_Critical_High::Compelete()
	{
		this->SetState(eState::Paused);
	}
}