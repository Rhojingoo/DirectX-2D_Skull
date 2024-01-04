#include "Yggdrasil_Dead_Impact1.h"
#include "Include_Common.h"

namespace jk
{
	Yggdrasil_Dead_Impact1::Yggdrasil_Dead_Impact1()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Yggdrasil_Dead_Impact1::~Yggdrasil_Dead_Impact1()
	{
	}
	void Yggdrasil_Dead_Impact1::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		tr = this->GetComponent<Transform>();

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Effect\\Die_Impact", this, 0);

		at->CompleteEvent(L"EffectDie_Impact") = std::bind(&Yggdrasil_Dead_Impact1::complete, this);
		
		at->PlayAnimation(L"EffectDie_Impact", true);
		GameObject::Initialize();
	}
	void Yggdrasil_Dead_Impact1::Update()
	{
		GameObject::Update();
	}
	void Yggdrasil_Dead_Impact1::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Yggdrasil_Dead_Impact1::Render()
	{
		GameObject::Render();
	}
	void Yggdrasil_Dead_Impact1::OnCollisionEnter(Collider2D* other)
	{
	}
	void Yggdrasil_Dead_Impact1::OnCollisionStay(Collider2D* other)
	{
	}
	void Yggdrasil_Dead_Impact1::OnCollisionExit(Collider2D* other)
	{
	}
	void Yggdrasil_Dead_Impact1::complete()
	{
		this->SetState(eState::Paused);
	}
}