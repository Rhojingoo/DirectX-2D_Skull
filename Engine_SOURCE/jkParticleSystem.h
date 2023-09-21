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
		ParticleSystem(const Vector3 &set, float setimage = 0);
		~ParticleSystem();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
		graphics::StructuredBuffer* mBuffer;
		std::shared_ptr<ParticleShader> mCS;
		graphics::StructuredBuffer* mSharedBuffer;
		Vector3 _Pos = {};

		UINT    mCount;
		Vector4 pos = Vector4::Zero;
		Vector4 mStartSize;
		Vector4 mEndSize;
		Vector4 mStartColor;
		Vector4 mEndColor;
		float   mLifeTime;
		float	mFrequency;

		float mTime;
	};
}
