#include "TwinMeteor_Boss.h"

namespace jk
{
	int TwinMeteor_Boss::mDir = 1;
	bool TwinMeteor_Boss::_SwitchOn = false;
	bool TwinMeteor_Boss::_SwitchOff = false;
	TwinMeteor_Boss::TwinMeteor_Boss()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	TwinMeteor_Boss::~TwinMeteor_Boss()
	{
	}
	void TwinMeteor_Boss::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Effect\\TwinMeteor_Boss", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Effect\\TwinMeteor_Boss", this, 1);
		//at->CompleteEvent(L"EffectTwinMeteor_Boss") = std::bind(&TwinMeteor_Boss::Compelete_Pierce, this);
		//at->CompleteEvent(L"EffectTwinMeteor_BossR") = std::bind(&TwinMeteor_Boss::Compelete_Pierce, this);
		
		at->PlayAnimation(L"EffectTwinMeteor_Boss", false);
		GameObject::Initialize();
	}
	void TwinMeteor_Boss::Update()
	{
		if (_SwitchOn == true)
		{
			//if (mDir == 1)
			//	at->PlayAnimation(L"EffectTwinMeteor_Boss", true);
			//else
			//	at->PlayAnimation(L"EffectTwinMeteor_BossR", true);
			_SwitchOn = false;
		}
		GameObject::Update();
	}
	void TwinMeteor_Boss::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void TwinMeteor_Boss::Render()
	{
		GameObject::Render();
	}
	void TwinMeteor_Boss::OnCollisionEnter(Collider2D* other)
	{
	}
	void TwinMeteor_Boss::OnCollisionStay(Collider2D* other)
	{
	}
	void TwinMeteor_Boss::OnCollisionExit(Collider2D* other)
	{
	}
	void TwinMeteor_Boss::Compelete_Pierce()
	{
		_SwitchOff = true;
		this->SetState(eState::Paused);
	}
}