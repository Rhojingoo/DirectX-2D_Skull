#include "Player.h"
#include "Include_Common.h"
#include "Face_UI.h"
#include "Player_Hp_Bar.h"

namespace jk
{
	Player:: PlayerList Player::player_select = PlayerList::basic_Skul;
	Player::PlayerList Player::player_check = PlayerList::basic_Skul;

	float Player::_Max_Player_Hp = 200.f;
	float Player::_Curren_Player_Hp = 200.f;

	
	Vector3 Player::_Pos = Vector3(0.f, 0.f, 0.f);
	Vector3 Player::_Player_GRpos = Vector3(0.f, 0.f, 0.f);
	bool Player:: _check_change = 0;
	bool Player::_skulhead_check = false;
	bool Player::_Ground_On = false;
	bool Player::firstGroundcheck = false;
	
	bool Player::_skul_act = false;
	bool Player::_wolf_act = false;
	bool Player::_spear_act = false;

	int Player:: mDir = 1;

	Player::Player() 	
	{
	}
	Player::~Player()
	{
	}
	void Player::Initialize()
	{
		PlayerTR = GetComponent<Transform>();
		_Pos = PlayerTR->GetPosition();

		Player_State_UI* Player_State = object::Instantiate<Player_State_UI>(Vector3(-620.f, -300.f, 1.f), eLayerType::UI);
		Player_State->GetComponent<Transform>()->SetScale(Vector3(168.f * 2, 66.f * 2, 0.f));
		Player_State->SetName(L"playyer_state_inventory");

		Basic_Face = object::Instantiate<Face_UI>(Vector3(-730.f, -280.f, -2.1f), eLayerType::UI, L"Skul_UI");
		Basic_Face->GetComponent<Transform>()->SetScale(Vector3(68.f * 1.5, 68.f * 1.5, 0.f));
		Basic_Face->SetName(L"player_head");

		Wolf_Face = object::Instantiate<Face_UI>(Vector3(-730.f, -280.f, -2.1f), eLayerType::UI, L"Wolf_UI");
		Wolf_Face->GetComponent<Transform>()->SetScale(Vector3(68.f * 1.5, 68.f * 1.5, 0.f));
		Wolf_Face->SetName(L"player_head");
		Wolf_Face->SetState(eState::Paused);

		Spear_Face = object::Instantiate<Face_UI>(Vector3(-730.f, -280.f, -2.1f), eLayerType::UI, L"Spear_UI");
		Spear_Face->GetComponent<Transform>()->SetScale(Vector3(68.f * 1.5, 68.f * 1.5, 0.f));
		Spear_Face->SetName(L"player_head");
		Spear_Face->SetState(eState::Paused);

			Scene* scene = SceneManager::GetInitializeScene();
		//hp����
		{
			Player_Hp = new Player_Hp_Bar(L"HealthUar_Ui");
			scene->AddGameObject(eLayerType::UI, Player_Hp);
			Transform* hp_tr = Player_Hp->GetComponent<Transform>();
			hp_tr->SetPosition(Vector3(-584.5f, -333.f, -3));
			hp_tr->SetScale(235, 20, 0);
			Player_Hp->Set_Max_Hp(_Max_Player_Hp);
			Player_Hp->Set_Current_Hp(_Curren_Player_Hp);
			Player_Hp->SetState(eState::Active);
		}
		{
			Player_Hp_Damage = new Player_Hp_Bar(L"DamageBar_Ui");
			scene->AddGameObject(eLayerType::UI, Player_Hp_Damage);
			Transform* hp_tr = Player_Hp_Damage->GetComponent<Transform>();
			hp_tr->SetPosition(Vector3(-584.5f, -333.f, -2));
			hp_tr->SetScale(235, 20, 0);
			Player_Hp_Damage->Set_Max_Hp(_Max_Player_Hp);
			Player_Hp_Damage->Set_Current_Hp(_Curren_Player_Hp);
			Player_Hp_Damage->Set_Type(1);
			Player_Hp_Damage->SetState(eState::Active);
		}


		_Gobjs[0] = new Skul_Basic;
		_Gobjs[0]->Initialize();
		_Gobjs[1] = new Skul_Wolf;
		_Gobjs[1]->Initialize();
		_Gobjs[2] = new Skul_Spear;
		_Gobjs[2]->Initialize();


		for (int i = 0; i < 3; i++)
		{
			scene->AddGameObject(eLayerType::Player, _Gobjs[i]);
			Transform* tr = _Gobjs[i]->GetComponent<Transform>();
			tr->SetPosition(Vector3(_Pos.x, _Pos.y, _Pos.z));

			if ((UINT)player_select != i)
			_Gobjs[i]->SetState(eState::Paused);
		}
		GameObject::Initialize();
	}
	void Player::Update()
	{
		player_select;
		_Pos;		

		Monster::SetPlayerPos(_Pos);

		if (Input::GetKeyDown(eKeyCode::K))
		{
			_Curren_Player_Hp = _Curren_Player_Hp - 50;
			Player_Hp->_HitOn = true;
			Player_Hp->SetHitDamage(50);
			Player_Hp_Damage->_HitOn = true;
			Player_Hp_Damage->Set_Target(_Curren_Player_Hp);
		}




		if (_check_change == true)
		{
			if (player_select == PlayerList::basic_Skul)
			{
				_skul_act = true; 	_wolf_act = false; 	_spear_act = false;
				_Gobjs[(UINT)PlayerList::basic_Skul]->SetState(eState::Active);
				Transform* tr = _Gobjs[(UINT)PlayerList::basic_Skul]->GetComponent<Transform>();
				if(_Switch ==false)
					tr->SetPosition(_Pos), Skul_Basic::SetDirection(mDir, true);
				else
					tr->SetPosition(_Pos), Skul_Basic::SetDirection(mDir, false);
			
				Basic_Face->SetState(eState::Active);
				Spear_Face->SetState(eState::Paused);
				Wolf_Face->SetState(eState::Paused);
				_Gobjs[(UINT)PlayerList::wolf_Skul]->SetState(eState::Paused);
				_Gobjs[(UINT)PlayerList::spere_Skul]->SetState(eState::Paused);

				_Switch = false;
			}

			if (player_select == PlayerList::wolf_Skul)
			{
				_skul_act = false; 	_wolf_act = true; 	_spear_act = false;
				_Gobjs[(UINT)PlayerList::wolf_Skul]->SetState(eState::Active);
				Transform* tr = _Gobjs[(UINT)PlayerList::wolf_Skul]->GetComponent<Transform>();
				if (_Switch == false)
					tr->SetPosition(_Pos), Skul_Wolf::SetDirection(mDir, true);
				else
					tr->SetPosition(_Pos), Skul_Wolf::SetDirection(mDir, false);
			
				Wolf_Face->SetState(eState::Active);
				Spear_Face->SetState(eState::Paused);
				Basic_Face->SetState(eState::Paused);
				_Gobjs[(UINT)PlayerList::basic_Skul]->SetState(eState::Paused);
				_Gobjs[(UINT)PlayerList::spere_Skul]->SetState(eState::Paused);

				_Switch = false;
			}

			if (player_select == PlayerList::spere_Skul)
			{
				_skul_act = false; 	_wolf_act = false; 	_spear_act = true;
				_Gobjs[(UINT)PlayerList::spere_Skul]->SetState(eState::Active);
				Transform* tr = _Gobjs[(UINT)PlayerList::spere_Skul]->GetComponent<Transform>();
				if (_Switch == false)
					tr->SetPosition(_Pos), Skul_Spear::SetDirection(mDir, true);
				else				
					tr->SetPosition(_Pos), Skul_Spear::SetDirection(mDir, false);
							
				Spear_Face->SetState(eState::Active);
				Wolf_Face->SetState(eState::Paused);
				Basic_Face->SetState(eState::Paused);
				_Gobjs[(UINT)PlayerList::wolf_Skul]->SetState(eState::Paused);
				_Gobjs[(UINT)PlayerList::basic_Skul]->SetState(eState::Paused);

				_Switch = false;
			}		

			_check_change = false;
		}
		
		PlayerTR->SetPosition(_Pos);
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