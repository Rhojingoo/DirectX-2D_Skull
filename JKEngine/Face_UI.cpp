#include "Face_UI.h"

namespace jk
{
	Face_UI::Face_UI()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Skul_UI"));
	}
	Face_UI::~Face_UI()
	{
	}
	void Face_UI::Initialize()
	{
		GameObject::Initialize();
	}
	void Face_UI::Update()
	{
		GameObject::Update();
	}
	void Face_UI::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Face_UI::Render()
	{
		GameObject::Render();
	}
}