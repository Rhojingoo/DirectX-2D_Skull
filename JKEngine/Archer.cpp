#include "Archer.h"


namespace jk
{
	Archer::Archer()
	{
	}
	Archer::~Archer()
	{
	}
	void Archer::Initialize()
	{
		GameObject::Initialize();
	}
	void Archer::Update()
	{
		GameObject::Update();
	}
	void Archer::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Archer::Render()
	{
		GameObject::Render();
	}
	void Archer::OnCollisionEnter(Collider2D* other)
	{
	}
	void Archer::OnCollisionStay(Collider2D* other)
	{
	}
	void Archer::OnCollisionExit(Collider2D* other)
	{
	}
}