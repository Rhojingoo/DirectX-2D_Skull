#include "jkStage1_MiniBoss.h"
#include "jkParticleSystem.h"
#include "jkComputeShader.h"
#include "jkPaintShader.h"

namespace jk
{
	Stage1_MiniBoss::Stage1_MiniBoss()
	{
	}
	Stage1_MiniBoss::~Stage1_MiniBoss()
	{
	}
	void Stage1_MiniBoss::Initialize()
	{

		//std::shared_ptr<PaintShader> paintShader = Resources::Find<PaintShader>(L"PaintShader");
		//std::shared_ptr<Texture> paintTexture = Resources::Find<Texture>(L"PaintTexuture");
		//paintShader->SetTarget(paintTexture);
		//paintShader->OnExcute();

		//ComputeShader* cs = new ComputeShader();
		//cs->Create(L"PaintCS.hlsl", "main");


			#pragma region Test_particle
					//GameObject* player = new GameObject();
					//player->SetName(L"Particle");
					//AddGameObject(eLayerType::Monster, player);
					//ParticleSystem* mr = player->AddComponent<ParticleSystem>();
					//player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -20.0f));
					//player->GetComponent<Transform>()->SetScale(Vector3(100.2f, 100.2f, 0.2f));
			#pragma endregion

		#pragma region BG	
				{
					//Back_ground* Fore_S1_1_color = object::Instantiate<Back_ground>(Vector3(0.f, 50.f, 105.f), eLayerType::Fore_Ground, L"Stage1_Fore_GR_Color");
					//Fore_S1_1_color->GetComponent<Transform>()->SetScale(Vector3(960.f * 1.5, 800.f, 0.f));	Fore_S1_1_color->SetName(L"s1_1_fore_gr_color");

					//Back_ground* Fore_S1_1_tree = object::Instantiate<Back_ground>(Vector3(0.f, -200.f, 103.f), eLayerType::Fore_Ground, L"Stage1_Fore_GR_Tree");
					//Fore_S1_1_tree->GetComponent<Transform>()->SetScale(Vector3(960.f * 1.5, 800.f, 0.f));	Fore_S1_1_tree->SetName(L"s1_1_fore_gr_tree");

					//Back_ground* Mid_S1_1 = object::Instantiate<Back_ground>(Vector3(0.f, 0.f, 101.f), eLayerType::Fore_Ground, L"Stage1_Mid_GR1_1");
					//Mid_S1_1->GetComponent<Transform>()->SetScale(Vector3(960.f * 1.5, 800.f, 0.f));	Mid_S1_1->SetName(L"Mid_S1_1");

					//Back_ground* Back_GR03 = object::Instantiate<Back_ground>(Vector3(50.f, -150.f, 99.f), eLayerType::Fore_Ground, L"Stage1_Back_GR12");
					//Back_GR03->GetComponent<Transform>()->SetScale(Vector3(718.f, 380.f, 0.f));	Back_GR03->SetName(L"back_gr00");

					//Back_ground* Back_GR04 = object::Instantiate<Back_ground>(Vector3(-450.f, -90.f, 99.f), eLayerType::Fore_Ground, L"Stage1_Back_GR02");
					//Back_GR04->GetComponent<Transform>()->SetScale(Vector3(145.f, 172.f, 0.f));	Back_GR04->SetName(L"back_gr01");

					//Back_ground* Back_GR05 = object::Instantiate<Back_ground>(Vector3(420.f, -80.f, 99.f), eLayerType::Fore_Ground, L"Stage1_Back_GR02");
					//Back_GR05->GetComponent<Transform>()->SetScale(Vector3(145.f, 172.f, 0.f));	Back_GR05->SetName(L"back_gr02");
				}
		#pragma endregion

		#pragma region tile_map		
				{
					//static Vector2 TileSize = Vector2(32.f, 32.f);
					//static int Tile_Colum = 40;
					//static int Tile_Row = 30;

					//static Tile_Ground* Tile_map = object::Instantiate<Tile_Ground>(eLayerType::BACK_GROUND);
					//Tile_map->SetName(L"tile_stage1_miniboss");
					////Collider2D* cd = Tile_map->AddComponent<Collider2D>();
					//Transform* tr = Tile_map->GetComponent<Transform>();
					////tr->SetPositionZ(-200.f);
					//tr->AddPositionY(0.f);
					//tr->SetPositionX(0.f);
					//tr->SetScale(Vector3(Tile_Colum * TileSize.x, Tile_Row * TileSize.y, 0.f));

					//TileMap::TileMap_Setting(Tile_map, L"Stage1_MiniBoss", TileSize, Tile_Colum, Tile_Row, L"\\Resources\\Metadata\\TileMap\\Stage1_MiniBoss.xml");
				}
		#pragma endregion	

		#pragma region Cam & Mouse& Grid
				//Main Camera			
				Main_Camera* camera = object::Instantiate<Main_Camera>(Vector3(0.f, 0.f, -10.f), eLayerType::Camera);
				Camera* cameraComp = camera->AddComponent<Camera>();
				cameraComp->TurnLayerMask(eLayerType::UI, false);
				camera->AddComponent<CameraScript>();
				renderer::cameras.push_back(cameraComp);
				renderer::mainCamera = cameraComp;

				//UI Camera		
				//UI_Camera* UI_camera = object::Instantiate<UI_Camera>(Vector3(0.f, 0.f, -10.f), eLayerType::Camera);
				//Camera* cameraComp_ui = UI_camera->AddComponent<Camera>();
				//cameraComp_ui->TurnLayerMask(eLayerType::Player, false);
				//cameraComp_ui->TurnLayerMask(eLayerType::Monster, false);
				//cameraComp_ui->TurnLayerMask(eLayerType::MiniBoss, false);
				//cameraComp_ui->TurnLayerMask(eLayerType::Boss, false);
				//cameraComp_ui->TurnLayerMask(eLayerType::Bullet, false);
				//cameraComp_ui->TurnLayerMask(eLayerType::Camera, false);
				//cameraComp_ui->TurnLayerMask(eLayerType::Item, false);
				//cameraComp_ui->TurnLayerMask(eLayerType::BACK_GROUND, false);
				//cameraComp_ui->TurnLayerMask(eLayerType::Fore_Ground, false);
				//cameraComp_ui->TurnLayerMask(eLayerType::Mid_Ground, false);
				//cameraComp_ui->TurnLayerMask(eLayerType::Map_Effect, false);
				//cameraComp_ui->TurnLayerMask(eLayerType::Camera, false);
				//renderer::cameras.push_back(cameraComp_ui);

				//UI_Mouse
				//UI_Mouse* cursor = object::Instantiate<UI_Mouse>(Vector3(Vector3::One), eLayerType::Camera);
				//cursor->SetName(L"Catle_Cursor_UI");
				//cursor->GetComponent<Transform>()->SetScale(Vector3(42.f, 42.f, -250.f));
				//cursor->SetName(L"Mouse_UI"); cursor->SetCamera(UI_camera);

				//Grid
				//Grid* grid = object::Instantiate<Grid>(Vector3(Vector3::One), eLayerType::Grid);
				//grid->SetName(L"Catle_Grid");
				//GridScript* gridSc = grid->AddComponent<GridScript>();
				//gridSc->SetCamera(cameraComp);
#pragma endregion	

	}
	void Stage1_MiniBoss::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(L"Stage1_2");
		}
		Scene::Update();
	}
	void Stage1_MiniBoss::LateUpdate()
	{
		Vector3 pos(800, 450, 0.0f);
		Vector3 pos2(800, 450, 1000.0f);
		Viewport viewport;
		viewport.width = 1600.0f;
		viewport.height = 900.0f;
		viewport.x = 0;
		viewport.y = 0;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		pos = viewport.Unproject(pos, Camera::GetGpuProjectionMatrix(), Camera::GetGpuViewMatrix(), Matrix::Identity);
		pos2 = viewport.Unproject(pos2, Camera::GetGpuProjectionMatrix(), Camera::GetGpuViewMatrix(), Matrix::Identity);

		Scene::LateUpdate();
	}
	void Stage1_MiniBoss::Render()
	{
		Scene::Render();
	}
}