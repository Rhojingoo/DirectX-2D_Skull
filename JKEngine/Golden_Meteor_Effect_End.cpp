#include "Golden_Meteor_Effect_End.h"

namespace jk
{
	Golden_Meteor_Effect_End::Golden_Meteor_Effect_End()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Golden_Meteor_Effect_End::~Golden_Meteor_Effect_End()
	{
	}
	void Golden_Meteor_Effect_End::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Effect\\Golden_Meteor_Effect_End", this, 0 );
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Effect\\Golden_Meteor_Effect_End", this, 1 );
		at->CompleteEvent(L"EffectGolden_Meteor_Effect_End") = std::bind(&Golden_Meteor_Effect_End::Compelete_Pierce, this);
		at->CompleteEvent(L"EffectGolden_Meteor_Effect_EndR") = std::bind(&Golden_Meteor_Effect_End::Compelete_Pierce, this);

		at->PlayAnimation(L"EffectGolden_Meteor_Effect_End", true);
		GameObject::Initialize();
	}
	void Golden_Meteor_Effect_End::Update()
	{
		if (_SwitchOn == true)
		{
			if (mDir == 1)
				at->PlayAnimation(L"EffectGolden_Meteor_Effect_End", true);
			else
				at->PlayAnimation(L"EffectGolden_Meteor_Effect_EndR", true);
			_SwitchOn = false;
		}
		GameObject::Update();
	}
	void Golden_Meteor_Effect_End::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Golden_Meteor_Effect_End::Render()
	{
		GameObject::Render();
	}
	void Golden_Meteor_Effect_End::OnCollisionEnter(Collider2D* other)
	{
	}
	void Golden_Meteor_Effect_End::OnCollisionStay(Collider2D* other)
	{
	}
	void Golden_Meteor_Effect_End::OnCollisionExit(Collider2D* other)
	{
	}
	void Golden_Meteor_Effect_End::Compelete_Pierce()
	{
		this->SetState(eState::Paused);
	}
}