#pragma once
#include "..\\Engine_SOURCE\\jkScript.h"
#include "..\\Engine_SOURCE\\jkCamera.h"
#include "Include_Common.h"


namespace jk
{
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
		Camera* mCamera;
		float	mMeshScale;
	};
}