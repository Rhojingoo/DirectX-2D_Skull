#include "Mage_BoomSign.h"
#include "Include_Common.h"

namespace jk
{
	Mage_BoomSign::Mage_BoomSign()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Mage_BoomSign::~Mage_BoomSign()
	{
	}
	void Mage_BoomSign::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Effect\\Attack_BoomSign", this);

		at->CompleteEvent(L"EffectAttack_BoomSign") = std::bind(&Mage_BoomSign::Compelete, this);
		at->PlayAnimation(L"EffectAttack_BoomSign", true);

		GameObject::Initialize();
	}
	void Mage_BoomSign::Update()
	{
		GameObject::Update();
	}
	void Mage_BoomSign::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Mage_BoomSign::Render()
	{
		GameObject::Render();
	}
	void Mage_BoomSign::OnCollisionEnter(Collider2D* other)
	{
	}
	void Mage_BoomSign::OnCollisionStay(Collider2D* other)
	{
	}
	void Mage_BoomSign::OnCollisionExit(Collider2D* other)
	{
	}
	void Mage_BoomSign::Compelete()
	{
		_effect_On = false;
		this->SetState(eState::Paused);
	}
}