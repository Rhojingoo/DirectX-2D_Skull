#include "Layana_Awken_Rush_Sign.h"


namespace jk
{
	int Layana_Awken_Rush_Sign::mDir = 1;

	Layana_Awken_Rush_Sign::Layana_Awken_Rush_Sign()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Layana_Awken_Rush_Sign::~Layana_Awken_Rush_Sign()
	{
	}
	void Layana_Awken_Rush_Sign::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Effect\\Dark_DimensionRush_Sign", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Effect\\Dark_DimensionRush_Sign", this, 1);
		//at->CompleteEvent(L"EffectDark_DimensionRush_Sign") = std::bind(&Layana_Awken_Rush_Sign::Compelete_Pierce, this);
		//at->CompleteEvent(L"EffectDark_DimensionRush_SignR") = std::bind(&Layana_Awken_Rush_Sign::Compelete_Pierce, this);

		at->PlayAnimation(L"EffectDark_DimensionRush_Sign", false);
		GameObject::Initialize();
	}
	void Layana_Awken_Rush_Sign::Update()
	{
		if (_SwitchOn == true)
		{
			if (mDir == 1)
				at->PlayAnimation(L"EffectDark_DimensionRush_Sign", false);
			else
				at->PlayAnimation(L"EffectDark_DimensionRush_SignR", false);
			_SwitchOn = false;
		}
		GameObject::Update();
	}
	void Layana_Awken_Rush_Sign::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Layana_Awken_Rush_Sign::Render()
	{
		GameObject::Render();
	}
	void Layana_Awken_Rush_Sign::OnCollisionEnter(Collider2D* other)
	{
	}
	void Layana_Awken_Rush_Sign::OnCollisionStay(Collider2D* other)
	{
	}
	void Layana_Awken_Rush_Sign::OnCollisionExit(Collider2D* other)
	{
	}
	void Layana_Awken_Rush_Sign::Compelete_Pierce()
	{
		//_SwitchOff = true;
		//this->SetState(eState::Paused);
	}
}