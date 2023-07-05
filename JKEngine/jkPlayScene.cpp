#include "jkPlayScene.h"
#include "jkSceneManager.h"
#include "jkTransform.h"
#include "jkMeshRenderer.h"
#include "jkResources.h"
#include "jkMesh.h"
#include "jkCameraScript.h"
#include "jkCamera.h"
#include "jkInput.h"
#include "jkApplication.h"


extern jk::Application application;

namespace jk
{
	PlayScene::PlayScene()
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize(HWND hWnd)
	{
		mHwnd = hWnd;
		mHdc = GetDC(hWnd);

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
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
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


		Scene::LateUpdate();
	}

	void PlayScene::Render()
	{
		//HPEN redPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
		//HPEN oldPen = (HPEN)SelectObject(mHdc, redPen);

		//int maxRow = application.GetHeight() / TILE_SIZE_Y + 1;
		//for (size_t y = 0; y < maxRow; y++)
		//{
		//	MoveToEx(mHdc, 0, TILE_SIZE_Y * y, NULL);
		//	LineTo(mHdc, application.GetWidth(), TILE_SIZE_Y * y);
		//}
		//int maxColumn = application.GetWidth() / TILE_SIZE_X + 1;
		//for (size_t x = 0; x < maxColumn; x++)
		//{
		//	MoveToEx(mHdc, TILE_SIZE_X * x, 0, NULL);
		//	LineTo(mHdc, TILE_SIZE_X * x, application.GetHeight());
		//}
		//(HPEN)SelectObject(mHdc, oldPen);
		//DeleteObject(redPen);


		Scene::Render();
	}
}