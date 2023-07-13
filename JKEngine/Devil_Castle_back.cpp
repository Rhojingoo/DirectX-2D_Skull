#include "Devil_Castle_back.h"

namespace jk
{
	Devil_Castle::Devil_Castle()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));		
		mr->SetMaterial(Resources::Find<Material>(L"Catle_wall_Back"));
		
	}
	Devil_Castle::~Devil_Castle()
	{
	}
	void Devil_Castle::Initialize()
	{
		GameObject::Initialize();
	}
	void Devil_Castle::Update()
	{
		GameObject::Update();
	}
	void Devil_Castle::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Devil_Castle::Render()
	{
		GameObject::Render();
	}
}
