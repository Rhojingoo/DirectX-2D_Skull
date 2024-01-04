#include "HitBox_Archer.h"
#include "Include_Common.h"


namespace jk
{
	HitBox_Archer::HitBox_Archer()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"DebugRect"));
		mr->SetMaterial(Resources::Find<Material>(L"DebugMaterial"));
	}
	HitBox_Archer::~HitBox_Archer()
	{
	}
	void HitBox_Archer::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_collider->SetSize(_Size);
		_collider->SetPosition(_Center);
		GameObject::Initialize();
	}
	void HitBox_Archer::Update()
	{
		GameObject::Update();
	}
	void HitBox_Archer::LateUpdate()
	{
		_Center.y = -15;
		_collider->SetSize(_Size);
		_collider->SetPosition(_Center);

		GameObject::LateUpdate();
	}
	void HitBox_Archer::Render()
	{
		GameObject::Render();
	}
	void HitBox_Archer::OnCollisionEnter(Collider2D* other)
	{
	}
	void HitBox_Archer::OnCollisionStay(Collider2D* other)
	{
	}
	void HitBox_Archer::OnCollisionExit(Collider2D* other)
	{
	}
}