#include "Death_Elect_First.h"

namespace jk
{
	Death_Elect_First::Death_Elect_First()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Death_Elect_First::~Death_Elect_First()
	{
	}
	void Death_Elect_First::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Death_Effect\\Dark_Dead_Electric1", this, 0, 0.075f);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Death_Effect\\Dark_Dead_Electric1", this, 1, 0.075f);
		at->CompleteEvent(L"Death_EffectDark_Dead_Electric1") = std::bind(&Death_Elect_First::Compelete_Pierce, this);
		at->CompleteEvent(L"Death_EffectDark_Dead_Electric1") = std::bind(&Death_Elect_First::Compelete_Pierce, this);

		at->PlayAnimation(L"Death_EffectDark_Dead_Electric1", true);
		GameObject::Initialize();
	}
	void Death_Elect_First::Update()
	{
		if (_SwitchOn == true)
		{
			if (mDir == 1)
				at->PlayAnimation(L"Death_EffectDark_Dead_Electric1", true);
			else
				at->PlayAnimation(L"Death_EffectDark_Dead_Electric1R", true);
			_SwitchOn = false;
		}
		GameObject::Update();
	}
	void Death_Elect_First::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Death_Elect_First::Render()
	{
		GameObject::Render();
	}
	void Death_Elect_First::OnCollisionEnter(Collider2D* other)
	{
	}
	void Death_Elect_First::OnCollisionStay(Collider2D* other)
	{
	}
	void Death_Elect_First::OnCollisionExit(Collider2D* other)
	{
	}
	void Death_Elect_First::Compelete_Pierce()
	{
		this->SetState(eState::Paused);
	}
}