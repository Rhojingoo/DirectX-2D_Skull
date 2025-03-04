#include "Layana_Awaken_Meteor_Electric.h"
#include "Include_Common.h"


namespace jk
{
	int Layana_Awaken_Meteor_Electric::_Dir = 1;

	Layana_Awaken_Meteor_Electric::Layana_Awaken_Meteor_Electric()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Layana_Awaken_Meteor_Electric::~Layana_Awaken_Meteor_Electric()
	{
	}
	void Layana_Awaken_Meteor_Electric::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Effect\\Dark_GoldenMeteor_Effect", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Effect\\Dark_GoldenMeteor_Effect", this, 1);

		at->CompleteEvent(L"EffectDark_GoldenMeteor_Effect") = std::bind(&Layana_Awaken_Meteor_Electric::Compelete, this);
		at->CompleteEvent(L"EffectDark_GoldenMeteor_EffectR") = std::bind(&Layana_Awaken_Meteor_Electric::Compelete, this);

		at->PlayAnimation(L"EffectDark_GoldenMeteor_Effect", true);
		GameObject::Initialize();
	}
	void Layana_Awaken_Meteor_Electric::Update()
	{
		if (_SwitchOn == true)
		{
			if (_Dir == 1)
				at->PlayAnimation(L"EffectDark_GoldenMeteor_Effect", true);
			else
				at->PlayAnimation(L"EffectDark_GoldenMeteor_EffectR", true);
			_SwitchOn = false;
		}
		GameObject::Update();
	}
	void Layana_Awaken_Meteor_Electric::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Layana_Awaken_Meteor_Electric::Render()
	{
		GameObject::Render();
	}
	void Layana_Awaken_Meteor_Electric::OnCollisionEnter(Collider2D* other)
	{
	}
	void Layana_Awaken_Meteor_Electric::OnCollisionStay(Collider2D* other)
	{
	}
	void Layana_Awaken_Meteor_Electric::OnCollisionExit(Collider2D* other)
	{
	}
	void Layana_Awaken_Meteor_Electric::Compelete()
	{
		this->SetState(eState::Paused);
	}
}