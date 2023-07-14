#include "jkStage1.h"


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
	
			S1_King_BG* player = object::Instantiate<S1_King_BG>(Vector3(0.f, 0.f, -100.f), eLayerType::BACK_GROUND);				
			player->GetComponent<Transform>()->SetScale(Vector3(900.f, 560.0f, 0.0f));			

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
			SceneManager::LoadScene(L"Stage2");
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