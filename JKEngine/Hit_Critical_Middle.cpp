#include "Hit_Critical_Middle.h"

namespace jk
{
	Hit_Critical_Middle::Hit_Critical_Middle()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Hit_Critical_Middle::~Hit_Critical_Middle()
	{
	}
	void Hit_Critical_Middle::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Effect\\Hit_Critical_Middle", this, 0);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Effect\\Hit_Critical_Middle", this, 1);

		at->CompleteEvent(L"EffectHit_Critical_Middle") = std::bind(&Hit_Critical_Middle::Compelete, this);
		at->CompleteEvent(L"EffectHit_Critical_MiddleR") = std::bind(&Hit_Critical_Middle::Compelete, this);

		at->PlayAnimation(L"EffectHit_Critical_Middle", true);

		GameObject::Initialize();
	}
	void Hit_Critical_Middle::Update()
	{
		if (_effect_animation == true)
		{
			if (_dir == 1)
				at->PlayAnimation(L"EffectHit_Critical_Middle", true);
			else
				at->PlayAnimation(L"EffectHit_Critical_MiddleR", true);
			_effect_animation = false;
		}

		GameObject::Update();
	}
	void Hit_Critical_Middle::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Hit_Critical_Middle::Render()
	{
		GameObject::Render();
	}
	void Hit_Critical_Middle::OnCollisionEnter(Collider2D* other)
	{
	}
	void Hit_Critical_Middle::OnCollisionStay(Collider2D* other)
	{
	}
	void Hit_Critical_Middle::OnCollisionExit(Collider2D* other)
	{
	}
	void Hit_Critical_Middle::Compelete()
	{
		this->SetState(eState::Paused);
	}
}