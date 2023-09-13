#include "Alpha_Blend.h"

namespace jk
{
	Alpha_Blend::Alpha_Blend()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"AlphaMaterial"));
	}
	Alpha_Blend::~Alpha_Blend()
	{
	}
	void Alpha_Blend::Initialize()
	{
		GameObject::Initialize();
	}
	void Alpha_Blend::Update()
	{

		//_Time += 0.1 * (float)Time::DeltaTime();
		//if (_Time > 2.f)
		//{
		//	_Time = 0.f;
		//}
		GameObject::Update();
	}
	void Alpha_Blend::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Alpha_Blend::Render()
	{
		BindConstantBuffer();
		GameObject::Render();
	}

	void Alpha_Blend::BindConstantBuffer()
	{
		renderer::_AlphaBlendCB _Alphacb = {};
		_Alphacb._Alpha.x = mTime;
		_Alphacb._Alpha.y = _Time;

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::AlphaBlend];
		cb->SetData(&_Alphacb);
		cb->Bind(eShaderStage::PS);
	}

}