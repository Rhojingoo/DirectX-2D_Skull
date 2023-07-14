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
				Title_Image* sc_image = object::Instantiate<Title_Image>(Vector3(0.f, 0.f, 10.f), eLayerType::Fore_Ground);
				sc_image->GetComponent<Transform>()->SetScale(Vector3(1920.f, 1080.f, 0.f));		
	
				//Title_Logo1* sc_logo = object::Instantiate<Title_Logo1>(Vector3(0.f, 0.f, 0.f), eLayerType::BACK_GROUND);
				//sc_logo->GetComponent<Transform>()->SetScale(Vector3(1275, 693.f, 0.f));

				Title_Logo2* sc_logo2 = object::Instantiate<Title_Logo2>(Vector3(0.f, 0.f, 0.f), eLayerType::BACK_GROUND);
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