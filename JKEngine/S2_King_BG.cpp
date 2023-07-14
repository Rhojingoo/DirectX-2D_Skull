#include "S2_King_BG.h"


namespace jk
{
	S2_King_BG::S2_King_BG()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Stage_king2"));
	}
	S2_King_BG::~S2_King_BG()
	{
	}
	void S2_King_BG::Initialize()
	{
		GameObject::Initialize();
	}
	void S2_King_BG::Update()
	{
		GameObject::Update();
	}
	void S2_King_BG::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void S2_King_BG::Render()
	{
		GameObject::Render();
	}
}
