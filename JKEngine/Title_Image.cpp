#include "Title_Image.h"

namespace jk
{
	Title_Image::Title_Image()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Title_Image"));
	}
	Title_Image::~Title_Image()
	{
	}
	void Title_Image::Initialize()
	{
		GameObject::Initialize();
	}
	void Title_Image::Update()
	{
		GameObject::Update();
	}
	void Title_Image::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Title_Image::Render()
	{
		GameObject::Render();
	}
}