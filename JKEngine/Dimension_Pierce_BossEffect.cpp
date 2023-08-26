#include "Dimension_Pierce_BossEffect.h"


namespace jk
{
	int Dimension_Pierce_BossEffect::mDir = 1;
	bool Dimension_Pierce_BossEffect::_SwitchOn = false;

	Dimension_Pierce_BossEffect::Dimension_Pierce_BossEffect()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Dimension_Pierce_BossEffect::~Dimension_Pierce_BossEffect()
	{
	}
	void Dimension_Pierce_BossEffect::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Effect\\DimensionPierce_Boss", this,0,0.05);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Effect\\DimensionPierce_Boss", this,1,0.05);
		at->CompleteEvent(L"EffectDimensionPierce_Boss") = std::bind(&Dimension_Pierce_BossEffect::Compelete_Pierce, this);
		at->CompleteEvent(L"EffectDimensionPierce_BossR") = std::bind(&Dimension_Pierce_BossEffect::Compelete_Pierce, this);

		at->PlayAnimation(L"EffectDimensionPierce_Boss", true);
		GameObject::Initialize();
	}
	void Dimension_Pierce_BossEffect::Update()
	{
		if (_SwitchOn == true)
		{
			if (mDir == 1)
				at->PlayAnimation(L"EffectDimensionPierce_Boss", true);
			else
				at->PlayAnimation(L"EffectDimensionPierce_BossR", true);
			_SwitchOn = false;
		}
		GameObject::Update();
	}
	void Dimension_Pierce_BossEffect::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Dimension_Pierce_BossEffect::Render()
	{
		GameObject::Render();
	}
	void Dimension_Pierce_BossEffect::OnCollisionEnter(Collider2D* other)
	{
	}
	void Dimension_Pierce_BossEffect::OnCollisionStay(Collider2D* other)
	{
	}
	void Dimension_Pierce_BossEffect::OnCollisionExit(Collider2D* other)
	{
	}
	void Dimension_Pierce_BossEffect::Compelete_Pierce()
	{
		this->SetState(eState::Paused);
	}
}
