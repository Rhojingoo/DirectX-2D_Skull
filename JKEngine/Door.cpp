#include "Door.h"

namespace jk
{
	Door::Door()
	{
	}
	Door::~Door()
	{
	}
	void Door::Initialize()
	{
		GameObject::Initialize();
	}
	void Door::Update()
	{
		GameObject::Update();
	}
	void Door::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Door::Render()
	{
		GameObject::Render();
	}

	void Door::OnCollisionEnter(Collider2D* other)
	{

	}

	void Door::OnCollisionStay(Collider2D* other)
	{

	}

	void Door::OnCollisionExit(Collider2D* other)
	{

	}

}