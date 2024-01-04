#include "Public_UltimateSkill_Effect_Fail.h"
#include "Include_Common.h"


namespace jk
{
	Public_UltimateSkill_Effect_Fail::Public_UltimateSkill_Effect_Fail()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Public_UltimateSkill_Effect_Fail::~Public_UltimateSkill_Effect_Fail()
	{
	}
	void Public_UltimateSkill_Effect_Fail::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Public\\Effect\\UltimateSkill_Effect_Fail", this, 0, 0.05f);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Public\\Effect\\UltimateSkill_Effect_Fail", this, 1, 0.05f);

		at->CompleteEvent(L"EffectUltimateSkill_Effect_Fail") = std::bind(&Public_UltimateSkill_Effect_Fail::Compelete, this);
		at->CompleteEvent(L"EffectUltimateSkill_Effect_FailR") = std::bind(&Public_UltimateSkill_Effect_Fail::Compelete, this);


		at->PlayAnimation(L"EffectUltimateSkill_Effect_Fail", true);

		GameObject::Initialize();
	}
	void Public_UltimateSkill_Effect_Fail::Update()
	{
		if (_effect_animation == true)
		{
			if (_dir == 1)
				at->PlayAnimation(L"EffectUltimateSkill_Effect_Fail", true);
			else
				at->PlayAnimation(L"EffectUltimateSkill_Effect_FailR", true);
			_effect_animation = false;
		}

		GameObject::Update();
	}
	void Public_UltimateSkill_Effect_Fail::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Public_UltimateSkill_Effect_Fail::Render()
	{
		GameObject::Render();
	}
	void Public_UltimateSkill_Effect_Fail::OnCollisionEnter(Collider2D* other)
	{
	}
	void Public_UltimateSkill_Effect_Fail::OnCollisionStay(Collider2D* other)
	{
	}
	void Public_UltimateSkill_Effect_Fail::OnCollisionExit(Collider2D* other)
	{
	}
	void Public_UltimateSkill_Effect_Fail::Compelete()
	{
		this->SetState(eState::Paused);

	}
}