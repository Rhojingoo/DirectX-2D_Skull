#include "Mage_Phoenix_Landing_Land.h"

namespace jk
{
	Mage_Phoenix_Landing_Land::Mage_Phoenix_Landing_Land()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Mage_Phoenix_Landing_Land::~Mage_Phoenix_Landing_Land()
	{
	}
	void Mage_Phoenix_Landing_Land::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Effect\\Phoenix_Landing_Land", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Effect\\Phoenix_Landing_Land", this, 1);

		at->CompleteEvent(L"EffectPhoenix_Landing_Land") = std::bind(&Mage_Phoenix_Landing_Land::Compelete, this);
		at->CompleteEvent(L"EffectPhoenix_Landing_LandR") = std::bind(&Mage_Phoenix_Landing_Land::Compelete, this);

		at->PlayAnimation(L"EffectPhoenix_Landing_Land", true);
		GameObject::Initialize();
	}	
	void Mage_Phoenix_Landing_Land::Update()
	{
		if (_effect_Animation == true)
		{
			if (_dir == 1)
				at->PlayAnimation(L"EffectPhoenix_Landing_Land", true);
			if (_dir == -1)
				at->PlayAnimation(L"EffectPhoenix_Landing_Land", true);
			_effect_Animation = false;
		}
		GameObject::Update();
	}
	void Mage_Phoenix_Landing_Land::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Mage_Phoenix_Landing_Land::Render()
	{
		GameObject::Render();
	}
	void Mage_Phoenix_Landing_Land::OnCollisionEnter(Collider2D* other)
	{
	}
	void Mage_Phoenix_Landing_Land::OnCollisionStay(Collider2D* other)
	{
	}
	void Mage_Phoenix_Landing_Land::OnCollisionExit(Collider2D* other)
	{
	}
	void Mage_Phoenix_Landing_Land::Compelete()
	{
		this->SetState(eState::Paused);
		_effect_On = false;
	}
}