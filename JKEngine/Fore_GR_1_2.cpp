#include "Fore_GR_1_2.h"


namespace jk
{
	Fore_GR_1_2::Fore_GR_1_2()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Fore_GR1_2"));
	}
	Fore_GR_1_2::~Fore_GR_1_2()
	{
	}
	void Fore_GR_1_2::Initialize()
	{
		GameObject::Initialize();
	}
	void Fore_GR_1_2::Update()
	{
		GameObject::Update();
	}
	void Fore_GR_1_2::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Fore_GR_1_2::Render()
	{
		GameObject::Render();
	}
}