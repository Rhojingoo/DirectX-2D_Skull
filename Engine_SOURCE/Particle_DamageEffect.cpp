#include "Particle_DamageEffect.h"
#include "jkTime.h"
#include "jkMesh.h"
#include "jkMaterial.h"
#include "jkResources.h"
#include "jkTransform.h"
#include "jkGameObject.h"
#include "jkAnimator.h"


namespace jk
{
	float Particle_DamageEffect::mDir = 1.f;

	Particle_DamageEffect::Particle_DamageEffect(const Vector3& set)
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

		std::shared_ptr<Material> material = Resources::Find<Material>(L"HITParticleMaterial");
		SetMaterial(material);

		mCS = Resources::Find<ParticleShader>(L"HITParticleSystemShader");
		_Pos = set;

		mSharedBuffer = new graphics::StructuredBuffer();
		mSharedBuffer->Create(sizeof(ParticleShared), 1000, eViewType::UAV, nullptr, true);
	}
	Particle_DamageEffect::~Particle_DamageEffect()
	{
		delete mSharedBuffer;
		delete mBuffer;	
	}

	void Particle_DamageEffect::Initialize()
	{
	}
	void Particle_DamageEffect::Update()
	{
		if (Setposition == true)
		{
			Particle particle[1000] = {};
			for (size_t i = 0; i < 1000; i++)
			{
				Vector4 pos = Vector4(_Pos.x, _Pos.y, _Pos.z - 1, 0.f);

				particle[i].direction =
					Vector4(cosf((float)i * (XM_2PI / (float)1000))
						, sinf((float)i * (XM_2PI / 100.f))
						, mDir, 1.0f);
				particle[i].position = pos;
				particle[i].speed = 2.0f;
				particle[i].active = 0;
			}
			if (mBuffer) // 이미 mBuffer가 있으면 해제
			{
				delete mBuffer;
			}
			mBuffer = new graphics::StructuredBuffer();
			mBuffer->Create(sizeof(Particle), 1000, eViewType::UAV, particle);
			Setposition = false;
		}
	}
	void Particle_DamageEffect::LateUpdate()
	{	
		float AliveTime = 1.f /1.f;
		mTime += static_cast<float>(Time::DeltaTime());

		if (mTime > AliveTime)
		{
			float f = (mTime / AliveTime);
			UINT AliveCount = (UINT)f;
			mTime = f - floor(f);

			ParticleShared shareData = {};
			shareData.sharedActiveCount = 35;
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
	void Particle_DamageEffect::Render()
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