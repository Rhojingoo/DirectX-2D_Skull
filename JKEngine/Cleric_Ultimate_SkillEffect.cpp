#include "Cleric_Ultimate_SkillEffect.h"
#include "Include_Common.h"


namespace jk
{
	Cleric_Ultimate_SkillEffect::Cleric_Ultimate_SkillEffect()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Cleric_Ultimate_SkillEffect::~Cleric_Ultimate_SkillEffect()
	{
	}
	void Cleric_Ultimate_SkillEffect::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		at = AddComponent<Animator>();

		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Effect\\Grace_Of_Leonia_1", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Cleric\\Effect\\Grace_Of_Leonia_2", this);
		at->CompleteEvent(L"EffectGrace_Of_Leonia_1") = std::bind(&Cleric_Ultimate_SkillEffect::Compelete1, this);
		at->CompleteEvent(L"EffectGrace_Of_Leonia_2") = std::bind(&Cleric_Ultimate_SkillEffect::Compelete2, this);

		at->PlayAnimation(L"EffectGrace_Of_Leonia_1", true);


		GameObject::Initialize();
	}
	void Cleric_Ultimate_SkillEffect::Update()
	{
		GameObject::Update();
	}
	void Cleric_Ultimate_SkillEffect::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Cleric_Ultimate_SkillEffect::Render()
	{
		GameObject::Render();
	}
	void Cleric_Ultimate_SkillEffect::OnCollisionEnter(Collider2D* other)
	{
	}
	void Cleric_Ultimate_SkillEffect::OnCollisionStay(Collider2D* other)
	{
	}
	void Cleric_Ultimate_SkillEffect::OnCollisionExit(Collider2D* other)
	{
	}

	void Cleric_Ultimate_SkillEffect::Compelete1()
	{
		at->PlayAnimation(L"EffectGrace_Of_Leonia_2", true);
	}
	void Cleric_Ultimate_SkillEffect::Compelete2()
	{
		this->SetState(eState::Paused);
		_effect_On = false;
	}

}