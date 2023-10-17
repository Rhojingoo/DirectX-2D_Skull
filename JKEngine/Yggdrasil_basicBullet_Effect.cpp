#include "Yggdrasil_basicBullet_Effect.h"

namespace jk
{
	Yggdrasil_basicBullet_Effect::Yggdrasil_basicBullet_Effect()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Yggdrasil_basicBullet_Effect::~Yggdrasil_basicBullet_Effect()
	{
	}
	void Yggdrasil_basicBullet_Effect::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Effect\\Basic_bullet", this, 0, 0.045);
		at->CompleteEvent(L"EffectBasic_bullet") = std::bind(&Yggdrasil_basicBullet_Effect::Compelete, this);

		at->PlayAnimation(L"EffectBasic_bullet", true);
		GameObject::Initialize();
	}
	void Yggdrasil_basicBullet_Effect::Update()
	{
		GameObject::Update();
	}
	void Yggdrasil_basicBullet_Effect::LateUpdate()
	{
		_collider->SetSize(Vector2(0.0f, 0.0f));
		_collider->SetCenter(Vector2(0.0f, -0.01f));
		GameObject::LateUpdate();
	}
	void Yggdrasil_basicBullet_Effect::Render()
	{
		GameObject::Render();
	}
	void Yggdrasil_basicBullet_Effect::OnCollisionEnter(Collider2D* other)
	{
	}
	void Yggdrasil_basicBullet_Effect::OnCollisionStay(Collider2D* other)
	{
	}
	void Yggdrasil_basicBullet_Effect::OnCollisionExit(Collider2D* other)
	{
	}
	void Yggdrasil_basicBullet_Effect::Compelete()
	{
		this->SetState(eState::Paused);
	}
}