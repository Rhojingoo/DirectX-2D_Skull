#include "Title_Logo2.h"


namespace jk
{
	Title_Logo2::Title_Logo2()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Title_Mini_Logo")); 
	}
	Title_Logo2::~Title_Logo2()
	{
	}
	void Title_Logo2::Initialize()
	{
		GameObject::Initialize();
	}
	void Title_Logo2::Update()
	{
		GameObject::Update();
	}
	void Title_Logo2::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Title_Logo2::Render()
	{
		GameObject::Render();
	}
}
