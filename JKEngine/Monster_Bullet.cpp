#include "Monster_Bullet.h"

namespace jk
{
	Monster_Bullet::Monster_Bullet()
	{
	}
	Monster_Bullet::~Monster_Bullet()
	{
	}
	void Monster_Bullet::Initialize()
	{
		Bullet::Initialize();
	}
	void Monster_Bullet::Update()
	{
		Bullet::Update();
	}
	void Monster_Bullet::LateUpdate()
	{
		Bullet::LateUpdate();
	}
	void Monster_Bullet::Render()
	{
		Bullet::Render();
	}
	void Monster_Bullet::OnCollisionEnter(Collider2D* other)
	{
	}
	void Monster_Bullet::OnCollisionStay(Collider2D* other)
	{
	}
	void Monster_Bullet::OnCollisionExit(Collider2D* other)
	{
	}
}