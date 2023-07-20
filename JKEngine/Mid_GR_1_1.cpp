#include "Mid_GR_1_1.h"

namespace jk
{
	Mid_GR_1_1::Mid_GR_1_1()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Mid_GR1_1"));
	}
	Mid_GR_1_1::~Mid_GR_1_1()
	{
	}
	void Mid_GR_1_1::Initialize()
	{
		GameObject::Initialize();
	}
	void Mid_GR_1_1::Update()
	{
		_Time += 0.1 * (float)Time::DeltaTime();
		if (_Time > 7.f)
		{
			_Time = 0.f;
		}
		GameObject::Update();
	}
	void Mid_GR_1_1::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Mid_GR_1_1::Render()
	{
		BindConstantBuffer();
		GameObject::Render();
	}

	void Mid_GR_1_1::BindConstantBuffer()
	{
		renderer::MoveCB trCB = {};
		trCB.mTime.x = mTime;
		trCB.mTime.y = _Time;

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Move];
		cb->SetData(&trCB);
		cb->Bind(eShaderStage::PS);
	}
}
