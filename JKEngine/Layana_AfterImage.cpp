#include "Layana_AfterImage.h"
#include "jkTime.h"
#include "jkResources.h"
#include "jkAnimator.h"

namespace jk
{
	Layana_AfterImage::Layana_AfterImage()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"After_Image_Skul"));
	}
	Layana_AfterImage::~Layana_AfterImage()
	{
	}
	void Layana_AfterImage::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();
		

		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Meteor_Cross04_Attack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Meteor_Cross04_Attack", this, 1);

		GameObject::Initialize();
	}
	void Layana_AfterImage::Update()
	{
		switch (_State)
		{
		case jk::Layana_AfterImage::LayanaAfterImage_State::MeterorCross:
			MeterorCross();
			break;

		case jk::Layana_AfterImage::LayanaAfterImage_State::Finish_Image:
			Finish_Image();
			break;

		default:
			break;
		}

		tr->SetPosition(_Pos);
		GameObject::Update();
	}
	void Layana_AfterImage::LateUpdate()
	{
		_collider->SetSize(Vector2(0.f, 0.f));
		GameObject::LateUpdate();
	}
	void Layana_AfterImage::Render()
	{
		BindConstantBuffer();
		GameObject::Render();
	}
	void Layana_AfterImage::BindConstantBuffer()
	{
		renderer::_AlphaBlendCB _Alphacb = {};
		_Alphacb._Alpha.x = mTime;

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::AlphaBlend];
		cb->SetData(&_Alphacb);
		cb->Bind(eShaderStage::PS);
	}
	void Layana_AfterImage::MeterorCross()
	{
		_Time += Time::DeltaTime();
		if (_Time > delayBetweenImages)
		{
			_Time = 0.f;
			_State = LayanaAfterImage_State::Finish_Image;
		}
		else
		{
			if (_Dir == 1)
				at->PlayAnimation(L"Awaken_PowerMeteor_Cross04_Attack", false);
			else
				at->PlayAnimation(L"Awaken_PowerMeteor_Cross04_AttackR", false);
		}
	}
	void Layana_AfterImage::Finish_Image()
	{
		_Pos = Vector3();
		_AfterImage = false;
		this->SetState(eState::Paused);
	}
}