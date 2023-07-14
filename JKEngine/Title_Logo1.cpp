#include "Title_Logo1.h"

namespace jk
{
	Title_Logo1::Title_Logo1()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Title_Logo")); 
	}
	Title_Logo1::~Title_Logo1()
	{
	}
	void Title_Logo1::Initialize()
	{
		GameObject::Initialize();
	}
	void Title_Logo1::Update()
	{
		GameObject::Update();
	}
	void Title_Logo1::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Title_Logo1::Render()
	{
		GameObject::Render();
	}
}