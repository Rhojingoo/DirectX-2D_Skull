#include "Intro_Somke.h"

namespace jk
{
	Intro_Somke::Intro_Somke()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Intro_Somke::~Intro_Somke()
	{
	}
	void Intro_Somke::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Smoke\\Intro_land", this, 0, 0.05);
		at->CompleteEvent(L"SmokeIntro_land") = std::bind(&Intro_Somke::Compelete_Pierce, this);

		at->PlayAnimation(L"SmokeIntro_land", true);
		GameObject::Initialize();
	}
	void Intro_Somke::Update()
	{
		if (_SwitchOn == true)
		{
			at->PlayAnimation(L"SmokeIntro_land", true);
			_SwitchOn = false;
		}
		GameObject::Update();
	}
	void Intro_Somke::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Intro_Somke::Render()
	{
		GameObject::Render();
	}
	void Intro_Somke::OnCollisionEnter(Collider2D* other)
	{
	}
	void Intro_Somke::OnCollisionStay(Collider2D* other)
	{
	}
	void Intro_Somke::OnCollisionExit(Collider2D* other)
	{
	}
	void Intro_Somke::Compelete_Pierce()
	{
		this->SetState(eState::Paused);
	}
}