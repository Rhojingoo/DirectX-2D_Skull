#include "jkCloud.h"



namespace jk
{
	Cloud::Cloud(const std::wstring& path)
		: meshrenderer()
		, tr()		
		, _Pos(1000)
		, _Time(0.f)
		, mTime(0.f)
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(path));
		tr = GetComponent<Transform>();
	}
	Cloud::Cloud(Vector3 mPos)
		: meshrenderer()
		, tr()
		, _Pos(1000)
		, _Time(0.f)
		, mTime(0.f)
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
		_Time +=  0.1f* static_cast<float>(Time::DeltaTime());
		if(_Time>7.f)
		{
			_Time = 0.f;
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
		trCB.mTime.x = mTime;
		trCB.mTime.y = _Time;

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Move];
		cb->SetData(&trCB);
		cb->Bind(eShaderStage::PS);
	}
}