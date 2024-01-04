#include "Monster_Ent_GroundAttack.h"
#include "Include_Common.h"

namespace jk
{
	Monster_Ent_GroundAttack::Monster_Ent_GroundAttack()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Monster_Ent_GroundAttack::~Monster_Ent_GroundAttack()
	{
	}
	void Monster_Ent_GroundAttack::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		tr = this->GetComponent<Transform>();

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GreenTree\\Bullet\\Ent_Attack", this);

		at->CompleteEvent(L"BulletEnt_Attack") = std::bind(&Monster_Ent_GroundAttack::complete, this);

		at->PlayAnimation(L"BulletEnt_Attack", true);
		GameObject::Initialize();
	}
	void Monster_Ent_GroundAttack::Update()
	{
		GameObject::Update();
	}
	void Monster_Ent_GroundAttack::LateUpdate()
	{
		_collider->SetSize(Vector2(0.85f, 0.85f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Monster_Ent_GroundAttack::Render()
	{
		GameObject::Render();
	}
	void Monster_Ent_GroundAttack::OnCollisionEnter(Collider2D* other)
	{
	}
	void Monster_Ent_GroundAttack::OnCollisionStay(Collider2D* other)
	{
	}
	void Monster_Ent_GroundAttack::OnCollisionExit(Collider2D* other)
	{
	}
	void Monster_Ent_GroundAttack::complete()
	{
		this->SetState(eState::Paused);
	}
}