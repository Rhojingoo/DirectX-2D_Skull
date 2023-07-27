#include "Player.h"

namespace jk
{
	Player:: PlayerList Player::player_select = PlayerList::basic_Skul;
	Player:: PlayerList Player::player_check = PlayerList::basic_Skul;
	Vector3 Player::_Pos = Vector3(0.f, 0.f, 0.f);
	bool Player:: _check_change = 0;

	Player::Player() 	
	{
	}
	Player::~Player()
	{
	}
	void Player::Initialize()
	{
		_Gobjs[0] = new Skul_Basic;
		_Gobjs[0]->Initialize();
		_Gobjs[1] = new Skul_Wolf;
		_Gobjs[1]->Initialize();
		_Gobjs[2] = new Skul_Spear;
		_Gobjs[2]->Initialize();

		for (int i = 0; i < 3; i++)
		{
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Player, _Gobjs[i]);
			Transform* tr = _Gobjs[i]->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.f, 0.f, -250.f));

			if ((UINT)player_select != i)
			_Gobjs[i]->SetState(eState::Paused);
		}
		GameObject::Initialize();
	}
	void Player::Update()
	{

		player_select;
		player_check;
		_Pos;
		int a;

		if (_check_change == true)
		{
			if (player_select == PlayerList::basic_Skul)
			{
				_Gobjs[(UINT)PlayerList::basic_Skul]->SetState(eState::Active);
				Transform* tr = _Gobjs[(UINT)PlayerList::basic_Skul]->GetComponent<Transform>();
				tr->SetPosition(_Pos);


				if (player_check == PlayerList::wolf_Skul)
					_Gobjs[(UINT)PlayerList::wolf_Skul]->SetState(eState::Paused);
				else if (player_check == PlayerList::spere_Skul)
					_Gobjs[(UINT)PlayerList::spere_Skul]->SetState(eState::Paused);

			}
			if (player_select == PlayerList::wolf_Skul)
			{
				_Gobjs[(UINT)PlayerList::wolf_Skul]->SetState(eState::Active);
				Transform* tr = _Gobjs[(UINT)PlayerList::wolf_Skul]->GetComponent<Transform>();
				tr->SetPosition(_Pos);

				if (player_check == PlayerList::basic_Skul)
					_Gobjs[(UINT)PlayerList::basic_Skul]->SetState(eState::Paused);
				else if (player_check == PlayerList::spere_Skul)
					_Gobjs[(UINT)PlayerList::spere_Skul]->SetState(eState::Paused);
			}
			if (player_select == PlayerList::spere_Skul)
			{
				_Gobjs[(UINT)PlayerList::spere_Skul]->SetState(eState::Active);
				Transform* tr = _Gobjs[(UINT)PlayerList::spere_Skul]->GetComponent<Transform>();
				tr->SetPosition(_Pos);

				if (player_check == PlayerList::wolf_Skul)
					_Gobjs[(UINT)PlayerList::wolf_Skul]->SetState(eState::Paused);
				else if (player_check == PlayerList::basic_Skul)
					_Gobjs[(UINT)PlayerList::basic_Skul]->SetState(eState::Paused);
			}
			_check_change = false;
		}
		
		GameObject::Update();
	}
	void Player::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Player::Render()
	{
		GameObject::Render();
	}

	void Player::OnCollisionEnter(Collider2D* other)
	{
	}
	void Player::OnCollisionStay(Collider2D* other)
	{
	}
	void Player::OnCollisionExit(Collider2D* other)
	{
	}

}