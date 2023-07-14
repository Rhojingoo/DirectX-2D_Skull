#include "Player_Hp_Bar.h"

namespace jk
{
	Player_Hp_Bar::Player_Hp_Bar()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"HealthUar_Ui"));
	}
	Player_Hp_Bar::~Player_Hp_Bar()
	{
	}
	void Player_Hp_Bar::Initialize()
	{
		GameObject::Initialize();
	}
	void Player_Hp_Bar::Update()
	{
		GameObject::Update();
	}
	void Player_Hp_Bar::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Player_Hp_Bar::Render()
	{
		GameObject::Render();
	}
}