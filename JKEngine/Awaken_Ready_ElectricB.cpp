#include "Awaken_Ready_ElectricB.h"
#include "Include_Common.h"


namespace jk
{
	Awaken_Ready_ElectricB::Awaken_Ready_ElectricB()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Awaken_Ready_ElectricB::~Awaken_Ready_ElectricB()
	{
	}
	void Awaken_Ready_ElectricB::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Change_Effect\\Awaken_Ready_ElectricB", this, 0, 0.075f);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Change_Effect\\Awaken_Ready_ElectricB", this, 1, 0.075f);
		at->CompleteEvent(L"Change_EffectAwaken_Ready_ElectricB") = std::bind(&Awaken_Ready_ElectricB::Compelete_Pierce, this);
		at->CompleteEvent(L"Change_EffectAwaken_Ready_ElectricBR") = std::bind(&Awaken_Ready_ElectricB::Compelete_Pierce, this);

		at->PlayAnimation(L"Change_EffectAwaken_Ready_ElectricB", true);
		GameObject::Initialize();
	}
	void Awaken_Ready_ElectricB::Update()
	{
		if (_SwitchOn == true)
		{
			if (_Dir == 1)
				at->PlayAnimation(L"Change_EffectAwaken_Ready_ElectricB", true);
			else
				at->PlayAnimation(L"Change_EffectAwaken_Ready_ElectricBR", true);
			_SwitchOn = false;
		}
		GameObject::Update();
	}
	void Awaken_Ready_ElectricB::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Awaken_Ready_ElectricB::Render()
	{
		GameObject::Render();
	}
	void Awaken_Ready_ElectricB::OnCollisionEnter(Collider2D* other)
	{
	}
	void Awaken_Ready_ElectricB::OnCollisionStay(Collider2D* other)
	{
	}
	void Awaken_Ready_ElectricB::OnCollisionExit(Collider2D* other)
	{
	}
	void Awaken_Ready_ElectricB::Compelete_Pierce()
	{
		this->SetState(eState::Paused);
	}
}