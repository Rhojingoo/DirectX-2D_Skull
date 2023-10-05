#include "Layana_HpFrame.h"

namespace jk
{
	Layana_HpFrame::Layana_HpFrame()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Layana_HpFrame::~Layana_HpFrame()
	{
	}
	void Layana_HpFrame::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		tr = this->GetComponent<Transform>();

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\EnergeBar\\Boss_EnergeBar\\Layana\\FirtsPhase", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\EnergeBar\\Boss_EnergeBar\\Layana\\SecondPhase", this);

		at->PlayAnimation(L"LayanaFirtsPhase", true);
		GameObject::Initialize();
	}
	void Layana_HpFrame::Update()
	{
		if (_SetAnimation == true)
		{
			if (_SellectHp_bar == 0)
			{
				at->PlayAnimation(L"LayanaFirtsPhase", true);
				_State = Layana_HP_State::First_Phase;
			}
			if (_SellectHp_bar == 1)
			{
				at->PlayAnimation(L"LayanaSecondPhase", true);
				_State = Layana_HP_State::Second_Phase;
			}
			_SetAnimation = false;
		}

		switch (_State)
		{
		case jk::Layana_HpFrame::Layana_HP_State::First_Phase:
			First_Phase();
			break;

		case jk::Layana_HpFrame::Layana_HP_State::Second_Phase:
			Second_Phase();
			break;

		default:
			break;
		}
		GameObject::Update();
	}
	void Layana_HpFrame::LateUpdate()
	{
		_collider->SetSize(Vector2(0.0f, 0.0f));
		_collider->SetCenter(Vector2(0.0f, -0.01f));
		GameObject::LateUpdate();
	}
	void Layana_HpFrame::Render()
	{
		GameObject::Render();
	}
	void Layana_HpFrame::First_Phase()
	{
	}
	void Layana_HpFrame::Second_Phase()
	{
	}
}