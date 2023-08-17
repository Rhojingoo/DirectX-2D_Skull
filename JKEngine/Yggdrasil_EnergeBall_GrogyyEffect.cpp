#include "Yggdrasil_EnergeBall_GrogyyEffect.h"

namespace jk
{
	bool Yggdrasil_EnergeBall_GrogyyEffect::Groggy_Strat = false;
	Yggdrasil_EnergeBall_GrogyyEffect::Yggdrasil_EnergeBall_GrogyyEffect()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Yggdrasil_EnergeBall_GrogyyEffect::~Yggdrasil_EnergeBall_GrogyyEffect()
	{
	}
	void Yggdrasil_EnergeBall_GrogyyEffect::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Effect\\EnergyBallmerge", this, 0, 0.05);
		at->CompleteEvent(L"EffectEnergyBallmerge") = std::bind(&Yggdrasil_EnergeBall_GrogyyEffect::Compelete, this);

		at->PlayAnimation(L"EffectEnergyBallmerge", true);
		GameObject::Initialize();
	}
	void Yggdrasil_EnergeBall_GrogyyEffect::Update()
	{
		GameObject::Update();
	}
	void Yggdrasil_EnergeBall_GrogyyEffect::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Yggdrasil_EnergeBall_GrogyyEffect::Render()
	{
		GameObject::Render();
	}
	void Yggdrasil_EnergeBall_GrogyyEffect::OnCollisionEnter(Collider2D* other)
	{
	}
	void Yggdrasil_EnergeBall_GrogyyEffect::OnCollisionStay(Collider2D* other)
	{
	}
	void Yggdrasil_EnergeBall_GrogyyEffect::OnCollisionExit(Collider2D* other)
	{
	}
	void Yggdrasil_EnergeBall_GrogyyEffect::Compelete()
	{
		Groggy_Strat = true;
		this->SetState(eState::Paused);
	}
}