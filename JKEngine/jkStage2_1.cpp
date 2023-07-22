#include "jkStage2_1.h"

namespace jk
{
	Stage2_1::Stage2_1()
	{
	}
	Stage2_1::~Stage2_1()
	{
	}
	void Stage2_1::Initialize()
	{
			Back_ground* player = object::Instantiate<Back_ground>(Vector3(0.f, 0.f, -100.f), eLayerType::BACK_GROUND, L"Stage_king2");
			player->GetComponent<Transform>()->SetScale(Vector3(900.f, 400.0f, 0.0f));
		
		//Main Camera
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			camera->AddComponent<CameraScript>();
	}
	void Stage2_1::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(L"TitleScene");
		}
		Scene::Update();
	}
	void Stage2_1::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void Stage2_1::Render()
	{
		Scene::Render();
	}
}