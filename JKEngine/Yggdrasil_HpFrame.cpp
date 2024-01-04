#include "Yggdrasil_HpFrame.h"
#include "Include_Common.h"

namespace jk
{
	Yggdrasil_HpFrame::Yggdrasil_HpFrame()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Yggdrasil_HpFrame::~Yggdrasil_HpFrame()
	{
	}
	void Yggdrasil_HpFrame::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		tr = this->GetComponent<Transform>();

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\EnergeBar\\Boss_EnergeBar\\Yggdrasil\\FirtsPhase", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\EnergeBar\\Boss_EnergeBar\\Yggdrasil\\SecondPhase", this);

		at->PlayAnimation(L"YggdrasilFirtsPhase", true);
		GameObject::Initialize();
	}
	void Yggdrasil_HpFrame::Update()
	{
		if (_SetAnimation == true)
		{
			if (_SellectHp_bar == 0)
			{
				at->PlayAnimation(L"YggdrasilFirtsPhase", true);
				_State = Yggdrasil_HP_State::First_Phase;
			}
			if (_SellectHp_bar == 1)
			{
				at->PlayAnimation(L"YggdrasilSecondPhase", true);
				_State = Yggdrasil_HP_State::Second_Phase;
			}
			_SetAnimation = false;
		}

		switch (_State)
		{
		case jk::Yggdrasil_HpFrame::Yggdrasil_HP_State::First_Phase:
			First_Phase();
			break;

		case jk::Yggdrasil_HpFrame::Yggdrasil_HP_State::Second_Phase:
			Second_Phase();
			break;

		default:
			break;
		}
		GameObject::Update();
	}
	void Yggdrasil_HpFrame::LateUpdate()
	{
		_collider->SetSize(Vector2(0.0f, 0.0f));
		_collider->SetCenter(Vector2(0.0f, -0.01f));
		GameObject::LateUpdate();
	}
	void Yggdrasil_HpFrame::Render()
	{
		GameObject::Render();
	}
	void Yggdrasil_HpFrame::First_Phase()
	{
	}
	void Yggdrasil_HpFrame::Second_Phase()
	{
	}
}