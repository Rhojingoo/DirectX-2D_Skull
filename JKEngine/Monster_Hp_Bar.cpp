#include "Monster_Hp_Bar.h"

namespace jk
{
	Monster_Hp_Bar::Monster_Hp_Bar(const std::wstring& path)
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(path));
	}
	Monster_Hp_Bar::~Monster_Hp_Bar()
	{
	}
	void Monster_Hp_Bar::Initialize()
	{
		GameObject::Initialize();
	}
	void Monster_Hp_Bar::Update()
	{
		if (_HitOn == true)
		{
			if (_Type == 1)
			{
				if (_target_point < _CurrentHp)				
					_CurrentHp -= 50*Time::DeltaTime();
				else
				{
					_CurrentHp = _target_point;
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
	void Monster_Hp_Bar::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Monster_Hp_Bar::Render()
	{
		BindConstantBuffer();
		GameObject::Render();
	}
	void Monster_Hp_Bar::BindConstantBuffer()
	{
		renderer::HP_BarCB trCB = {};		
		trCB._Damage.x = _MaxHp;
		trCB._Damage.y = _CurrentHp;

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::HP_Bar];
		cb->SetData(&trCB);
		cb->Bind(eShaderStage::PS);
	}
}