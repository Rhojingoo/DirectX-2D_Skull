#include "jkBack_ground.h"

namespace jk
{
	Back_ground::Back_ground(const std::wstring& path)
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(path));
	}
	Back_ground::~Back_ground()
	{
	}
	void Back_ground::Initialize()
	{
		GameObject::Initialize();
	}
	void Back_ground::Update()
	{
		GameObject::Update();
	}
	void Back_ground::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Back_ground::Render()
	{
		GameObject::Render();
	}
	void Back_ground::OnCollisionEnter(Collider2D* other)
	{
	}
	void Back_ground::OnCollisionStay(Collider2D* other)
	{
	}
	void Back_ground::OnCollisionExit(Collider2D* other)
	{
	}
}