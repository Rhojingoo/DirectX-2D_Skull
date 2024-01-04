#include "Monster_StoneWizard_Icicle_Effect.h"
#include "Include_Common.h"


namespace jk
{
	Monster_StoneWizard_Icicle_Effect::Monster_StoneWizard_Icicle_Effect()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Monster_StoneWizard_Icicle_Effect::~Monster_StoneWizard_Icicle_Effect()
	{
	}
	void Monster_StoneWizard_Icicle_Effect::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Stone_wizard\\Effect\\Icicle_Spawn_Effect", this, 0);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Stone_wizard\\Effect\\Icicle_Spawn_Effect", this, 1);

		at->CompleteEvent(L"EffectIcicle_Spawn_Effect") = std::bind(&Monster_StoneWizard_Icicle_Effect::Compelete, this);
		at->CompleteEvent(L"EffectIcicle_Spawn_EffectR") = std::bind(&Monster_StoneWizard_Icicle_Effect::Compelete, this);

		at->PlayAnimation(L"EffectIcicle_Spawn_Effect", false);

		GameObject::Initialize();
	}
	void Monster_StoneWizard_Icicle_Effect::Update()
	{
		if (_effect_On == true)
		{
			if(_dir==1)
				at->PlayAnimation(L"EffectIcicle_Spawn_Effect", true);
			else
				at->PlayAnimation(L"EffectIcicle_Spawn_EffectR", true);
			_effect_On = false;		
		}
		GameObject::Update();
	}
	void Monster_StoneWizard_Icicle_Effect::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Monster_StoneWizard_Icicle_Effect::Render()
	{
		GameObject::Render();
	}

	void Monster_StoneWizard_Icicle_Effect::OnCollisionEnter(Collider2D* other)
	{
	}
	void Monster_StoneWizard_Icicle_Effect::OnCollisionStay(Collider2D* other)
	{
	}
	void Monster_StoneWizard_Icicle_Effect::OnCollisionExit(Collider2D* other)
	{
	}

	void Monster_StoneWizard_Icicle_Effect::Compelete()
	{
		_endanimation = true;
		this->SetState(eState::Paused);
	}
}