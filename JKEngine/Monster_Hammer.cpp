#include "Monster_Hammer.h"


namespace jk
{
	Monster_Hammer::Monster_Hammer()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}
	Monster_Hammer::~Monster_Hammer()
	{
	}

	void Monster_Hammer::Initialize()
	{
		GameObject::Initialize();
	}

	void Monster_Hammer::Update()
	{
		GameObject::Update();
	}

	void Monster_Hammer::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Monster_Hammer::Render()
	{
		GameObject::Render();
	}

	void Monster_Hammer::OnCollisionEnter(Collider2D* other)
	{
	}

	void Monster_Hammer::OnCollisionStay(Collider2D* other)
	{
	}

	void Monster_Hammer::OnCollisionExit(Collider2D* other)
	{
	}

	void Monster_Hammer::idle()
	{
	}

	void Monster_Hammer::attack()
	{
	}

	void Monster_Hammer::tackle()
	{
	}

	void Monster_Hammer::walk()
	{
	}

	void Monster_Hammer::dead()
	{
	}
}