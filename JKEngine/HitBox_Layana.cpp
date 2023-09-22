#include "HitBox_Layana.h"

namespace jk
{
	HitBox_Layana::HitBox_Layana()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"DebugRect"));
		mr->SetMaterial(Resources::Find<Material>(L"DebugMaterial"));
	}
	HitBox_Layana::~HitBox_Layana()
	{
	}
	void HitBox_Layana::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_collider->SetSize(_Size);
		_collider->SetPosition(_Center);
		GameObject::Initialize();
	}
	void HitBox_Layana::Update()
	{
		GameObject::Update();
	}
	void HitBox_Layana::LateUpdate()
	{
		_Center.y = -15;
		_collider->SetSize(_Size);
		_collider->SetPosition(_Center);

		GameObject::LateUpdate();
	}
	void HitBox_Layana::Render()
	{
		GameObject::Render();
	}
	void HitBox_Layana::OnCollisionEnter(Collider2D* other)
	{
	}
	void HitBox_Layana::OnCollisionStay(Collider2D* other)
	{
	}
	void HitBox_Layana::OnCollisionExit(Collider2D* other)
	{
	}
}