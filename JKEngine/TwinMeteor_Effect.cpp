#include "TwinMeteor_Effect.h"

namespace jk
{
	int TwinMeteor_Effect::mDir = 1;
	bool TwinMeteor_Effect::_SwitchOn = false;
	bool TwinMeteor_Effect::_SwitchOff = false;
	TwinMeteor_Effect::TwinMeteor_Effect()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	TwinMeteor_Effect::~TwinMeteor_Effect()
	{
	}
	void TwinMeteor_Effect::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Effect\\TwinMeteor_Impact", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Effect\\TwinMeteor_Impact", this, 1);
		at->CompleteEvent(L"EffectTwinMeteor_Impact") = std::bind(&TwinMeteor_Effect::Compelete_Pierce, this);
		at->CompleteEvent(L"EffectTwinMeteor_ImpactR") = std::bind(&TwinMeteor_Effect::Compelete_Pierce, this);
		
		at->PlayAnimation(L"EffectTwinMeteor_Impact", true);
		GameObject::Initialize();
	}
	void TwinMeteor_Effect::Update()
	{
		if (_SwitchOn == true)
		{
			if (mDir == 1)
				at->PlayAnimation(L"EffectTwinMeteor_Impact", true);
			else
				at->PlayAnimation(L"EffectTwinMeteor_ImpactR", true);
			_SwitchOn = false;
		}
		GameObject::Update();
	}
	void TwinMeteor_Effect::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void TwinMeteor_Effect::Render()
	{
		GameObject::Render();
	}
	void TwinMeteor_Effect::OnCollisionEnter(Collider2D* other)
	{
	}
	void TwinMeteor_Effect::OnCollisionStay(Collider2D* other)
	{
	}
	void TwinMeteor_Effect::OnCollisionExit(Collider2D* other)
	{
	}
	void TwinMeteor_Effect::Compelete_Pierce()
	{
		_SwitchOff = true;
		this->SetState(eState::Paused);
	}
}