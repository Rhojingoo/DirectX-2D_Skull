#include "S1_King_BG.h"

namespace jk
{
	S1_King_BG::S1_King_BG()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Stage_king1"));
	}
	S1_King_BG::~S1_King_BG()
	{
	}
	void S1_King_BG::Initialize()
	{
		GameObject::Initialize();
	}
	void S1_King_BG::Update()
	{
		GameObject::Update();
	}
	void S1_King_BG::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void S1_King_BG::Render()
	{
		GameObject::Render();
	}
}