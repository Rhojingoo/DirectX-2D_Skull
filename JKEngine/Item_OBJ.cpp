#include "Item_OBJ.h"

namespace jk
{
	Item_OBJ::Item_OBJ()
	{
	}
	Item_OBJ::~Item_OBJ()
	{
	}
	void Item_OBJ::Initialize()
	{
		GameObject::Initialize();
	}
	void Item_OBJ::Update()
	{
		GameObject::Update();
	}
	void Item_OBJ::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Item_OBJ::Render()
	{
		GameObject::Render();
	}
	void Item_OBJ::OnCollisionEnter(Collider2D* other)
	{
	}
	void Item_OBJ::OnCollisionStay(Collider2D* other)
	{
	}
	void Item_OBJ::OnCollisionExit(Collider2D* other)
	{
	}
}