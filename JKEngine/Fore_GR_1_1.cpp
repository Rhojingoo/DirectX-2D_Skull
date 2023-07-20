#include "Fore_GR_1_1.h"


namespace jk
{
	Fore_GR_1_1::Fore_GR_1_1()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Fore_GR1_1"));
	}
	Fore_GR_1_1::~Fore_GR_1_1()
	{
	}
	void Fore_GR_1_1::Initialize()
	{
		GameObject::Initialize();
	}
	void Fore_GR_1_1::Update()
	{
		GameObject::Update();
	}
	void Fore_GR_1_1::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Fore_GR_1_1::Render()
	{
		GameObject::Render();
	}
}

