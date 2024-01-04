#include "Yggdrasil_EnergyBullet_Effect.h"
#include "Include_Common.h"

namespace jk
{
	Yggdrasil_EnergyBullet_Effect::Yggdrasil_EnergyBullet_Effect()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Yggdrasil_EnergyBullet_Effect::~Yggdrasil_EnergyBullet_Effect()
	{
	}
	void Yggdrasil_EnergyBullet_Effect::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Effect\\EnergyBullet_Effect", this,0,0.05f);
		at->CompleteEvent(L"EffectEnergyBullet_Effect") = std::bind(&Yggdrasil_EnergyBullet_Effect::Compelete, this);

		at->PlayAnimation(L"EffectEnergyBullet_Effect", true);
		GameObject::Initialize();
	}
	void Yggdrasil_EnergyBullet_Effect::Update()
	{
		GameObject::Update();
	}
	void Yggdrasil_EnergyBullet_Effect::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Yggdrasil_EnergyBullet_Effect::Render()
	{
		GameObject::Render();
	}
	void Yggdrasil_EnergyBullet_Effect::OnCollisionEnter(Collider2D* other)
	{
	}
	void Yggdrasil_EnergyBullet_Effect::OnCollisionStay(Collider2D* other)
	{
	}
	void Yggdrasil_EnergyBullet_Effect::OnCollisionExit(Collider2D* other)
	{
	}
	void Yggdrasil_EnergyBullet_Effect::Compelete()
	{
		this->SetState(eState::Paused);
	}
}