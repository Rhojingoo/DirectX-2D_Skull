#pragma once
#include "jkBaseRenderer.h"
#include "jkMeshRenderer.h"
#include "jkStructuredBuffer.h"
#include "jkParticleShader.h"

namespace jk
{
	class ParticleSystem : public MeshRenderer
	{
	public:
		ParticleSystem();
		~ParticleSystem();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
		graphics::StructuredBuffer* mBuffer;
		std::shared_ptr<ParticleShader> mCS;
		//graphics::StructuredBuffer* mSharedBuffer;


		UINT    mCount;
		Vector4 mStartSize;
		Vector4 mEndSize;
		Vector4 mStartColor;
		Vector4 mEndColor;
		float   mLifeTime;
		float	mFrequency;

		float mTime;
	};
}
