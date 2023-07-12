#include "jkMouse.h"
#include "jkInput.h"
#include "jkTransform.h"
#include "jkMeshRenderer.h"
#include "jkResources.h"
#include "jkSceneManager.h"
#include "jkCamera.h"


namespace jk
{
	using namespace jk;

	Mouse::Mouse()
		:mPos(Vector3(0.0f, 0.0f, 10.0f))
		,mCamera(nullptr)
	{
	}
	Mouse::~Mouse()
	{
	}

	void Mouse::Initialize()
	{
	}
	void Mouse::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 Pos = jk::Input::GetMousePos();
		mPos = Vector3(Pos.x, Pos.y, -10.0f);
		tr->SetPosition(ChangeWorldPos(mPos));

		GameObject::Update();
	}
	void Mouse::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Mouse::Render()
	{
		GameObject::Render();
	}

	Vector3 Mouse::ChangeWorldPos(Vector3 pos)
	{
		Camera* camera = mCamera->GetComponent<Camera>();
		Vector3 mpos = Vector3(pos.x, pos.y, pos.z);
		Matrix projection = camera->GetmProjection();
		Matrix view = camera->GetmView();
		Matrix world = Matrix::Identity;
		RECT rt = {};
		GetClientRect(application.GetHwnd(), &rt);
		Viewport viewport(rt);
		Vector3 Current_Pos = viewport.Unproject(mpos, projection, view, world);
		return Vector3(Current_Pos.x, Current_Pos.y, Current_Pos.z);
	}
}