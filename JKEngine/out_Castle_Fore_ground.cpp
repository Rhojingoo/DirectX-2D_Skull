#include "out_Castle_Fore_ground.h"

namespace jk
{
	out_Castle_Fore_ground::out_Castle_Fore_ground()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Out_Fore_GR"));
	}
	out_Castle_Fore_ground::~out_Castle_Fore_ground()
	{
	}
	void out_Castle_Fore_ground::Initialize()
	{
		GameObject::Initialize();
	}
	void out_Castle_Fore_ground::Update()
	{
		GameObject::Update();
	}
	void out_Castle_Fore_ground::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void out_Castle_Fore_ground::Render()
	{
		GameObject::Render();
	}
}