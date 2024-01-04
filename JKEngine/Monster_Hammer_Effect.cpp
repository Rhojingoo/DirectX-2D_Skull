#include "Monster_Hammer_Effect.h"
#include "Include_Common.h"

namespace jk
{
	Monster_Hammer_Effect::Monster_Hammer_Effect()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Monster_Hammer_Effect::~Monster_Hammer_Effect()
	{
	}
	void Monster_Hammer_Effect::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Public\\Effect\\Hammer_Spark", this, 0);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Public\\Effect\\Hammer_Spark", this, 1);

		at->CompleteEvent(L"EffectHammer_Spark") = std::bind(&Monster_Hammer_Effect::Compelete, this);
		at->CompleteEvent(L"EffectHammer_SparkR") = std::bind(&Monster_Hammer_Effect::Compelete, this);

		at->PlayAnimation(L"EffectHammer_Spark", true);

		GameObject::Initialize();
	}
	void Monster_Hammer_Effect::Update()
	{
		if (_effect_animation == true)
		{
			if (_dir == 1)
				at->PlayAnimation(L"EffectHammer_Spark", true);
			else
				at->PlayAnimation(L"EffectHammer_SparkR", true);
			_effect_animation = false;
		}

		GameObject::Update();
	}
	void Monster_Hammer_Effect::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Monster_Hammer_Effect::Render()
	{
		GameObject::Render();
	}
	void Monster_Hammer_Effect::OnCollisionEnter(Collider2D* other)
	{
	}
	void Monster_Hammer_Effect::OnCollisionStay(Collider2D* other)
	{
	}
	void Monster_Hammer_Effect::OnCollisionExit(Collider2D* other)
	{
	}
	void Monster_Hammer_Effect::Compelete()
	{
		this->SetState(eState::Paused);
	}
}