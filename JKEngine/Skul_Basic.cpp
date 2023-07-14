#include "Skul_Basic.h"

namespace jk
{
	Skul_Basic::Skul_Basic()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Basic_Skul"));
	}
	Skul_Basic::~Skul_Basic()
	{
	}
	void Skul_Basic::Initialize()
	{
		GameObject::Initialize();
	}
	void Skul_Basic::Update()
	{
		GameObject::Update();
	}
	void Skul_Basic::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Skul_Basic::Render()
	{
		GameObject::Render();
	}
}
