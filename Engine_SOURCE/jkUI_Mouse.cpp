#include "jkUI_Mouse.h"



namespace jk
{
	using namespace jk;

	UI_Mouse::UI_Mouse()
		:mPos(Vector3(0.0f, 0.0f, 10.0f))
		,mCamera(nullptr)
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMaterial(Resources::Find<Material>(L"Mouse"));
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		
	}
	UI_Mouse::~UI_Mouse()
	{
	}

	void UI_Mouse::Initialize()
	{
	}
	void UI_Mouse::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 Pos = jk::Input::GetMousePos();
		mPos = Vector3(Pos.x, Pos.y, -10.0f);
		tr->SetPosition(ChangeWorldPos(mPos));

		GameObject::Update();
	}
	void UI_Mouse::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void UI_Mouse::Render()
	{
		GameObject::Render();
	}

	Vector3 UI_Mouse::ChangeWorldPos(Vector3 pos)
	{
		Camera* camera = mCamera->GetComponent<Camera>();
		Vector3 mpos = Vector3(pos.x, pos.y, pos.z);
		Matrix projection = camera->GetProjectionMatrix();
		Matrix view = camera->GetViewMatrix();
		Matrix world = Matrix::Identity;
		RECT rt = {};
		GetClientRect(application.GetHwnd(), &rt);
		Viewport viewport(rt);
		Vector3 Current_Pos = viewport.Unproject(mpos, projection, view, world);
		return Vector3(Current_Pos.x, Current_Pos.y, Current_Pos.z);
	}
}