#include "Death_Effect_First.h"
#include "Include_Common.h"


namespace jk
{
	Death_Effect_First::Death_Effect_First()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Death_Effect_First::~Death_Effect_First()
	{
	}
	void Death_Effect_First::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Death_Effect\\Dark_Dead_Loop", this, 0, 0.075f);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Death_Effect\\Dark_Dead_Loop", this, 1, 0.075f);
		at->CompleteEvent(L"Death_EffectDark_Dead_Loop") = std::bind(&Death_Effect_First::Compelete_Pierce, this);
		at->CompleteEvent(L"Death_EffectDark_Dead_LoopR") = std::bind(&Death_Effect_First::Compelete_Pierce, this);

		at->PlayAnimation(L"Death_EffectDark_Dead_Loop", true);
		GameObject::Initialize();
	}
	void Death_Effect_First::Update()
	{
		if (_SwitchOn == true)
		{
			if (_Dir == 1)
				at->PlayAnimation(L"Death_EffectDark_Dead_Loop", true);
			else
				at->PlayAnimation(L"Death_EffectDark_Dead_LoopR", true);
			_SwitchOn = false;
		}
		GameObject::Update();
	}
	void Death_Effect_First::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Death_Effect_First::Render()
	{
		GameObject::Render();
	}
	void Death_Effect_First::OnCollisionEnter(Collider2D* other)
	{
	}
	void Death_Effect_First::OnCollisionStay(Collider2D* other)
	{
	}
	void Death_Effect_First::OnCollisionExit(Collider2D* other)
	{
	}
	void Death_Effect_First::Compelete_Pierce()
	{
		//this->SetState(eState::Paused);
	}
}