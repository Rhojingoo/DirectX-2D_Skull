#include "Death_Elect_Second.h"

namespace jk
{
	Death_Elect_Second::Death_Elect_Second()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Death_Elect_Second::~Death_Elect_Second()
	{
	}
	void Death_Elect_Second::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Death_Effect\\Dark_Dead_Electric2", this, 0, 0.075f);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Death_Effect\\Dark_Dead_Electric2", this, 1, 0.075f);
		at->CompleteEvent(L"Death_EffectDark_Dead_Electric2") = std::bind(&Death_Elect_Second::Compelete_Pierce, this);
		at->CompleteEvent(L"Death_EffectDark_Dead_Electric2R") = std::bind(&Death_Elect_Second::Compelete_Pierce, this);

		at->PlayAnimation(L"Death_EffectDark_Dead_Electric2", true);
		GameObject::Initialize();
	}
	void Death_Elect_Second::Update()
	{
		if (_SwitchOn == true)
		{
			if (mDir == 1)
				at->PlayAnimation(L"Death_EffectDark_Dead_Electric2", true);
			else
				at->PlayAnimation(L"Death_EffectDark_Dead_Electric2R", true);
			_SwitchOn = false;
		}
		GameObject::Update();
	}
	void Death_Elect_Second::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Death_Elect_Second::Render()
	{
		GameObject::Render();
	}
	void Death_Elect_Second::OnCollisionEnter(Collider2D* other)
	{
	}
	void Death_Elect_Second::OnCollisionStay(Collider2D* other)
	{
	}
	void Death_Elect_Second::OnCollisionExit(Collider2D* other)
	{
	}
	void Death_Elect_Second::Compelete_Pierce()
	{
		this->SetState(eState::Paused);
	}
}