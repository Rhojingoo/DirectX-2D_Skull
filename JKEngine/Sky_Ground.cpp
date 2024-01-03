#include "Sky_Ground.h"
#include "Include_Common.h"

namespace jk
{
	Sky_Ground::Sky_Ground()
	{
		_collider = AddComponent<Collider2D>();
	}
	Sky_Ground::~Sky_Ground()
	{
	}
	void Sky_Ground::Initialize()
	{
		GameObject::Initialize();
	}
	void Sky_Ground::Update()
	{
		GameObject::Update();
	}
	void Sky_Ground::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Sky_Ground::Render()
	{
		GameObject::Render();
	}
	void Sky_Ground::OnCollisionEnter(Collider2D* other)
	{
	}
	void Sky_Ground::OnCollisionStay(Collider2D* other)
	{
	}
	void Sky_Ground::OnCollisionExit(Collider2D* other)
	{
	}
}