#include "jkCloud.h"
#include "Include_Common.h"


namespace jk
{
	Cloud::Cloud(const std::wstring& path)
		: _MeshRenderer()
		, tr()		
		, _Pos(1000)
		, _Time2(0.f)
		, _Time(0.f)
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(path));
		tr = GetComponent<Transform>();
	}
	Cloud::Cloud(Vector3 _Pos)
		: _MeshRenderer()
		, tr()
		, _Pos(1000)
		, _Time2(0.f)
		, _Time(0.f)
	{

	}
	Cloud::~Cloud()
	{
	}
	void Cloud::Initialize()
	{
		GameObject::Initialize();
	}
	void Cloud::Update()
	{		
		_Time2 +=  0.1f* static_cast<float>(Time::DeltaTime());
		if(_Time2>7.f)
		{
			_Time2 = 0.f;
		}

		GameObject::Update();
	}
	void Cloud::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Cloud::Render()
	{
		BindConstantBuffer();
		GameObject::Render();
	}
	void Cloud::BindConstantBuffer()
	{
		renderer::MoveCB trCB = {};
		trCB.mTime.x = _Time;
		trCB.mTime.y = _Time2;

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Move];
		cb->SetData(&trCB);
		cb->Bind(eShaderStage::PS);
	}
}