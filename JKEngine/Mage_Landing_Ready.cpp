#include "Mage_Landing_Ready.h"

namespace jk
{
	Mage_Landing_Ready::Mage_Landing_Ready()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Mage_Landing_Ready::~Mage_Landing_Ready()
	{
	}
	void Mage_Landing_Ready::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Effect\\Phoenix_Landing_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Effect\\Phoenix_Landing_Ready", this, 1);

		at->CompleteEvent(L"EffectPhoenix_Landing_Ready") = std::bind(&Mage_Landing_Ready::Compelete, this);
		at->CompleteEvent(L"EffectPhoenix_Landing_ReadyR") = std::bind(&Mage_Landing_Ready::Compelete, this);

		at->PlayAnimation(L"EffectPhoenix_Landing_Ready", true);
		GameObject::Initialize();
	}
	void Mage_Landing_Ready::Update()
	{
		if (_effect_Animation == true)
		{
			if (_dir == 1)
				at->PlayAnimation(L"EffectPhoenix_Landing_Ready", true);
			if (_dir == -1)
				at->PlayAnimation(L"EffectPhoenix_Landing_ReadyR", true);
			_effect_Animation = false;
		}
		GameObject::Update();
	}
	void Mage_Landing_Ready::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Mage_Landing_Ready::Render()
	{
		GameObject::Render();
	}
	void Mage_Landing_Ready::OnCollisionEnter(Collider2D* other)
	{
	}
	void Mage_Landing_Ready::OnCollisionStay(Collider2D* other)
	{
	}
	void Mage_Landing_Ready::OnCollisionExit(Collider2D* other)
	{
	}
	void Mage_Landing_Ready::Compelete()
	{
		_effect_On = false;
		this->SetState(eState::Paused);
	}
}