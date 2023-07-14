#include "guiEditor.h"
#include "..\\Engine_SOURCE\\jkMesh.h"
#include "..\\Engine_SOURCE\\jkResources.h"
#include "..\\Engine_SOURCE\\jkTransform.h"
#include "..\\Engine_SOURCE\\jkMeshRenderer.h"
#include "..\\Engine_SOURCE\\jkMaterial.h"
#include "..\\Engine_SOURCE\\jkRenderer.h"
#include "jkGridScript.h"

namespace gui
{
	using namespace jk::enums;
	std::vector<Widget*> Editor::mWidgets = {};
	std::vector<EditorObject*> Editor::mEditorObjects = {};
	std::vector<DebugOjbect*> Editor::mDebugOjbects = {};

	void Editor::Initialize()
	{
		mDebugOjbects.resize((UINT)eColliderType::End);

		std::shared_ptr<jk::Mesh> mesh
			= jk::Resources::Find<jk::Mesh>(L"DebugRect");
		std::shared_ptr<jk::Material> material
			= jk::Resources::Find<jk::Material>(L"DebugMaterial");

		mDebugOjbects[(UINT)eColliderType::Rect] = new DebugOjbect();
		mDebugOjbects[(UINT)eColliderType::Rect]->AddComponent<jk::Transform>();
		jk::MeshRenderer* mr
			= mDebugOjbects[(UINT)eColliderType::Rect]->AddComponent<jk::MeshRenderer>();
		mr->SetMaterial(material);
		mr->SetMesh(mesh);


		//EditorObject* grid = new EditorObject();
		//grid->SetName(L"Grid");

		//mr = grid->AddComponent<jk::MeshRenderer>();
		//mr->SetMesh(jk::Resources::Find<jk::Mesh>(L"RectMesh"));
		//mr->SetMaterial(jk::Resources::Find<jk::Material>(L"GridMaterial"));
		//jk::GridScript* gridSc = grid->AddComponent<jk::GridScript>();
		//gridSc->SetCamera(jk::renderer::cameras[0]);

		//mEditorObjects.push_back(grid);

	}
	void Editor::Run()
	{
		Update();
		LateUpdate();
		Render();
	}
	void Editor::Update()
	{


		for (EditorObject* obj : mEditorObjects)
		{
			obj->Update();
		}
	}
	void Editor::LateUpdate()
	{
		for (EditorObject* obj : mEditorObjects)
		{
			obj->LateUpdate();
		}
	}
	void Editor::Render()
	{	
		for (EditorObject* obj : mEditorObjects)
		{
			obj->Render();
		}

		for (const jk::graphics::DebugMesh& mesh
			: jk::renderer::debugMeshs)
		{
			DebugRender(mesh);
		}
	}
	void Editor::Release()
	{
		for (auto widget : mWidgets)
		{
			delete widget;
			widget = nullptr;
		}

		for (auto editorObj : mEditorObjects)
		{
			delete editorObj;
			editorObj = nullptr;
		}

		for (auto debugObj : mDebugOjbects)
		{
			delete debugObj;
			debugObj = nullptr;
		}
	}

	void Editor::DebugRender(const jk::graphics::DebugMesh& mesh)
	{
		DebugOjbect* debugObj = mDebugOjbects[(UINT)mesh.type];

		// 위치 크기 회전 정보를 받아와서
		// 해당 게임오브젝트위에 그려주면된다.
		jk::Transform* tr = debugObj->GetComponent<jk::Transform>();
		Vector3 pos = mesh.position;
		pos.z -= 0.01f;

		tr->SetPosition(pos);
		tr->SetScale(mesh.scale);
		tr->SetRotation(mesh.rotation);
		tr->LateUpdate();

		jk::Camera* mainCamara = renderer::mainCamera;
		jk::Camera::SetGpuViewMatrix(mainCamara->GetViewMatrix());
		jk::Camera::SetGpuProjectionMatrix(mainCamara->GetProjectionMatrix());

		debugObj->Render();
	}
}
