#include "Player_AfterImage.h"
#include "jkTime.h"
#include "jkResources.h"
#include "jkAnimator.h"
#include "Player.h"

namespace jk
{
	Player_AfterImage::Player_AfterImage()
	{
		//MeshRenderer* mr = AddComponent<MeshRenderer>();
		//mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//mr->SetMaterial(Resources::Find<Material>(L"Basic_Skul"));

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"PointMesh");
		SetMesh(mesh);
		std::shared_ptr<Material> material = Resources::Find<Material>(L"ParticleMaterial");
		SetMaterial(material);

		mCS = Resources::Find<ParticleShader>(L"ParticleSystemShader");

		After_Image particle[10] = {};
		for (size_t i = 0; i < 10; i++)
		{
			Vector4 pos = Vector4::Zero;

			particle[i].position = pos;	
			particle[i].active = 0;
		}

		mBuffer = new graphics::StructuredBuffer();
		mBuffer->Create(sizeof(Particle), 10, eViewType::UAV, particle);
		mSharedBuffer = new graphics::StructuredBuffer();
		mSharedBuffer->Create(sizeof(ParticleShared), 1, eViewType::UAV, nullptr, true);

	}
	Player_AfterImage::~Player_AfterImage()
	{
		delete mSharedBuffer;
		delete mBuffer;
	}
	void Player_AfterImage::Initialize()
	{
		//at = AddComponent<Animator>();
		//at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\Dash", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\Dash", this, 1);
		//at->PlayAnimation(L"Skul_BasicDash", true);
		//GameObject::Initialize();
	}
	void Player_AfterImage::Update()
	{		
		//GameObject::Update();
	}
	void Player_AfterImage::LateUpdate()
	{
		//GameObject::LateUpdate();
		mTime += Time::DeltaTime();

		if (mTime > AliveTime)
		{
			float f = (mTime / AliveTime);
			UINT AliveCount = (UINT)f;
			mTime = f - floor(f);

			ParticleShared shareData = {};
			shareData.sharedActiveCount = 2;
			mSharedBuffer->SetData_Buffer(&shareData, 1);
		}
		else
		{
			ParticleShared shareData = {};
			shareData.sharedActiveCount = 0;
			mSharedBuffer->SetData_Buffer(&shareData, 1);
		}

		mCS->SetParticleBuffer(mBuffer);
		mCS->SetSharedBuffer(mSharedBuffer);
		mCS->OnExcute();
	}
	void Player_AfterImage::Render()
	{
		GetOwner()->GetComponent<Transform>()->BindConstantBuffer();
		mBuffer->BindSRV(eShaderStage::VS, 14);
		mBuffer->BindSRV(eShaderStage::GS, 14);
		mBuffer->BindSRV(eShaderStage::PS, 14);

		GetMaterial()->Binds();
		GetMesh()->RenderInstanced(1000);
		mBuffer->Clear();
		//BindConstantBuffer();
		//GameObject::Render();float AliveTime = 1.0f / 1.0f;
		
		
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