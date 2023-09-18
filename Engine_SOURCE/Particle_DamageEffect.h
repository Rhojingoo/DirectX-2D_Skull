#pragma once
#include "jkBaseRenderer.h"
#include "jkMeshRenderer.h"
#include "jkStructuredBuffer.h"
#include "jkParticleShader.h"

namespace jk
{
	class Particle_DamageEffect : public MeshRenderer
	{
	public:
		Particle_DamageEffect(const Vector3& set);
		~Particle_DamageEffect();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void Setpos_siwtch(bool set) { Setposition = set; }
		void SetPosition(Vector3 set) { _Pos = set; }
		void SetDirection(float set) { mDir = set; }
		void BindConstantBuffer();

	private:
		graphics::StructuredBuffer* mBuffer;
		std::shared_ptr<ParticleShader> mCS;
		graphics::StructuredBuffer* mSharedBuffer;
		Vector3 _Pos = {};

		//Particle particle[1000] = {};
		UINT    mCount;
		Vector4 pos = Vector4::Zero;
		Vector4 mStartSize;
		Vector4 mEndSize;
		Vector4 mStartColor;
		Vector4 mEndColor;		

		float   mLifeTime;
		float	mFrequency;
		float mTime;

		bool Setposition = false;
		static float mDir; // 1이면 오른쪽, -1이면 왼쪽
	};
}
