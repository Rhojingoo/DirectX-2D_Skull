#include "Awaken_Ready_ElectricA.h"
#include "Include_Common.h"

namespace jk
{
	Awaken_Ready_ElectricA::Awaken_Ready_ElectricA()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Awaken_Ready_ElectricA::~Awaken_Ready_ElectricA()
	{
	}
	void Awaken_Ready_ElectricA::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Change_Effect\\Awaken_Ready_ElectricA", this, 0, 0.075f);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Change_Effect\\Awaken_Ready_ElectricA", this, 1, 0.075f);
		at->CompleteEvent(L"Change_EffectAwaken_Ready_ElectricA") = std::bind(&Awaken_Ready_ElectricA::Compelete_Pierce, this);
		at->CompleteEvent(L"Change_EffectAwaken_Ready_ElectricAR") = std::bind(&Awaken_Ready_ElectricA::Compelete_Pierce, this);

		at->PlayAnimation(L"Change_EffectAwaken_Ready_ElectricA", true);
		GameObject::Initialize();
	}
	void Awaken_Ready_ElectricA::Update()
	{
		if (_SwitchOn == true)
		{
			if (_Dir == 1)
				at->PlayAnimation(L"Change_EffectAwaken_Ready_ElectricA", true);
			else
				at->PlayAnimation(L"Change_EffectAwaken_Ready_ElectricA", true);
			_SwitchOn = false;
		}
		GameObject::Update();
	}
	void Awaken_Ready_ElectricA::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Awaken_Ready_ElectricA::Render()
	{
		GameObject::Render();
	}
	void Awaken_Ready_ElectricA::OnCollisionEnter(Collider2D* other)
	{
	}
	void Awaken_Ready_ElectricA::OnCollisionStay(Collider2D* other)
	{
	}
	void Awaken_Ready_ElectricA::OnCollisionExit(Collider2D* other)
	{
	}
	void Awaken_Ready_ElectricA::Compelete_Pierce()
	{
		this->SetState(eState::Paused);
	}
}