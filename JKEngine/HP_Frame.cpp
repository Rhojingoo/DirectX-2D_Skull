#include "HP_Frame.h"

namespace jk
{
	HP_Frame::HP_Frame(const std::wstring& path)
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(path));
	}
	HP_Frame::~HP_Frame()
	{
	}
	void HP_Frame::Initialize()
	{
		GameObject::Initialize();
	}
	void HP_Frame::Update()
	{
		GameObject::Update();
	}
	void HP_Frame::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void HP_Frame::Render()
	{
		GameObject::Render();
	}
}