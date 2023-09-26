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
		GameObject::Initialize();
	}
	void HitBox_Player::Update()
	{
		if (Player::GetCurrentPlay_List() == Player::PlayerList::basic_Skul)
		{
			_HitType = random(1, 10);
			if (_HitType >= 1 && _HitType < 6)
				_Damage = random(10, 15);

			if (_HitType >= 6 && _HitType < 9)
				_Damage = random(22, 28);

			if (_HitType >= 9 && _HitType <= 10)
				_Damage = random(30, 45);
		}


		GameObject::Update();
	}
	void HitBox_Player::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void HitBox_Player::Render()
	{
		GameObject::Render();
	}
	void HitBox_Player::OnCollisionEnter(Collider2D* other)
	{
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