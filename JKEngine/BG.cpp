#include "BG.h"


namespace jk
{
	BG::BG()
	{

	}
	BG::~BG()
	{
	}
	void BG::Initialize()
	{
		GameObject::Initialize();
	}
	void BG::Update()
	{
		GameObject::Update();
	}
	void BG::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void BG::Render()
	{
		GameObject::Render();
	}
	void BG::OnCollisionEnter(Collider2D* other)
	{
	}
	void BG::OnCollisionStay(Collider2D* other)
	{
	}
	void BG::OnCollisionExit(Collider2D* other)
	{
	}
}