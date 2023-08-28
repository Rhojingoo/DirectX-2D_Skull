#include "Layana_Awaken_GoldenMeteor_Effect.h"

namespace jk
{
	int Layana_Awaken_GoldenMeteor_Effect::mDir = 1;

	Layana_Awaken_GoldenMeteor_Effect::Layana_Awaken_GoldenMeteor_Effect()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Layana_Awaken_GoldenMeteor_Effect::~Layana_Awaken_GoldenMeteor_Effect()
	{
	}
	void Layana_Awaken_GoldenMeteor_Effect::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Effect\\Dark_GoldenMeteor_Effect", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Effect\\Dark_GoldenMeteor_Effect", this, 1);

		at->CompleteEvent(L"EffectDark_GoldenMeteor_Effect") = std::bind(&Layana_Awaken_GoldenMeteor_Effect::Compelete, this);
		at->CompleteEvent(L"EffectDark_GoldenMeteor_EffectR") = std::bind(&Layana_Awaken_GoldenMeteor_Effect::Compelete, this);

		at->PlayAnimation(L"EffectDark_GoldenMeteor_Effect", true);
		GameObject::Initialize();
	}
	void Layana_Awaken_GoldenMeteor_Effect::Update()
	{
		if (_SwitchOn == true)
		{
			if (mDir == 1)
				at->PlayAnimation(L"EffectDark_GoldenMeteor_Effect", true);
			else
				at->PlayAnimation(L"EffectDark_GoldenMeteor_EffectR", true);
			_SwitchOn = false;
		}
		GameObject::Update();
	}
	void Layana_Awaken_GoldenMeteor_Effect::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Layana_Awaken_GoldenMeteor_Effect::Render()
	{
		GameObject::Render();
	}
	void Layana_Awaken_GoldenMeteor_Effect::OnCollisionEnter(Collider2D* other)
	{
	}
	void Layana_Awaken_GoldenMeteor_Effect::OnCollisionStay(Collider2D* other)
	{
	}
	void Layana_Awaken_GoldenMeteor_Effect::OnCollisionExit(Collider2D* other)
	{
	}
	void Layana_Awaken_GoldenMeteor_Effect::Compelete()
	{
		this->SetState(eState::Paused);
	}
}