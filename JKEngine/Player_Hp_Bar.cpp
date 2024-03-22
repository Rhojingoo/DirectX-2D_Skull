#include "Player_Hp_Bar.h"
#include "Include_Common.h"


namespace jk
{
	float Player_Hp_Bar::_MaxHp = 200.f;
	float Player_Hp_Bar::_CurrentHp = _MaxHp;
	float Player_Hp_Bar::_DamageHp = _MaxHp;

	Player_Hp_Bar::Player_Hp_Bar(const std::wstring& path)
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(path));
	}
	Player_Hp_Bar::~Player_Hp_Bar()
	{
	}
	void Player_Hp_Bar::Initialize()
	{		
		GameObject::Initialize();
	}
	void Player_Hp_Bar::Update()
	{
		if (_HitOn == true)
		{
			if (_Type == 1)
			{
				if (_target_point < _DamageHp)
					_DamageHp -= 10.f * static_cast<float>(Time::DeltaTime());
				else
				{
					_DamageHp = _target_point;
					_HitOn = false;
					_DageSwitch = true;
				}
			}
			else
			{
				_CurrentHp = _CurrentHp - _Hit_Damage;
				_HitOn = false;
			}
		}
		GameObject::Update();
	}
	void Player_Hp_Bar::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Player_Hp_Bar::Render()
	{
		BindConstantBuffer();
		GameObject::Render();
	}
	void Player_Hp_Bar::BindConstantBuffer()
	{
		renderer::HP_BarCB trCB = {};
		if (_Type == 1)
		{
			trCB._Damage.x = _MaxHp;
			trCB._Damage.y = _DamageHp;
		}
		else
		{
			trCB._Damage.x = _MaxHp;
			trCB._Damage.y = _CurrentHp;
		}


		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::HP_Bar];
		cb->SetData(&trCB);
		cb->Bind(eShaderStage::PS);
	}
}