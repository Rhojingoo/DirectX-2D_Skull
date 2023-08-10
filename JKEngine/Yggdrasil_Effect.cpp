#include "Yggdrasil_Effect.h"

namespace jk
{
	bool Yggdrasil_Effect::_effect_switch = false;
	Vector3 Yggdrasil_Effect::_pos = Vector3(0.f, 0.f, 0.f);

	Yggdrasil_Effect::Yggdrasil_Effect()
	{
	}
	Yggdrasil_Effect::~Yggdrasil_Effect()
	{
	}
	void Yggdrasil_Effect::Initialize()
	{
		GameObject::Initialize();
	}
	void Yggdrasil_Effect::Update()
	{
		GameObject::Update();
	}
	void Yggdrasil_Effect::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Yggdrasil_Effect::Render()
	{
		GameObject::Render();
	}
	void Yggdrasil_Effect::OnCollisionEnter(Collider2D* other)
	{
	}
	void Yggdrasil_Effect::OnCollisionStay(Collider2D* other)
	{
	}
	void Yggdrasil_Effect::OnCollisionExit(Collider2D* other)
	{
	}
}