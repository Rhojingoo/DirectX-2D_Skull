#include "Player.h"

namespace jk
{
	Player:: PlayerList Player::player_select = PlayerList::basic_Skul;
	Player:: PlayerList Player::player_check = PlayerList::basic_Skul;
	Vector3 Player::_Pos = Vector3(0.f, 0.f, 0.f);
	bool Player:: _check_change = 0;
	bool Player::_skulhead_check = false;
	int Player:: mDir = 1;

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
		_Gobjs[3] = new Skul_Sword;
		_Gobjs[3]->Initialize();
		_Gobjs[4] = new Skul_Thief;
		_Gobjs[4]->Initialize();
		//CameraScript* cam = AddComponent<CameraScript>();
		//cam->SetTarget(this);

		for (int i = 0; i < 5; i++)
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

		//Yggdrasil::SetPlayerPos(_Pos);
		//Mini_Boss::SetPlayerPos(_Pos);
		Monster::SetPlayerPos(_Pos);

		if (_check_change == true)
		{
			if (player_select == PlayerList::basic_Skul)
			{
				_Gobjs[(UINT)PlayerList::basic_Skul]->SetState(eState::Active);
				Transform* tr = _Gobjs[(UINT)PlayerList::basic_Skul]->GetComponent<Transform>();
				tr->SetPosition(_Pos); Skul_Basic::SetDirection(mDir, true);

				if (player_check == PlayerList::wolf_Skul)
					_Gobjs[(UINT)PlayerList::wolf_Skul]->SetState(eState::Paused);
				else if (player_check == PlayerList::spere_Skul)
					_Gobjs[(UINT)PlayerList::spere_Skul]->SetState(eState::Paused);
				else if (player_check == PlayerList::sowrd_Skul)
					_Gobjs[(UINT)PlayerList::spere_Skul]->SetState(eState::Paused);
				else if (player_check == PlayerList::thief_Skul)
					_Gobjs[(UINT)PlayerList::thief_Skul]->SetState(eState::Paused);
			}

			if (player_select == PlayerList::wolf_Skul)
			{
				_Gobjs[(UINT)PlayerList::wolf_Skul]->SetState(eState::Active);
				Transform* tr = _Gobjs[(UINT)PlayerList::wolf_Skul]->GetComponent<Transform>();
				tr->SetPosition(_Pos);  Skul_Wolf::SetDirection(mDir, true);

				if (player_check == PlayerList::basic_Skul)
					_Gobjs[(UINT)PlayerList::basic_Skul]->SetState(eState::Paused);
				else if (player_check == PlayerList::spere_Skul)
					_Gobjs[(UINT)PlayerList::spere_Skul]->SetState(eState::Paused);
				else if (player_check == PlayerList::sowrd_Skul)
					_Gobjs[(UINT)PlayerList::spere_Skul]->SetState(eState::Paused);
				else if (player_check == PlayerList::thief_Skul)
					_Gobjs[(UINT)PlayerList::thief_Skul]->SetState(eState::Paused);
			}

			if (player_select == PlayerList::spere_Skul)
			{
				_Gobjs[(UINT)PlayerList::spere_Skul]->SetState(eState::Active);
				Transform* tr = _Gobjs[(UINT)PlayerList::spere_Skul]->GetComponent<Transform>();
				tr->SetPosition(_Pos);  Skul_Spear::SetDirection(mDir, true);

				if (player_check == PlayerList::wolf_Skul)
					_Gobjs[(UINT)PlayerList::wolf_Skul]->SetState(eState::Paused);
				else if (player_check == PlayerList::basic_Skul)
					_Gobjs[(UINT)PlayerList::basic_Skul]->SetState(eState::Paused);
				else if (player_check == PlayerList::sowrd_Skul)
					_Gobjs[(UINT)PlayerList::spere_Skul]->SetState(eState::Paused);
				else if (player_check == PlayerList::thief_Skul)
					_Gobjs[(UINT)PlayerList::thief_Skul]->SetState(eState::Paused);
			}

			if (player_select == PlayerList::sowrd_Skul)
			{
				_Gobjs[(UINT)PlayerList::sowrd_Skul]->SetState(eState::Active);
				Transform* tr = _Gobjs[(UINT)PlayerList::sowrd_Skul]->GetComponent<Transform>();
				tr->SetPosition(_Pos);  Skul_Sword::SetDirection(mDir, true);

				if (player_check == PlayerList::wolf_Skul)
					_Gobjs[(UINT)PlayerList::wolf_Skul]->SetState(eState::Paused);
				else if (player_check == PlayerList::basic_Skul)
					_Gobjs[(UINT)PlayerList::basic_Skul]->SetState(eState::Paused);
				else if (player_check == PlayerList::spere_Skul)
					_Gobjs[(UINT)PlayerList::spere_Skul]->SetState(eState::Paused);
				else if (player_check == PlayerList::thief_Skul)
					_Gobjs[(UINT)PlayerList::thief_Skul]->SetState(eState::Paused);
			}

			if (player_select == PlayerList::thief_Skul)
			{
				_Gobjs[(UINT)PlayerList::thief_Skul]->SetState(eState::Active);
				Transform* tr = _Gobjs[(UINT)PlayerList::thief_Skul]->GetComponent<Transform>();
				tr->SetPosition(_Pos);  Skul_Thief::SetDirection(mDir, true);

				if (player_check == PlayerList::wolf_Skul)
					_Gobjs[(UINT)PlayerList::wolf_Skul]->SetState(eState::Paused);
				else if (player_check == PlayerList::basic_Skul)
					_Gobjs[(UINT)PlayerList::basic_Skul]->SetState(eState::Paused);
				else if (player_check == PlayerList::spere_Skul)
					_Gobjs[(UINT)PlayerList::spere_Skul]->SetState(eState::Paused);
				else if (player_check == PlayerList::sowrd_Skul)
					_Gobjs[(UINT)PlayerList::sowrd_Skul]->SetState(eState::Paused);
			}

			_check_change = false;
		}

		//if (_skulhead_check == false)
		//{
		//	_Gobjs[(UINT)PlayerList::head]->SetState(eState::Paused);
		//	Skul_head::Setattack(false);
		//}
		//else
		//{
		//	_Gobjs[(UINT)PlayerList::head]->SetState(eState::Active);
		//	Skul_head::Setattack(true);  Skul_head::SetDirection(Skul_Basic::GetDirection());
		//	Transform* tr = _Gobjs[(UINT)PlayerList::head]->GetComponent<Transform>();
		//	tr->SetPosition(_Pos.x+100, _Pos.y, _Pos.z);
		//}
		
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