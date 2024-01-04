#include "Mini_Boss.h"
#include <iostream>
#include <random>
#include "Include_Common.h"

namespace jk
{
	GameObject* Mini_Boss::_player = nullptr;
	Mini_Boss::MinibossList Mini_Boss::miniboss_select = MinibossList();
	Vector3 Mini_Boss::_Pos = Vector3(0.f,0.f,0.f);
	Vector3 Mini_Boss::_playerpos = Vector3(0.f, 0.f, 0.f);

	Vector3 Mini_Boss::Left_Ground = Vector3(0.f, 0.f, 0.f);
	Vector3 Mini_Boss::Right_Ground = Vector3(0.f, 0.f, 0.f);


	Mini_Boss::Mini_Boss()
		:_mboss()
	{
	}
	Mini_Boss::~Mini_Boss()
	{
	}

	void Mini_Boss::Initialize()
	{
		GameObject::Initialize();
	}

	void Mini_Boss::Update()
	{
		_playerpos = Player::GetPlayer_Pos();

		GameObject::Update();
	}

	void Mini_Boss::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Mini_Boss::Render()
	{
		GameObject::Render();
	}

	void Mini_Boss::OnCollisionEnter(Collider2D* other)
	{
	}
	void Mini_Boss::OnCollisionStay(Collider2D* other)
	{
	}
	void Mini_Boss::OnCollisionExit(Collider2D* other)
	{
	}


	int Mini_Boss::random(int a, int b)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> distribution(a, b);
		int answer_random = distribution(gen);
		return answer_random;
	}
}
