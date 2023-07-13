#include "Decil_chair.h"

namespace jk
{
	Decil_chair::Decil_chair()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Devil_Chair"));
	}
	Decil_chair::~Decil_chair()
	{
	}
	void Decil_chair::Initialize()
	{
		GameObject::Initialize();
	} 
	void Decil_chair::Update()
	{
		GameObject::Update();
	}
	void Decil_chair::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Decil_chair::Render()
	{
		GameObject::Render();
	}
}