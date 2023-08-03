#include "Monster.h"

namespace jk
{
	GameObject* Monster::_player = nullptr;
	Monster::MonsterList Monster::monster_select = MonsterList();
	Vector3 Monster::_Pos = Vector3(0.f, 0.f, 0.f);
	Vector3 Monster::_playerpos = Vector3(0.f, 0.f, 0.f);

	Monster::Monster()
	{
	}
	Monster::~Monster()
	{
	}
	void Monster::Initialize()
	{
		_Gobjs[0] = new Monster_warrior;
		_Gobjs[0]->Initialize();
		//_Gobjs[1] = new Ice_wizard;
		//_Gobjs[1]->Initialize();
		//_Gobjs[2] = new Monster_Hammer;
		//_Gobjs[2]->Initialize();


		for (int i = 0; i < 1; i++)
		{
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::MiniBoss, _Gobjs[i]);
			Transform* tr = _Gobjs[i]->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.f, 0.f, -250.f));

			//if (0 == i)
			//	_Gobjs[i]->SetState(eState::Paused);
		}

		GameObject::Initialize();
	}
	void Monster::Update()
	{
		_playerpos;

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