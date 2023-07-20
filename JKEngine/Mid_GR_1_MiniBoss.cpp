#include "Mid_GR_1_MiniBoss.h"


namespace jk
{
	Mid_GR_1_MiniBoss::Mid_GR_1_MiniBoss()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Mid_GR1_MB"));
	}
	Mid_GR_1_MiniBoss::~Mid_GR_1_MiniBoss()
	{
	}
	void Mid_GR_1_MiniBoss::Initialize()
	{
		GameObject::Initialize();
	}
	void Mid_GR_1_MiniBoss::Update()
	{
		GameObject::Update();
	}
	void Mid_GR_1_MiniBoss::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Mid_GR_1_MiniBoss::Render()
	{
		GameObject::Render();
	}
}
