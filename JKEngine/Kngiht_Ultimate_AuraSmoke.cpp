#include "Kngiht_Ultimate_AuraSmoke.h"


namespace jk
{
	Kngiht_Ultimate_AuraSmoke::Kngiht_Ultimate_AuraSmoke()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Kngiht_Ultimate_AuraSmoke::~Kngiht_Ultimate_AuraSmoke()
	{
	}
	void Kngiht_Ultimate_AuraSmoke::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Effect\\UltimateSkill_AuraSmoke", this,0,0.08);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Effect\\UltimateSkill_AuraSmoke", this, 1, 0.08);

		//at->CompleteEvent(L"EffectEnergyBall_Impact") = std::bind(&Kngiht_EnergyBall_Impact::Compelete, this);

		at->PlayAnimation(L"EffectUltimateSkill_AuraSmoke", true);

		GameObject::Initialize();
	}
	void Kngiht_Ultimate_AuraSmoke::Update()
	{
		if (_effect_animation == true)
		{
			if (_dir == 1)
				at->PlayAnimation(L"EffectUltimateSkill_AuraSmoke", true);
			else
				at->PlayAnimation(L"EffectUltimateSkill_AuraSmokeR", true);
			_effect_animation = false;
		}

		GameObject::Update();
	}
	void Kngiht_Ultimate_AuraSmoke::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Kngiht_Ultimate_AuraSmoke::Render()
	{
		GameObject::Render();
	}
	void Kngiht_Ultimate_AuraSmoke::OnCollisionEnter(Collider2D* other)
	{
	}
	void Kngiht_Ultimate_AuraSmoke::OnCollisionStay(Collider2D* other)
	{
	}
	void Kngiht_Ultimate_AuraSmoke::OnCollisionExit(Collider2D* other)
	{
	}
	void Kngiht_Ultimate_AuraSmoke::Compelete()
	{
	}
}