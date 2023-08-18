#include "Knight_EnergyBall_StartEffect.h"

namespace jk
{
	bool Knight_EnergyBall_StartEffect::_effect_switch = true;
	bool Knight_EnergyBall_StartEffect::_effect_animation = true;
	

	Knight_EnergyBall_StartEffect::Knight_EnergyBall_StartEffect()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Knight_EnergyBall_StartEffect::~Knight_EnergyBall_StartEffect()
	{
	}
	void Knight_EnergyBall_StartEffect::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Effect\\Energy_Ball_Star_Effect", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Effect\\Energy_Ball_Star_Effect", this,1);
		at->CompleteEvent(L"EffectEnergy_Ball_Star_Effect") = std::bind(&Knight_EnergyBall_StartEffect::Compelete, this);
		at->CompleteEvent(L"EffectEnergy_Ball_Star_EffectR") = std::bind(&Knight_EnergyBall_StartEffect::Compelete, this);

		at->PlayAnimation(L"EffectEnergy_Ball_Star_Effect", true);

		GameObject::Initialize();
	}
	void Knight_EnergyBall_StartEffect::Update()
	{
		if (_effect_animation == true)
		{
			if (_dir == 1)
				at->PlayAnimation(L"EffectEnergy_Ball_Star_Effect", true);
			else
				at->PlayAnimation(L"EffectEnergy_Ball_Star_EffectR", true);
			_effect_animation = false;
		}

		GameObject::Update();
	}
	void Knight_EnergyBall_StartEffect::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Knight_EnergyBall_StartEffect::Render()
	{
		GameObject::Render();
	}
	void Knight_EnergyBall_StartEffect::OnCollisionEnter(Collider2D* other)
	{
	}
	void Knight_EnergyBall_StartEffect::OnCollisionStay(Collider2D* other)
	{
	}
	void Knight_EnergyBall_StartEffect::OnCollisionExit(Collider2D* other)
	{
	}
	void Knight_EnergyBall_StartEffect::Compelete()
	{
		_effect_switch = false;
		this->SetState(eState::Paused);
	}
}