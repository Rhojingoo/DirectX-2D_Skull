#include "Death_Effect_Second.h"

namespace jk
{
	Death_Effect_Second::Death_Effect_Second()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Death_Effect_Second::~Death_Effect_Second()
	{
	}
	void Death_Effect_Second::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Death_Effect\\Dark_Dead_Outro", this, 0, 0.075f);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Death_Effect\\Dark_Dead_Outro", this, 1, 0.075f);
		at->CompleteEvent(L"Death_EffectDark_Dead_Outro") = std::bind(&Death_Effect_Second::Compelete_Pierce, this);
		at->CompleteEvent(L"Death_EffectDark_Dead_OutroR") = std::bind(&Death_Effect_Second::Compelete_Pierce, this);

		at->PlayAnimation(L"Death_EffectDark_Dead_Outro", true);
		GameObject::Initialize();
	}
	void Death_Effect_Second::Update()
	{
		if (_SwitchOn == true)
		{
			if (mDir == 1)
				at->PlayAnimation(L"Death_EffectDark_Dead_Outro", true);
			else
				at->PlayAnimation(L"Death_EffectDark_Dead_OutroR", true);
			_SwitchOn = false;
		}
		GameObject::Update();
	}
	void Death_Effect_Second::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Death_Effect_Second::Render()
	{
		GameObject::Render();
	}
	void Death_Effect_Second::OnCollisionEnter(Collider2D* other)
	{
	}
	void Death_Effect_Second::OnCollisionStay(Collider2D* other)
	{
	}
	void Death_Effect_Second::OnCollisionExit(Collider2D* other)
	{
	}
	void Death_Effect_Second::Compelete_Pierce()
	{
		this->SetState(eState::Paused);
	}
}