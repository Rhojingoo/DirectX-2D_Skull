#include "MiniBoss_Bullet_Archer.h"

namespace jk
{
	MiniBoss_Bullet_Archer::MiniBoss_Bullet_Archer()
	{
	}
	MiniBoss_Bullet_Archer::~MiniBoss_Bullet_Archer()
	{
	}
	void MiniBoss_Bullet_Archer::Initialize()
	{
		Bullet::Initialize();
	}
	void MiniBoss_Bullet_Archer::Update()
	{
		Bullet::Update();
	}
	void MiniBoss_Bullet_Archer::LateUpdate()
	{
		Bullet::LateUpdate();
	}
	void MiniBoss_Bullet_Archer::Render()
	{
		Bullet::Render();
	}
	void MiniBoss_Bullet_Archer::OnCollisionEnter(Collider2D* other)
	{
	}
	void MiniBoss_Bullet_Archer::OnCollisionStay(Collider2D* other)
	{
	}
	void MiniBoss_Bullet_Archer::OnCollisionExit(Collider2D* other)
	{
	}
}