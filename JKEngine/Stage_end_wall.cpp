#include "Stage_end_wall.h"

namespace jk
{
	Stage_end_wall::Stage_end_wall()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Stage_end_wall::~Stage_end_wall()
	{
	}
	void Stage_end_wall::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		tr = this->GetComponent<Transform>();

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Gate\\Stage1\\Wall", this, 0, 0.05f);
		at->CreateAnimations(L"..\\Resources\\Texture\\Gate\\Stage2\\Wall", this, 0, 0.05f);

		at->PlayAnimation(L"Stage1Wall", true);
		GameObject::Initialize();
	}
	void Stage_end_wall::Update()
	{
		if (_Set_Wall_Allow == true)
		{
			if (_Stage_Wall == 0)
			{
				at->PlayAnimation(L"Stage1Wall", true);
				_State = End_Wall_State::Stage1_EnD_Wall;
			}
			if (_Stage_Wall == 1)
			{
				at->PlayAnimation(L"Stage2Wall", true);
				_State = End_Wall_State::Stage2_EnD_Wall;
			}
		}


		switch (_State)
		{
		case jk::Stage_end_wall::End_Wall_State::Stage1_EnD_Wall:
			Stage1_End_Wall();
			break;

		case jk::Stage_end_wall::End_Wall_State::Stage2_EnD_Wall:
			Stage2_End_Wall();
			break;

		default:
			break;
		}
		GameObject::Update();
	}
	void Stage_end_wall::LateUpdate()
	{
		_collider->SetSize(Vector2(0.f, 0.f));
		_collider->SetCenter(Vector2(0.f, 0.f));
		GameObject::LateUpdate();
	}
	void Stage_end_wall::Render()
	{
		GameObject::Render();
	}
	void Stage_end_wall::OnCollisionEnter(Collider2D* other)
	{
	}
	void Stage_end_wall::OnCollisionStay(Collider2D* other)
	{
	}
	void Stage_end_wall::OnCollisionExit(Collider2D* other)
	{
	}
	void Stage_end_wall::Stage1_End_Wall()
	{
	}
	void Stage_end_wall::Stage2_End_Wall()
	{
	}
}