#include "Yggdrasil_FistSlam_Effect.h"

namespace jk
{
	Yggdrasil_FistSlam_Effect::Yggdrasil_FistSlam_Effect()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Yggdrasil_FistSlam_Effect::~Yggdrasil_FistSlam_Effect()
	{
	}
	void Yggdrasil_FistSlam_Effect::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Effect\\FistSlam_Impact", this, 0, 0.02f);
		at->CompleteEvent(L"EffectFistSlam_Impact") = std::bind(&Yggdrasil_FistSlam_Effect::Compelete, this);

		at->PlayAnimation(L"EffectFistSlam_Impact", true);
		GameObject::Initialize();
	}
	void Yggdrasil_FistSlam_Effect::Update()
	{
		GameObject::Update();
	}
	void Yggdrasil_FistSlam_Effect::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Yggdrasil_FistSlam_Effect::Render()
	{
		GameObject::Render();
	}
	void Yggdrasil_FistSlam_Effect::OnCollisionEnter(Collider2D* other)
	{
	}
	void Yggdrasil_FistSlam_Effect::OnCollisionStay(Collider2D* other)
	{
	}
	void Yggdrasil_FistSlam_Effect::OnCollisionExit(Collider2D* other)
	{
	}
	void Yggdrasil_FistSlam_Effect::Compelete()
	{
		_EffectOn = false;
		this->SetState(eState::Paused);
	}
}