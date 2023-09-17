#include "Player_AfterImage.h"
#include "jkTime.h"
#include "jkResources.h"
#include "jkAnimator.h"
#include "Player.h"

namespace jk
{
	Player_AfterImage::Player_AfterImage()
	{
		
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"PointMesh");
		SetMesh(mesh);
		std::shared_ptr<Material> material = Resources::Find<Material>(L"DashBase_Material");
		SetMaterial(material);
		mCS = Resources::Find<ParticleShader>(L"ParticleSystemShader");
		//MeshRenderer* mr = AddComponent<MeshRenderer>();
		//mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//mr->SetMaterial(Resources::Find<Material>(L"Basic_Skul"));

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
		PlayerTr = mOwner->GetComponent<Transform>();
		if (_AfterImage == true)
		{
			After_Image particle[15] = {};
			for (size_t i = 0; i < 15; i++)
			{
				Vector4 pos = Vector4(PlayerTr->GetPosition().x, PlayerTr->GetPosition().y, PlayerTr->GetPosition().z + 1, 0.f);
				particle[i].position = pos;
				particle[i].active = 0;
				particle[i].endTime = 2.f;
			}
			mBuffer = new graphics::StructuredBuffer();
			mBuffer->Create(sizeof(Particle), 15, eViewType::UAV, particle);
			mSharedBuffer = new graphics::StructuredBuffer();
			mSharedBuffer->Create(sizeof(ParticleShared), 1, eViewType::UAV, nullptr, true);
			_AfterImage = false;
			_AfterImage_Late = true;
		}
	
	}
	void Player_AfterImage::LateUpdate()
	{
		//GameObject::LateUpdate();
		if (_AfterImage_Late == true)
		{
			float AliveTime = 1.0f / 1.0f;
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
			_AfterImage_Late = false;
			_AfterImage_Render = true;
		}
	}
	void Player_AfterImage::Render()
	{
		if (_AfterImage_Render == true)
		{
			GetOwner()->GetComponent<Transform>()->BindConstantBuffer();
			mBuffer->BindSRV(eShaderStage::VS, 14);
			mBuffer->BindSRV(eShaderStage::GS, 14);
			mBuffer->BindSRV(eShaderStage::PS, 14);

			GetMaterial()->Binds();
			GetMesh()->RenderInstanced(15);
			mBuffer->Clear();
			_AfterImage_Render = false;
		}
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