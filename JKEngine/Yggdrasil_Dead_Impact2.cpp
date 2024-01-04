#include "Yggdrasil_Dead_Impact2.h"
#include "Include_Common.h"


namespace jk
{
	Yggdrasil_Dead_Impact2::Yggdrasil_Dead_Impact2()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Yggdrasil_Dead_Impact2::~Yggdrasil_Dead_Impact2()
	{
	}
	void Yggdrasil_Dead_Impact2::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		tr = this->GetComponent<Transform>();

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Effect\\Die_Impact2", this, 0);

		at->CompleteEvent(L"EffectDie_Impact2") = std::bind(&Yggdrasil_Dead_Impact2::complete, this);

		at->PlayAnimation(L"EffectDie_Impact2", true);
		GameObject::Initialize();
	}
	void Yggdrasil_Dead_Impact2::Update()
	{
		GameObject::Update();
	}
	void Yggdrasil_Dead_Impact2::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Yggdrasil_Dead_Impact2::Render()
	{
		GameObject::Render();
	}
	void Yggdrasil_Dead_Impact2::OnCollisionEnter(Collider2D* other)
	{
	}
	void Yggdrasil_Dead_Impact2::OnCollisionStay(Collider2D* other)
	{
	}
	void Yggdrasil_Dead_Impact2::OnCollisionExit(Collider2D* other)
	{
	}
	void Yggdrasil_Dead_Impact2::complete()
	{
		this->SetState(eState::Paused);
	}
}