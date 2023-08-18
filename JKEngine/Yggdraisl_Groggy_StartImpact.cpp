#include "Yggdraisl_Groggy_StartImpact.h"

namespace jk
{
	Yggdraisl_Groggy_StartImpact::Yggdraisl_Groggy_StartImpact()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Yggdraisl_Groggy_StartImpact::~Yggdraisl_Groggy_StartImpact()
	{
	}
	void Yggdraisl_Groggy_StartImpact::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Effect\\EnergyCorps_StartImpact", this, 0);
		at->CompleteEvent(L"EffectEnergyCorps_StartImpact") = std::bind(&Yggdraisl_Groggy_StartImpact::Compelete, this);

		at->PlayAnimation(L"EffectEnergyCorps_StartImpact", true);
		GameObject::Initialize();
	}
	void Yggdraisl_Groggy_StartImpact::Update()
	{
		GameObject::Update();
	}
	void Yggdraisl_Groggy_StartImpact::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Yggdraisl_Groggy_StartImpact::Render()
	{
		GameObject::Render();
	}
	void Yggdraisl_Groggy_StartImpact::OnCollisionEnter(Collider2D* other)
	{
	}
	void Yggdraisl_Groggy_StartImpact::OnCollisionStay(Collider2D* other)
	{
	}
	void Yggdraisl_Groggy_StartImpact::OnCollisionExit(Collider2D* other)
	{
	}
	void Yggdraisl_Groggy_StartImpact::Compelete()
	{
		_groggystartefeect_switch = false;
		this->SetState(eState::Paused);
	}
}
