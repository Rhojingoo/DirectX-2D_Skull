#include "AdventureUI.h"

namespace jk
{
	AdventureUI::AdventureUI()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	AdventureUI::~AdventureUI()
	{
	}
	void AdventureUI::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\EnergeBar\\AdventureUI\\ArcherUI", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\EnergeBar\\AdventureUI\\Archer_DeadUI", this);

		at->CreateAnimations(L"..\\Resources\\Texture\\EnergeBar\\AdventureUI\\ClericUI", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\EnergeBar\\AdventureUI\\Cleric_DeadUI", this);

		at->CreateAnimations(L"..\\Resources\\Texture\\EnergeBar\\AdventureUI\\HeroUI", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\EnergeBar\\AdventureUI\\Hero_DeadUI", this);

		at->CreateAnimations(L"..\\Resources\\Texture\\EnergeBar\\AdventureUI\\MageUI", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\EnergeBar\\AdventureUI\\Mage_DeadUI", this);

		at->PlayAnimation(L"AdventureUIArcherUI", true);

		GameObject::Initialize();
	}

	void AdventureUI::Update()
	{
		if (_animation == true)
		{
			if (_UISelect == 0)
			{
				at->PlayAnimation(L"AdventureUIArcherUI", true);
				_State = AdventureUI_State::ArcherUI;
			}
			if (_UISelect == 1)
			{
				at->PlayAnimation(L"AdventureUIArcher_DeadUI", true);
				_State = AdventureUI_State::Archer_DeadUI;
			}


			if (_UISelect == 2)
			{
				at->PlayAnimation(L"AdventureUIClericUI", true);
				_State = AdventureUI_State::ClericUI;
			}
			if (_UISelect == 3)
			{
				at->PlayAnimation(L"AdventureUICleric_DeadUI", true);
				_State = AdventureUI_State::Cleric_DeadUI;
			}


			if (_UISelect == 4)
			{
				at->PlayAnimation(L"AdventureUIHeroUI", true);
				_State = AdventureUI_State::HeroUI;
			}
			if (_UISelect == 5)
			{
				at->PlayAnimation(L"AdventureUIHero_DeadUI", true);
				_State = AdventureUI_State::Hero_DeadUI;
			}


			if (_UISelect == 6)
			{
				at->PlayAnimation(L"AdventureUIMageUI", true);
				_State = AdventureUI_State::MageUI;
			}
			if (_UISelect == 7)
			{
				at->PlayAnimation(L"AdventureUIMage_DeadUI", true);
				_State = AdventureUI_State::Mage_DeadUI;
			}


			_animation = false;
		}

		switch (_State)
		{
		case jk::AdventureUI::AdventureUI_State::ArcherUI:
			ArcherUI();
			break;

		case jk::AdventureUI::AdventureUI_State::Archer_DeadUI:
			Dead();
			break;

		case jk::AdventureUI::AdventureUI_State::ClericUI:
			ClericUI();
			break;

		case jk::AdventureUI::AdventureUI_State::Cleric_DeadUI:
			Dead();
			break;

		case jk::AdventureUI::AdventureUI_State::HeroUI:
			HeroUI();
			break;

		case jk::AdventureUI::AdventureUI_State::Hero_DeadUI:
			Dead();
			break;

		case jk::AdventureUI::AdventureUI_State::MageUI:
			MageUI();
			break;

		case jk::AdventureUI::AdventureUI_State::Mage_DeadUI:
			Dead();
			break;

		default:
			break;
		}

		GameObject::Update();
	}


	void AdventureUI::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}


	void AdventureUI::Render()
	{
		GameObject::Render();
	}


	void AdventureUI::ArcherUI()
	{
	}
	void AdventureUI::ClericUI()
	{
	}
	void AdventureUI::HeroUI()
	{
	}
	void AdventureUI::MageUI()
	{
	}
	void AdventureUI::Dead()
	{
	}
}