#include "Player_AfterImage.h"
#include "jkTime.h"
#include "jkResources.h"
#include "jkAnimator.h"
#include "Player.h"

namespace jk
{
	Player_AfterImage::Player_AfterImage()
	{		
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"After_Image_Skul"));
	}

	Player_AfterImage::~Player_AfterImage()
	{
	}

	void Player_AfterImage::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();
		//at1 = AddComponent<Animator>();
		//at2 = AddComponent<Animator>();

		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\Dash", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\Dash", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\NoHead\\Dash", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\NoHead\\Dash", this, 1);

		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\After_Image\\BasicDash", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\After_Image\\BasicDash", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\After_Image\\NoHeadDash", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\After_Image\\NoHeadDash", this, 1);
		//at->PlayAnimation(L"Skul_BasicDash", true);
		
		
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Wolf\\Dash", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Wolf\\Dash_End", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Wolf\\Dash", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Wolf\\Dash_End", this);
		//at1->CreateAnimations(L"..\\Resources\\Texture\\Player\\Wolf\\Dash", this);
		//at1->CreateAnimations(L"..\\Resources\\Texture\\Player\\Wolf\\Dash_End", this);
		//at1->CreateAnimations(L"..\\Resources\\Texture\\Player\\Wolf\\Dash", this, 1);
		//at1->CreateAnimations(L"..\\Resources\\Texture\\Player\\Wolf\\Dash_End", this);
		//at1->PlayAnimation(L"WolfDash", true);
		


		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Spear\\Dash", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Spear\\Dash", this, 1);
		//at2->CreateAnimations(L"..\\Resources\\Texture\\Player\\Spear\\Dash", this);
		//at2->CreateAnimations(L"..\\Resources\\Texture\\Player\\Spear\\Dash", this, 1);
		//at2->PlayAnimation(L"SpearDash", true);

		GameObject::Initialize();
	}

	void Player_AfterImage::Update()
	{					

		switch (_State)
		{
		case jk::Player_AfterImage::AfterImage_State::Skul_Basic:
			Skul_Basic();
			break;

		case jk::Player_AfterImage::AfterImage_State::Skul_NoHead:
			Skul_NoHead();
			break;

		case jk::Player_AfterImage::AfterImage_State::Skul_Wolf:
			Skul_Wolf();
			break;

		case jk::Player_AfterImage::AfterImage_State::Skul_Spear:
			Skul_Spear();
			break;

		case jk::Player_AfterImage::AfterImage_State::Finish_Image:
			Finish_Image();
			break;

		default:
			break;
		}	

		tr->SetPosition(_Pos);
		GameObject::Update();
	}

	void Player_AfterImage::LateUpdate()
	{
		_collider->SetSize(Vector2(0.f, 0.f));
		GameObject::LateUpdate();
	}

	void Player_AfterImage::Render()
	{
		BindConstantBuffer();
		GameObject::Render();
	}

	void Player_AfterImage::BindConstantBuffer()
	{
		renderer::_AlphaBlendCB _Alphacb = {};
		_Alphacb._Alpha.x = mTime;	

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::AlphaBlend];
		cb->SetData(&_Alphacb);
		cb->Bind(eShaderStage::PS);
	}

	void Player_AfterImage::Skul_Basic()
	{
		_Time += Time::DeltaTime();
		if (_Time > delayBetweenImages)
		{
			_Time = 0.f;
			_State = AfterImage_State::Finish_Image;
		}
		else
		{
			if(_Dir==1)
				at->PlayAnimation(L"After_ImageBasicDash", false);
			else
				at->PlayAnimation(L"After_ImageBasicDashR", false);
		}
	}

	void Player_AfterImage::Skul_NoHead()
	{
		_Time += Time::DeltaTime();
		if (_Time > delayBetweenImages)
		{
			_Time = 0.f;
			_State = AfterImage_State::Finish_Image;
		}
		else
		{
			if (_Dir == 1)
				at->PlayAnimation(L"Skul_BasicDash", false);
			else
				at->PlayAnimation(L"Skul_BasicDashR", false);
		}
	}

	void Player_AfterImage::Skul_Wolf()
	{
		_Time += Time::DeltaTime();
		if (_Time > delayBetweenImages)
		{
			_Time = 0.f;
			_State = AfterImage_State::Finish_Image;
		}
		else
		{
			if (_Dir == 1)
				at->PlayAnimation(L"WolfDash", false);
			else
				at->PlayAnimation(L"WolfDashR", false);
		}
	}

	void Player_AfterImage::Skul_Spear()
	{
		_Time += Time::DeltaTime();
		if (_Time > delayBetweenImages)
		{
			_Time = 0.f;
			_State = AfterImage_State::Finish_Image;
		}
		else
		{
			if (_Dir == 1)
				at->PlayAnimation(L"SpearDash", false);
			else
				at->PlayAnimation(L"SpearDashR", false);
		}
	}

	void Player_AfterImage::Finish_Image()
	{
		_Pos = Vector3();
		_AfterImage = false;
		this->SetState(eState::Paused);
	}
}