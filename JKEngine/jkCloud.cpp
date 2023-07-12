#include "jkCloud.h"
#include "jkTime.h"
#include "jkResources.h"
#include "jkTransform.h"
#include "jkMeshRenderer.h"


namespace jk
{
	Cloud::Cloud()
		: meshrenderer()
		, tr()		
		, _Pos(1000)
		, _Time(0.f)
		, mTime(0.f)
	{
		tr = GetComponent<Transform>();
	}
	Cloud::Cloud(Vector3 mPos)
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
		//_Pos = tr->GetPosition();
		//if (_Pos.x <= -1000.0f)
		//{
		//	_Pos.x = 1000.0f;
		//}
		//_Pos.x -= 100.f * Time::DeltaTime();

		//tr->SetPosition(_Pos);

		
		_Time +=  0.1*Time::DeltaTime();
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