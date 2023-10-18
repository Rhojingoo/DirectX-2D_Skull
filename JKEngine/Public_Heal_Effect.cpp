#include "Public_Heal_Effect.h"

namespace jk
{
	Public_Heal_Effect::Public_Heal_Effect()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Public_Heal_Effect::~Public_Heal_Effect()
	{
	}
	void Public_Heal_Effect::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Public\\Effect\\Heal", this, 0, 0.07f);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Public\\Effect\\Heal", this, 1, 0.07f);

		at->CompleteEvent(L"EffectHeal") = std::bind(&Public_Heal_Effect::Compelete, this);
		at->CompleteEvent(L"EffectHealR") = std::bind(&Public_Heal_Effect::Compelete, this);

		at->PlayAnimation(L"EffectHeal", true);

		GameObject::Initialize();
	}
	void Public_Heal_Effect::Update()
	{
		if (_effect_animation == true)
		{
			if (_dir == 1)
				at->PlayAnimation(L"EffectHeal", true);
			else
				at->PlayAnimation(L"EffectHealR", true);
			_effect_animation = false;
		}

		GameObject::Update();
	}
	void Public_Heal_Effect::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Public_Heal_Effect::Render()
	{
		GameObject::Render();
	}
	void Public_Heal_Effect::OnCollisionEnter(Collider2D* other)
	{
	}
	void Public_Heal_Effect::OnCollisionStay(Collider2D* other)
	{
	}
	void Public_Heal_Effect::OnCollisionExit(Collider2D* other)
	{
	}
	void Public_Heal_Effect::Compelete()
	{
		this->SetState(eState::Paused);
		_effect_switch = false;
	}
}