#include "Knight_Energe_Blast.h"


namespace jk
{
	Knight_Energe_Blast::Knight_Energe_Blast()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Knight_Energe_Blast::~Knight_Energe_Blast()
	{
	}
	void Knight_Energe_Blast::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		tr = this->GetComponent<Transform>();


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Bullet\\Energe_Blast", this);
		at->CompleteEvent(L"BulletEnerge_Blast") = std::bind(&Knight_Energe_Blast::Compelete, this);

		at->PlayAnimation(L"BulletEnerge_Blast", true);
		GameObject::Initialize();
	}
	void Knight_Energe_Blast::Update()
	{
		GameObject::Update();
	}
	void Knight_Energe_Blast::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Knight_Energe_Blast::Render()
	{
		GameObject::Render();
	}
	void Knight_Energe_Blast::OnCollisionEnter(Collider2D* other)
	{
	}
	void Knight_Energe_Blast::OnCollisionStay(Collider2D* other)
	{
	}
	void Knight_Energe_Blast::OnCollisionExit(Collider2D* other)
	{
	}
	void Knight_Energe_Blast::Compelete()
	{
		_EffectEnd = true;
		this->SetState(eState::Paused);
	}
}