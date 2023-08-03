#include "Ice_wizard.h"

jk::Ice_wizard::Ice_wizard()
{
	MeshRenderer* mr = AddComponent<MeshRenderer>();
	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
	mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
}

jk::Ice_wizard::~Ice_wizard()
{
}

void jk::Ice_wizard::Initialize()
{
	GameObject::Initialize();
}

void jk::Ice_wizard::Update()
{
	GameObject::Update();
}

void jk::Ice_wizard::LateUpdate()
{
	GameObject::LateUpdate();
}

void jk::Ice_wizard::Render()
{
	GameObject::Render();
}

void jk::Ice_wizard::OnCollisionEnter(Collider2D* other)
{
}

void jk::Ice_wizard::OnCollisionStay(Collider2D* other)
{
}

void jk::Ice_wizard::OnCollisionExit(Collider2D* other)
{
}

void jk::Ice_wizard::idle()
{
}

void jk::Ice_wizard::attack()
{
}

void jk::Ice_wizard::hit()
{
}

void jk::Ice_wizard::teleport_in()
{
}

void jk::Ice_wizard::teleport_out()
{
}
