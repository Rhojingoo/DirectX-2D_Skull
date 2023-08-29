#include "Ground_Map.h"


namespace jk
{
	Ground_Map::Ground_Map()
	{
		_collider = AddComponent<Collider2D>();
	}
	Ground_Map::~Ground_Map()
	{
	}
	void Ground_Map::Initialize()
	{
		GameObject::Initialize();
	}
	void Ground_Map::Update()
	{
		GameObject::Update();
	}
	void Ground_Map::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Ground_Map::Render()
	{
		GameObject::Render();
	}
	void Ground_Map::OnCollisionEnter(Collider2D* other)
	{
	}
	void Ground_Map::OnCollisionStay(Collider2D* other)
	{
	}
	void Ground_Map::OnCollisionExit(Collider2D* other)
	{
	}
}