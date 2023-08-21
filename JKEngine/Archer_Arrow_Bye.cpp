#include "Archer_Arrow_Bye.h"

namespace jk
{
	Archer_Arrow_Bye::Archer_Arrow_Bye()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Archer_Arrow_Bye::~Archer_Arrow_Bye()
	{
	}
	void Archer_Arrow_Bye::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Effect\\Bye\\END", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Effect\\Bye\\BASIC", this);

		at->CompleteEvent(L"ByeEND") = std::bind(&Archer_Arrow_Bye::Compelete, this);
		at->PlayAnimation(L"ByeBASIC", false);

		GameObject::Initialize();
	}
	void Archer_Arrow_Bye::Update()
	{		
		if (_effect_On == true)
		{
			_Lifetime += Time::DeltaTime();
			if (_Lifetime >= 7)
			{
				at->PlayAnimation(L"ByeEND", true);				
				_effect_On = false;
				_Lifetime = 0;
			}
		}		
		GameObject::Update();
	}
	void Archer_Arrow_Bye::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Archer_Arrow_Bye::Render()
	{
		GameObject::Render();
	}
	void Archer_Arrow_Bye::OnCollisionEnter(Collider2D* other)
	{
	}
	void Archer_Arrow_Bye::OnCollisionStay(Collider2D* other)
	{
	}
	void Archer_Arrow_Bye::OnCollisionExit(Collider2D* other)
	{
	}
	void Archer_Arrow_Bye::Compelete()
	{
		this->SetState(eState::Paused);
		_Lifetime = 0;
		_effect_On = false;
		at->PlayAnimation(L"ByeBASIC", false);
	}
}