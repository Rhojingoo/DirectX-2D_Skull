#include "Dark_DimensionPierce_Sign.h"
#include "Include_Common.h"

namespace jk
{
	int Dark_DimensionPierce_Sign::mDir = 1;

	Dark_DimensionPierce_Sign::Dark_DimensionPierce_Sign()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Dark_DimensionPierce_Sign::~Dark_DimensionPierce_Sign()
	{
	}
	void Dark_DimensionPierce_Sign::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();

		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Effect\\Dark_DimensionPierce_SignS", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Effect\\Dark_DimensionPierce_SignS", this, 1);

		at->CompleteEvent(L"EffectDark_DimensionPierce_SignS") = std::bind(&Dark_DimensionPierce_Sign::Compelete, this);
		at->CompleteEvent(L"EffectDark_DimensionPierce_SignSR") = std::bind(&Dark_DimensionPierce_Sign::Compelete, this);

		at->PlayAnimation(L"EffectDark_DimensionPierce_SignS", true);


		GameObject::Initialize();
	}
	void Dark_DimensionPierce_Sign::Update()
	{
		if (_SwitchOn == true)
		{
			if (mDir == 1)
				at->PlayAnimation(L"EffectDark_DimensionPierce_SignS", true);
			else
				at->PlayAnimation(L"EffectDark_DimensionPierce_SignSR", true);
			_SwitchOn = false;
		}
		GameObject::Update();
	}
	void Dark_DimensionPierce_Sign::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Dark_DimensionPierce_Sign::Render()
	{
		GameObject::Render();
	}
	void Dark_DimensionPierce_Sign::OnCollisionEnter(Collider2D* other)
	{
	}
	void Dark_DimensionPierce_Sign::OnCollisionStay(Collider2D* other)
	{
	}
	void Dark_DimensionPierce_Sign::OnCollisionExit(Collider2D* other)
	{
	}
	void Dark_DimensionPierce_Sign::Compelete()
	{
		_SwitchOff = true;
		this->SetState(eState::Paused);
	}
}