#pragma once
#include <jkGameObject.h>
#include "jkBaseRenderer.h"
#include "jkMeshRenderer.h"
#include "jkMaterial.h"
#include "jkStructuredBuffer.h"
#include "jkParticleShader.h"

namespace jk
{
	class Player_AfterImage :  public MeshRenderer, public GameObject
	{
	public:
		Player_AfterImage(Player* obj);
		virtual ~Player_AfterImage();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		void BindConstantBuffer();

	private:
		graphics::StructuredBuffer* mBuffer;
		std::shared_ptr<ParticleShader> mCS;
		graphics::StructuredBuffer* mSharedBuffer;

	private:
		Player* mOwner = nullptr;
		Transform* PlayerTr = nullptr;
		bool _AfterImage = false;

	
	private://첨에 오브젝트로 진행하려할때의 변수들
		class Animator* mAnimator;
		std::shared_ptr<Material> mMaterial;
		Animator* at = nullptr;
		Animator* at1 = nullptr;
		Animator* at2 = nullptr;
		float mTime = 1.f;
		float _Time = 0.f;
		static bool _FadeCheck;
	};
}