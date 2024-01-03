#include "Dimension_Pierce_BulletEffect.h"
#include "Include_Common.h"


namespace jk
{
	int Dimension_Pierce_BulletEffect::_Dir = 1;
	bool Dimension_Pierce_BulletEffect::_SwitchOn = false;
	bool Dimension_Pierce_BulletEffect::_SwitchOff = false;

	Dimension_Pierce_BulletEffect::Dimension_Pierce_BulletEffect()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}


	Dimension_Pierce_BulletEffect::~Dimension_Pierce_BulletEffect()
	{
	}


	void Dimension_Pierce_BulletEffect::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Effect\\DimensionPierce_Impact", this, 0, 0.075f);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Effect\\DimensionPierce_Impact", this, 1, 0.075f);
		at->CompleteEvent(L"EffectDimensionPierce_Impact") = std::bind(&Dimension_Pierce_BulletEffect::Compelete_Pierce, this);
		at->CompleteEvent(L"EffectDimensionPierce_ImpactR") = std::bind(&Dimension_Pierce_BulletEffect::Compelete_Pierce, this);

		at->PlayAnimation(L"EffectDimensionPierce_Impact", true);
		GameObject::Initialize();
	}


	void Dimension_Pierce_BulletEffect::Update()
	{
		if (_SwitchOn == true)
		{
			if (_Dir == 1)
				at->PlayAnimation(L"EffectDimensionPierce_Boss", true);
			else
				at->PlayAnimation(L"EffectDimensionPierce_BossR", true);
			_SwitchOn = false;
		}
		GameObject::Update();
	}


	void Dimension_Pierce_BulletEffect::LateUpdate()
	{
		_collider->SetSize(Vector2(0.85f, 0.5f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}

	void Dimension_Pierce_BulletEffect::Render()
	{
		GameObject::Render();
	}

	void Dimension_Pierce_BulletEffect::OnCollisionEnter(Collider2D* other)
	{
	}
	void Dimension_Pierce_BulletEffect::OnCollisionStay(Collider2D* other)
	{
	}
	void Dimension_Pierce_BulletEffect::OnCollisionExit(Collider2D* other)
	{
	}


	void Dimension_Pierce_BulletEffect::Compelete_Pierce()
	{
		_SwitchOff = true;
		this->SetState(eState::Paused);
	}
}