#include "jkTitleScene.h"
#include "jkAudioListener.h"
#include "jkAudioClip.h"
#include "jkAudioSource.h"
#include "jkFontWrapper.h"


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
				sc_image->GetComponent<Transform>()->SetScale(Vector3(1600.f, 900.f, 0.f));		//(1920.f, 1080.f, 0.f)

				Back_ground* sc_logo2 = object::Instantiate<Back_ground>(Vector3(0.f, 0.f, 0.f), eLayerType::BACK_GROUND, L"Title_Mini_Logo");
				sc_logo2->GetComponent<Transform>()->SetScale(Vector3(1632, 257.f, 0.f));


				//GameObject* player = new GameObject();
				//AddGameObject(eLayerType::Player, player);
				//as = player->AddComponent<AudioSource>();
				//as->SetClip(Resources::Load<AudioClip>(L"TestSound", L"..\\Resources\\Sound\\Title\\MainTitle_Hardmode.wav"));
				//as->Play();

				//Main Camera
				GameObject* camera = new GameObject();
				AddGameObject(eLayerType::Camera, camera);
				camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
				Camera* cameraComp = camera->AddComponent<Camera>();		
				camera->AddComponent<AudioListener>();
		
		#pragma endregion
	}
	void jkTitleScene::Update()
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
			_time += 2.75 * Time::DeltaTime();
			if (_time > 3)
			{
				SceneManager::LoadScene(L"Start_Scene");
				_time = 0;
				_Fadecheck = false;				
			}
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
	void jkTitleScene::OnEnter()
	{
	}
	void jkTitleScene::OnExit()
	{
		//as->Stop();
	}
}