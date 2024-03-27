#include "Stage2_Door.h"
#include "Include_Common.h"
#include "Alpha_Blend.h"

namespace jk
{
	Stage2_Door::Stage2_Door()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Stage2_Door::~Stage2_Door()
	{
	}
	void Stage2_Door::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		tr = this->GetComponent<Transform>();

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Door\\Stage2\\Open_Door\\Basic_Door", this, 0, 0.05f);
		at->CreateAnimations(L"..\\Resources\\Texture\\Door\\Stage2\\Open_Door\\Boss_Door", this, 0, 0.05f);
		at->CreateAnimations(L"..\\Resources\\Texture\\Door\\Stage2\\Open_Door\\GetSkull_Door", this, 0, 0.05f);
		at->CreateAnimations(L"..\\Resources\\Texture\\Door\\Stage2\\Open_Door\\GetTreasure_Door", this, 0, 0.05f);
		at->CreateAnimations(L"..\\Resources\\Texture\\Door\\Stage2\\Open_Door\\MiniBoss_Door", this, 0, 0.05f);
		at->CreateAnimations(L"..\\Resources\\Texture\\Door\\Stage2\\Open_Door\\DarkMarcket", this, 0, 0.05f);
		at->CreateAnimations(L"..\\Resources\\Texture\\Door\\Stage2\\Open_Door\\Upgrade_Door", this, 0, 0.05f);

		at->CreateAnimations(L"..\\Resources\\Texture\\Door\\Stage2\\Close_Door\\Close_Basic_Door", this, 0, 0.05f);
		at->CreateAnimations(L"..\\Resources\\Texture\\Door\\Stage2\\Close_Door\\Close_Boss_Door", this, 0, 0.05f);
		at->CreateAnimations(L"..\\Resources\\Texture\\Door\\Stage2\\Close_Door\\Close_DarkMarcket", this, 0, 0.05f);
		at->CreateAnimations(L"..\\Resources\\Texture\\Door\\Stage2\\Close_Door\\Close_GetSkull_Door", this, 0, 0.05f);
		at->CreateAnimations(L"..\\Resources\\Texture\\Door\\Stage2\\Close_Door\\Close_GetTreasure_Door", this, 0, 0.05f);
		at->CreateAnimations(L"..\\Resources\\Texture\\Door\\Stage2\\Close_Door\\Close_MiniBoss_Door", this, 0, 0.05f);

		at->CreateAnimations(L"..\\Resources\\Texture\\Door\\Stage2\\Deactivate_Door\\First", this, 0, 0.05f);
		at->CreateAnimations(L"..\\Resources\\Texture\\Door\\Stage2\\Deactivate_Door\\Second", this, 0, 0.05f);

		at->PlayAnimation(L"Open_DoorBasic_Door", true);
		GameObject::Initialize();
	}
	void Stage2_Door::Update()
	{
		if (_Set_Door_Allow == true)
		{
			if (_Stage2_Door == 0)
			{
				at->PlayAnimation(L"Open_DoorBasic_Door", true);
				_State = Stage2Door_State::Open_Basic_Door;
			}
			if (_Stage2_Door == 1)
			{
				at->PlayAnimation(L"Open_DoorGetSkull_Door", true);
				_State = Stage2Door_State::Open_GetSkull_Door;
			}
			if (_Stage2_Door == 2)
			{
				at->PlayAnimation(L"Open_DoorMiniBoss_Door", true);
				_State = Stage2Door_State::Open_MiniBoss_Door;
			}
			if (_Stage2_Door == 3)
			{
				at->PlayAnimation(L"Open_DoorBoss_Door", true);
				_State = Stage2Door_State::Open_Boss_Door;
			}


			if (_Stage2_Door == 4)
			{
				at->PlayAnimation(L"Close_DoorClose_Basic_Door", true);
				_State = Stage2Door_State::Close_Basic_Door;
			}
			if (_Stage2_Door == 5)
			{
				at->PlayAnimation(L"Close_DoorClose_GetSkull_Door", true);
				_State = Stage2Door_State::Close_GetSkull_Door;
			}
			if (_Stage2_Door == 6)
			{
				at->PlayAnimation(L"Close_DoorClose_MiniBoss_Door", true);
				_State = Stage2Door_State::Close_MiniBoss_Door;
			}
			if (_Stage2_Door == 7)
			{
				at->PlayAnimation(L"Close_DoorClose_Boss_Door", true);
				_State = Stage2Door_State::Close_Boss_Door;
			}
			if (_Stage2_Door == 8)
			{
				at->PlayAnimation(L"Deactivate_DoorFirst", true);
				_State = Stage2Door_State::Deactivate_Door_First;
			}
			if (_Stage2_Door == 9)
			{
				at->PlayAnimation(L"Deactivate_DoorSecond", true);
				_State = Stage2Door_State::Deactivate_Door_Second;
			}
			_Set_Door_Allow = false;
		}


		switch (_State)
		{
		case jk::Stage2_Door::Stage2Door_State::Open_Basic_Door:
			basic_door();
			break;

		case jk::Stage2_Door::Stage2Door_State::Open_GetSkull_Door:
			get_skull_door();
			break;

		case jk::Stage2_Door::Stage2Door_State::Open_MiniBoss_Door:
			mini_boss_door();
			break;

		case jk::Stage2_Door::Stage2Door_State::Open_Boss_Door:
			boss_door();
			break;

		case jk::Stage2_Door::Stage2Door_State::Close_Basic_Door:
			basic_door();
			break;

		case jk::Stage2_Door::Stage2Door_State::Close_GetSkull_Door:
			get_skull_door();
			break;

		case jk::Stage2_Door::Stage2Door_State::Close_MiniBoss_Door:
			mini_boss_door();
			break;

		case jk::Stage2_Door::Stage2Door_State::Close_Boss_Door:
			boss_door();
			break;

		case jk::Stage2_Door::Stage2Door_State::Deactivate_Door_First:
			basic_door();
			break;

		case jk::Stage2_Door::Stage2Door_State::Deactivate_Door_Second:
			basic_door();
			break;

		default:
			break;
		}
		GameObject::Update();
	}

	void Stage2_Door::LateUpdate()
	{
		_collider->SetSize(Vector2(0.35f, 0.65f));
		_collider->SetCenter(Vector2(5.f, -20.f));
		GameObject::LateUpdate();
	}

	void Stage2_Door::Render()
	{
		GameObject::Render();
	}

	void Stage2_Door::OnCollisionEnter(Collider2D* other)
	{

	}
	void Stage2_Door::OnCollisionStay(Collider2D* other)
	{
		if (Player* _head = dynamic_cast<Player*>(other->GetOwner()))
		{
			if (Input::GetKeyState(eKeyCode::F) == eKeyState::Down)
			{
				_Alpha = object::InstantiateActive<Alpha_Blend>(Vector3(0.f, 0.f, -251.f), eLayerType::Map_Effect);
				_Alpha->GetComponent<Transform>()->SetScale(Vector3(10000.f, 10000.f, 0.f));
				_Alpha->Set_Black_Transparent();
				_Fadecheck = true;
			}
			if (_Fadecheck == true)
			{
				_time += 2.75f * static_cast<float>(Time::DeltaTime());
				if (_time > 3)
				{
					SceneManager::LoadScene(Path);
					_time = 0;
					_Fadecheck = false;
				}
			}
		}
	}
	void Stage2_Door::OnCollisionExit(Collider2D* other)
	{
	}

	void Stage2_Door::basic_door()
	{
	}
	void Stage2_Door::get_skull_door()
	{
	}
	void Stage2_Door::mini_boss_door()
	{
	}
	void Stage2_Door::boss_door()
	{
	}
}