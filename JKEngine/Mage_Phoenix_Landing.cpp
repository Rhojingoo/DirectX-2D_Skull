#include "Mage_Phoenix_Landing.h"
#include "Include_Common.h"


namespace jk
{
	Mage_Phoenix_Landing::Mage_Phoenix_Landing()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Mage_Phoenix_Landing::~Mage_Phoenix_Landing()
	{
	}
	void Mage_Phoenix_Landing::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Effect\\Phoenix_Landing", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Effect\\Phoenix_Landing", this, 1);

		at->CompleteEvent(L"EffectPhoenix_Landing") = std::bind(&Mage_Phoenix_Landing::Compelete, this);
		at->CompleteEvent(L"EffectPhoenix_LandingR") = std::bind(&Mage_Phoenix_Landing::Compelete, this);

		at->PlayAnimation(L"EffectPhoenix_Landing", true);
		GameObject::Initialize();
	}
	void Mage_Phoenix_Landing::Update()
	{
		if (_effect_Animation == true)
		{
			if (_dir == 1)
				at->PlayAnimation(L"EffectPhoenix_Landing", true);
			if (_dir == -1)
				at->PlayAnimation(L"EffectPhoenix_LandingR", true);
			_effect_Animation = false;
		}
		GameObject::Update();
	}
	void Mage_Phoenix_Landing::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Mage_Phoenix_Landing::Render()
	{
		GameObject::Render();
	}
	void Mage_Phoenix_Landing::OnCollisionEnter(Collider2D* other)
	{
	}
	void Mage_Phoenix_Landing::OnCollisionStay(Collider2D* other)
	{
	}
	void Mage_Phoenix_Landing::OnCollisionExit(Collider2D* other)
	{
	}
	void Mage_Phoenix_Landing::Compelete()
	{
		this->SetState(eState::Paused);
	}
}