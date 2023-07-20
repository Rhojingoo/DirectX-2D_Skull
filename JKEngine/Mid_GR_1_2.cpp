#include "Mid_GR_1_2.h"


namespace jk
{
	Mid_GR_1_2::Mid_GR_1_2()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Cloud_S1_2"));
		tr = GetComponent<Transform>();
	}
	Mid_GR_1_2::~Mid_GR_1_2()
	{
	}
	void Mid_GR_1_2::Initialize()
	{
		GameObject::Initialize();
	}
	void Mid_GR_1_2::Update()
	{
		_Time += 0.1 * (float)Time::DeltaTime();
		if (_Time > 7.f)
		{
			_Time = 0.f;
		}
		GameObject::Update();
	}
	void Mid_GR_1_2::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Mid_GR_1_2::Render()
	{
		BindConstantBuffer();
		GameObject::Render();
	}
	void Mid_GR_1_2::BindConstantBuffer()
	{
		renderer::MoveCB trCB = {};
		trCB.mTime.x = mTime;
		trCB.mTime.y = _Time;

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Move];
		cb->SetData(&trCB);
		cb->Bind(eShaderStage::PS);
	}
}