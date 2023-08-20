#include "Kngiht_EnergyBall_Impact.h"

namespace jk
{
	Kngiht_EnergyBall_Impact::Kngiht_EnergyBall_Impact()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Kngiht_EnergyBall_Impact::~Kngiht_EnergyBall_Impact()
	{
	}
	void Kngiht_EnergyBall_Impact::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Effect\\EnergyBall_Impact", this);
		at->CompleteEvent(L"EffectEnergyBall_Impact") = std::bind(&Kngiht_EnergyBall_Impact::Compelete, this);

		at->PlayAnimation(L"EffectEnergyBall_Impact", true);

		GameObject::Initialize();
	}
	void Kngiht_EnergyBall_Impact::Update()
	{
		GameObject::Update();
	}
	void Kngiht_EnergyBall_Impact::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Kngiht_EnergyBall_Impact::Render()
	{
		GameObject::Render();
	}
	void Kngiht_EnergyBall_Impact::OnCollisionEnter(Collider2D* other)
	{
	}
	void Kngiht_EnergyBall_Impact::OnCollisionStay(Collider2D* other)
	{
	}
	void Kngiht_EnergyBall_Impact::OnCollisionExit(Collider2D* other)
	{
	}
	void Kngiht_EnergyBall_Impact::Compelete()
	{
		this->SetState(eState::Paused);
	}
}