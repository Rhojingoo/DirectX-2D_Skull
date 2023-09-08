#pragma once
//#include "Include_Common.h"
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

		static Matrix& GetGpuViewMatrix() { return View; }
		static void SetGpuViewMatrix(Matrix view) { View = view; }
		static Matrix& GetGpuProjectionMatrix() { return Projection; }
		static void SetGpuProjectionMatrix(Matrix projection) { Projection = projection; }

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

		void RenderOpaque();
		void RenderCutOut();
		void RenderTransparent();

		void EnableDepthStencilState();
		void DisableDepthStencilState();

		float GetSize() { return mSize; }
		void SetSize(float size) { mSize = size;}
		Matrix& GetViewMatrix() { return mView; }
		Matrix& GetProjectionMatrix() { return mProjection; }

		static Vector3 GetWorldpos_Camera(Vector3 pos);
		static void SetTarget(GameObject* target) { mTarget = target; }
		static void SetTarget_BG(GameObject* target) { mTarget_BG = target; }

		Vector3 GetWorldTransform(Vector3 pos);

		void Set_MaxPlayerX(float set) { _MaxPlayerX = set; }
		void Set_MaxPlayerY(float set) { _MaxPlayerY = set; }
		void Set_MinPlayerX(float set) { _MinPlayerX = set; }
		void Set_MinPlayerY(float set) { _MinPlayerY = set; }
		void Set_MaxBGX(float set) { _MaxBgX = set; }
		void Set_MaxBGY(float set) { _MaxBgY = set; }
		void Set_MinBGX(float set) { _MinBgX = set; }
		void Set_MinBGY(float set) { _MinBgY = set; }

		bool SetCamera = false;
		bool SetCameraXY = false;
		bool SetCameraX = false;
		bool SetCameraY = false;
		bool StayCamera = false;
		bool BgCamera = false;


	private:
		static Matrix View;
		static Matrix Projection;
		static GameObject* mTarget;
		static GameObject* mTarget_BG;


		Matrix mView;
		Matrix mProjection;

		eProjectionType mType;
		float mAspectRatio;
		float mNear;
		float mFar;
		float mSize;
		float _MaxPlayerX = 0.f;
		float _MaxPlayerY = 0.f;
		float _MinPlayerX = 0.f;
		float _MinPlayerY = 0.f;
		float _MaxBgX = 0.f;
		float _MaxBgY = 0.f;
		float _MinBgX = 0.f;
		float _MinBgY = 0.f;

		std::bitset<(UINT)eLayerType::End> mLayerMask;
		std::vector<GameObject*> mOpaqueGameObjects;
		std::vector<GameObject*> mCutOutGameObjects;
		std::vector<GameObject*> mTransparentGameObjects;
	};	
}
