#include "Public_Ultimate_Aura.h"


namespace jk
{
	Public_Ultimate_Aura::Public_Ultimate_Aura()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Public_Ultimate_Aura::~Public_Ultimate_Aura()
	{
	}
	void Public_Ultimate_Aura::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Public\\Effect\\UltimateSkill_Aura", this,0, 0.07);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Public\\Effect\\UltimateSkill_Aura", this,1, 0.07);

		//at->CompleteEvent(L"EffectEnergyBall_Impact") = std::bind(&Kngiht_EnergyBall_Impact::Compelete, this);

		at->PlayAnimation(L"EffectUltimateSkill_Aura", true);

		GameObject::Initialize();
	}
	void Public_Ultimate_Aura::Update()
	{
		if (_effect_animation == true)
		{
			if(_dir == 1)
			at->PlayAnimation(L"EffectUltimateSkill_Aura", true);
			else
			at->PlayAnimation(L"EffectUltimateSkill_AuraR", true);
			_effect_animation = false;
		}

		GameObject::Update();
	}
	void Public_Ultimate_Aura::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Public_Ultimate_Aura::Render()
	{
		GameObject::Render();
	}
	void Public_Ultimate_Aura::OnCollisionEnter(Collider2D* other)
	{
	}
	void Public_Ultimate_Aura::OnCollisionStay(Collider2D* other)
	{
	}
	void Public_Ultimate_Aura::OnCollisionExit(Collider2D* other)
	{
	}
	void Public_Ultimate_Aura::Compelete()
	{
	}
}