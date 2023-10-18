#include "Yggdrasil_EnergeBall_CreateEffect.h"

namespace jk
{
	bool Yggdrasil_EnergeBall_CreateEffect::Groggy_Strat = false;
	Yggdrasil_EnergeBall_CreateEffect::Yggdrasil_EnergeBall_CreateEffect()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Yggdrasil_EnergeBall_CreateEffect::~Yggdrasil_EnergeBall_CreateEffect()
	{
	}
	void Yggdrasil_EnergeBall_CreateEffect::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Effect\\EnergyBallmerge", this, 0, 0.02f);
		at->CompleteEvent(L"EffectEnergyBallmerge") = std::bind(&Yggdrasil_EnergeBall_CreateEffect::Compelete, this);

		at->PlayAnimation(L"EffectEnergyBallmerge", true);
		GameObject::Initialize();
	}
	void Yggdrasil_EnergeBall_CreateEffect::Update()
	{
		GameObject::Update();
	}
	void Yggdrasil_EnergeBall_CreateEffect::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Yggdrasil_EnergeBall_CreateEffect::Render()
	{
		GameObject::Render();
	}
	void Yggdrasil_EnergeBall_CreateEffect::OnCollisionEnter(Collider2D* other)
	{
	}
	void Yggdrasil_EnergeBall_CreateEffect::OnCollisionStay(Collider2D* other)
	{
	}
	void Yggdrasil_EnergeBall_CreateEffect::OnCollisionExit(Collider2D* other)
	{
	}
	void Yggdrasil_EnergeBall_CreateEffect::Compelete()
	{
		_EffectOn = false;
	}
}