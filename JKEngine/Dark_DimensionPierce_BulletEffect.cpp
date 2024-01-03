#include "Dark_DimensionPierce_BulletEffect.h"
#include "Include_Common.h"

namespace jk
{
	int	Dark_DimensionPierce_BulletEffect::mDir = 1;
	bool Dark_DimensionPierce_BulletEffect::_effect_switch = false;
	bool Dark_DimensionPierce_BulletEffect::_bulletoff = false;

	Dark_DimensionPierce_BulletEffect::Dark_DimensionPierce_BulletEffect()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Dark_DimensionPierce_BulletEffect::~Dark_DimensionPierce_BulletEffect()
	{
	}
	void Dark_DimensionPierce_BulletEffect::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Bullet\\Dark_DimensionPierce_BulletEffect", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Bullet\\Dark_DimensionPierce_BulletEffect", this, 1);


		at->CompleteEvent(L"BulletDark_DimensionPierce_BulletEffect") = std::bind(&Dark_DimensionPierce_BulletEffect::Compelete_Pierce, this);
		at->CompleteEvent(L"BulletDark_DimensionPierce_BulletEffectR") = std::bind(&Dark_DimensionPierce_BulletEffect::Compelete_Pierce, this);

		at->PlayAnimation(L"BulletDark_DimensionPierce_BulletEffect", true);
		GameObject::Initialize();
	}
	void Dark_DimensionPierce_BulletEffect::Update()
	{
		if (_effect_switch == true)
		{
			if (mDir == 1)
				at->PlayAnimation(L"BulletDark_DimensionPierce_BulletEffect", true);
			else
				at->PlayAnimation(L"BulletDark_DimensionPierce_BulletEffectR", true);
			_effect_switch = false;
		}

		GameObject::Update();
	}
	void Dark_DimensionPierce_BulletEffect::LateUpdate()
	{
		_collider->SetSize(Vector2(0.95f, 0.25f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Dark_DimensionPierce_BulletEffect::Render()
	{
		GameObject::Render();
	}
	void Dark_DimensionPierce_BulletEffect::OnCollisionEnter(Collider2D* other)
	{
	}
	void Dark_DimensionPierce_BulletEffect::OnCollisionStay(Collider2D* other)
	{
	}
	void Dark_DimensionPierce_BulletEffect::OnCollisionExit(Collider2D* other)
	{
	}
	void Dark_DimensionPierce_BulletEffect::Compelete_Pierce()
	{
		this->SetState(eState::Paused);
	}
}