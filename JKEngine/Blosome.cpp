#include "Blosome.h"
#include "Include_Common.h"

namespace jk
{
	Blosome::Blosome()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Blosome::~Blosome()
	{
	}
	void Blosome::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		//_collider->SetType(eColliderType::Circle);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\particle\\Blossom", this);
		at->PlayAnimation(L"particleBlossom", true);
		GameObject::Initialize();
	}
	void Blosome::Update()
	{
		GameObject::Update();
	}
	void Blosome::LateUpdate()
	{
		//_collider->SetSize(Vector2(0.0f, 0.0f));
		//_collider->SetCenter(Vector2(0.0f, -0.01f));
		GameObject::LateUpdate();
	}
	void Blosome::Render()
	{
		GameObject::Render();
	}
	void Blosome::OnCollisionEnter(Collider2D* other)
	{
	}
	void Blosome::OnCollisionStay(Collider2D* other)
	{
	}
	void Blosome::OnCollisionExit(Collider2D* other)
	{
	}
}