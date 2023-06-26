#include "jkStage1.h"
#include "jkSceneManager.h"
#include "jkTransform.h"
#include "jkMeshRenderer.h"
#include "jkResources.h"
#include "jkMesh.h"
#include "jkCameraScript.h"
#include "jkCamera.h"
#include "jkInput.h"

namespace jk
{
	jkStage1::jkStage1()
	{
	}
	jkStage1::~jkStage1()
	{
	}
	void jkStage1::Initialize()
	{
		{
			GameObject* player = new GameObject();
			AddGameObject(eLayerType::Player, player);
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial03"));
			player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
			player->GetComponent<Transform>()->SetScale(Vector3(7.f, 7.0f, 0.0f));
			//player->AddComponent<CameraScript>();
		}

		//Main Camera
		GameObject* camera = new GameObject();
		AddGameObject(eLayerType::Player, camera);
		camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		camera->AddComponent<CameraScript>();
	}
	void jkStage1::Update()
	{
		Scene::Update();

		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(L"TitleScene");
		}
	}
	void jkStage1::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void jkStage1::Render()
	{
		Scene::Render();
	}
}