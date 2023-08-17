#pragma once
#include "jkComputeShader.h"
#include "jkStructuredBuffer.h"

namespace jk::graphics
{
	class ParticleShader : public ComputeShader
	{
	public:
		ParticleShader();
		~ParticleShader();

		virtual void Binds() override;
		virtual void Clear() override;

		void SetParticleBuffer(StructuredBuffer* particleBuffer);
		void SetSharedBuffer(StructuredBuffer* sharedBuffer) { mSharedBuffer = sharedBuffer; }

	private:
		StructuredBuffer* mParticleBuffer;
		StructuredBuffer* mSharedBuffer;
	};
}
