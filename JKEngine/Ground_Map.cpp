#include "Ground_Map.h"
#include "Include_Common.h"
#include "Alpha_Blend.h"


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
		if (Player* _head = dynamic_cast<Player*>(other->GetOwner()))
		{
			if (_StageTurn == true)
			{
			_turnon = true;
			}
		}		
	}
	void Ground_Map::OnCollisionStay(Collider2D* other)
	{

	}
	void Ground_Map::OnCollisionExit(Collider2D* other)
	{
	}
}