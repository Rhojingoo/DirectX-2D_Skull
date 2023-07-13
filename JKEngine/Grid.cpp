#include "Grid.h"

namespace jk
{
	Grid::Grid()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"GridMaterial"));
	}
	Grid::~Grid()
	{
	}
	void Grid::Initialize()
	{
		GameObject::Initialize();
	}
	void Grid::Update()
	{
		GameObject::Update();
	}
	void Grid::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Grid::Render()
	{
		GameObject::Render();
	}
}