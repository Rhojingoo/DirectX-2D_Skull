#include "Archer_Utimate_Sign.h"

namespace jk
{
	Archer_Utimate_Sign::Archer_Utimate_Sign()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Archer_Utimate_Sign::~Archer_Utimate_Sign()
	{
	}
	void Archer_Utimate_Sign::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Effect\\Ultimate_Sign_Archer", this);
		
		at->CompleteEvent(L"EffectUltimate_Sign_Archer") = std::bind(&Archer_Utimate_Sign::Compelete, this);
		at->PlayAnimation(L"EffectUltimate_Sign_Archer", true);

		GameObject::Initialize();
	}
	void Archer_Utimate_Sign::Update()
	{
		GameObject::Update();
	}
	void Archer_Utimate_Sign::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Archer_Utimate_Sign::Render()
	{
		GameObject::Render();
	}
	void Archer_Utimate_Sign::OnCollisionEnter(Collider2D* other)
	{
	}
	void Archer_Utimate_Sign::OnCollisionStay(Collider2D* other)
	{
	}
	void Archer_Utimate_Sign::OnCollisionExit(Collider2D* other)
	{
	}
	void Archer_Utimate_Sign::Compelete()
	{
		_effect_On = false;
		this->SetState(eState::Paused);
	}
}