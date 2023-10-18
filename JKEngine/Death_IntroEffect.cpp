#include "Death_IntroEffect.h"

namespace jk
{
	Death_IntroEffect::Death_IntroEffect()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Death_IntroEffect::~Death_IntroEffect()
	{
	}
	void Death_IntroEffect::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Death_Effect\\Dark_Dead_Intro", this, 0, 0.075f);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Death_Effect\\Dark_Dead_Intro", this, 1, 0.075f);
		at->CompleteEvent(L"Death_EffectDark_Dead_Intro") = std::bind(&Death_IntroEffect::Compelete_Pierce, this);
		at->CompleteEvent(L"Death_EffectDark_Dead_IntroR") = std::bind(&Death_IntroEffect::Compelete_Pierce, this);

		at->PlayAnimation(L"Death_EffectDark_Dead_Intro", true);
		GameObject::Initialize();
	}
	void Death_IntroEffect::Update()
	{
		if (_SwitchOn == true)
		{
			if (mDir == 1)
				at->PlayAnimation(L"Death_EffectDark_Dead_Intro", true);
			else
				at->PlayAnimation(L"Death_EffectDark_Dead_IntroR", true);
			_SwitchOn = false;
		}
		GameObject::Update();
	}
	void Death_IntroEffect::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Death_IntroEffect::Render()
	{
		GameObject::Render();
	}
	void Death_IntroEffect::OnCollisionEnter(Collider2D* other)
	{
	}
	void Death_IntroEffect::OnCollisionStay(Collider2D* other)
	{
	}
	void Death_IntroEffect::OnCollisionExit(Collider2D* other)
	{
	}
	void Death_IntroEffect::Compelete_Pierce()
	{
		_Fnish = true;
		this->SetState(eState::Paused);
	}
}