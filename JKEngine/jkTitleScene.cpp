#include "jkTitleScene.h"

namespace jk
{
	jkTitleScene::jkTitleScene()
	{
	}
	jkTitleScene::~jkTitleScene()
	{
	}
	void jkTitleScene::Initialize()
	{
		#pragma region Title_Image & Camera
				Back_ground* sc_image = object::Instantiate<Back_ground>(Vector3(0.f, 0.f, 10.f), eLayerType::Fore_Ground, L"Title_Image");
				sc_image->GetComponent<Transform>()->SetScale(Vector3(1920.f, 1080.f, 0.f));		
			
				//Back_ground* sc_logo = object::Instantiate<Back_ground>(Vector3(0.f, 0.f, 0.f), eLayerType::BACK_GROUND, L"Title_Logo");
				//sc_logo->GetComponent<Transform>()->SetScale(Vector3(1275, 693.f, 0.f));

				Back_ground* sc_logo2 = object::Instantiate<Back_ground>(Vector3(0.f, 0.f, 0.f), eLayerType::BACK_GROUND, L"Title_Mini_Logo");
				sc_logo2->GetComponent<Transform>()->SetScale(Vector3(1632, 257.f, 0.f));

				//Main Camera
				GameObject* camera = new GameObject();
				AddGameObject(eLayerType::Player, camera);
				camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
				Camera* cameraComp = camera->AddComponent<Camera>();		
		#pragma endregion
	}
	void jkTitleScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(L"Start_Scene");
		}
	}
	void jkTitleScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void jkTitleScene::Render()
	{
		Scene::Render();
	}
}