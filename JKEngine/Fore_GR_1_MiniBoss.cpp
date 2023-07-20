#include "Fore_GR_1_MiniBoss.h"


namespace jk
{
	Fore_GR_1_MiniBoss::Fore_GR_1_MiniBoss()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Fore_GR1_MB"));
	}
	Fore_GR_1_MiniBoss::~Fore_GR_1_MiniBoss()
	{
	}
	void Fore_GR_1_MiniBoss::Initialize()
	{
		GameObject::Initialize();
	}
	void Fore_GR_1_MiniBoss::Update()
	{
		GameObject::Update();
	}
	void Fore_GR_1_MiniBoss::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Fore_GR_1_MiniBoss::Render()
	{
		GameObject::Render();
	}
}