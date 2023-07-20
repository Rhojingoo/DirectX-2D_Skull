#include "Back_GR_1_1.h"


namespace jk
{
	Back_GR_1_1::Back_GR_1_1()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Back_GR1_1"));
	}
	Back_GR_1_1::~Back_GR_1_1()
	{
	}
	void Back_GR_1_1::Initialize()
	{
		GameObject::Initialize();
	}
	void Back_GR_1_1::Update()
	{

		GameObject::Update();
	}
	void Back_GR_1_1::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Back_GR_1_1::Render()
	{		
		GameObject::Render();
	}
}