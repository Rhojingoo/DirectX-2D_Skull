#include "jkStage2.h"

namespace jk
{
	Stage2::Stage2()
	{
	}
	Stage2::~Stage2()
	{
	}
	void Stage2::Initialize()
	{
			S2_King_BG* player = object::Instantiate<S2_King_BG>(Vector3(0.f, 0.f, -100.f), eLayerType::BACK_GROUND);
			player->GetComponent<Transform>()->SetScale(Vector3(900.f, 400.0f, 0.0f));
		
		//Main Camera
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			camera->AddComponent<CameraScript>();
	}
	void Stage2::Update()
	{
		Scene::Update();

		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(L"TitleScene");
		}
	}
	void Stage2::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void Stage2::Render()
	{
		Scene::Render();
	}
}