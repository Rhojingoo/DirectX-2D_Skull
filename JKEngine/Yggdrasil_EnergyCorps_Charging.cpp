#include "Yggdrasil_EnergyCorps_Charging.h"
#include "Include_Common.h"


namespace jk
{
	Yggdrasil_EnergyCorps_Charging::Yggdrasil_EnergyCorps_Charging()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Yggdrasil_EnergyCorps_Charging::~Yggdrasil_EnergyCorps_Charging()
	{
	}
	void Yggdrasil_EnergyCorps_Charging::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Effect\\EnergyCorps_Charging", this, 0);
		at->CompleteEvent(L"EffectEnergyCorps_Charging") = std::bind(&Yggdrasil_EnergyCorps_Charging::Compelete, this);

		at->PlayAnimation(L"EffectEnergyCorps_Charging", true);
		GameObject::Initialize();
	}
	void Yggdrasil_EnergyCorps_Charging::Update()
	{
		GameObject::Update();
	}
	void Yggdrasil_EnergyCorps_Charging::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Yggdrasil_EnergyCorps_Charging::Render()
	{
		GameObject::Render();
	}
	void Yggdrasil_EnergyCorps_Charging::OnCollisionEnter(Collider2D* other)
	{
	}
	void Yggdrasil_EnergyCorps_Charging::OnCollisionStay(Collider2D* other)
	{
	}
	void Yggdrasil_EnergyCorps_Charging::OnCollisionExit(Collider2D* other)
	{
	}
	void Yggdrasil_EnergyCorps_Charging::Compelete()
	{
		Yggdrasil_Face::_Firstbullet = true;
		this->SetState(eState::Paused);
	}
}