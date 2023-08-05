#include "Boss.h"

namespace jk
{
	Boss::Boss()
	{
	}
	Boss::~Boss()
	{
	}
	void Boss::Initialize()
	{
		GameObject::Initialize();
	}
	void Boss::Update()
	{
		GameObject::Update();
	}
	void Boss::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Boss::Render()
	{
		GameObject::Render();
	}
	void Boss::OnCollisionEnter(Collider2D* other)
	{
	}
	void Boss::OnCollisionStay(Collider2D* other)
	{
	}
	void Boss::OnCollisionExit(Collider2D* other)
	{
	}
}