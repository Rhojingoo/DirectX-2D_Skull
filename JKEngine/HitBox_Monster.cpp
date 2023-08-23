#include "HitBox_Monster.h"

namespace jk
{
	HitBox_Monster::HitBox_Monster()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"DebugRect"));
		mr->SetMaterial(Resources::Find<Material>(L"DebugMaterial"));
	}
	HitBox_Monster::~HitBox_Monster()
	{
	}
	void HitBox_Monster::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_collider->SetSize(_Size);
		_collider->SetPosition(_Center);
		GameObject::Initialize();
	}
	void HitBox_Monster::Update()
	{
		GameObject::Update();
	}
	void HitBox_Monster::LateUpdate()
	{
		_Center.y = -15;
		_collider->SetSize(_Size);
		_collider->SetPosition(_Center);

		GameObject::LateUpdate();
	}
	void HitBox_Monster::Render()
	{
		GameObject::Render();
	}
	void HitBox_Monster::OnCollisionEnter(Collider2D* other)
	{
	}
	void HitBox_Monster::OnCollisionStay(Collider2D* other)
	{
	}
	void HitBox_Monster::OnCollisionExit(Collider2D* other)
	{
	}
}