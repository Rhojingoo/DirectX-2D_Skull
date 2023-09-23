#include "Layana_Dash_Smoke.h"

namespace jk
{
	Layana_Dash_Smoke::Layana_Dash_Smoke()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Layana_Dash_Smoke::~Layana_Dash_Smoke()
	{
	}
	void Layana_Dash_Smoke::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Smoke\\Dash_Somke", this, 0, 0.05);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Smoke\\Dash_Somke", this, 1, 0.05);
		at->CompleteEvent(L"SmokeDash_Somke") = std::bind(&Layana_Dash_Smoke::Compelete_Pierce, this);
		at->CompleteEvent(L"SmokeDash_SomkeR") = std::bind(&Layana_Dash_Smoke::Compelete_Pierce, this);

		at->PlayAnimation(L"SmokeDash_Somke", true);
		GameObject::Initialize();
	}
	void Layana_Dash_Smoke::Update()
	{
		if (_SwitchOn == true)
		{
			if (mDir == 1)
				at->PlayAnimation(L"SmokeDash_Somke", true);
			else
				at->PlayAnimation(L"SmokeDash_SomkeR", true);
			_SwitchOn = false;
		}
		GameObject::Update();
	}
	void Layana_Dash_Smoke::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Layana_Dash_Smoke::Render()
	{
		GameObject::Render();
	}
	void Layana_Dash_Smoke::OnCollisionEnter(Collider2D* other)
	{
	}
	void Layana_Dash_Smoke::OnCollisionStay(Collider2D* other)
	{
	}
	void Layana_Dash_Smoke::OnCollisionExit(Collider2D* other)
	{
	}
	void Layana_Dash_Smoke::Compelete_Pierce()
	{
		this->SetState(eState::Paused);
	}
}