#include "HitBox_YggDrasil.h"
#include "Include_Common.h"


namespace jk
{
	HitBox_YggDrasil::HitBox_YggDrasil()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"DebugRect"));
		mr->SetMaterial(Resources::Find<Material>(L"DebugMaterial"));
	}
	HitBox_YggDrasil::~HitBox_YggDrasil()
	{
	}
	void HitBox_YggDrasil::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_collider->SetSize(_Size);
		_collider->SetPosition(_Center);
		GameObject::Initialize();
	}
	void HitBox_YggDrasil::Update()
	{
		GameObject::Update();
	}
	void HitBox_YggDrasil::LateUpdate()
	{
		_Center.y = -15;
		_collider->SetSize(_Size);
		_collider->SetPosition(_Center);

		GameObject::LateUpdate();
	}
	void HitBox_YggDrasil::Render()
	{
		GameObject::Render();
	}
	void HitBox_YggDrasil::OnCollisionEnter(Collider2D* other)
	{
	}
	void HitBox_YggDrasil::OnCollisionStay(Collider2D* other)
	{
	}
	void HitBox_YggDrasil::OnCollisionExit(Collider2D* other)
	{
	}
}
