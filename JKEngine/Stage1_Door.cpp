#include "Stage1_Door.h"

namespace jk
{
	Stage1_Door::Stage1_Door()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Stage1_Door::~Stage1_Door()
	{
	}
	void Stage1_Door::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		tr = this->GetComponent<Transform>();

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Door\\Stage1\\Open_Door\\Basic_Door", this,0, 0.05);
		at->CreateAnimations(L"..\\Resources\\Texture\\Door\\Stage1\\Open_Door\\Boss_Door", this,0, 0.05);
		at->CreateAnimations(L"..\\Resources\\Texture\\Door\\Stage1\\Open_Door\\GetSkull_Door", this,0, 0.05);
		at->CreateAnimations(L"..\\Resources\\Texture\\Door\\Stage1\\Open_Door\\GetTreasure_Door", this,0, 0.05);
		at->CreateAnimations(L"..\\Resources\\Texture\\Door\\Stage1\\Open_Door\\MiniBoss_Door", this,0, 0.05);
		at->CreateAnimations(L"..\\Resources\\Texture\\Door\\Stage1\\Open_Door\\DarkMarcket", this, 0, 0.05);
		at->CreateAnimations(L"..\\Resources\\Texture\\Door\\Stage1\\Open_Door\\Upgrade_Door", this, 0, 0.05);


		at->CreateAnimations(L"..\\Resources\\Texture\\Door\\Stage1\\Close_Door\\Close_Basic_Door", this, 0, 0.05);
		at->CreateAnimations(L"..\\Resources\\Texture\\Door\\Stage1\\Close_Door\\Close_Boss_Door", this, 0, 0.05);
		at->CreateAnimations(L"..\\Resources\\Texture\\Door\\Stage1\\Close_Door\\Close_DarkMarcket", this, 0, 0.05);
		at->CreateAnimations(L"..\\Resources\\Texture\\Door\\Stage1\\Close_Door\\Close_GetSkull_Door", this, 0, 0.05);
		at->CreateAnimations(L"..\\Resources\\Texture\\Door\\Stage1\\Close_Door\\Close_GetTreasure_Door", this, 0, 0.05);
		at->CreateAnimations(L"..\\Resources\\Texture\\Door\\Stage1\\Close_Door\\Close_MiniBoss_Door", this, 0, 0.05);
		

		at->CreateAnimations(L"..\\Resources\\Texture\\Door\\Stage1\\Deactivate_Door\\First", this, 0, 0.05);
		at->CreateAnimations(L"..\\Resources\\Texture\\Door\\Stage1\\Deactivate_Door\\Second", this, 0, 0.05);
		

		at->PlayAnimation(L"Open_DoorBasic_Door", true);
		GameObject::Initialize();
	}
	void Stage1_Door::Update()
	{
		if (_Set_Door_Allow == true)
		{
			if (_Stage1_Door == 0)
			{
				at->PlayAnimation(L"Open_DoorBasic_Door", true);
				_State = Stage1Door_State::Open_Basic_Door;
			}
			if (_Stage1_Door == 1)
			{
				at->PlayAnimation(L"Open_DoorGetSkull_Door", true);
				_State = Stage1Door_State::Open_GetSkull_Door;
			}
			if (_Stage1_Door == 2)
			{
				at->PlayAnimation(L"Open_DoorMiniBoss_Door", true);
				_State = Stage1Door_State::Open_MiniBoss_Door;
			}
			if (_Stage1_Door == 3)
			{
				at->PlayAnimation(L"Open_DoorBoss_Door", true);
				_State = Stage1Door_State::Open_Boss_Door;
			}


			if (_Stage1_Door == 4)
			{
				at->PlayAnimation(L"Close_DoorClose_Basic_Door", true);
				_State = Stage1Door_State::Close_Basic_Door;
			}
			if (_Stage1_Door == 5)
			{
				at->PlayAnimation(L"Close_DoorClose_GetSkull_Door", true);
				_State = Stage1Door_State::Close_GetSkull_Door;
			}
			if (_Stage1_Door == 6)
			{
				at->PlayAnimation(L"Close_DoorClose_MiniBoss_Door", true);
				_State = Stage1Door_State::Close_MiniBoss_Door;

			}
			if (_Stage1_Door == 7)
			{
				at->PlayAnimation(L"Close_DoorClose_Boss_Door", true);
				_State = Stage1Door_State::Close_Boss_Door;
			}
			if (_Stage1_Door == 8)
			{
				at->PlayAnimation(L"Deactivate_DoorFirst", true);
				_State = Stage1Door_State::Deactivate_Door_First;
			}
			if (_Stage1_Door == 9)
			{
				at->PlayAnimation(L"Deactivate_DoorSecond", true);
				_State = Stage1Door_State::Deactivate_Door_Second;
			}
			_Set_Door_Allow = false;
		}



		switch (_State)
		{
		case jk::Stage1_Door::Stage1Door_State::Open_Basic_Door:
			basic_door();
			break;

		case jk::Stage1_Door::Stage1Door_State::Open_GetSkull_Door:
			get_skull_door();
			break;

		case jk::Stage1_Door::Stage1Door_State::Open_MiniBoss_Door:
			mini_boss_door();
			break;

		case jk::Stage1_Door::Stage1Door_State::Open_Boss_Door:
			boss_door();
			break;		


		case jk::Stage1_Door::Stage1Door_State::Close_Basic_Door:
			basic_door();
			break;

		case jk::Stage1_Door::Stage1Door_State::Close_GetSkull_Door:
			get_skull_door();
			break;

		case jk::Stage1_Door::Stage1Door_State::Close_MiniBoss_Door:
			mini_boss_door();
			break;

		case jk::Stage1_Door::Stage1Door_State::Close_Boss_Door:
			boss_door();
			break;



		case jk::Stage1_Door::Stage1Door_State::Deactivate_Door_First:
			basic_door();
			break;

		case jk::Stage1_Door::Stage1Door_State::Deactivate_Door_Second:
			basic_door();
			break;



		default:
			break;
		}
		GameObject::Update();
	}
	void Stage1_Door::LateUpdate()
	{
		_collider->SetSize(Vector2(0.35f, 0.65f));
		_collider->SetCenter(Vector2(5.f, -20.f));
		GameObject::LateUpdate();
	}
	void Stage1_Door::Render()
	{
		GameObject::Render();
	}
	void Stage1_Door::OnCollisionEnter(Collider2D* other)
	{
	}
	void Stage1_Door::OnCollisionStay(Collider2D* other)
	{
	}
	void Stage1_Door::OnCollisionExit(Collider2D* other)
	{
	}
	void Stage1_Door::basic_door()
	{
	}
	void Stage1_Door::get_skull_door()
	{
	}
	void Stage1_Door::mini_boss_door()
	{
	}
	void Stage1_Door::boss_door()
	{
	}
}