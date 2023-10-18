#include "Yggdrasil_Effect.h"

namespace jk
{
	bool Yggdrasil_Effect::_effect_switch = true;

	Yggdrasil_Effect::Yggdrasil_Effect()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Yggdrasil_Effect::~Yggdrasil_Effect()
	{
	}
	void Yggdrasil_Effect::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Effect\\EnergyBomb_Charging", this,0, 0.05f);
		at->CompleteEvent(L"EffectEnergyBomb_Charging") = std::bind(&Yggdrasil_Effect::Compelete, this);

		at->PlayAnimation(L"EffectEnergyBomb_Charging", true);
		GameObject::Initialize();
	}
	void Yggdrasil_Effect::Update()
	{
		GameObject::Update();
	}
	void Yggdrasil_Effect::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Yggdrasil_Effect::Render()
	{
		GameObject::Render();
	}
	void Yggdrasil_Effect::OnCollisionEnter(Collider2D* other)
	{
	}
	void Yggdrasil_Effect::OnCollisionStay(Collider2D* other)
	{
	}
	void Yggdrasil_Effect::OnCollisionExit(Collider2D* other)
	{
	}
	void Yggdrasil_Effect::Compelete()
	{
		Yggdrasil_Face::_Firstbullet = true;
		_effect_switch = false;
		this->SetState(eState::Paused);
	}
}