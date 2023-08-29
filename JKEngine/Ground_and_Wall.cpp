#include "Ground_and_Wall.h"

namespace jk
{
	Ground_and_Wall::Ground_and_Wall()
	{
		_collider = AddComponent<Collider2D>();
	}
	Ground_and_Wall::~Ground_and_Wall()
	{
	}
	void Ground_and_Wall::Initialize()
	{
		GameObject::Initialize();
	}
	void Ground_and_Wall::Update()
	{
		GameObject::Update();
	}
	void Ground_and_Wall::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Ground_and_Wall::Render()
	{
		GameObject::Render();
	}
	void Ground_and_Wall::OnCollisionEnter(Collider2D* other)
	{
	}
	void Ground_and_Wall::OnCollisionStay(Collider2D* other)
	{
	}
	void Ground_and_Wall::OnCollisionExit(Collider2D* other)
	{
	}
}