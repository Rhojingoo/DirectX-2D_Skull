#include "HitBox_Knight.h"
#include "Include_Common.h"


namespace jk
{
	HitBox_Knight::HitBox_Knight()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"DebugRect"));
		mr->SetMaterial(Resources::Find<Material>(L"DebugMaterial"));
	}
	HitBox_Knight::~HitBox_Knight()
	{
	}
	void HitBox_Knight::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_collider->SetSize(_Size);
		_collider->SetPosition(_Center);
		GameObject::Initialize();
	}
	void HitBox_Knight::Update()
	{
		GameObject::Update();
	}
	void HitBox_Knight::LateUpdate()
	{
		_Center.y = -15;
		_collider->SetSize(_Size);
		_collider->SetPosition(_Center);

		GameObject::LateUpdate();
	}
	void HitBox_Knight::Render()
	{
		GameObject::Render();
	}
	void HitBox_Knight::OnCollisionEnter(Collider2D* other)
	{
	}
	void HitBox_Knight::OnCollisionStay(Collider2D* other)
	{
	}
	void HitBox_Knight::OnCollisionExit(Collider2D* other)
	{
	}
}