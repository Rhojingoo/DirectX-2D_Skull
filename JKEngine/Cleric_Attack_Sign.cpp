#include "Cleric_Attack_Sign.h"

namespace jk
{
	Cleric_Attack_Sign::Cleric_Attack_Sign()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Cleric_Attack_Sign::~Cleric_Attack_Sign()
	{
	}
	void Cleric_Attack_Sign::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Effect\\Attack_Sign_Cleric", this);

		at->CompleteEvent(L"EffectAttack_Sign_Cleric") = std::bind(&Cleric_Attack_Sign::Compelete, this);
		at->PlayAnimation(L"EffectAttack_Sign_Cleric", true);

		GameObject::Initialize();
	}
	void Cleric_Attack_Sign::Update()
	{
		GameObject::Update();
	}
	void Cleric_Attack_Sign::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Cleric_Attack_Sign::Render()
	{
		GameObject::Render();
	}
	void Cleric_Attack_Sign::OnCollisionEnter(Collider2D* other)
	{
	}
	void Cleric_Attack_Sign::OnCollisionStay(Collider2D* other)
	{
	}
	void Cleric_Attack_Sign::OnCollisionExit(Collider2D* other)
	{
	}
	void Cleric_Attack_Sign::Compelete()
	{
		_effect_On = false;
		this->SetState(eState::Paused);
	}
}