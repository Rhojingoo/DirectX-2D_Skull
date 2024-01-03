#include "Layana_Awaken_Ground_Thunder_Sign.h"
#include "Include_Common.h"


namespace jk
{
	int Layana_Awaken_Ground_Thunder_Sign::_Dir = 1;

	Layana_Awaken_Ground_Thunder_Sign::Layana_Awaken_Ground_Thunder_Sign()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Layana_Awaken_Ground_Thunder_Sign::~Layana_Awaken_Ground_Thunder_Sign()
	{
	}
	void Layana_Awaken_Ground_Thunder_Sign::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Effect\\Dark_Ground_Thunder_Sign", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Effect\\Dark_Ground_Thunder_Sign", this, 1);
		at->CompleteEvent(L"EffectDark_Ground_Thunder_Sign") = std::bind(&Layana_Awaken_Ground_Thunder_Sign::Compelete, this);
		at->CompleteEvent(L"EffectDark_Ground_Thunder_SignR") = std::bind(&Layana_Awaken_Ground_Thunder_Sign::Compelete, this);

		at->PlayAnimation(L"EffectDark_Ground_Thunder_Sign", true);
		GameObject::Initialize();
	}
	void Layana_Awaken_Ground_Thunder_Sign::Update()
	{
		if (_SwitchOn == true)
		{
			if (_Dir == 1)
				at->PlayAnimation(L"EffectDark_Ground_Thunder_Sign", true);
			else
				at->PlayAnimation(L"EffectDark_Ground_Thunder_SignR", true);
			_SwitchOn = false;
		}
		GameObject::Update();
	}
	void Layana_Awaken_Ground_Thunder_Sign::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Layana_Awaken_Ground_Thunder_Sign::Render()
	{
		GameObject::Render();
	}
	void Layana_Awaken_Ground_Thunder_Sign::OnCollisionEnter(Collider2D* other)
	{
	}
	void Layana_Awaken_Ground_Thunder_Sign::OnCollisionStay(Collider2D* other)
	{
	}
	void Layana_Awaken_Ground_Thunder_Sign::OnCollisionExit(Collider2D* other)
	{
	}
	void Layana_Awaken_Ground_Thunder_Sign::Compelete()
	{
		_SwitchOff = true;
		this->SetState(eState::Paused);
	}
}