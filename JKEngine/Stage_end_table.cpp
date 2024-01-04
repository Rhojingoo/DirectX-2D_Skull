#include "Stage_end_table.h"
#include "Include_Common.h"


namespace jk
{
	Stage_end_table::Stage_end_table()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Stage_end_table::~Stage_end_table()
	{
	}
	void Stage_end_table::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		tr = this->GetComponent<Transform>();

		at = AddComponent<Animator>();

		at->CreateAnimations(L"..\\Resources\\Texture\\Gate\\Stage1\\Table", this, 0);
		at->CreateAnimations(L"..\\Resources\\Texture\\Gate\\Stage1\\Choice_Table", this, 0);

		at->CreateAnimations(L"..\\Resources\\Texture\\Gate\\Stage2\\Table", this, 0);
		at->CreateAnimations(L"..\\Resources\\Texture\\Gate\\Stage2\\Choice_Table", this, 0);

		at->PlayAnimation(L"Stage1Table", false);

		GameObject::Initialize();
	}
	void Stage_end_table::Update()
	{
		if (_Set_Table_Allow == true)
		{
			if (_Stage_Table == 0)
			{
				at->PlayAnimation(L"Stage1Table", false);
				_State = End_Table_State::Stage1_EnD_Table;
			}
			if (_Stage_Table == 1)
			{
				at->PlayAnimation(L"Stage2Table", false);
				_State = End_Table_State::Stage2_EnD_Table;
			}
			if (_Stage_Table == 2)
			{
				at->PlayAnimation(L"Stage1Choice_Table", false);
				_State = End_Table_State::Stage1_EnD_Choice_Table;
			}
			if (_Stage_Table == 3)
			{
				at->PlayAnimation(L"Stage2Choice_Table", false);
				_State = End_Table_State::Stage2_EnD_Choice_Table;
			}
		}


		switch (_State)
		{
		case jk::Stage_end_table::End_Table_State::Stage1_EnD_Table:
			EnD_Table();
			break;

		case jk::Stage_end_table::End_Table_State::Stage2_EnD_Table:
			EnD_Table();
			break;

		case jk::Stage_end_table::End_Table_State::Stage1_EnD_Choice_Table:
			EnD_Choice_Table();
			break;

		case jk::Stage_end_table::End_Table_State::Stage2_EnD_Choice_Table:
			EnD_Choice_Table();
			break;


		default:
			break;
		}
		GameObject::Update();
	}
	void Stage_end_table::LateUpdate()
	{
		_collider->SetSize(Vector2(0.f, 0.f));
		_collider->SetCenter(Vector2(0.f, 0.f));
		GameObject::LateUpdate();
	}
	void Stage_end_table::Render()
	{
		GameObject::Render();
	}
	void Stage_end_table::OnCollisionEnter(Collider2D* other)
	{
	}
	void Stage_end_table::OnCollisionStay(Collider2D* other)
	{
	}
	void Stage_end_table::OnCollisionExit(Collider2D* other)
	{
	}
	void Stage_end_table::EnD_Table()
	{
	}
	void Stage_end_table::EnD_Choice_Table()
	{
	}
}