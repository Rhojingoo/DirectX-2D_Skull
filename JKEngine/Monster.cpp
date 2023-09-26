#include "Monster.h"

namespace jk
{
	GameObject* Monster::_player = nullptr;
	//Monster::MonsterList Monster::monster_select = MonsterList();
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