#include "Devil_Castle_mid.h"


namespace jk
{
	Devil_Castle_mid::Devil_Castle_mid()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Catle_wall_Front_01"));
	}
	Devil_Castle_mid::~Devil_Castle_mid()
	{
	}
	void Devil_Castle_mid::Initialize()
	{
		GameObject::Initialize();
	}
	void Devil_Castle_mid::Update()
	{
		GameObject::Update();
	}
	void Devil_Castle_mid::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Devil_Castle_mid::Render()
	{
		GameObject::Render();
	}
}
