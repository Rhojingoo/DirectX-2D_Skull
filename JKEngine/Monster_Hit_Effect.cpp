#include "Monster_Hit_Effect.h"

namespace jk
{
	Monster_Hit_Effect::Monster_Hit_Effect()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Monster_Hit_Effect::~Monster_Hit_Effect()
	{
	}

	void Monster_Hit_Effect::Initialize()
	{
		_collider = AddComponent<Collider2D>();

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Public\\Effect\\Hit_Normal", this, 0,0.05f);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Public\\Effect\\Hit_Normal", this, 1,0.05f);

		at->CompleteEvent(L"EffectHit_Normal") = std::bind(&Monster_Hit_Effect::Compelete, this);
		at->CompleteEvent(L"EffectHit_NormalR") = std::bind(&Monster_Hit_Effect::Compelete, this);

		at->PlayAnimation(L"EffectHit_Normal", true);

		GameObject::Initialize();
	}

	void Monster_Hit_Effect::Update()
	{
		if (_effect_animation == true)
		{
			if (_dir == 1)
				at->PlayAnimation(L"EffectHit_Normal", true);
			else
				at->PlayAnimation(L"EffectHit_NormalR", true);
			_effect_animation = false;
		}

		GameObject::Update();
	}

	void Monster_Hit_Effect::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}

	void Monster_Hit_Effect::Render()
	{
		GameObject::Render();
	}

	void Monster_Hit_Effect::OnCollisionEnter(Collider2D* other)
	{
	}

	void Monster_Hit_Effect::OnCollisionStay(Collider2D* other)
	{
	}

	void Monster_Hit_Effect::OnCollisionExit(Collider2D* other)
	{
	}

	void Monster_Hit_Effect::Compelete()
	{
		this->SetState(eState::Paused);
	}
}