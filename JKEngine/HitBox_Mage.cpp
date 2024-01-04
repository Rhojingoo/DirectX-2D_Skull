#include "HitBox_Mage.h"
#include "Include_Common.h"


namespace jk
{
	HitBox_Mage::HitBox_Mage()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"DebugRect"));
		mr->SetMaterial(Resources::Find<Material>(L"DebugMaterial"));
	}
	HitBox_Mage::~HitBox_Mage()
	{
	}
	void HitBox_Mage::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_collider->SetSize(_Size);
		_collider->SetPosition(_Center);
		GameObject::Initialize();
	}
	void HitBox_Mage::Update()
	{
		GameObject::Update();
	}
	void HitBox_Mage::LateUpdate()
	{
		_Center.y = -15;
		_collider->SetSize(_Size);
		_collider->SetPosition(_Center);

		GameObject::LateUpdate();
	}
	void HitBox_Mage::Render()
	{
		GameObject::Render();
	}
	void HitBox_Mage::OnCollisionEnter(Collider2D* other)
	{
	}
	void HitBox_Mage::OnCollisionStay(Collider2D* other)
	{
	}
	void HitBox_Mage::OnCollisionExit(Collider2D* other)
	{
	}
}