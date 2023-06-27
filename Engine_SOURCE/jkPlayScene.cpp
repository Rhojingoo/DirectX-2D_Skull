#include "jkPlayScene.h"
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
	PlayScene::PlayScene()
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		{
			GameObject* player = new GameObject();
			AddGameObject(eLayerType::Player, player);
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"Catle_wall_Back"));
			player->GetComponent<Transform>()->SetScale(Vector3(9.f, 3.f, 0.f));
			player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 100.0f));
			//player->AddComponent<CameraScript>();
		}

		{
			GameObject* player = new GameObject();
			AddGameObject(eLayerType::Player, player);
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"Catle_wall_Front_01"));
			player->GetComponent<Transform>()->SetScale(Vector3(1.f, 2.5f, 0.f));
			player->GetComponent<Transform>()->SetPosition(Vector3(-4.0f, 0.35f, 0.0f));
			//player->AddComponent<CameraScript>();
		}

		{
			GameObject* player = new GameObject();
			AddGameObject(eLayerType::Player, player);
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"Catle_wall_Front_04"));
			player->GetComponent<Transform>()->SetScale(Vector3(0.7f, 2.5f, 0.f));
			player->GetComponent<Transform>()->SetPosition(Vector3(-4.77f, 0.35f, 0.0f));
			//player->AddComponent<CameraScript>();
		}


		//{
		//	GameObject* player = new GameObject();
		//	AddGameObject(eLayerType::Player, player);
		//	MeshRenderer* mr = player->AddComponent<MeshRenderer>();
		//	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//	mr->SetMaterial(Resources::Find<Material>(L"Catle_wall_Front_03"));
		//	//player->GetComponent<Transform>()->SetScale(Vector3(10.25f, 5.0f, 0.0f));
		//	player->GetComponent<Transform>()->SetPosition(Vector3(2.0f, 0.0f, 0.0f));
		//	//player->AddComponent<CameraScript>();
		//}


		//{
		//	GameObject* player = new GameObject();
		//	AddGameObject(eLayerType::Player, player);
		//	MeshRenderer* mr = player->AddComponent<MeshRenderer>();
		//	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//	mr->SetMaterial(Resources::Find<Material>(L"Catle_wall_Front_04"));
		//	//player->GetComponent<Transform>()->SetScale(Vector3(10.25f, 5.0f, 0.0f));
		//	player->GetComponent<Transform>()->SetPosition(Vector3(2.0f, 0.0f, 0.0f));
		//	//player->AddComponent<CameraScript>();
		//}



		//Main Camera
		GameObject* camera = new GameObject();
		AddGameObject(eLayerType::Player, camera);
		camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		camera->AddComponent<CameraScript>();
		//GameObject* player2 = new GameObject();
		//AddGameObject(eLayerType::Player, player2);
		//player2->AddComponent<MeshRenderer>();
	}

	void PlayScene::Update()
	{
		Scene::Update();
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(L"Stage1");
		}
	}

	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void PlayScene::Render()
	{
		Scene::Render();
	}
}