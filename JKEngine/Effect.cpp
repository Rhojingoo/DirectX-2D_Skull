#include "Effect.h"


namespace jk
{
	Effect::Effect()
	{
	}
	Effect::~Effect()
	{
	}
	void Effect::Initialize()
	{
		GameObject::Initialize();
	}
	void Effect::Update()
	{
		GameObject::Update();
	}
	void Effect::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Effect::Render()
	{
		GameObject::Render();
	}
	void Effect::OnCollisionEnter(Collider2D* other)
	{
	}
	void Effect::OnCollisionStay(Collider2D* other)
	{
	}
	void Effect::OnCollisionExit(Collider2D* other)
	{
	}
}

