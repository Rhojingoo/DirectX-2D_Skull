#include "Layana_Awake_Ground_DashSmoke.h"


namespace jk
{
	int Layana_Awake_Ground_DashSmoke::mDir = 1;

	Layana_Awake_Ground_DashSmoke::Layana_Awake_Ground_DashSmoke()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Layana_Awake_Ground_DashSmoke::~Layana_Awake_Ground_DashSmoke()
	{
	}
	void Layana_Awake_Ground_DashSmoke::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();

		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Effect\\Dark_Ground_DashSmoke", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Effect\\Dark_Ground_DashSmoke", this, 1);
		at->CompleteEvent(L"EffectDark_Ground_DashSmoke") = std::bind(&Layana_Awake_Ground_DashSmoke::Compelete, this);
		at->CompleteEvent(L"EffectDark_Ground_DashSmokeR") = std::bind(&Layana_Awake_Ground_DashSmoke::Compelete, this);

		at->PlayAnimation(L"EffectDark_Ground_DashSmokeR", true);


		GameObject::Initialize();
	}
	void Layana_Awake_Ground_DashSmoke::Update()
	{
		if (_SwitchOn == true)
		{
			if (mDir == 1)
				at->PlayAnimation(L"EffectDark_Ground_DashSmoke", true);
			else
				at->PlayAnimation(L"EffectDark_Ground_DashSmokeR", true);
			_SwitchOn = false;
		}
		GameObject::Update();
	}
	void Layana_Awake_Ground_DashSmoke::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Layana_Awake_Ground_DashSmoke::Render()
	{
		GameObject::Render();
	}
	void Layana_Awake_Ground_DashSmoke::OnCollisionEnter(Collider2D* other)
	{
	}
	void Layana_Awake_Ground_DashSmoke::OnCollisionStay(Collider2D* other)
	{
	}
	void Layana_Awake_Ground_DashSmoke::OnCollisionExit(Collider2D* other)
	{
	}
	void Layana_Awake_Ground_DashSmoke::Compelete()
	{
		_SwitchOff = true;
		this->SetState(eState::Paused);
	}
}