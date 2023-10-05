#include "MiniBoss_State_UI.h"

namespace jk
{
	MiniBoss_State_UI::MiniBoss_State_UI()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Adventurer_Frame"));
	}
	MiniBoss_State_UI::~MiniBoss_State_UI()
	{
	}
	void MiniBoss_State_UI::Initialize()
	{
		GameObject::Initialize();
	}
	void MiniBoss_State_UI::Update()
	{
		GameObject::Update();
	}
	void MiniBoss_State_UI::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void MiniBoss_State_UI::Render()
	{
		GameObject::Render();
	}
}