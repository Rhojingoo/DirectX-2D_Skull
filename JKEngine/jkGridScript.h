#pragma once
#include "..\\Engine_SOURCE\\jkScript.h"


namespace jk
{
	class Camera;
	class GridScript : public Script
	{
	public:
		GridScript();
		~GridScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetCamera(Camera* camera) { mCamera = camera; }

	private:
		class Camera* mCamera;
		float	mMeshScale;
	};
}