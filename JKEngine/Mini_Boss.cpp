#include "Mini_Boss.h"
#include <iostream>
#include <random>

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
		_Gobjs[0] = new Cleric;
		_Gobjs[0]->Initialize();


		//_Gobjs[0] = new Knight_male;
		//_Gobjs[0]->Initialize();
		//_Gobjs[1] = new Archer;
		//_Gobjs[1]->Initialize();
		//_Gobjs[2] = new Mage;
		//_Gobjs[2]->Initialize();
		//_Gobjs[3] = new Cleric;
		//_Gobjs[3]->Initialize();

		//std::random_device rd;
		//std::mt19937 gen(rd());
		//std::uniform_int_distribution<int> distribution(0, 1);
		//_minibosschoice = distribution(gen);


		for (int i = 0; i < 1; i++)
		{
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::MiniBoss, _Gobjs[i]);
			Transform* tr = _Gobjs[i]->GetComponent<Transform>();
			tr->SetPosition(Vector3(200.f, 0.f, -250.f));

			//if (0 == i)
			//	_Gobjs[i]->SetState(eState::Paused);

			//if (_minibosschoice != i)
			//	_Gobjs[i]->SetState(eState::Paused);
		}
		GameObject::Initialize();
	}

	void Mini_Boss::Update()
	{
			_playerpos = Player::GetPlayer_Pos();

			//if (_mboss == MinibossList::knight)
			//{
			//	_Gobjs[(UINT)MinibossList::knight]->SetState(eState::Active);
			//	Transform* tr = _Gobjs[(UINT)MinibossList::knight]->GetComponent<Transform>();
			//	tr->SetPosition(_Pos); //Skul_Basic::SetDirection(mDir, true);
			//	//if (_mboss == MinibossList::knight)
			//	//	_Gobjs[(UINT)MinibossList::knight]->SetState(eState::Paused);
			//}

			//if (_mboss == MinibossList::archer)
			//{
			//	_Gobjs[(UINT)MinibossList::archer]->SetState(eState::Active);
			//	Transform* tr = _Gobjs[(UINT)MinibossList::archer]->GetComponent<Transform>();
			//	tr->SetPosition(_Pos);  //Skul_Wolf::SetDirection(mDir, true);

			//	if (_mboss == MinibossList::knight)
			//		_Gobjs[(UINT)MinibossList::knight]->SetState(eState::Paused);
			//}
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
