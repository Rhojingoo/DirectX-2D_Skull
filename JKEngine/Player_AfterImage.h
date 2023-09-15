#pragma once
#include <jkGameObject.h>
#include "jkMaterial.h"

namespace jk
{
	class Player_AfterImage : public GameObject
	{
	public:
		Player_AfterImage();
		virtual ~Player_AfterImage();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		void BindConstantBuffer();

	private:
		Player* mOwner;
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