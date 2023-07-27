#include "Player.h"

namespace jk
{
	Player::Player()
	{
	}
	Player::~Player()
	{
	}
	void Player::Initialize()
	{
		GameObject::Initialize();
	}
	void Player::Update()
	{
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