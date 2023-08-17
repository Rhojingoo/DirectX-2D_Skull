#include "Yggdrasil_EnergyCorps_Spark.h"

namespace jk
{
	Yggdrasil_EnergyCorps_Spark::Yggdrasil_EnergyCorps_Spark()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Yggdrasil_EnergyCorps_Spark::~Yggdrasil_EnergyCorps_Spark()
	{
	}
	void Yggdrasil_EnergyCorps_Spark::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Effect\\EnergyCorps_Spark", this, 0, 0.03);
		at->CompleteEvent(L"EffectEnergyCorps_Spark") = std::bind(&Yggdrasil_EnergyCorps_Spark::Compelete, this);

		at->PlayAnimation(L"EffectEnergyCorps_Spark", true);
		GameObject::Initialize();
	}
	void Yggdrasil_EnergyCorps_Spark::Update()
	{
		GameObject::Update();
	}
	void Yggdrasil_EnergyCorps_Spark::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Yggdrasil_EnergyCorps_Spark::Render()
	{
		GameObject::Render();
	}
	void Yggdrasil_EnergyCorps_Spark::OnCollisionEnter(Collider2D* other)
	{
	}
	void Yggdrasil_EnergyCorps_Spark::OnCollisionStay(Collider2D* other)
	{
	}
	void Yggdrasil_EnergyCorps_Spark::OnCollisionExit(Collider2D* other)
	{
	}
	void Yggdrasil_EnergyCorps_Spark::Compelete()
	{
		this->SetState(eState::Paused);
	}
}