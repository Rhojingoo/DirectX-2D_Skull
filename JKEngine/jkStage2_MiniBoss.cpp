#include "jkStage2_MiniBoss.h"

jk::Stage2_MiniBoss::Stage2_MiniBoss()
{
}

jk::Stage2_MiniBoss::~Stage2_MiniBoss()
{
}

void jk::Stage2_MiniBoss::Initialize()
{

#pragma region Camera & Grid

	//Main Camera
	Main_Camera* camera = object::Instantiate<Main_Camera>(Vector3(0.f, 0.f, -10.f), eLayerType::Camera);
	Camera* cameraComp = camera->AddComponent<Camera>();
	cameraComp->TurnLayerMask(eLayerType::UI, false);
	camera->AddComponent<CameraScript>();
	renderer::cameras.push_back(cameraComp);
	renderer::mainCamera = cameraComp;

	//UI Camera		
	UI_Camera* UI_camera = object::Instantiate<UI_Camera>(Vector3(0.f, 0.f, -10.f), eLayerType::Camera);
	Camera* cameraComp_ui = UI_camera->AddComponent<Camera>();
	cameraComp_ui->TurnLayerMask(eLayerType::Player, false);
	cameraComp_ui->TurnLayerMask(eLayerType::Monster, false);
	cameraComp_ui->TurnLayerMask(eLayerType::MiniBoss, false);
	cameraComp_ui->TurnLayerMask(eLayerType::Boss, false);
	cameraComp_ui->TurnLayerMask(eLayerType::Bullet, false);
	cameraComp_ui->TurnLayerMask(eLayerType::Effect, false);
	cameraComp_ui->TurnLayerMask(eLayerType::Camera, false);
	cameraComp_ui->TurnLayerMask(eLayerType::Item, false);
	cameraComp_ui->TurnLayerMask(eLayerType::BACK_GROUND, false);
	cameraComp_ui->TurnLayerMask(eLayerType::Fore_Ground, false);
	cameraComp_ui->TurnLayerMask(eLayerType::Mid_Ground, false);
	cameraComp_ui->TurnLayerMask(eLayerType::Map_Effect, false);
	cameraComp_ui->TurnLayerMask(eLayerType::Camera, false);
	//renderer::cameras.push_back(cameraComp_ui);

	//Grid* grid = object::Instantiate<Grid>(Vector3(Vector3::One), eLayerType::Grid);
	//grid->SetName(L"Catle_Grid");
	//GridScript* gridSc = grid->AddComponent<GridScript>();
	//gridSc->SetCamera(cameraComp);
#pragma endregion 
}

void jk::Stage2_MiniBoss::Update()
{
	if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
	{
		SceneManager::LoadScene(L"Stage2_2");
	}
	Scene::Update();
}

void jk::Stage2_MiniBoss::LateUpdate()
{
	Scene::LateUpdate();
}

void jk::Stage2_MiniBoss::Render()
{
	Scene::Render();
}
