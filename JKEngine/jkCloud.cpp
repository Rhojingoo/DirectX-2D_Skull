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
		mr = AddComponent<MeshRenderer>();
	}
	Cloud::Cloud(Vector3 mPos)
	{

	}
	Cloud::~Cloud()
	{
	}
	void Cloud::Initialize()
	{
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Cloud_Devil"));
		tr->SetScale(2.0f, 1.0f, 1.0f);
		//AddComponent<testScript>();
		GameObject::Initialize();

	}
	void Cloud::Update()
	{
		mPos = tr->GetPosition();
		if (mPos.x <= -7.0f)
		{
			mPos.x = 7.0f;
		}

		mPos.x -= 0.5f * Time::DeltaTime();

		tr->SetPosition(mPos.x, mPos.y, mPos.z);
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