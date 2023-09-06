#include "Hit_Sword.h"

namespace jk
{
	Hit_Sword::Hit_Sword()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Hit_Sword::~Hit_Sword()
	{
	}
	void Hit_Sword::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Effect\\Hit_SkeletonSword", this, 0);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Effect\\Hit_SkeletonSword", this, 1);

		at->CompleteEvent(L"EffectHit_SkeletonSword") = std::bind(&Hit_Sword::Compelete, this);
		at->CompleteEvent(L"EffectHit_SkeletonSwordR") = std::bind(&Hit_Sword::Compelete, this);

		at->PlayAnimation(L"EffectHit_SkeletonSword", true);

		GameObject::Initialize();
	}
	void Hit_Sword::Update()
	{
		if (_effect_animation == true)
		{
			if (_dir == 1)
				at->PlayAnimation(L"EffectHit_SkeletonSword", true);
			else
				at->PlayAnimation(L"EffectHit_SkeletonSwordR", true);
			_effect_animation = false;
		}

		GameObject::Update();
	}
	void Hit_Sword::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Hit_Sword::Render()
	{
		GameObject::Render();
	}
	void Hit_Sword::OnCollisionEnter(Collider2D* other)
	{
	}
	void Hit_Sword::OnCollisionStay(Collider2D* other)
	{
	}
	void Hit_Sword::OnCollisionExit(Collider2D* other)
	{
	}
	void Hit_Sword::Compelete()
	{
		this->SetState(eState::Paused);
	}
}