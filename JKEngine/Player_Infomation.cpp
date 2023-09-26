#include "Player_Infomation.h"

namespace jk
{
	Player_Infomation::PlayerList Player_Infomation::Current_player = PlayerList::basic_Skul;
	float Player_Infomation::Current_player_HP = 0.f;

	Player_Infomation::Player_Infomation()
	{
	}

	Player_Infomation::~Player_Infomation()
	{
	}

	void Player_Infomation::Initialize()
	{
		GameObject::Initialize();
	}

	void Player_Infomation::Update()
	{
		GameObject::Update();
	}

	void Player_Infomation::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Player_Infomation::Render()
	{
	}

	void Player_Infomation::OnCollisionEnter(Collider2D* other)
	{
	}

	void Player_Infomation::OnCollisionStay(Collider2D* other)
	{
	}

	void Player_Infomation::OnCollisionExit(Collider2D* other)
	{
	}

}