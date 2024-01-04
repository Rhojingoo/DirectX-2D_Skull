#include "Monster_Death_Effect.h"
#include "Include_Common.h"


namespace jk
{
	Monster_Death_Effect::Monster_Death_Effect()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Monster_Death_Effect::~Monster_Death_Effect()
	{
	}
	void Monster_Death_Effect::Initialize()
	{
		_collider = AddComponent<Collider2D>();


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Public\\Effect\\Death_Effect", this, 0);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Public\\Effect\\Death_Effect", this, 1);

		at->CompleteEvent(L"EffectDeath_Effect") = std::bind(&Monster_Death_Effect::Compelete, this);
		at->CompleteEvent(L"EffectDeath_EffectR") = std::bind(&Monster_Death_Effect::Compelete, this);

		at->PlayAnimation(L"EffectDeath_Effect", true);

		GameObject::Initialize();
	}
	void Monster_Death_Effect::Update()
	{
		if (_effect_animation == true)
		{
			if (_dir == 1)
				at->PlayAnimation(L"EffectDeath_Effect", true);
			else
				at->PlayAnimation(L"EffectDeath_EffectR", true);
			_effect_animation = false;
		}

		GameObject::Update();
	}
	void Monster_Death_Effect::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Monster_Death_Effect::Render()
	{
		GameObject::Render();
	}
	void Monster_Death_Effect::OnCollisionEnter(Collider2D* other)
	{
	}
	void Monster_Death_Effect::OnCollisionStay(Collider2D* other)
	{
	}
	void Monster_Death_Effect::OnCollisionExit(Collider2D* other)
	{
	}
	void Monster_Death_Effect::Compelete()
	{
		this->SetState(eState::Paused);
	}
}