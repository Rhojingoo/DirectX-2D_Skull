#pragma once
#include "jkComponent.h"
#include "jkGraphics.h"

namespace jk
{
	class Camera : public Component
	{
	public:
		enum class eProjectionType
		{
			Perpective,
			OrthoGraphic,
			None,
		};

		static Matrix GetViewMatrix() { return View; }
		static Matrix GetProjectionMatrix() { return Projection; }

		Camera();
		~Camera();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		bool CreateViewMatrix();
		bool CreateProjectionMatrix(eProjectionType type);
		void RegisterCameraInRenderer();

		void TurnLayerMask(eLayerType type, bool enable = true);
		void EnableLayerMasks() { mLayerMask.set(); }
		void DisableLayerMasks() { mLayerMask.reset(); }

		void AlphaSortGameObjects();
		void ZSortTransparencyGameObjects();
		void DivideAlphaBlendGameObjects(const std::vector<GameObject*> gameObjs);


		float GetScale() { return mSize; }
		void SetScale(float scale) { mSize = scale; }
		//Matrix& GetViewMatrix() { return mView; }
		//Matrix& GetProjectionMatrix() { return mProjection; }



		void RenderOpaque();
		void RenderCutOut();
		void RenderTransparent();


		void EnableDepthStencilState();
		void DisableDepthStencilState();

	private:
		static Matrix View;
		static Matrix Projection;


		// 다중 카메라 지원을 위해 멤버 변수로 뷰, 투영행렬을 추가로 관리
		Matrix mView;
		Matrix mProjection;

		eProjectionType mType;
		float mAspectRatio;
		float mNear;
		float mFar;
		float mSize;

		std::bitset<(UINT)eLayerType::End> mLayerMask;
		std::vector<GameObject*> mOpaqueGameObjects;
		std::vector<GameObject*> mCutOutGameObjects;
		std::vector<GameObject*> mTransparentGameObjects;
	};	
}
