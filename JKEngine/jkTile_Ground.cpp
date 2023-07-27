#include "jkTile_Ground.h"


namespace jk
{
	Tile_Ground::Tile_Ground()
	{
		_collider = AddComponent<Collider2D>();
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
		//if (Skul_Basic* mSkul_Basic = dynamic_cast<Skul_Basic*>(other->GetOwner()))
		//{
		//	RigidBody* rb = mSkul_Basic->GetComponent<RigidBody>();
		//	rb->SetGround(true);
		//	rb->ClearVelocityY();

		//	Vector3 _Tile_ColPos = _collider->GetPosition();
		//	Collider2D* mSkul_Basic_Col = mSkul_Basic->GetComponent<Collider2D>();
		//	Vector3 mSkul_Basic_ColPos = mSkul_Basic_Col->GetPosition();

		//	Transform* mSkul_Basic_Tr = mSkul_Basic->GetComponent<Transform>();
		//	Vector3 mSkul_Basic_Pos = mSkul_Basic_Tr->GetPosition();

		//	mSkul_Basic_Pos.y = _Tile_ColPos.y + mSkul_Basic_Col->GetSize().y+ _collider->GetSize().y;
		//	mSkul_Basic_Tr->SetPosition(mSkul_Basic_Pos);
		//}
	}
	void Tile_Ground::OnCollisionStay(Collider2D* other)
	{

	}
	void Tile_Ground::OnCollisionExit(Collider2D* other)
	{
	}
}