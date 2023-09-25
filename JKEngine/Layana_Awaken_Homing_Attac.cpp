#include "Layana_Awaken_Homing_Attac.h"

namespace jk
{
	Layana_Awaken_Homing_Attac::Layana_Awaken_Homing_Attac()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Layana_Awaken_Homing_Attac::~Layana_Awaken_Homing_Attac()
	{
	}
	void Layana_Awaken_Homing_Attac::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Bullet\\Dark_HomingPierce_Effect_Attac", this, 0, 0.1, Vector2(0.06f, 0.0f));

		at->CompleteEvent(L"BulletDark_HomingPierce_Effect_Attac") = std::bind(&Layana_Awaken_Homing_Attac::Compelete_Pierce, this);

		at->PlayAnimation(L"BulletDark_HomingPierce_Effect_Attac", true);
		GameObject::Initialize();
	}
	void Layana_Awaken_Homing_Attac::Update()
	{
		GameObject::Update();
	}
	void Layana_Awaken_Homing_Attac::LateUpdate()
	{
		_collider->SetSize(Vector2(0.9f, 0.2f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Layana_Awaken_Homing_Attac::Render()
	{
		GameObject::Render();
	}
	void Layana_Awaken_Homing_Attac::OnCollisionEnter(Collider2D* other)
	{
	}
	void Layana_Awaken_Homing_Attac::OnCollisionStay(Collider2D* other)
	{
	}
	void Layana_Awaken_Homing_Attac::OnCollisionExit(Collider2D* other)
	{
	}
	void Layana_Awaken_Homing_Attac::Compelete_Pierce()
	{
		_bulletoff = true;
		this->SetState(eState::Paused);
	}
}