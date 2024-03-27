#include "jkLoadingScene.h"
#include "jkAudioListener.h"
#include "jkAudioClip.h"
#include "jkAudioSource.h"
#include "jkFontWrapper.h"
#include "Include_Common.h"
#include "Alpha_Blend.h"
#include "..\Engine_SOURCE\jkAudioSource.h"

namespace jk
{
	jkLoadingScene::jkLoadingScene()
	{
	}
	jkLoadingScene::~jkLoadingScene()
	{
	}
	void jkLoadingScene::Initialize()
	{
#pragma region Title_Image & Camera
		Back_ground* sc_image = object::Instantiate<Back_ground>(Vector3(0.f, 0.f, 10.f), eLayerType::Fore_Ground, L"Loading_Image");
		sc_image->GetComponent<Transform>()->SetScale(Vector3(1600.f, 900.f, 0.f));		//(1920.f, 1080.f, 0.f)



		//Main Camera
		GameObject* camera = new GameObject();
		AddGameObject(eLayerType::Camera, camera);
		camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		camera->AddComponent<AudioListener>();

#pragma endregion
	}
	void jkLoadingScene::Update()
	{
		Scene::Update();
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			_Alpha = object::Instantiate<Alpha_Blend>(Vector3(0.f, 0.f, -251.f), eLayerType::Map_Effect);
			_Alpha->GetComponent<Transform>()->SetScale(Vector3(2600.f, 1500.f, 0.f));
			_Alpha->Set_Black_Transparent();
			_Fadecheck = true;
		}
		if (_Fadecheck == true)
		{
			_time += 2.75f * static_cast<float>(Time::DeltaTime());
			if (_time > 3)
			{
				SceneManager::LoadScene(L"Start_Scene");
				_time = 0;
				_Fadecheck = false;
			}
		}
	}
	void jkLoadingScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void jkLoadingScene::Render()
	{
		Scene::Render();
	}
	void jkLoadingScene::OnEnter()
	{
	}
	void jkLoadingScene::OnExit()
	{
	}
}