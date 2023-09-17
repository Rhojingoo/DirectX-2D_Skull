#pragma once
#include "Include_Common.h"
#include "..\Engine_SOURCE\jkMeshRenderer.h"
#include "..\Engine_SOURCE\jkMaterial.h"
#include "..\Engine_SOURCE\jkStructuredBuffer.h"
#include "..\Engine_SOURCE\jkParticleShader.h"
//#include "jkMaterial.h"
//#include "jkStructuredBuffer.h"
//#include "jkParticleShader.h"


namespace jk
{
	class Player_AfterImage :  public MeshRenderer
	{
	public:
		Player_AfterImage();
		virtual ~Player_AfterImage();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		void BindConstantBuffer();
		void Set_Owner(Player* set) { mOwner = set; }
		void Set_AfterImage_Switch(bool set) { _AfterImage = set; }

	private:
		graphics::StructuredBuffer* mBuffer;
		std::shared_ptr<ParticleShader> mCS;
		graphics::StructuredBuffer* mSharedBuffer;

	private:
		Player* mOwner = nullptr;
		Transform* PlayerTr = nullptr;
		bool _AfterImage = false;
		bool _AfterImage_Late = false;
		bool _AfterImage_Render = false;
	
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