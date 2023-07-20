#include "Back_GR_1_2.h"

namespace jk
{
	Back_GR_1_2::Back_GR_1_2()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Back_GR1_1"));
	}
	Back_GR_1_2::~Back_GR_1_2()
	{
	}
	void Back_GR_1_2::Initialize()
	{
		GameObject::Initialize();
	}
	void Back_GR_1_2::Update()
	{
		GameObject::Update();
	}
	void Back_GR_1_2::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Back_GR_1_2::Render()
	{
		GameObject::Render();
	}
}
