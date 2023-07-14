#include "Skull_Basic.h"

namespace jk
{
	Skull_Basic::Skull_Basic()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Title_Logo"));
	}
	Skull_Basic::~Skull_Basic()
	{
	}
	void Skull_Basic::Initialize()
	{
		GameObject::Initialize();
	}
	void Skull_Basic::Update()
	{
		GameObject::Update();
	}
	void Skull_Basic::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Skull_Basic::Render()
	{
		GameObject::Render();
	}
}
