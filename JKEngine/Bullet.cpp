#include "Bullet.h"

namespace jk
{
	Bullet::Bullet()
	{
	}
	Bullet::~Bullet()
	{
	}
	void Bullet::Initialize()
	{
		GameObject::Initialize();
	}
	void Bullet::Update()
	{
		GameObject::Update();
	}
	void Bullet::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Bullet::Render()
	{
		GameObject::Render();
	}

	void Bullet::OnCollisionEnter(Collider2D* other)
	{
	}
	void Bullet::OnCollisionStay(Collider2D* other)
	{
	}
	void Bullet::OnCollisionExit(Collider2D* other)
	{
	}
}
