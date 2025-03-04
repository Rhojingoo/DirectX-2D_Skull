#include "jkParticleShader.h"
#include "jkRenderer.h"
#include "jkConstantBuffer.h"
#include "jkTime.h"

namespace jk::graphics
{
	ParticleShader::ParticleShader()
		: ComputeShader(128, 1, 1)
		, mParticleBuffer(nullptr)
	{
	}

	ParticleShader::~ParticleShader()
	{

	}

	void ParticleShader::Binds()
	{
		mParticleBuffer->BindUAV(0);
		mSharedBuffer->BindUAV(1);

		mGroupX = mParticleBuffer->GetStride() / mThreadGroupCountX + 1;
		mGroupY = 1;
		mGroupZ = 1;
	}

	void ParticleShader::Clear()
	{
		mParticleBuffer->Clear();
		mSharedBuffer->Clear();
	}

	void ParticleShader::SetParticleBuffer(StructuredBuffer* particleBuffer)
	{
		mParticleBuffer = particleBuffer;

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Particle];

		static float elapsedTime = 0.0f;
		elapsedTime += static_cast<float>(Time::DeltaTime());

		renderer::ParticleCB data = {};
		data.elementCount = mParticleBuffer->GetStride();
		data.elpasedTime = elapsedTime;
		data.deltaTime = static_cast<float>(Time::DeltaTime());


		cb->SetData(&data);
		cb->Bind(eShaderStage::CS);
	}

}
