#include "jkTile_Mouse.h"
#include "jkInput.h"
#include "jkTransform.h"
#include "jkCamera.h"
#include "jkSceneManager.h"

namespace jk
{
	Tile_Mouse::Tile_Mouse()
		:mCamera()
	{
	}

	Tile_Mouse::~Tile_Mouse()
	{
	}

	void Tile_Mouse::Initialize()
	{
	}

	void Tile_Mouse::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 Pos = jk::Input::GetMousePos();
		mPos = Vector3(Pos.x, Pos.y, -10.0f);

		Camera* camera = mCamera->GetComponent<Camera>();
		tr->SetPosition(camera->GetWorldTransform(mPos));

		GameObject::Update();
	}
	void Tile_Mouse::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Tile_Mouse::Render()
	{
		GameObject::Render();
	}

}