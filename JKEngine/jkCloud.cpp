#include "jkCloud.h"
#include "jkTime.h"
#include "jkResources.h"
#include "jkTransform.h"
#include "jkMeshRenderer.h"


namespace jk
{
	Cloud::Cloud()
		:mTime(0.0f)
	{
		tr = GetComponent<Transform>();
		meshrenderer = AddComponent<MeshRenderer>();
	}
	Cloud::Cloud(Vector3 mPos)
	{

	}
	Cloud::~Cloud()
	{
	}
	void Cloud::Initialize()
	{
		meshrenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		meshrenderer->SetMaterial(Resources::Find<Material>(L"Cloud_Devil"));
		tr->SetScale(2.0f, 1.0f, 1.0f);
		GameObject::Initialize();

	}
	void Cloud::Update()
	{

		GameObject::Update();
	}
	void Cloud::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Cloud::Render()
	{
		GameObject::Render();
	}
}