#pragma once
#include "jkGameObject.h"
//#include "jkUICamera.h"

using namespace jk::math;
using namespace jk;

namespace jk
{
	class Mouse : public jk::GameObject
	{
	public:
		Mouse();
		~Mouse();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetCamera(GameObject* cm) { mCamera = cm; }
		Vector3 GetPosition() { return mPos; }
		Vector3 ChangeWorldPos(Vector3 pos);

	private:
		Vector3 mPos;
		GameObject* mCamera;
	};
}

