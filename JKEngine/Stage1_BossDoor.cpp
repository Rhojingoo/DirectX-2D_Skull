#include "Stage1_BossDoor.h"

namespace jk
{
	Stage1_BossDoor::Stage1_BossDoor()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Stage1_BossDoor::~Stage1_BossDoor()
	{
	}
	void Stage1_BossDoor::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		tr = this->GetComponent<Transform>();

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Door\\Stage1\\Boss_StageDoor", this, 0, 0.05f);
		at->PlayAnimation(L"Stage1Boss_StageDoor", true);
		GameObject::Initialize();
	}
	void Stage1_BossDoor::Update()
	{
		GameObject::Update();
	}
	void Stage1_BossDoor::LateUpdate()
	{
		_collider->SetSize(Vector2(0.55f, 0.65f));
		_collider->SetCenter(Vector2(-3.f, -50.f));
		GameObject::LateUpdate();
	}
	void Stage1_BossDoor::Render()
	{
		GameObject::Render();
	}
	void Stage1_BossDoor::OnCollisionEnter(Collider2D* other)
	{
	}
	void Stage1_BossDoor::OnCollisionStay(Collider2D* other)
	{
		if (Player* _head = dynamic_cast<Player*>(other->GetOwner()))
		{
			if (Input::GetKeyState(eKeyCode::F) == eKeyState::Down)
			{
				_Alpha = object::Instantiate<Alpha_Blend>(Vector3(0.f, 0.f, -251.f), eLayerType::Map_Effect);
				_Alpha->GetComponent<Transform>()->SetScale(Vector3(10000.f, 10000.f, 0.f));
				_Alpha->Set_Black_Transparent();
				_Fadecheck = true;
			}
			if (_Fadecheck == true)
			{
				_time += 2.75f * static_cast<float>(Time::DeltaTime());
				if (_time > 3)
				{
					SceneManager::LoadScene(L"Stage2_1");
					_time = 0;
					_Fadecheck = false;
				}
			}
		}
	}
	void Stage1_BossDoor::OnCollisionExit(Collider2D* other)
	{
	}
}