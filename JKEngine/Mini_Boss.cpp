#include "Mini_Boss.h"


namespace jk
{
	GameObject* Mini_Boss::_player = nullptr;
	Vector3 Mini_Boss::_Pos = Vector3(0.f,0.f,0.f);
	Vector3 Mini_Boss::_playerpos = Vector3(0.f, 0.f, 0.f);

	Mini_Boss::Mini_Boss()
		:_mboss()
	{
	}
	Mini_Boss::~Mini_Boss()
	{
	}

	void Mini_Boss::Initialize()
	{
		_Gobjs[0] = new Knight_male;
		_Gobjs[0]->Initialize();
		//_Gobjs[1] = new Skul_Wolf;
		//_Gobjs[1]->Initialize();
		//_Gobjs[2] = new Skul_Spear;
		//_Gobjs[2]->Initialize();

		for (int i = 0; i < 1; i++)
		{
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::MiniBoss, _Gobjs[i]);
			Transform* tr = _Gobjs[i]->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.f, 0.f, -250.f));

			//if ((UINT)player_select != i)
			//	_Gobjs[i]->SetState(eState::Paused);
		}
		GameObject::Initialize();
	}

	void Mini_Boss::Update()
	{
			_playerpos;  // 플레이어 포스 확인용

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
}
