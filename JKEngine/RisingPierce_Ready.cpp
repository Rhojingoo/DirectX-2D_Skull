#include "RisingPierce_Ready.h"


namespace jk
{
	RisingPierce_Ready::RisingPierce_Ready()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	RisingPierce_Ready::~RisingPierce_Ready()
	{
	}
	void RisingPierce_Ready::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Effect\\RisingPierce_Ready", this, 0, 0.05);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Effect\\RisingPierce_Ready", this, 1, 0.05);
		at->CompleteEvent(L"EffectRisingPierce_Ready") = std::bind(&RisingPierce_Ready::Compelete_Pierce, this);
		at->CompleteEvent(L"EffectRisingPierce_ReadyR") = std::bind(&RisingPierce_Ready::Compelete_Pierce, this);

		at->PlayAnimation(L"EffectRisingPierce_Ready", true);
		GameObject::Initialize();
	}
	void RisingPierce_Ready::Update()
	{
		if (_SwitchOn == true)
		{
			if (mDir == 1)
				at->PlayAnimation(L"EffectRisingPierce_Ready", true);
			else
				at->PlayAnimation(L"EffectRisingPierce_ReadyR", true);
			_SwitchOn = false;
		}
		GameObject::Update();
	}
	void RisingPierce_Ready::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void RisingPierce_Ready::Render()
	{
		GameObject::Render();
	}
	void RisingPierce_Ready::OnCollisionEnter(Collider2D* other)
	{
	}
	void RisingPierce_Ready::OnCollisionStay(Collider2D* other)
	{
	}
	void RisingPierce_Ready::OnCollisionExit(Collider2D* other)
	{
	}

	void RisingPierce_Ready::Compelete_Pierce()
	{
		this->SetState(eState::Paused);
	}
}