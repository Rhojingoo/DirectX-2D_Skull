#include "Player_State_UI.h"

namespace jk
{
	Player_State_UI::Player_State_UI()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Skul_UI"));
	}
	Player_State_UI::~Player_State_UI()
	{
	}
	void Player_State_UI::Initialize()
	{
		GameObject::Initialize();
	}
	void Player_State_UI::Update()
	{
		GameObject::Update();
	}
	void Player_State_UI::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Player_State_UI::Render()
	{
		GameObject::Render();
	}
}
