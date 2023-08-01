#include "Mini_Boss.h"


namespace jk
{
	GameObject* Mini_Boss::_player = nullptr;

	Mini_Boss::Mini_Boss()
	{
	}
	Mini_Boss::~Mini_Boss()
	{
	}

	void Mini_Boss::Initialize()
	{



		GameObject::Initialize();
	}

	void Mini_Boss::Update()
	{
		GameObject::Update();
	}

	void Mini_Boss::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Mini_Boss::Render()
	{
		GameObject::Render();
	}

	void Mini_Boss::OnCollisionEnter(Collider2D* other)
	{
	}
	void Mini_Boss::OnCollisionStay(Collider2D* other)
	{
	}
	void Mini_Boss::OnCollisionExit(Collider2D* other)
	{
	}
}
