#include "Devil_Castle_front.h"


namespace jk
{
	Devil_Castle_front::Devil_Castle_front()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Catle_wall_Front_01"));
	}
	Devil_Castle_front::~Devil_Castle_front()
	{
	}
	void Devil_Castle_front::Initialize()
	{
		GameObject::Initialize();
	}
	void Devil_Castle_front::Update()
	{
		GameObject::Update();
	}
	void Devil_Castle_front::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Devil_Castle_front::Render()
	{
		GameObject::Render();
	}
}
