#pragma once
#include "jkGameObject.h"
namespace jk
{
	class Tile_Mouse : public GameObject
	{
	public:
		Tile_Mouse();
		~Tile_Mouse();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
		void SetCamera(GameObject* cm) { mCamera = cm; }

	private:
		GameObject* mCamera;
		Vector3 mPos;
	};


}
