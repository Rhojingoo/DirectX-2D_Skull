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
		mr->SetMaterial(Resources::Find<Material>(L"Basic_Skul"));
	}
	Player_AfterImage::~Player_AfterImage()
	{
	}
	void Player_AfterImage::Initialize()
	{
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\Dash", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\Dash", this, 1);

		at->PlayAnimation(L"Skul_BasicDash", true);
		GameObject::Initialize();
	}
	void Player_AfterImage::Update()
	{		
		GameObject::Update();
	}
	void Player_AfterImage::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Player_AfterImage::Render()
	{
		BindConstantBuffer();
		GameObject::Render();
	}
	void Player_AfterImage::BindConstantBuffer()
	{
		//renderer::_AlphaBlendCB _Alphacb = {};
		//_Alphacb._Alpha.x = mTime;
		//_Alphacb._Alpha.y = _Time;

		//ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::AlphaBlend];
		//cb->SetData(&_Alphacb);
		//cb->Bind(eShaderStage::PS);
	}
}