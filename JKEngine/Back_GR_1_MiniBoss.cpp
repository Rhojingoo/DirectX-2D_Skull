#include "Back_GR_1_MiniBoss.h"

namespace jk
{
	Back_GR_1_MiniBoss::Back_GR_1_MiniBoss()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Back_GR1_MB"));
	}
	Back_GR_1_MiniBoss::~Back_GR_1_MiniBoss()
	{
	}
	void Back_GR_1_MiniBoss::Initialize()
	{
		GameObject::Initialize();
	}
	void Back_GR_1_MiniBoss::Update()
	{
		GameObject::Update();
	}
	void Back_GR_1_MiniBoss::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Back_GR_1_MiniBoss::Render()
	{
		GameObject::Render();
	}
}