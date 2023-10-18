#include "Layana_Meteor_GR_Smoke.h"

namespace jk
{
	Layana_Meteor_GR_Smoke::Layana_Meteor_GR_Smoke()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Layana_Meteor_GR_Smoke::~Layana_Meteor_GR_Smoke()
	{
	}
	void Layana_Meteor_GR_Smoke::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Smoke\\Meteor_GR_Smoke", this, 0, 0.05f);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Smoke\\Meteor_GR_Smoke", this, 1, 0.05f);
		at->CompleteEvent(L"SmokeMeteor_GR_Smoke") = std::bind(&Layana_Meteor_GR_Smoke::Compelete_Pierce, this);
		at->CompleteEvent(L"SmokeMeteor_GR_SmokeR") = std::bind(&Layana_Meteor_GR_Smoke::Compelete_Pierce, this);

		at->PlayAnimation(L"SmokeMeteor_GR_Smoke", true);
		GameObject::Initialize();
	}
	void Layana_Meteor_GR_Smoke::Update()
	{
		if (_SwitchOn == true)
		{
			if (mDir == 1)
				at->PlayAnimation(L"SmokeMeteor_GR_Smoke", true);
			else
				at->PlayAnimation(L"SmokeMeteor_GR_SmokeR", true);
			_SwitchOn = false;
		}
		GameObject::Update();
	}
	void Layana_Meteor_GR_Smoke::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Layana_Meteor_GR_Smoke::Render()
	{
		GameObject::Render();
	}
	void Layana_Meteor_GR_Smoke::OnCollisionEnter(Collider2D* other)
	{
	}
	void Layana_Meteor_GR_Smoke::OnCollisionStay(Collider2D* other)
	{
	}
	void Layana_Meteor_GR_Smoke::OnCollisionExit(Collider2D* other)
	{
	}
	void Layana_Meteor_GR_Smoke::Compelete_Pierce()
	{
		this->SetState(eState::Paused);
	}
}