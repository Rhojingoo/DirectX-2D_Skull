#include "Yggdrasil_ChinDead_Effect.h"

namespace jk
{
	Yggdrasil_ChinDead_Effect::Yggdrasil_ChinDead_Effect()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Yggdrasil_ChinDead_Effect::~Yggdrasil_ChinDead_Effect()
	{
	}
	void Yggdrasil_ChinDead_Effect::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		tr = this->GetComponent<Transform>();

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Chind\\CHIN_Die_Effect", this, 0);


		at->PlayAnimation(L"ChindCHIN_Die_Effect", false);
		GameObject::Initialize();
	}
	void Yggdrasil_ChinDead_Effect::Update()
	{
		mTime = Time::DeltaTime();
		if (mTime > 1)
		{
			this->SetState(eState::Paused);
		}
		GameObject::Update();
	}
	void Yggdrasil_ChinDead_Effect::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Yggdrasil_ChinDead_Effect::Render()
	{
		GameObject::Render();
	}
	void Yggdrasil_ChinDead_Effect::OnCollisionEnter(Collider2D* other)
	{
	}
	void Yggdrasil_ChinDead_Effect::OnCollisionStay(Collider2D* other)
	{
	}
	void Yggdrasil_ChinDead_Effect::OnCollisionExit(Collider2D* other)
	{
	}
}