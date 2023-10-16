#include "HitBox_Player.h"
#include <iostream>
#include <random>


namespace jk
{
	HitBox_Player::HitBox_Player()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"DebugRect"));
		mr->SetMaterial(Resources::Find<Material>(L"DebugMaterial"));
	}
	HitBox_Player::~HitBox_Player()
	{
	}
	void HitBox_Player::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_collider->SetSize(Vector2(150.f, 150.f));
		_collider->SetPosition(Vector3(0.f, 0.f, -250.f));
		
		
		as = AddComponent<AudioSource>();
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\Common_Hit\\Hit_Blunt_Small.wav", "Hit_Blunt_Small");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\Common_Hit\\Hit_Sword_Small.wav", "Hit_Sword_Small");

		GameObject::Initialize();
	}
	void HitBox_Player::Update()
	{
		if (Player::GetCurrentPlay_List() == Player::PlayerList::basic_Skul)
		{
			_HitType = random(1, 10);
			if (_HitType >= 1 && _HitType < 6)
			{
				_Damage = random(10, 15);
				attack = true;
			}

			if (_HitType >= 6 && _HitType < 9)
			{
				_Damage = random(22, 28);
				attack_Cri_Mid = true;
			}

			if (_HitType >= 9 && _HitType <= 10)
			{
				_Damage = random(30, 45);
				attack_Cri_High = true;
			}
		}
		if (Player::GetCurrentPlay_List() == Player::PlayerList::wolf_Skul)
		{
			_HitType = random(1, 10);
			if (_HitType >= 1 && _HitType < 6)
			{
				_Damage = random(30, 35);
				attack = true;
			}

			if (_HitType >= 6 && _HitType < 9)
			{
				_Damage = random(40, 55);
				attack_Cri_Mid = true;
			}

			if (_HitType >= 9 && _HitType <= 10)
			{
				_Damage = random(55, 79);
				attack_Cri_High = true;
			}
		}


		GameObject::Update();
	}
	void HitBox_Player::LateUpdate()
	{
		_Center.y = -15;
		_collider->SetSize(_Size);
		_collider->SetPosition(_Center);
		GameObject::LateUpdate();
	}
	void HitBox_Player::Render()
	{
		GameObject::Render();
	}
	void HitBox_Player::OnCollisionEnter(Collider2D* other)
	{
		if (Monster* mon = dynamic_cast<Monster*>(other->GetOwner()))
		{
			if (Player::GetCurrentPlay_List() == Player::PlayerList::basic_Skul)
			{
				as->Play("Hit_Blunt_Small");
			}
			if (Player::GetCurrentPlay_List() == Player::PlayerList::wolf_Skul)
			{
				as->Play("Hit_Sword_Small");
			}
		}

		if (Mini_Boss* mon = dynamic_cast<Mini_Boss*>(other->GetOwner()))
		{
			if (Player::GetCurrentPlay_List() == Player::PlayerList::basic_Skul)
			{
				as->Play("Hit_Blunt_Small");
			}
			if (Player::GetCurrentPlay_List() == Player::PlayerList::wolf_Skul)
			{
				as->Play("Hit_Sword_Small");
			}
		}
	}
	void HitBox_Player::OnCollisionStay(Collider2D* other)
	{
	}
	void HitBox_Player::OnCollisionExit(Collider2D* other)
	{
	}
	int HitBox_Player::random(int a, int b)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> distribution(a, b);
		int abc = distribution(gen);
		return abc;
	}
}