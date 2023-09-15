#include "jkParticleSystem.h"

#include "jkTime.h"
#include "jkMesh.h"
#include "jkMaterial.h"
#include "jkResources.h"
#include "jkTransform.h"
#include "jkGameObject.h"

namespace jk
{
	ParticleSystem::ParticleSystem()
		: mCount(0)
		, mStartSize(Vector4::One)
		, mEndSize(Vector4::One)
		, mStartColor(Vector4::Zero)
		, mEndColor(Vector4::Zero)
		, mLifeTime(0.0f)
		, mTime(0.0f)
	{
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"PointMesh");
		SetMesh(mesh);

		std::shared_ptr<Material> material = Resources::Find<Material>(L"ParticleMaterial");
		SetMaterial(material);

		mCS = Resources::Find<ParticleShader>(L"ParticleSystemShader");

		Particle particles[100] = {};
		for (size_t i = 0; i < 100; i++)
		{
			Vector4 pos = Vector4::Zero;

			particles[i].direction =
				Vector4(cosf((float)i * (XM_2PI / (float)1000))
					, sinf((float)i * (XM_2PI / 100.f))
					, 0.0f, 1.0f);

			particles[i].position = pos;
			particles[i].speed = 1.0f;
			particles[i].active = 0;
		}

		mBuffer = new graphics::StructuredBuffer();
		mBuffer->Create(sizeof(Particle), 100, eViewType::UAV, particles);

		mSharedBuffer = new graphics::StructuredBuffer();
		mSharedBuffer->Create(sizeof(ParticleShared), 1, eViewType::UAV, nullptr, true);
	}
	ParticleSystem::~ParticleSystem()
	{
	}
	void ParticleSystem::Initialize()
	{
	}
	void ParticleSystem::Update()
	{
	}
	void ParticleSystem::LateUpdate()
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
	}
	void ParticleSystem::Render()
	{
		GetOwner()->GetComponent<Transform>()->BindConstantBuffer();
		mBuffer->BindSRV(eShaderStage::VS, 14);
		mBuffer->BindSRV(eShaderStage::GS, 14);
		mBuffer->BindSRV(eShaderStage::PS, 14);

		GetMaterial()->Binds();
		GetMesh()->RenderInstanced(1000);

		mBuffer->Clear();
	}
}