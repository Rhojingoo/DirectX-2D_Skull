#include "Player_Hp_Bar.h"

namespace jk
{
	Player_Hp_Bar::Player_Hp_Bar()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"HealthUar_Ui"));
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
			_CurrentHp = _MaxHp - _Hit_Damage;
			_HitOn = false;
		}
		GameObject::Update();
	}
	void Player_Hp_Bar::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Player_Hp_Bar::Render()
	{
		//BindConstantBuffer();
		GameObject::Render();
	}
	void Player_Hp_Bar::BindConstantBuffer()
	{
		renderer::HP_BarCB trCB = {};
		//trCB._Damage.x = _CurrentHp /_MaxHp;
		trCB._Damage.x = _MaxHp;
		trCB._Damage.y = _CurrentHp;

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::HP_Bar];
		cb->SetData(&trCB);
		cb->Bind(eShaderStage::VS);
	}
}