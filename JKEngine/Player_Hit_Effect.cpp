#include "Player_Hit_Effect.h"

namespace jk
{
	Player_Hit_Effect::Player_Hit_Effect()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Player_Hit_Effect::~Player_Hit_Effect()
	{
	}
	void Player_Hit_Effect::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Effect\\Hit_Skul", this, 0,0.05);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Effect\\Hit_Skul", this, 1,0.05);

		at->CompleteEvent(L"EffectHit_Skul") = std::bind(&Player_Hit_Effect::Compelete, this);
		at->CompleteEvent(L"EffectHit_SkulR") = std::bind(&Player_Hit_Effect::Compelete, this);

		at->PlayAnimation(L"EffectHit_Skul", true);

		GameObject::Initialize();
	}
	void Player_Hit_Effect::Update()
	{
		if (_effect_animation == true)
		{
			if (_dir == 1)
				at->PlayAnimation(L"EffectHit_Skul", true);
			else
				at->PlayAnimation(L"EffectHit_SkulR", true);
			_effect_animation = false;
		}

		GameObject::Update();
	}
	void Player_Hit_Effect::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Player_Hit_Effect::Render()
	{
		GameObject::Render();
	}
	void Player_Hit_Effect::OnCollisionEnter(Collider2D* other)
	{
	}
	void Player_Hit_Effect::OnCollisionStay(Collider2D* other)
	{
	}
	void Player_Hit_Effect::OnCollisionExit(Collider2D* other)
	{
	}


	void Player_Hit_Effect::Compelete()
	{
		_endeffect = true;
		this->SetState(eState::Paused);
	}
}