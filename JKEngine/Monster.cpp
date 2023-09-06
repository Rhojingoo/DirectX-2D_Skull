#include "Monster.h"

namespace jk
{
	GameObject* Monster::_player = nullptr;
	Monster::MonsterList Monster::monster_select = MonsterList();
	Vector3 Monster::_Pos = Vector3(0.f, 0.f, 0.f);
	Vector3 Monster::_playerpos = Vector3(0.f, 0.f, 0.f);
	Vector3 Monster::_playerGRpos = Vector3(0.f, 0.f, 0.f);	
	bool Monster::_player_groundcheck = false;

	Monster::Monster()
	{
	}
	Monster::~Monster()
	{
	}
	void Monster::Initialize()
	{
		_Gobjs[0] = new Stone_wizard;
		_Gobjs[0]->Initialize();

		//_Gobjs[0] = new Monster_warrior;
		//_Gobjs[0]->Initialize();
		//_Gobjs[1] = new Monster_Hammer;
		//_Gobjs[1]->Initialize();
		//_Gobjs[2] = new Stone_wizard;
		//_Gobjs[2]->Initialize();
		//_Gobjs[3] = new Monster_BigEnt;
		//_Gobjs[3]->Initialize();
		//_Gobjs[4] = new Monster_GreenTree;
		//_Gobjs[4]->Initialize();
		//_Gobjs[5] = new Monster_BlossomEnt;
		//_Gobjs[5]->Initialize();
		//_Gobjs[6] = new Monster_Goldwarrior;
		//_Gobjs[6]->Initialize();
		//_Gobjs[7] = new Monster_GoldHammer;
		//_Gobjs[7]->Initialize();


		for (int i = 0; i < 1; i++)
		{
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Monster, _Gobjs[i]);
			Transform* tr = _Gobjs[i]->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.f, 0.f, -250.f));
		}

		GameObject::Initialize();
	}
	void Monster::Update()
	{
		_playerpos = Player::GetPlayer_Pos();
		_player_groundcheck = Player::Get_Ground_On();
		_playerGRpos = Player::GetPlayer_GRPos();

		GameObject::Update();
	}
	void Monster::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Monster::Render()
	{
		GameObject::Render();
	}
	void Monster::OnCollisionEnter(Collider2D* other)
	{
	}
	void Monster::OnCollisionStay(Collider2D* other)
	{
	}
	void Monster::OnCollisionExit(Collider2D* other)
	{
	}

}