#include "in_Castle_Fore_ground.h"

namespace jk
{
	in_Castle_Fore_ground::in_Castle_Fore_ground()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"In_Fore_GR"));
	}
	in_Castle_Fore_ground::~in_Castle_Fore_ground()
	{
	}
	void in_Castle_Fore_ground::Initialize()
	{
		GameObject::Initialize();
	}
	void in_Castle_Fore_ground::Update()
	{
		GameObject::Update();
	}
	void in_Castle_Fore_ground::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void in_Castle_Fore_ground::Render()
	{
		GameObject::Render();
	}
}