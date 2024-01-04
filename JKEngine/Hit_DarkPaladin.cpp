#include "Hit_DarkPaladin.h"
#include "Include_Common.h"

namespace jk
{
	Hit_DarkPaladin::Hit_DarkPaladin()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Hit_DarkPaladin::~Hit_DarkPaladin()
	{
	}
	void Hit_DarkPaladin::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Effect\\Hit_DarkPaladin", this, 0);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Effect\\Hit_DarkPaladin", this, 1);

		at->CompleteEvent(L"EffectHit_DarkPaladin") = std::bind(&Hit_DarkPaladin::Compelete, this);
		at->CompleteEvent(L"EffectHit_DarkPaladinR") = std::bind(&Hit_DarkPaladin::Compelete, this);

		at->PlayAnimation(L"EffectHit_DarkPaladin", true);

		GameObject::Initialize();
	}
	void Hit_DarkPaladin::Update()
	{
		if (_effect_animation == true)
		{
			if (_dir == 1)
				at->PlayAnimation(L"EffectHit_DarkPaladin", true);
			else
				at->PlayAnimation(L"EffectHit_DarkPaladinR", true);
			_effect_animation = false;
		}

		GameObject::Update();
	}
	void Hit_DarkPaladin::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Hit_DarkPaladin::Render()
	{
		GameObject::Render();
	}
	void Hit_DarkPaladin::OnCollisionEnter(Collider2D* other)
	{
	}
	void Hit_DarkPaladin::OnCollisionStay(Collider2D* other)
	{
	}
	void Hit_DarkPaladin::OnCollisionExit(Collider2D* other)
	{
	}
	void Hit_DarkPaladin::Compelete()
	{
		this->SetState(eState::Paused);
	}
}