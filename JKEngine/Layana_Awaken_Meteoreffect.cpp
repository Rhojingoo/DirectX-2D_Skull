#include "Layana_Awaken_Meteoreffect.h"


namespace jk
{
	int Layana_Awaken_Meteoreffect::mDir = 1;

	Layana_Awaken_Meteoreffect::Layana_Awaken_Meteoreffect()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Layana_Awaken_Meteoreffect::~Layana_Awaken_Meteoreffect()
	{
	}
	void Layana_Awaken_Meteoreffect::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Effect\\Dark_GoldenMeteor_Impact", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Effect\\Dark_GoldenMeteor_Impact", this, 1);

		at->CompleteEvent(L"EffectDark_GoldenMeteor_Impact") = std::bind(&Layana_Awaken_Meteoreffect::Compelete, this);
		at->CompleteEvent(L"EffectDark_GoldenMeteor_ImpactR") = std::bind(&Layana_Awaken_Meteoreffect::Compelete, this);

		at->PlayAnimation(L"EffectDark_GoldenMeteor_Impact", true);
		GameObject::Initialize();
	}
	void Layana_Awaken_Meteoreffect::Update()
	{
		if (_SwitchOn == true)
		{
			if (mDir == 1)
				at->PlayAnimation(L"EffectDark_GoldenMeteor_Impact", true);
			else
				at->PlayAnimation(L"EffectDark_GoldenMeteor_ImpactRR", true);
			_SwitchOn = false;
		}
		GameObject::Update();
	}
	void Layana_Awaken_Meteoreffect::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Layana_Awaken_Meteoreffect::Render()
	{
		GameObject::Render();
	}
	void Layana_Awaken_Meteoreffect::OnCollisionEnter(Collider2D* other)
	{
	}
	void Layana_Awaken_Meteoreffect::OnCollisionStay(Collider2D* other)
	{
	}
	void Layana_Awaken_Meteoreffect::OnCollisionExit(Collider2D* other)
	{
	}
	void Layana_Awaken_Meteoreffect::Compelete()
	{	
		//_SwitchOff = true;
		this->SetState(eState::Paused);
	}
}
