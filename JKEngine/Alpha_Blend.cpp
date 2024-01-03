#include "Alpha_Blend.h"
#include "Include_Common.h"
#include "jkApplication.h"


extern jk::Application application;
namespace jk
{
	bool Alpha_Blend::_FadeCheck = false;
	Alpha_Blend::Alpha_Blend()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"AlphaMaterial"));

		_tr = this->GetComponent<Transform>();
		_tr->SetScale(Vector3(static_cast<float>(application.GetWidth()), static_cast<float>(application.GetHeight()), 0.f));
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
		switch (_State)
		{
		case Alpha_Blend_State::FadeIn_White_Transparent:
			FadeIn_White_Transparent();
			break;

		case Alpha_Blend_State::FadeIn_DeepWhite:
			FadeIn_DeepWhite();
			break;

		case Alpha_Blend_State::FadeIn_Black_Transparent:
			FadeIn_Black_Transparent();
			break;

		case Alpha_Blend_State::FadeIn_DeepBlack:
			FadeIn_DeepBlack();
			break;

		case Alpha_Blend_State::FadeOut:
			FadeOut();
			break;

		default:
			break;
		}
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
		_Alphacb._Alpha.x = _Time;
		_Alphacb._Alpha.y = _Time2;
		_Alphacb._Alpha.z = _Colorcheck;

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::AlphaBlend];
		cb->SetData(&_Alphacb);
		cb->Bind(eShaderStage::PS);
	}

	void Alpha_Blend::FadeIn_White_Transparent()
	{
		//화면이 하얗게 변하는거
		_Time2 += 2.75f * static_cast<float>(Time::DeltaTime());
		if (_Time2 > 3.f)
		{
			_Time2 = 0.f;
			_State = Alpha_Blend_State::FadeOut;
		}
	}
	void Alpha_Blend::FadeIn_DeepWhite()
	{
		//화면이 하얀것에서 점점 투명해지는거
		_Time2 -= 2.75f * static_cast<float>(Time::DeltaTime());
		if (_Time2 <= 0.f)
		{
			_Time2 = 0.f;
			_State = Alpha_Blend_State::FadeOut;
		}
	}
	void Alpha_Blend::FadeIn_Black_Transparent()
	{
		_Time2 += 2.75f * static_cast<float>(Time::DeltaTime());
		if (_Time2 > 3.f)
		{
			_Time2 = 0.f;
			_State = Alpha_Blend_State::FadeOut;
		}
	}
	void Alpha_Blend::FadeIn_DeepBlack()
	{
		_Time2 -= 2.75f * static_cast<float>(Time::DeltaTime());
		if (_Time2 <= 0.f)
		{
			_Time2 = 0.f;
			_State = Alpha_Blend_State::FadeOut;
		}
	}
	void Alpha_Blend::FadeOut()
	{		
		_FadeCheck = true;
	}
}