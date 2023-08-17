#include "Yggdrasil_Groggy_GroundEffect.h"


namespace jk
{
	Yggdrasil_Groggy_GroundEffect::Yggdrasil_Groggy_GroundEffect()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Yggdrasil_Groggy_GroundEffect::~Yggdrasil_Groggy_GroundEffect()
	{
	}
	void Yggdrasil_Groggy_GroundEffect::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Effect\\Grogy_Impact", this, 0, 0.05);
		at->CompleteEvent(L"EffectGrogy_Impact") = std::bind(&Yggdrasil_Groggy_GroundEffect::Compelete, this);

		at->PlayAnimation(L"EffectGrogy_Impact", true);
		GameObject::Initialize();
	}
	void Yggdrasil_Groggy_GroundEffect::Update()
	{
		GameObject::Update();
	}
	void Yggdrasil_Groggy_GroundEffect::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Yggdrasil_Groggy_GroundEffect::Render()
	{
		GameObject::Render();
	}
	void Yggdrasil_Groggy_GroundEffect::OnCollisionEnter(Collider2D* other)
	{
	}
	void Yggdrasil_Groggy_GroundEffect::OnCollisionStay(Collider2D* other)
	{
	}
	void Yggdrasil_Groggy_GroundEffect::OnCollisionExit(Collider2D* other)
	{
	}
	void Yggdrasil_Groggy_GroundEffect::Compelete()
	{
		this->SetState(eState::Paused);
	}
}