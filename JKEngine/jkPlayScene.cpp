#include "jkPlayScene.h"
#include "jkSceneManager.h"
#include "jkTransform.h"
#include "jkMeshRenderer.h"
#include "jkResources.h"
#include "jkMesh.h"
#include "jkCameraScript.h"
#include "jkCamera.h"
#include "jkInput.h"
#include "jkGridScript.h"

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
			player->SetName(L"Catle_Back");
			AddGameObject(eLayerType::Player, player);
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"Catle_wall_Back"));
			player->GetComponent<Transform>()->SetScale(Vector3(9.f, 3.f, 0.f));
			player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 100.01f));
		}

		{
			GameObject* player = new GameObject();
			player->SetName(L"Catle");
			AddGameObject(eLayerType::Player, player);
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"Catle_wall_Front_01"));
			player->GetComponent<Transform>()->SetScale(Vector3(16.5f, 6.f, 0.f));
			player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.35f, 10.0f)); 
		} 

		{
			GameObject* player = new GameObject();
			player->SetName(L"Devil_chair");
			AddGameObject(eLayerType::Player, player);
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"Devil_Chair"));
			player->GetComponent<Transform>()->SetScale(Vector3(3.f, 3.f, 0.f));
			player->GetComponent<Transform>()->SetPosition(Vector3(-7.f, 0.1f, 1.0f));
		}

		{
			GameObject* player = new GameObject();
			player->SetName(L"Skul_UI");
			AddGameObject(eLayerType::UI, player);
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"Skul_UI"));
			player->GetComponent<Transform>()->SetScale(Vector3(0.5f, 0.5f, 0.f));
			player->GetComponent<Transform>()->SetPosition(Vector3(-3.5f, -1.4f, 1.0f));
		}
		

		//Main Camera
		Camera* cameraComp = nullptr;
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			camera->AddComponent<CameraScript>();
		}

		//UI Camera
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -9.f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::Player, false);
		}


		{
			GameObject* grid = new GameObject();
			grid->SetName(L"Grid");
			AddGameObject(eLayerType::Grid, grid);
			MeshRenderer* mr = grid->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"GridMaterial"));
			GridScript* gridSc = grid->AddComponent<GridScript>();
			gridSc->SetCamera(cameraComp);
		}


		//{
		//	GameObject* player = new GameObject();
		//	AddGameObject(eLayerType::Player, player);
		//	MeshRenderer* mr = player->AddComponent<MeshRenderer>();
		//	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//	mr->SetMaterial(Resources::Find<Material>(L"Catle_wall_Front_04"));
		//	player->GetComponent<Transform>()->SetScale(Vector3(0.7f, 2.5f, 0.f));
		//	player->GetComponent<Transform>()->SetPosition(Vector3(-4.77f, 0.35f, 0.0f));
		//	//player->AddComponent<CameraScript>();
		//}


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

		//마우스좌표계 변경하는법
		//Vector3 pos(600, 450, 0.0f);
		//Vector3 pos2(600, 450, 1000.0f);
		//Viewport viewport;
		//viewport.width = 1600.0f;
		//viewport.height = 900.0f;
		//viewport.x = 0;
		//viewport.y = 0;
		//viewport.minDepth = 0.0f;
		//viewport.maxDepth = 1.0f;

		//pos = viewport.Unproject(pos, Camera::GetProjectionMatrix(), Camera::GetViewMatrix(), Matrix::Identity);
		//pos2 = viewport.Unproject(pos2, Camera::GetProjectionMatrix(), Camera::GetViewMatrix(), Matrix::Identity);

		Scene::LateUpdate();
	}

	void PlayScene::Render()
	{
		Scene::Render();
	}
}