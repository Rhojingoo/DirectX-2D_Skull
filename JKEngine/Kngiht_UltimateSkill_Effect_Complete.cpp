#include "Kngiht_UltimateSkill_Effect_Complete.h"

namespace jk
{
	Kngiht_UltimateSkill_Effect_Complete::Kngiht_UltimateSkill_Effect_Complete()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Kngiht_UltimateSkill_Effect_Complete::~Kngiht_UltimateSkill_Effect_Complete()
	{
	}
	void Kngiht_UltimateSkill_Effect_Complete::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Effect\\UltimateSkill_Effect_Complete", this,0,0.05);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Effect\\UltimateSkill_Effect_Complete", this, 1, 0.05);

		at->CompleteEvent(L"EffectUltimateSkill_Effect_Complete") = std::bind(&Kngiht_UltimateSkill_Effect_Complete::Compelete, this);
		at->CompleteEvent(L"EffectUltimateSkill_Effect_CompleteR") = std::bind(&Kngiht_UltimateSkill_Effect_Complete::Compelete, this);


		at->PlayAnimation(L"EffectUltimateSkill_Effect_Complete", true);

		GameObject::Initialize();
	}
	void Kngiht_UltimateSkill_Effect_Complete::Update()
	{
		if (_effect_animation == true)
		{
			if (_dir == 1)
				at->PlayAnimation(L"EffectUltimateSkill_Effect_Complete", true);
			else
				at->PlayAnimation(L"EffectUltimateSkill_Effect_CompleteR", true);
			_effect_animation = false;
		}

		GameObject::Update();
	}
	void Kngiht_UltimateSkill_Effect_Complete::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Kngiht_UltimateSkill_Effect_Complete::Render()
	{
		GameObject::Render();
	}
	void Kngiht_UltimateSkill_Effect_Complete::OnCollisionEnter(Collider2D* other)
	{
	}
	void Kngiht_UltimateSkill_Effect_Complete::OnCollisionStay(Collider2D* other)
	{
	}
	void Kngiht_UltimateSkill_Effect_Complete::OnCollisionExit(Collider2D* other)
	{
	}
	void Kngiht_UltimateSkill_Effect_Complete::Compelete()
	{
		this->SetState(eState::Paused);
	}
}