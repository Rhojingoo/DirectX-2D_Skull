#include "jkTile_Ground.h"


namespace jk
{
	Tile_Ground::Tile_Ground()
	{
		//_collider = AddComponent<Collider2D>();
	}
	Tile_Ground::~Tile_Ground()
	{
	}
	void Tile_Ground::Initialize()
	{
		
		GameObject::Initialize();
	}
	void Tile_Ground::Update()
	{
		tr = GetComponent<Transform>();
		pos = tr->GetPosition();
		GameObject::Update();
	}
	void Tile_Ground::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Tile_Ground::Render()
	{
		GameObject::Render();
	}
	void Tile_Ground::OnCollisionEnter(Collider2D* other)
	{
		if (Player* _head = dynamic_cast<Player*>(other->GetOwner()))
		{
			if (_StageTurn == true)
			{
				_turnon = true;
			}
		}
	}
	void Tile_Ground::OnCollisionStay(Collider2D* other)
	{

	}
	void Tile_Ground::OnCollisionExit(Collider2D* other)
	{
	}
}