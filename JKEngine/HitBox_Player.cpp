#include "HitBox_Player.h"

namespace jk
{
	HitBox_Player::HitBox_Player()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"DebugRect"));
		mr->SetMaterial(Resources::Find<Material>(L"DebugMaterial"));
	}
	HitBox_Player::~HitBox_Player()
	{
	}
	void HitBox_Player::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_collider->SetSize(Vector2(150.f, 150.f));
		_collider->SetPosition(Vector3(0.f, 0.f, -250.f));
		GameObject::Initialize();
	}
	void HitBox_Player::Update()
	{
		GameObject::Update();
	}
	void HitBox_Player::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void HitBox_Player::Render()
	{
		GameObject::Render();
	}
	void HitBox_Player::OnCollisionEnter(Collider2D* other)
	{
	}
	void HitBox_Player::OnCollisionStay(Collider2D* other)
	{
	}
	void HitBox_Player::OnCollisionExit(Collider2D* other)
	{
	}
}